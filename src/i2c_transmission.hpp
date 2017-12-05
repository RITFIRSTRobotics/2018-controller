/**
 * src/i2c_transmission.cpp
 *
 * Handles data reading and i2c transmission
 *
 * @author Connor Henley, @thatging3rkid
 */
#ifndef _i2c_controller_trans
#define _i2c_controller_trans

/**
 * Initialize i2c and data collection pins
 */
void init_i2c();

/**
 * Read data from the pins and write it out to i2c
 */
void write_i2c();

#endif