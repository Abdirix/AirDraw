/* 
 * File:   AirDraw_Config.h
 */

#ifndef AIRDRAW_CONFIG_H
#define	AIRDRAW_CONFIG_H

#define FCY 16000000UL
#include <xc.h>
#include <stdint.h>

#pragma config JTAGEN = OFF, GCP = OFF, GWRP = OFF, FWDTEN = OFF, ICS = PGx1
#pragma config FNOSC = FRCPLL, FCKSM = CSDCMD, OSCIOFNC = OFF, IOL1WAY = OFF, I2C1SEL = PRI, POSCMOD = NONE

#define NEO_PIN      _LATA0
#define NEO_TRIS     _TRISA0
#define JOY_BTN      _RA1
#define MPU_ADDR_W   0xD0
#define MPU_ADDR_R   0xD1

#ifdef	__cplusplus
extern "C" {
#endif
    //click timestamps (in T2 overflow ticks, 1s each) 
extern volatile unsigned long timeCounter; 


void init_hardware(void);




#ifdef	__cplusplus
}
#endif

#endif	/* AIRDRAW_CONFIG_H */

