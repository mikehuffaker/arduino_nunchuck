
A library to read a Wii Nunchuk joystick connected to an Ardunino Uno Board
using the TWI protocol and the Wire library for the Arduino.  There 
are other libraries available, but I coded this library with some custom 
functionality to return coordinate X/Y values as percentages, instead of
raw values to help the programmer using the library to get a read of the 
joystick position without actually having to know the exact coordinate
values.

This is a work in progress and I may still change the code and improve it
more from time to time.

It should be noted that this library has only been tested with 2 actual
Wii Nunchuks from Nintendo connected via a Nunchucky breakout board.
I have not tried to test with any other 3rd party Nunchuk controllers.

To give credit where credit is due, I did research and looked at code
from the following resources to help me code this library:

Wii Nunchuk data logger at: http://www.windmeadow.com/node/54
WiiChuckClass by Tim Hirzel at: http://playground.arduino.cc/Main/WiiChuckClass
Chapter 7 in The Pragmatic Programmer by Maik Schmidt
