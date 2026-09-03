/* 
 * File:   AirDraw_IMU.h
 */

#ifndef AIRDRAW_IMU_H
#define	AIRDRAW_IMU_H
#include "AirDraw_Config.h"

#ifdef	__cplusplus
extern "C" {
#endif
    // Purpose: Initialize I2C1 and wake MPU6050
    void MPU6050_init(void);
    
    // Purpose: Read filtered and mapped coordinates (0-7) from the IMU
    void get_air_coords(int *x, int *y);




#ifdef	__cplusplus
}
#endif

#endif	/* AIRDRAW_IMU_H */

