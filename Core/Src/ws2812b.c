
#include "ws2812b.h"
#include "tim.h"
#include "usart.h"

static uint16_t DMABuffer1[BUFFER_SIZE1] = {0};

static uint32_t DMABuffer2[BUFFER_SIZE2] = {0};

/**
  * @brief  初始化缓冲区
  */
void WS2812B_Init(void)
{
  
}

/**
  * @brief  设置指定灯珠的 RGB 颜色
  * @param  index 0~3
  * @param  r,g,b 颜色亮度 0~255
  */
void WS2812B1_SetLED(uint8_t index, Color_t color)
{
  uint8_t i;
  uint16_t offset = RGB_BIT * index;
  for(i=0;i<8;i++){
    //G通道对应的PWM占空比，高位先发
    DMABuffer1[offset+i] = (color.g & (0x80 >> i)) ? CODE_1 : CODE_0;        //判断1/0，填充不同占空比
    //R通道
    DMABuffer1[offset+8+i] = (color.r & (0x80 >> i)) ? CODE_1 : CODE_0;      //判断1/0，填充不同占空比
    //B通道
    DMABuffer1[offset+16+i] = (color.b & (0x80 >> i)) ? CODE_1 : CODE_0;     //判断1/0，填充不同占空比
  }
}


void WS2812B2_SetAll(Color_t color)
{
  uint8_t i,j;

  for(i = 0; i < LED_NUM2; i++)
  {
    uint16_t offset = i * RGB_BIT;

    for(j = 0; j < 8; j++)
    {
      // G
      DMABuffer2[offset + j] =(color.g & (0x80 >> j)) ? CODE_1 : CODE_0;

      // R
      DMABuffer2[offset + 8 + j] = (color.r & (0x80 >> j)) ? CODE_1 : CODE_0;

      // B
      DMABuffer2[offset + 16 + j] = (color.b & (0x80 >> j)) ? CODE_1 : CODE_0;
    }
  }
}
  

/**
  * @brief  
  */
void WS2812B1_Show(void)
{ 
  //开启PWM功能，TIM溢出时DMA搬运数据，搬完停止
  HAL_TIM_PWM_Start_DMA(&htim16, TIM_CHANNEL_1, (uint32_t *)DMABuffer1,BUFFER_SIZE1);
}

void WS2812B2_Show(void){
  HAL_TIM_PWM_Start_DMA(&htim2,TIM_CHANNEL_2,(uint32_t *)DMABuffer2,BUFFER_SIZE2);
}

void WS2812B1_Clear(void)
{
  uint8_t i;
  for(i=0; i<LED_NUM1; i++){
    WS2812B1_SetLED(i,WS2812B_OFF);
  }
}

void WS2812B2_App(void)
{
  // static uint32_t rgbTick = 0;
  // static uint8_t colorIndex = 0;

  // if(HAL_GetTick() - rgbTick >= 3000){
    // switch (colorIndex)
    // {
    // case 0:
    //   WS2812B2_SetAll(WS2812B_RED);
    //   break;
    // case 1:
    //   WS2812B2_SetAll(WS2812B_GREEN);
    //   break;
    // case 2:
      // WS2812B2_SetAll(WS2812B_BLUE);
    // break;
    // default:
    //   break;
    // }
    // colorIndex = (colorIndex+1) % 3;
    // WS2812B2_Show();
   
  // }
}