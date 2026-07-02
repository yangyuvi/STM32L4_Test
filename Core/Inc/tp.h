#ifndef __TP_H
#define __TP_H

#include "stm32l4xx_hal.h"
#include "gpio.h"


#define  TOUCH_ADDR       (0x15 << 1)

// 定义一个结构体用来保存触摸状态
typedef struct {
    uint16_t x;             // X坐标 (0~171)
    uint16_t y;             // Y坐标 (0~319)
    uint8_t finger;         // 触摸点 1:按下 0:松开
    uint8_t event;          // 触摸事件类型
} TOUCH_Status;

extern TOUCH_Status tp_status;
extern uint8_t tp_irq_flag;

void TP_Read_Data(void);
#endif 
