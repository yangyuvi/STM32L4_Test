#ifndef __WS2812B_H
#define __WS2812B_H

#include "stm32l4xx_hal.h"

#define LED_NUM1         4       //灯珠数量
#define LED_NUM2         6   

#define RGB_BIT         24      //每个灯24bit的RGB数据
#define WS_RESET        300     //数据复位 300*1.25us（大于280us）

#define CODE_0          30      //逻辑0占空比
#define CODE_1          60      //逻辑1占空比

#define BUFFER_SIZE1     (LED_NUM1 * RGB_BIT) + WS_RESET
#define BUFFER_SIZE2     (LED_NUM2 * RGB_BIT) + WS_RESET

typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}Color_t;


//常用颜色
#define WS2812B_OFF       ((Color_t){0,  0,  0  })
#define WS2812B_RED       ((Color_t){25, 0,  0  })
#define WS2812B_GREEN     ((Color_t){0,  25, 0  })
#define WS2812B_BLUE      ((Color_t){0,   0, 25})
#define WS2812B_WHITE     ((Color_t){25, 25, 25})
#define WS2812B_YELLOW    ((Color_t){25, 25, 0  })
#define WS2812B_ORANGE    ((Color_t){25, 12, 0  })


void WS2812B_Init(void);
void WS2812B1_SetLED(uint8_t index, Color_t color);
void WS2812B1_Show(void);
void WS2812B1_Clear(void);
void WS2812B2_SetAll(Color_t color);
void WS2812B2_Show(void);
void WS2812B2_App(void);

#endif 
