/* 
 * File:   AirDraw_LED.h
 */

#ifndef AIRDRAW_LED_H
#define	AIRDRAW_LED_H
#include "AirDraw_Config.h"

#ifdef	__cplusplus
extern "C" {
#endif
    //Purpose: Memory array to store the RGB color values for all 64 LEDs on the matrix.
    extern uint8_t pixelBuffer[64][3];

    //Purpose: Uses assembly function that bit-bangs exactly eight bits of color data to the LEDs using precise timing.
    void send_pixel_byte(uint8_t b);
    void update_matrix(int curX, int curY);
    




#ifdef	__cplusplus
}
#endif

#endif	/* AIRDRAW_LED_H */

