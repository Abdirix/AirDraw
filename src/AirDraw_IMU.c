/*
 * File:   AirDraw_IMU.c
 */


#include "AirDraw_IMU.h"

// IMU Filter
static float filterX = 0, filterY = 0;
const float ALPHA = 0.5f;

// I2C Methods
static void i2c_init(void) { 
    I2C1BRG = 37; 
    I2C1CONbits.I2CEN = 1; 
}

static void i2c_start(void) { 
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN); 
}

static void i2c_stop(void) { 
    I2C1CONbits.PEN = 1; 
    while(I2C1CONbits.PEN); 
}

static void i2c_restart(void) { 
    I2C1CONbits.RSEN = 1;
    while(I2C1CONbits.RSEN); 
}

static void i2c_write(uint8_t data) { 
    I2C1TRN = data; 
    while(I2C1STATbits.TRSTAT); 
}

static uint8_t i2c_read(int ack) {
    I2C1CONbits.RCEN = 1; while(I2C1CONbits.RCEN);
    uint8_t temp = I2C1RCV;
    I2C1CONbits.ACKDT = (ack) ? 0 : 1;
    I2C1CONbits.ACKEN = 1; 
    while(I2C1CONbits.ACKEN);
    return temp;
}

void MPU6050_init(void) {
    i2c_init();
    i2c_start(); 
    i2c_write(MPU_ADDR_W); 
    i2c_write(0x6B); //Register to access Power
    i2c_write(0x00); // Wakes IMU from sleep
    i2c_stop();
}

void get_air_coords(int *x, int *y) {
    i2c_start();
    i2c_write(MPU_ADDR_W);
    i2c_write(0x3B); //Reads data from IMU
    i2c_restart();
    i2c_write(MPU_ADDR_R);
    int16_t imuRawX = (i2c_read(1) << 8) | i2c_read(1);
    int16_t imuRawY = (i2c_read(1) << 8) | i2c_read(0);
    i2c_stop();

    // Filter Logic: ALPHA = 0.5f
    filterX = (imuRawX * ALPHA) + (filterX * (1.0f - ALPHA));
    filterY = (imuRawY * ALPHA) + (filterY * (1.0f - ALPHA));

    // Coordinate Mapping Logic
    *x = (int)((-filterX + 16000) / 4000); 
    *y = (int)((filterY + 16000) / 4000);

    // Bounds checking
    if(*x < 0) *x = 0; if(*x > 7) *x = 7;
    if(*y < 0) *y = 0; if(*y > 7) *y = 7;
}
