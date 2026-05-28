
#include "motor.h"
#include "gpio.h"
#include "tim.h"


/**
  * @brief  低电平使能电机
  * @param  enable: 1-使能 0-失能
  */
void Motor_Enable(uint8_t enable)
{
  if(enable){
    HAL_GPIO_WritePin(GPIOC, StepEN_Pin, GPIO_PIN_RESET);
  }
  else{
    HAL_GPIO_WritePin(GPIOC, StepEN_Pin, GPIO_PIN_SET);
  }
}


/**
  * @brief  设置电机运行方向
  * @param  dir: 1-正转（前进） 0-反转（后退）
  */
void Motor_SetDir(uint8_t dir)
{
  if (dir){
    /* code */
    HAL_GPIO_WritePin(GPIOC,StepDIR_Pin,GPIO_PIN_SET);
  }
  else{
    HAL_GPIO_WritePin(GPIOC,StepDIR_Pin,GPIO_PIN_RESET);
  }
  
}


/**
  * @brief  停止脉冲，电机停止
  */
void Motor_Stop(void)
{
  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);    //设置占空比为0
}

/**
  * @brief  电机初始化
  */
void Motor_Init(void)
{
  //启动TIM3_CH1_PWM
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,208);    //设置占空比

  Motor_SetDir(1);
  Motor_Enable(0);
}
