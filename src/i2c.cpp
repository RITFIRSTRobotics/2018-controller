/**
 * src/i2c.cpp
 *
 * Handles data reading and i2c transmission
 *
 * @author Connor Henley, @thatging3rkid
 */

#define ADDRESS 0 // this should be set with hardware jumpers?

#include "Pins.h"
#include "i2c.hpp"
#include "i2c_constants.hpp"

#include <Wire.h>
#include <stdio.h>

static void __respond(); 

/**
 * @inherit-doc
 */
void init_i2c() {
	// Initialize i2c with an address
#ifdef ADDRESS
	Wire.begin(BASE_ADDR + ADDRESS);
#else
	// Maybe on a rev2 PCB, there should be hardware jumpers mapped to the microprocessor,
	// so that addresses can be swapped without recompiling
	pinMode(ADDR0_PIN, INPUT);
	pinMode(ADDR1_PIN, INPUT);

	if (digitalRead(ADDR0_PIN) && digitalRead(ADDR1_PIN)) {
		Wire.begin(ADDR2);
	} else if (digitalRead(ADDR1_PIN)) {
		Wire.begin(ADDR1);
	} else if (digitalRead(ADDR0_PIN)) {
		Wire.begin(ADDR0);
	}
#endif

	// Setup the response to a data request
	Wire.onRequest(__respond);
}

/**
 * A private method to responsd to an i2c data read
 */
static void __respond() {
	char buffer[I2CDATA_BUFFER_LEN];
	sprintf(buffer, I2CDATA_FORMAT_STRING, analogRead(JOY0_X) / 4, analogRead(JOY0_Y) / 4, analogRead(JOY1_X) / 4,
		analogRead(JOY1_Y) / 4, digitalRead(BUTTON0), digitalRead(BUTTON1), digitalRead(BUTTON2), 
		digitalRead(BUTTON3));
	Wire.write(buffer);
}
