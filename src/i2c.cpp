/**
 * src/i2c.cpp
 *
 * Handles data reading and i2c transmission
 *
 * @author Connor Henley, @thatging3rkid
 */

#define ADDRESS 0 // this should be set with hardware jumpers?

#include "pins.h"
#include "i2c.hpp"
#include "i2c_constants.hpp"

#include <Wire.h>
#include <stdio.h>
#include <stdint.h>

static void __respond();

// Set the address offset, so that it can be sent to the ASC
#ifdef ADDRESS
static uint8_t _addr_offset = ADDRESS;
#else
static uint8_t _addr_offset = 0;
#endif

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
    _addr_offset = 2;
  } else if (digitalRead(ADDR1_PIN)) {
    Wire.begin(ADDR1);
    _addr_offset = 1;
  } else if (digitalRead(ADDR0_PIN)) {
    Wire.begin(ADDR0);
    _addr_offset = 0;
  }
#endif

  // Setup the response to a data request
  Wire.onRequest(__respond);

  // Initalize pins
  pinMode(BUTTON0, BUTTONS_MODE);
  pinMode(BUTTON1, BUTTONS_MODE);
  pinMode(BUTTON2, BUTTONS_MODE);
  pinMode(BUTTON3, BUTTONS_MODE);

  pinMode(JOY0_X, JOYS_MODE);
  pinMode(JOY0_Y, JOYS_MODE);
  pinMode(JOY1_X, JOYS_MODE);
  pinMode(JOY1_Y, JOYS_MODE);
}

/**
 * A private method to responsd to an i2c data read
 */
static void __respond() {
  char buffer[I2CDATA_BUFFER_LEN]; // make the buffer
  uint8_t buttons_rep = 0; // make a temp variable to store the buttons pressed

  // Read button, see if it needs to be negated then, eliminate every bit but the last, then shift into position
  buttons_rep += ((digitalRead(BUTTON0) != BUTTON0_NEGATED) & 0x01) << 0;
  buttons_rep += ((digitalRead(BUTTON1) != BUTTON1_NEGATED) & 0x01) << 1;
  buttons_rep += ((digitalRead(BUTTON2) != BUTTON2_NEGATED) & 0x01) << 2;
  buttons_rep += ((digitalRead(BUTTON3) != BUTTON3_NEGATED) & 0x01) << 3;
  
  sprintf(buffer, I2CDATA_FORMAT_STRING, _addr_offset, analogRead(JOY0_X) / 4, analogRead(JOY0_Y) / 4, analogRead(JOY1_X) / 4, analogRead(JOY1_Y) / 4, buttons_rep);
  Wire.write(buffer);
}

