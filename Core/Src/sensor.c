
#include "sensor.h"
#include "adc.h"
#include "usart.h"

static uint16_t adc_buf[32];
static uint8_t sensorRunning = 0;
static uint16_t adc_zero = 0;


/**
  * @brief  启动传感器
  */
void Sensor_Start(void)
{
  sensorRunning = 1;
  HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adc_buf,32);
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
}

/**
  * @brief  获取ADC平均值
  */
uint16_t Sensor_GetADC(void)
{
  uint32_t sum = 0;
  uint16_t max = adc_buf[0];
  uint16_t min = adc_buf[0];

  for(int i = 0; i < 32; i++)
  {
    sum += adc_buf[i];

    if(adc_buf[i] > max)
      max = adc_buf[i];

    if(adc_buf[i] < min)
      min = adc_buf[i];
  }

  sum -= max;
  sum -= min;
 
  return sum / 30;
}

/**
  * @brief  调零
  */
 void Sensor_Zero(void)
 {
    adc_zero = Sensor_GetADC();
 }

/**
  * @brief  while里调用,每1000ms打印一次传感器数据
  */
void Sensor_App(void)
{
  static uint32_t sensorTick = 0;
  
  if(!sensorRunning) return;

  if(HAL_GetTick() - sensorTick >= 1000)
  {
    sensorTick = HAL_GetTick();
    uint16_t adc = Sensor_GetADC();
   
    float voltage = adc * 3300.0f / 4095.0f; 
   
    int32_t adc_net = (int32_t)adc - (int32_t)adc_zero;
    
    // 压力 = 净ADC * 系数k
    float pressure = (float)adc_net * 20.0f / 1517.0f;

    printf("ADC=%d  vol=%.2fmv  pre=%.2fg\r\n",adc,voltage,pressure);
  }
}

/**
  * @brief  传感器运行状态
  * @retval 1正在运行 0未运行
  */
uint8_t Sensor_IsOn(void)
{
  return sensorRunning;
} 