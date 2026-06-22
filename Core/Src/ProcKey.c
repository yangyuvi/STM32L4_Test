
#include "ProcKey.h"
#include "motor.h"
#include "main.h"
#include "ws2812b.h"
#include "lcd.h"
#include "audio.h"
#include "usart.h"
#include "sensor.h"


TestMode mode = MODE_SCREEN;   //默认屏幕测试
static uint8_t color = 0;
static uint8_t lcdon = 1;

/**
  * @brief  处理按键1事件，改变模式
  * @param  event 按键事件
  */
void OnKey1Event(KeyEvent event)
{  
  if (event != KEY_EVENT_UP) return;   // 只响应短按

  mode = (mode+1) % MODE_MAX;   

  //停止其他测试
  LCD_DisplayOff();
  Motor_Stop();
  Audio_Stop();
  Sensor_Stop();  

  //同步重置标志位
  color = 0;
  lcdon = 0;

  //指示灯
  WS2812B_Clear();
  WS2812B_SetLED(mode, WS2812B_GREEN);
  WS2812B_Show();
}


/**
  * @brief  处理按键2事件
  * @param  
  */
void OnKey2Event(KeyEvent event)
{ 
  if (event != KEY_EVENT_UP) return;   // 松手触发

  switch(mode)
  {
    case MODE_SCREEN:
      if(lcdon==0){
        lcdon = 1;
        LCD_DisplayOn();
        LCD_Init();
      }
      switch(color)
      {
        case 0: LCD_FillColor(COLOR_RED);   break;
        case 1: LCD_FillColor(COLOR_GREEN); break;
        case 2: LCD_FillColor(COLOR_BLUE);  break;
        case 3: LCD_FillColor(COLOR_WHITE); break;
        case 4: LCD_FillColor(COLOR_BLACK); break;
      }
      color = (color + 1) % 5;
      
      break;

    case MODE_AUDIO:
      if (!Audio_IsPlaying()) {
        Audio_Play();
        WS2812B_SetLED(MODE_AUDIO, WS2812B_BLUE);
      }
      else {
        Audio_Stop();
        WS2812B_SetLED(MODE_AUDIO, WS2812B_GREEN);
      }
      WS2812B_Show();
      break;

    case MODE_SENSOR:
      if (!Sensor_IsRunning()) {
        Sensor_Start();
        WS2812B_SetLED(MODE_SENSOR, WS2812B_BLUE);
      }
      else {
        Sensor_Stop();
        WS2812B_SetLED(MODE_SENSOR, WS2812B_GREEN);
      }
      WS2812B_Show();
      break;

    default: break;
  }
}


/**
  * @brief  处理按键3事件，实现电机点动 + 换向
  *         按下启动，松手停止并切换方向
  * @param  
  */
 void OnKey3Event(KeyEvent event)
{  
  static uint8_t dir = 0;
  
  if (mode != MODE_MOTOR) return;

  switch (event)
  {
  case KEY_EVENT_DOWN:
    WS2812B_SetLED(MODE_MOTOR, WS2812B_BLUE);
    Motor_SetDir(dir);
    Motor_Start();
    break;
  case KEY_EVENT_UP:
    WS2812B_SetLED(MODE_MOTOR, WS2812B_GREEN);
    Motor_Stop();
    dir ^= 1;           // 按位异或
    break;
  default:
    break;
  }
  WS2812B_Show();
}



