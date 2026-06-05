
#include "ws2812b.h"
#include "tim.h"

uint16_t DMABuffer[BUFFER_SIZE];

/**
  * @brief  初始化缓冲区
  */
void WS2812B_Init(void)
{
  uint8_t i;
  for(i=LED_NUM*RGB_BIT; i<BUFFER_SIZE; i++){
    DMABuffer[i] = 0;
  }

  for(i=0; i<LED_NUM*RGB_BIT; i++){
    DMABuffer[i] = CODE_0;
  }
}

/**
  * @brief  设置指定灯珠的 RGB 颜色
  * @param  index 0~3
  * @param  r,g,b 颜色亮度 0~255
  */
void WS2812B_SetLED(uint8_t index, Color_t color)
{
  uint8_t i;
  uint8_t offset = RGB_BIT * index;
  for(i=0;i<8;i++){
    //G通道对应的PWM占空比，高位先发
    DMABuffer[offset+i] = (color.g & (0x80 >> i)) ? CODE_1 : CODE_0;        //判断1/0，填充不同占空比
    //R通道
    DMABuffer[offset+8+i] = (color.r & (0x80 >> i)) ? CODE_1 : CODE_0;      //判断1/0，填充不同占空比
    //B通道
    DMABuffer[offset+16+i] = (color.b & (0x80 >> i)) ? CODE_1 : CODE_0;     //判断1/0，填充不同占空比
  }
}

/**
  * @brief  
  */
void WS2812B_Show(void)
{
  //开启PWM功能，TIM溢出时DMA搬运数据，搬完停止
  HAL_TIM_PWM_Start_DMA(&htim16, TIM_CHANNEL_1, (uint32_t *)DMABuffer,BUFFER_SIZE);
}
