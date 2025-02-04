## Arduino_nunchuck

A library to read a Wii Nunchuk joystick connected to an Ardunino Uno Board
using the TWI protocol and the Wire library for the Arduino.

## Intro

The main reason I coded this library was so I could use a Wii Nunchuk
to play and also develop games for a Arduino with an attached Gameduino
using a Nunchuck as the controller, instead of a simple 8 way joystick. 

There are other libraries that do this, but I found that most just returned
raw coordinates from the Nunchuk, which then have to be understood by the game
code.

So I wrote this library that has functionallity to return the coordinate X/Y
values as percentages, instead of raw values to help the programmer using the
library to get a read of the joystick position without actually having to
code for the exact coordinate values. 

## Usage

It should be noted that this library has only been tested with 2 actual
Wii Nunchuks from Nintendo connected via a Nunchucky breakout board.
I have not tried to test with any other 3rd party Nunchuk controllers.

## Credits

To give credit where credit is due, I did research and looked at code
from the following resources to help me code this library:

* Wii Nunchuk data logger at: http://www.windmeadow.com/node/54
* WiiChuckClass by Tim Hirzel at: http://playground.arduino.cc/Main/WiiChuckClass
* Chapter 7 in The Pragmatic Programmer by Maik Schmidt

