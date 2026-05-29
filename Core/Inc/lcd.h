#ifndef __LCD_H
#define __LCD_H

#include "stm32l4xx_hal.h"
#include "gpio.h"

//颜色定义
#define COLOR_RED    0xF800
#define COLOR_GREEN  0x07E0
#define COLOR_BLUE   0x001F
#define COLOR_WHITE  0xFFFF
#define COLOR_BLACK  0x0000

//宏操作
#define LCD_CS_LOW()        HAL_GPIO_WritePin(GPIOA, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_HIGH()       HAL_GPIO_WritePin(GPIOA, LCD_CS_Pin, GPIO_PIN_SET)
#define LCD_DC_LOW()        HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin, GPIO_PIN_RESET)
#define LCD_DC_HIGH()       HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin, GPIO_PIN_SET)
#define LCD_RST_LOW()       HAL_GPIO_WritePin(GPIOA, LCD_RST_Pin, GPIO_PIN_RESET)
#define LCD_RST_HIGH()      HAL_GPIO_WritePin(GPIOA, LCD_RST_Pin, GPIO_PIN_SET)

void LCD_Init(void);
void LCD_FillColor(uint16_t color);

#endif 
