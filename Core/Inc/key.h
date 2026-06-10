#ifndef _KEY_H_
#define _KEY_H_

#include "stm32l4xx_hal.h"

//各个按键按下的电平
#define  KEY_DOWN_LEVEL_KEY1    0x00     //0x00表示按下为低电平
#define  KEY_DOWN_LEVEL_KEY2    0x00     //0x00表示按下为低电平
#define  KEY_DOWN_LEVEL_KEY3    0x00     //0x00表示按下为低电平

//当前按键状态
#define  WAIT_RELEASE        1         //等待松开
#define  WAIT_PUSH           0         //等待按下

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/
typedef enum
{
  KEY1 = 0,  //按键1
  KEY2,      //按键2
  KEY3,      //按键3
  KEY_MAX
}EnumKeyOneName;


typedef enum {
    KEY_EVENT_DOWN = 0,         //按键按下事件
    KEY_EVENT_UP                //按键弹起事件

} KeyEvent;


typedef struct {
    uint8_t  keyVal;           // 采样值
    uint8_t  flag;             // 标志
} KeyState;


void  Key_Init(void);                                        //初始化key模块

void  Key_Scan(uint8_t keyName,void(*OnKeyEvent)(KeyEvent));  


#endif
