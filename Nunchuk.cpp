// This is an alternative Nunchuk Arduino library which adds additional functions to 
// return joystick coordinates as percentages.
//
// Tested with Arduino Uno R3 standalone and with Arduino Uno R3 and Gameduino shield.
// 
//  Written by Mike H Huffaker
//  Distributed under the BSD license, please read license.txt for more information.

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#include <Wire.h>
#include "Nunchuk.h"

void Nunchuk::initialize()
{
    // Calculate an percentage/value table for both x and y and load it
    // Calculating up front like this will put the load of calculations
    // at the beginning of the library initialization, so the calculations
    // don't slow down the library once its polling for updates.
    calculatePercentages();

    Wire.begin();
    Wire.beginTransmission(NUNCHUK_DEVICE_ID);
    Wire.write(0100);
    Wire.write(00);
    Wire.endTransmission();
    read();
}

bool Nunchuk::read()
{
    delayMicroseconds(NUNCHUK_READ_DELAY);
    Wire.requestFrom(NUNCHUK_DEVICE_ID, NUNCHUK_BUFFER_SIZE);
    int byte_counter = 0;
    while ( Wire.available() && byte_counter < NUNCHUK_BUFFER_SIZE )
        read_buffer[byte_counter++] = decodeByte( Wire.read() );
    requestData();
    return byte_counter == NUNCHUK_BUFFER_SIZE;
}

void Nunchuk::calculatePercentages()
{
    // Calculate the "real" x and y values by subtracting
    // the min x/y the joystick can report from the max
    // x/y.  Then multiply by the percentage to get a value
    // that will probably be "accurate enough" for game play.
    int x;
    int p;
    double nunchuk_real_x_max = NUNCHUK_X_MAX - NUNCHUK_X_MIN;
    for ( x = 0, p = 0; x < 101; x = x + 5, p++ )
    {
        x_pct_pct[p] = x;
        if ( x == 0 )
            x_pct_val[p] = NUNCHUK_X_MIN;
        else if ( x == 100 )
            x_pct_val[p] = NUNCHUK_X_MAX;
        else
            x_pct_val[p] = NUNCHUK_X_MIN + lround(( nunchuk_real_x_max * ( x_pct_pct[p] * .01) ));
    }
    x_pct_array_size = p;
  
    int y;
    double nunchuk_real_y_max = NUNCHUK_Y_MAX - NUNCHUK_Y_MIN;
    for ( y = 0, p = 0; y < 101; y = y + 5, p++ )
    {
        y_pct_pct[p] = y;
        if ( y == 0 )
            y_pct_val[p] = NUNCHUK_Y_MIN;
        else if ( x == 100 )
            y_pct_val[p] = NUNCHUK_Y_MAX;
        else
            y_pct_val[p] = NUNCHUK_Y_MIN + lround(( nunchuk_real_y_max * ( y_pct_pct[p] * .01) ));
    }
    y_pct_array_size = p;
    
}
    
// Return percentage 0 = full left, 50 being the center, and
// 100 being full right
const int Nunchuk::getXPct()
{
    for ( int p = 0; p < x_pct_array_size; p++ )
    {
        if ( read_buffer[0] >= x_pct_val[p] && read_buffer[0] < x_pct_val[p+1] )
            return x_pct_pct[p];   
    }
    
    return x_pct_pct[x_pct_array_size-1];
}
// Return percentage 0 = downfull left, 50 being the center, and
// 100 being full right
const int Nunchuk::getYPct()
{
    for ( int p = 0; p < y_pct_array_size; p++ )
    {
        if ( read_buffer[1] >= y_pct_val[p] && read_buffer[1] < y_pct_val[p+1] )
            return y_pct_pct[p]; 
    }
    
    return y_pct_pct[y_pct_array_size-1];
}

// For debugging - return the Coord value directly from the table for the pct passed in
const int Nunchuk::getXPctCoordVal( int x )
{
    for ( int p = 0; p < x_pct_array_size; p++ )
    {
        if ( x_pct_pct[p] == x )
            return x_pct_val[p]; 
    }

    return 0;
}

// For debugging - return the Coord value directly from the table for the pct passed in
const int Nunchuk::getYPctCoordVal( int y )
{
    for ( int p = 0; p < y_pct_array_size; p++ )
    {
        if ( y_pct_pct[p] == y )
            return y_pct_val[p]; 
    }

    return 0;
}

void Nunchuk::requestData() 
{
    Wire.beginTransmission( NUNCHUK_DEVICE_ID );
    Wire.write(00);
    Wire.endTransmission();
}

char Nunchuk::decodeByte( const char b )
{
    return ( b ^ 027 ) + 027;
}
