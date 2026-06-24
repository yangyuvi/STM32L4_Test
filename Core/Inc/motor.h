#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32l4xx_hal.h"

typedef enum
{
    MOTOR_MODE_JOG = 0,   //点动
    MOTOR_MODE_AUTO       //自动
}MotorMode;

void Motor_SetDir(uint8_t dir);
void Motor_Stop(void);
void Motor_Start(void);
void Motor_Stop(void);
void Motor_Init(void);
void Motor_SetAutoFlag();
void Motor_ResetAutoFlag();
uint8_t Motor_IsOn(void);
void Motor_App(void);

#endif 
