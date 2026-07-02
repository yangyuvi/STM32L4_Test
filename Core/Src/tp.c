
#include "tp.h"
#include "i2c.h"
#include "usart.h"


TOUCH_Status tp_status;
uint8_t tp_irq_flag = 0;

void TP_Read_Data(void) {
  uint8_t buf[5];
    
  // 从 0x02 寄存器开始，连续读取 5 个字节
  if (HAL_I2C_Mem_Read(&hi2c3, TOUCH_ADDR, 0x02, I2C_MEMADD_SIZE_8BIT, buf, 5, 10) == HAL_OK) {
        
    tp_status.finger = buf[0]; 
    tp_status.event  = buf[1] >> 6;

    if (tp_status.finger > 0) { // 有手指按下
      // 拼接 X 坐标 (0x03高4位 + 0x04低4位)
      tp_status.x = ((buf[1] & 0x0F) << 8) | buf[2];
      // 拼接 Y 坐标 (0x05高4位 + 0x06低4位)
      tp_status.y = ((buf[3] & 0x0F) << 8) | buf[4];
    } 
  }
  else
  {
    tp_status.finger = 0;
    tp_status.x = 0;
    tp_status.y = 0;
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == Touch_INT_Pin) { // 确认是触摸屏的INT引脚触发的
    tp_irq_flag = 1;
  }
}
