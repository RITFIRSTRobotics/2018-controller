/**
 * src/Pins.h
 *
 * Pinout for the controller 
 *
 * @author Connor Henley, @thatging3rkid
 */
#ifndef _i2c_controller_pins
#define _i2c_controller_pins

#include <Arduino.h>

/*
 * Define the data pins
 */
// Buttons
#define BUTTON0 0
#define BUTTON1 0
#define BUTTON2 0
#define BUTTON3 0

// Joysticks
#define JOY0_X A0
#define JOY0_Y A0
#define JOY1_X A0
#define JOY1_Y A0

// Addressing pins (if implemented) 
#define ADDR0_PIN 0
#define ADDR1_PIN 0

/*
 * Define the initialization mode
 */
#define BUTTONS_MODE INPUT
#define JOYS_MODE INPUT

// See if addressing pins have been implemented
#if defined(ADDR0_PIN) && defined(ADDR1_PIN)
#define ADDR_PIN_MODE INPUT
#endif

/*
 * Define any pin negation
 */
#define BUTTON0_NEGATED false
#define BUTTON1_NEGATED false
#define BUTTON2_NEGATED false
#define BUTTON3_NEGATED false

#endif