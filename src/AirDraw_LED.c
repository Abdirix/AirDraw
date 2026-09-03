/*
 * File:   AirDraw_LED.c
 */


#include "AirDraw_LED.h"

uint8_t pixelBuffer[64][3];

void send_pixel_byte(uint8_t b) {
    int i;
    for(i = 7; i >= 0; i--) {
        if((b >> i) & 1) {
            asm volatile ("bset LATA, #0 \n\t repeat #11 \n\t nop \n\t bclr LATA, #0 \n\t repeat #8 \n\t nop");
        } else {
            asm volatile ("bset LATA, #0 \n\t repeat #4 \n\t nop \n\t bclr LATA, #0 \n\t repeat #14 \n\t nop");
        }
    }
}

void update_matrix(int curX, int curY) {
    int i;
    NEO_PIN = 0;
    // Manual 50us reset pulse
    for(i = 0; i < 1200; i++) { asm volatile ("nop"); } 
    
    for(i = 0; i < 64; i++) {
        if(i == (curY * 8) + curX) {
            // Cursor (White)
            send_pixel_byte(1);
            send_pixel_byte(2);
            send_pixel_byte(1);
        } else {
            // Buffer Data (GRB Order)
            send_pixel_byte(pixelBuffer[i][1]);
            send_pixel_byte(pixelBuffer[i][0]);
            send_pixel_byte(pixelBuffer[i][2]);
        }
    }
}
