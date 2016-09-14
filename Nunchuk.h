// This is an alternative Nunchuk Arduino library which adds additional functions to 
// return joystick coordinates as percentages.
//
// Tested with Arduino Uno R3 standalone and with Arduino Uno R3 and Gameduino shield.
// 
//  Written by Mike H Huffaker
//  Distributed under the BSD license, please read license.txt for more information.

#ifndef _NUNCHUK_H_
#define _NUNCHUK_H_

#define NUNCHUK_DEVICE_ID 0122
#define NUNCHUK_BUFFER_SIZE 6

// Delay in microseconds during Nunchuk.read() method.
#define NUNCHUK_READ_DELAY 100

// These are "guesses" based on testing, add calibration function in future version.
#define NUNCHUK_X_MIN 25
#define NUNCHUK_X_MAX 220

#define NUNCHUK_Y_MIN 29
#define NUNCHUK_Y_MAX 222

// Set to 21 for array of 5 percent value buckets
#define NUNCHUK_PCT_ARR_SZ 21

class Nunchuk
{

public:

    void initialize();
    bool read();

    // Stubbed in, will be added in future version to allow calling sketch to set the
    // min/max X and Y values to adjust for calibration.
    int setMinXCoord() const { return 0; }
    int setMaxXCoord() const { return 0; }
    int setMinYCoord() const { return 0; }
    int setMaxYCoord() const { return 0; }
	
    int getXCoord() const { return read_buffer[0]; }
    int getYCoord() const { return read_buffer[1]; }
    
    // Stubbed in, will be added in future version
    int getXAccel() const { return 0; }
    int getYAccel() const { return 0; }
    int getZAccel() const { return 0; }

    // Return calculated percentage for X and Y on the joystick.  Note that for X, 
    // 0 = max left and 100 = max right, while for Y, 0 = max down and 100 = max up.
    int const getXPct();
    int const getYPct();

    // For debugging, pulls the exact coordinate stored as a pct value
    int const getXPctCoordVal( int );
    int const getYPctCoordVal( int );
	
    // Return boolean indicating button pressed status
    bool getCPress() const { return !(read_buffer[5] & 02); }
    bool getZPress() const { return !(read_buffer[5] & 01); }
    
    
protected:

    void requestData();
    void calculatePercentages();
    char decodeByte( const char );
    unsigned char read_buffer[NUNCHUK_BUFFER_SIZE];
    
    int x_pct_pct[NUNCHUK_PCT_ARR_SZ];
    int x_pct_val[NUNCHUK_PCT_ARR_SZ];
    int x_pct_array_size;
    
    int y_pct_pct[NUNCHUK_PCT_ARR_SZ];
    int y_pct_val[NUNCHUK_PCT_ARR_SZ];
    int y_pct_array_size;
    
}
;

#endif
