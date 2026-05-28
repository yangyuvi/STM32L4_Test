#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32l4xx_hal.h"

void Motor_SetDir(uint8_t dir);
void Motor_Stop(void);
void Motor_Enable(uint8_t enable);
void Motor_Init(void);

#endif 
