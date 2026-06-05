
#include "audio.h"
#include "sai.h"
#include "audio_data.h"

#define BUF_HALF  512
#define BUF_SIZE  (BUF_HALF * 2)
static uint16_t dma_buf[BUF_SIZE];    //双缓冲

// PCM 数据指针
// static const int16_t *pcm_data  = NULL;
// static uint32_t       pcm_total = 0;
static uint32_t pcm_pos = 0;

/**
  * @brief  填充 DMA 缓冲区的一个半段
  * @param  dst     目标缓冲区
  * @param  half    要填充的半段长度
  */
static void FillBuf(uint16_t *dst, uint32_t half)
{
  uint32_t i;
  for(i=0; i<half; i++){
    dst[i] = (pcm_pos < audio_wav_len) ? (uint16_t)audio_wav[pcm_pos++] : 0;
  }

}

//DMA中断回调，HAL自动调用
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
  * @param  
  */
void Audio_Init(void)
{
  pcm_pos   = 0;

  //预填充
  FillBuf(&dma_buf[0],        BUF_HALF);
  FillBuf(&dma_buf[BUF_HALF], BUF_HALF);

}


// /**
//   * @brief  播放WAV文件
//   * @param  
//   */
// HAL_StatusTypeDef Audio_Play(const uint8_t *wav, uint32_t size)
// {
//   if(!wav || size<sizeof(WavHeader_t)) return HAL_ERROR;  //输入合法性检测

//   WavHeader_t *hdr = (WavHeader_t *)wav;

//   //格式校验 PCM格式 16bit
//   if(hdr->audio_format != 1) return HAL_ERROR;
//   if(hdr->bits_per_sample != 16) return HAL_ERROR;
  
//   pcm_data = (const int16_t *)(wav + 44);   //跳过44字节 WAV 头，指向 PCM 数据
//   pcm_total = hdr->data_size / 2;
//   pcm_pos = 0;

//   FillBuf(&dma_buf[0], BUF_HALF);
//   FillBuf(&dma_buf[BUF_HALF], BUF_HALF);

//   HAL_SAI_Transmit_DMA(&hsai_BlockA1,(uint8_t *)dma_buf,BUF_SIZE);

//   return HAL_OK;
// }

/**
  * @brief  
  * @param  
  */
void Audio_Play(void)
{
  //启动 DMA 播放
  HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t *)dma_buf, BUF_SIZE);
}