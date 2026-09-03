/* 
 * File:   AirDraw_Input.h
 */

#ifndef AIRDRAW_INPUT_H
#define	AIRDRAW_INPUT_H
#include "AirDraw_Config.h"

typedef enum { ACTION_NONE, ACTION_DOUBLE, ACTION_TRIPLE } Action;

#ifdef	__cplusplus
extern "C" {
#endif
    //Purpose: Reads and converts the physical voltage from a specific joystick axis into a digital number between 0 and 1023.
    uint16_t read_adc(uint8_t channel);

    //Purpose: Track how many times the button was pressed to signal a single, double, or triple clicks
    Action check_button_actions(void);




#ifdef	__cplusplus
}
#endif

#endif	/* AIRDRAW_INPUT_H */

