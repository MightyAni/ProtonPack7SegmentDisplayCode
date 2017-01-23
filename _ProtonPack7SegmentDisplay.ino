
/***************************************************
This is a library for our I2C LED Backpacks

Designed specifically to work with the Adafruit LED 7-Segment backpacks
----> http://www.adafruit.com/products/881
----> http://www.adafruit.com/products/880
----> http://www.adafruit.com/products/879
----> http://www.adafruit.com/products/878

These displays use I2C to communicate, 2 pins are required to
interface. There are multiple selectable I2C addresses. For backpacks
with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
with 3 Address Select pins: 0x70 thru 0x77

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, a
ll text above must be included in any redistribution
****************************************************/

// Enable one of these two #includes and comment out the other.
// Conditional #include doesn't work due to Arduino IDE shenanigans.
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.
//#include <USI_TWI_Master.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

int counter;
int delayval;		//This is the delay in milliseconds between updates of the number displayed
int low = 1001;	//The bottom of the number range
int high = 9999;	//The top of the number range

int cInitial;		//start the ramp at this number (chosen randomly each loop)
int cFinal;		//end the ramp here (chosen randomly each loop)
int i;

void setup() {

// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
	// End of trinket special code

#ifndef __AVR_ATtiny85__
	Serial.begin(9600);
	//	Serial.println("7 Segment Backpack Test");
#endif
	matrix.begin(0x70);	//This is the address of the Adafruit 7 segment display

	cInitial = random(low, high);	//Pick an initial random number
}

void loop() {

	//Have the Uno pick 2 numbers, then ramp between them
	cFinal = random(low, high);		//Pick another random number

	delayval = random(125, 250);	//Delay randomly between 1/8 and 1/4 seconds

	if (cInitial < cFinal) {	//If the first random number is less than the second random number...
		for (i = cInitial; i < cFinal; i = i + 17) {	//Ramp up
			matrix.println(i);
			matrix.writeDisplay();
			delay(delayval);
		}
	}
	if (cInitial > cFinal) {	//If the 2nd random number is less than the 1st...
		for (i = cInitial; i > cFinal; i = i - 18) {	//Ramp down
			matrix.println(i);
			matrix.writeDisplay();
			delay(delayval);
		}
	}

	cInitial = cFinal;		//The 2nd number is now the first number on the next loop
}
