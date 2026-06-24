 
#include "audio.h"
#include "sai.h"

#define BUF_HALF  8
#define BUF_SIZE  (BUF_HALF * 2)
static int16_t dma_buf[BUF_SIZE];    //双缓冲

#define SIN_LEN 64

//播放单一频段的正弦波
const int16_t sin_table[SIN_LEN] =
{
     0,   3212,   6393,   9512,
 12539,  15446,  18204,  20787,
 23170,  25329,  27245,  28898,
 30273,  31356,  32137,  32609,
 32767,  32609,  32137,  31356,
 30273,  28898,  27245,  25329,
 23170,  20787,  18204,  15446,
 12539,   9512,   6393,   3212,

     0,  -3212,  -6393,  -9512,
-12539, -15446, -18204, -20787,
-23170, -25329, -27245, -28898,
-30273, -31356, -32137, -32609,
-32767, -32609, -32137, -31356,
-30273, -28898, -27245, -25329,
-23170, -20787, -18204, -15446,
-12539,  -9512,  -6393,  -3212
};

const int16_t beep[] =
{
     0, 1000, 2000, 3000,
  2000, 1000,    0,-1000,
 -2000,-3000,-2000,-1000
};

// PCM 数据指针
static uint32_t pcm_pos = 0;
static uint8_t audioPlaying = 0;

/**
  * @brief  填充 DMA 缓冲区的一个半段
  * @param  dst     目标缓冲区
  * @param  half    要填充的半段长度
  */
static void FillBuf(int16_t *dst, uint32_t half)
{
  uint32_t i;
  for(i = 0; i < half; i++)
  {
    dst[i] = beep[pcm_pos] * 2;
    pcm_pos++;

    if(pcm_pos >= 12)
    {
      pcm_pos = 0;  //循环播放
    }
  }
}

// DMA中断回调，HAL自动调用
void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
  FillBuf(&dma_buf[0],BUF_HALF);          //前半完成，填充前半
}
void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{
  FillBuf(&dma_buf[BUF_HALF],BUF_HALF);   //后半完成，填充后半
}

/**
  * @brief   
  */
void Audio_Init(void)
{
  pcm_pos = 0;

  //预填充
  FillBuf(&dma_buf[0],        BUF_HALF);
  FillBuf(&dma_buf[BUF_HALF], BUF_HALF);

}


/**
  * @brief   
  */
void Audio_Play(void)
{
  audioPlaying = 1;

  //启动 DMA 播放
  HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t *)dma_buf, BUF_SIZE);
}

/**
  * @brief  停止播放
  */
void Audio_Stop(void)
{
  audioPlaying = 0;

  HAL_SAI_DMAStop(&hsai_BlockA1);
}

/**
  * @brief  播放状态
  * @retval 1正在播放 0未播放
  */
uint8_t Audio_IsOn(void)
{
  return audioPlaying;
}