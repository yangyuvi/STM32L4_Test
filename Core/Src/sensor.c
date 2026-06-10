
#include "sensor.h"
#include "adc.h"
#include <stdio.h>

static uint16_t adc_buf[1];
static uint8_t sensorRunning = 0;

/**
  * @brief  启动传感器
  */
void Sensor_Start(void)
{
  sensorRunning = 1;
  HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adc_buf,1);
}

/**
  * @brief  停止传感器
  */
void Sensor_Stop(void)
{
  sensorRunning = 0;
  HAL_ADC_Stop_DMA(&hadc1);
}

/**
  * @brief  传感器初始化
  */
void Sensor_Init(void)
{
  HAL_ADCEx_Calibration_Start(&hadc1,ADC_SINGLE_ENDED); //上电校准
  HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adc_buf,1);
}


/**
  * @brief  while里调用,每500ms打印一次传感器数据
  */
void Sensor_App(void)
{
  static uint32_t sensorTick = 0;
  if(!sensorRunning) return;

  if(HAL_GetTick() - sensorTick >= 500)
  {
    sensorTick = HAL_GetTick();
    
    printf("%d\r\n", adc_buf[0]);
  }
}

/**
  * @brief  传感器运行状态
  * @retval 1正在运行 0未运行
  */
uint8_t Sensor_IsRunning(void)
{
  return sensorRunning;
} 