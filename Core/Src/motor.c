
#include "motor.h"
#include "gpio.h"
#include "tim.h"

static uint8_t motorAutoOn = 0;


/**
  * @brief  电机启动
  */
void Motor_Start(void)
{
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_GPIO_WritePin(GPIOC, StepEN_Pin, GPIO_PIN_RESET);
}

/**
  * @brief  电机停止
  */
void Motor_Stop(void)
{
  HAL_GPIO_WritePin(GPIOC, StepEN_Pin, GPIO_PIN_SET);
  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

uint8_t Motor_IsOn(void)
{
  return motorAutoOn;
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

void Motor_SetAutoFlag()
{
  motorAutoOn = 1;
}

void Motor_ResetAutoFlag(){
  motorAutoOn = 0;
}

/**
  * @brief  电机初始化
  */
void Motor_Init(void)
{
  Motor_SetDir(0); //默认反转
  Motor_Stop();  //默认停止

  //启动TIM3_CH1_PWM
  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,50);    //设置占空比
}


/**
  * @brief  正转3s，反转3s
  */
void Motor_App(void)
{
  static uint32_t motorTick = 0;
  static uint8_t dir = 0;

  if(!motorAutoOn) return;
  
  if(HAL_GetTick() - motorTick >= 7000)
  {
    motorTick = HAL_GetTick();
    dir ^= 1;
    Motor_SetDir(dir);
  }
}