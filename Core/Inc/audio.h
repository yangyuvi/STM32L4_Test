#ifndef __AUDIO_H
#define __AUDIO_H

#include "stm32l4xx_hal.h"


void Audio_Play(void);
void Audio_Stop(void);
void Audio_Init(void);
uint8_t Audio_IsOn(void);

#endif 
