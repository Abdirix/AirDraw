/*
 * File:   AirDraw_Config.c
 */


#include "AirDraw_Config.h"
#include "AirDraw_IMU.h"

volatile unsigned long timeCounter = 0;



void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    timeCounter++;
    IFS0bits.T2IF = 0;
}



void init_hardware(void) {
    AD1PCFG = 0xFFF3;
    NEO_TRIS = 0;
    NEO_PIN = 0;
    _TRISA1 = 1;
    _TRISB0 = 1;
    _TRISB1 = 1;
    _CN3PUE = 1;
    CLKDIV = 0;
    AD1CON1 = 0x0000;
    AD1CON2 = 0x0000;
    AD1CON3 = 0x1003;
    AD1CHS = 0x0002;
    AD1CON1bits.ADON = 1;

    // Timer2: 1:256 prescaler, ~1s overflow
    T2CON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0b11; // 1:256
    PR2 = 62500; // 1s period
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    T2CONbits.TON = 1;

    // IMU Initialization (Wakes sensor)
    MPU6050_init();
}
