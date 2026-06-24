#ifndef __SENSOR_H
#define __SENSOR_H

#include "stm32l4xx_hal.h"
#include "gpio.h"

void Sensor_Start(void);
void Sensor_Stop(void);
void Sensor_Init(void);
void Sensor_App(void);
uint8_t Sensor_IsOn(void);
void Sensor_Zero(void);

#endif 
