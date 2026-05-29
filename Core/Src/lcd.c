
#include "lcd.h"
#include "spi.h"

//发送一字节
static void SPI_WriteByte(uint8_t data)
{
  HAL_SPI_Transmit(&hspi1,&data,1,HAL_MAX_DELAY);
}

/**
  * @brief  发送命令
  * @param  cmd
  */
void SSD_CMD(uint8_t cmd)
{
  LCD_DC_LOW();
  LCD_CS_LOW();
  SPI_WriteByte(cmd);
  LCD_CS_HIGH();
}

/**
  * @brief  发送数据/参数
  * @param  dat
  */
void SSD_PAR(uint8_t dat)
{
  LCD_DC_HIGH();
  LCD_CS_LOW();
  SPI_WriteByte(dat);
  LCD_CS_HIGH();
}

#define SSD_DAT SSD_PAR


void LCD_Reset(void)
{
  LCD_RST_HIGH();
  HAL_Delay(10);
  LCD_RST_LOW();    //复位低电平
  HAL_Delay(10);
  LCD_RST_HIGH();
  HAL_Delay(120);
}

/**
  * @brief  LCD初始化
  * @param  void
  */
void LCD_Init(void)
{
  LCD_CS_HIGH();
  LCD_DC_HIGH();

  LCD_Reset();

  //厂家提供的初始化代码
  SSD_CMD(0xDF);
  SSD_PAR(0x98);
  SSD_PAR(0x53);

  SSD_CMD(0xDE);
  SSD_PAR(0x00);

  SSD_CMD(0xB2);
  SSD_PAR(0x38);

  SSD_CMD(0xB7);
  SSD_PAR(0x00);
  SSD_PAR(0x21);
  SSD_PAR(0x00);
  SSD_PAR(0x49);

  SSD_CMD(0xBB);
  SSD_PAR(0x10);
  SSD_PAR(0x2F);
  SSD_PAR(0x77);
  SSD_PAR(0x77);
  SSD_PAR(0x63);
  SSD_PAR(0xF0);

  SSD_CMD(0xC0);
  SSD_PAR(0x22);
  SSD_PAR(0xA2);

  SSD_CMD(0xC1);
  SSD_PAR(0x12);

  SSD_CMD(0xC3);
  SSD_PAR(0x7D);
  SSD_PAR(0x08);
  SSD_PAR(0x0C);
  SSD_PAR(0x0C);
  SSD_PAR(0xC0);
  SSD_PAR(0x73);
  SSD_PAR(0x20);
  SSD_PAR(0x77);
  
  SSD_CMD(0xC4);
  SSD_PAR(0x00);
  SSD_PAR(0x00);
  SSD_PAR(0xA0);
  SSD_PAR(0x79);
  SSD_PAR(0x0E);
  SSD_PAR(0x0A);
  SSD_PAR(0x16);
  SSD_PAR(0x79);
  SSD_PAR(0x0E);
  SSD_PAR(0x0A);
  SSD_PAR(0x16);
  SSD_PAR(0x82);

  SSD_CMD(0xC8);
  SSD_PAR(0x3F);
  SSD_PAR(0x34);
  SSD_PAR(0x2D);
  SSD_PAR(0x2B);
  SSD_PAR(0x30);
  SSD_PAR(0x35);
  SSD_PAR(0x31);
  SSD_PAR(0x32);
  SSD_PAR(0x32);
  SSD_PAR(0x30);
  SSD_PAR(0x2E);
  SSD_PAR(0x20);
  SSD_PAR(0x1C);
  SSD_PAR(0x19);
  SSD_PAR(0x02);
  SSD_PAR(0x00);
  SSD_PAR(0x3F);
  SSD_PAR(0x34);
  SSD_PAR(0x2D);
  SSD_PAR(0x2B);
  SSD_PAR(0x30);
  SSD_PAR(0x35);  
  SSD_PAR(0x31);
  SSD_PAR(0x32);
  SSD_PAR(0x32);
  SSD_PAR(0x30);
  SSD_PAR(0x2E);
  SSD_PAR(0x20);
  SSD_PAR(0x1C);
  SSD_PAR(0x19);
  SSD_PAR(0x02);
  SSD_PAR(0x00);

  SSD_CMD(0xD0);
  SSD_PAR(0x04);
  SSD_PAR(0x06);
  SSD_PAR(0x6C);
  SSD_PAR(0x1F);
  SSD_PAR(0x03);

  SSD_CMD(0xD7);
  SSD_PAR(0x00);
  SSD_PAR(0x30);

  SSD_CMD(0xE6);
  SSD_PAR(0x10);

  SSD_CMD(0xDE);
  SSD_PAR(0x01);

  SSD_CMD(0xBB);
  SSD_PAR(0x04);
  SSD_PAR(0xD7);
  SSD_PAR(0x12);

  SSD_CMD(0xB7);
  SSD_PAR(0x03);
  SSD_PAR(0x13);
  SSD_PAR(0xE5);
  SSD_PAR(0x38);
  SSD_PAR(0x38);

  SSD_CMD(0xC1);
  SSD_PAR(0x14);
  SSD_PAR(0x15);
  SSD_PAR(0xC0);

  SSD_CMD(0xC2);
  SSD_PAR(0x06);
  SSD_PAR(0x3A);

  SSD_CMD(0xC4);
  SSD_PAR(0x72);
  SSD_PAR(0x12);

  SSD_CMD(0xBE);
  SSD_PAR(0x00);

  SSD_CMD(0xDE);
  SSD_PAR(0x02);

  SSD_CMD(0xE5);
  SSD_PAR(0x00);
  SSD_PAR(0x02);
  SSD_PAR(0x00);

  SSD_CMD(0xE5);
  SSD_PAR(0x01);
  SSD_PAR(0x02);
  SSD_PAR(0x00);

  SSD_CMD(0xDE);
  SSD_PAR(0x00);

  SSD_CMD(0xD8);
  SSD_PAR(0x08);
  SSD_PAR(0x00);

  SSD_CMD(0x35);
  SSD_PAR(0x00);

  SSD_CMD(0x3A);
  SSD_PAR(0x05);

  SSD_CMD(0x2A);
  SSD_PAR(0x00); SSD_PAR(0x22);//Start_X=34
  SSD_PAR(0x00); SSD_PAR(0xCD);//End_X=205

  SSD_CMD(0x2B);
  SSD_PAR(0x00); SSD_PAR(0x00);//Start_Y=0
  SSD_PAR(0x01); SSD_PAR(0x3F);//End_Y=319

  SSD_CMD(0x11);
  HAL_Delay(140);

  SSD_CMD(0xDE);
  SSD_PAR(0x02);

  SSD_CMD(0xE5);
  SSD_PAR(0x00);
  SSD_PAR(0x02);
  SSD_PAR(0x00);

  SSD_CMD(0xDE);
  SSD_PAR(0x00);

  SSD_CMD(0x29);
  HAL_Delay(10);
}


/**
  * @brief  设置显示窗口
  * @param  行列坐标 
  */
void LCD_SetWindow(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1)
{
  //列地址设置：实际列 = 像素列 + 34（偏移）
  SSD_CMD(0x2A);
  SSD_PAR((x0 + 34) >> 8);
  SSD_PAR((x0 + 34) & 0xFF);
  SSD_PAR((x1 + 34) >> 8);
  SSD_PAR((x1 + 34) & 0xFF);

  //行地址设置
  SSD_CMD(0x2B);
  SSD_PAR(y0 >> 8);
  SSD_PAR(y0 & 0xFF);
  SSD_PAR(y1 >> 8);
  SSD_PAR(y1 & 0xFF);
}

/**
  * @brief  填充颜色，RGB565，每像素2字节
  * @param  color 
  */
void LCD_FillColor(uint16_t color)
{
  uint32_t i;

  LCD_SetWindow(0,0,171,319);   //开窗 显示区域全屏
  SSD_CMD(0x2C); 

  for(i=0;i<172*320;i++){
    SSD_DAT(color >> 8);    //高字节
    SSD_DAT(color & 0xFF);  //低字节
  }
}

