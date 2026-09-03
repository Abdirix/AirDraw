/*
 * File:   AirDraw_Input.c
 */


#include "xc.h"
#include "AirDraw_Input.h"


static unsigned long press1 = 0;  // most recent press
static unsigned long press2 = 0;  // second most recent
static unsigned long press3 = 0;  // third most recent
static int prevState = 1;         // button idle = HIGH (active-low)

uint16_t read_adc(uint8_t channel) {
    AD1CHS = channel; AD1CON1bits.SAMP = 1;
    asm volatile ("repeat #30 \n\t nop");
    AD1CON1bits.SAMP = 0; while (!AD1CON1bits.DONE);
    return ADC1BUF0;
}

Action check_button_actions(void) {
    int curState = JOY_BTN;
    Action res = ACTION_NONE;

    // DETECT PRESS EVENT (falling edge)
    if (curState == 0 && prevState == 1) {
        // Shift timestamps: press3 <- press2 <- press1 <- now
        press3 = press2;
        press2 = press1;
        press1 = timeCounter;
    }

    // TRIPLE CLICK: all 3 presses within 1 tick (~1s)
    if (press1 > 0 && press2 > 0 && press3 > 0 && (press1 - press3) <= 1) {
        res = ACTION_TRIPLE;
        press1 = 0; press2 = 0; press3 = 0; // consume
    }
    // DOUBLE CLICK: 2 presses within 1 tick, no 3rd pending 
    else if (press1 > 0 && press2 > 0 && (press1 - press2) <= 1) {
        // Wait briefly to make sure a 3rd click isn't coming
        if (timeCounter - press1 >= 1) {
            res = ACTION_DOUBLE;
            press1 = 0; press2 = 0; press3 = 0; // consume
        }
    }

    // IDLE TIMEOUT: no press for 2+ ticks -> reset timestamps
    if (press1 > 0 && (timeCounter - press1) > 2) {
        press1 = 0; press2 = 0; press3 = 0;
    }

    prevState = curState;
    return res;
}
