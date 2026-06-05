#ifndef __WS2812B_H
#define __WS2812B_H

#include "stm32l4xx_hal.h"

#define LED_NUM         4       //灯珠数量
#define RGB_BIT         24      //每个灯24bit的RGB数据

#define WS_RESET        300     //数据复位 300*1.25us（大于280us）

#define CODE_0          32      //逻辑0占空比
#define CODE_1          64      //逻辑1占空比

#define BUFFER_SIZE     (LED_NUM * RGB_BIT) + WS_RESET

typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}Color_t;


//常用颜色
#define WS2812B_OFF       ((Color_t){0,   0,   0  })
#define WS2812B_RED       ((Color_t){255, 0,   0  })
#define WS2812B_GREEN     ((Color_t){0,   255, 0  })
#define WS2812B_BLUE      ((Color_t){0,   0,   255})
#define WS2812B_WHITE     ((Color_t){255, 255, 255})
#define WS2812B_YELLOW    ((Color_t){255, 255, 0  })
#define WS2812B_ORANGE    ((Color_t){255, 128, 0  })


void WS2812B_Init(void);
void WS2812B_SetLED(uint8_t index, Color_t color);
void WS2812B_Show(void);

#endif 
