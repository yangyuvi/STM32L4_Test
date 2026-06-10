/**
  ******************************************************************************
  * @file           : key.c
  * @brief          : 
  ******************************************************************************
  */


#include "key.h"
#include "gpio.h"

//KEY读取引脚电平
#define KEY1_ReadPin    (HAL_GPIO_ReadPin(GPIOA,KEY1_Pin)) 
#define KEY2_ReadPin    (HAL_GPIO_ReadPin(GPIOC,KEY2_Pin)) 
#define KEY3_ReadPin    (HAL_GPIO_ReadPin(GPIOC,KEY3_Pin))  

//按键按下时的电压，0xFF表示按下为高电平，0x00表示按下为低电平
static  uint8_t  s_arrKeyDownLevel[KEY_MAX];      //使用前要在InitKey函数中进行初始化   
static  KeyState s_key[KEY_MAX]; 


/**
  * @brief  初始化按键
  */
void Key_Init(void)
{
  uint8_t i;
                                                                
  s_arrKeyDownLevel[KEY1] = KEY_DOWN_LEVEL_KEY1;  //按键KEY1按下时为低电平
  s_arrKeyDownLevel[KEY2] = KEY_DOWN_LEVEL_KEY2;  //按键KEY2按下时为低电平
  s_arrKeyDownLevel[KEY3] = KEY_DOWN_LEVEL_KEY3;  //按键KEY3按下时为低电平

  for(i = 0; i < KEY_MAX; i++)
  {
    s_key[i].keyVal = (uint8_t)(~s_arrKeyDownLevel[i]);
    s_key[i].flag = WAIT_PUSH;
  }
}


/**
  * @brief  按键扫描，每10ms调用一次。
  * @param  OnKeyEvent 回调函数
  */
void Key_Scan(uint8_t keyName,void(*OnKeyEvent)(KeyEvent))
{
  KeyState *k = &s_key[keyName];
  
  k->keyVal = k->keyVal << 1;   //左移一位

  switch (keyName)
  {
    case KEY1:
      k->keyVal |= KEY1_ReadPin; //按下/弹起时，KEY1为0/1
      break;                                            
    case KEY2:                                 
      k->keyVal |= KEY2_ReadPin; //按下/弹起时，KEY2为0/1
      break;                                            
    case KEY3:                                 
      k->keyVal |= KEY3_ReadPin; //按下/弹起时，KEY3为0/1
      break;                                            
    default:
      break;
  }  
  
  //按键标志位的值为TRUE时，判断是否有按键有效按下
  if(k->keyVal == s_arrKeyDownLevel[keyName] && k->flag == WAIT_PUSH)
  {
    k->flag = WAIT_RELEASE; 
    OnKeyEvent(KEY_EVENT_DOWN);
  }

  //按键标志位的值为FALSE时，判断是否有按键有效弹起
  else if(k->keyVal == (uint8_t)(~s_arrKeyDownLevel[keyName]) && k->flag == WAIT_RELEASE)
  {
    k->flag = WAIT_PUSH;
    OnKeyEvent(KEY_EVENT_UP);
  }
}


