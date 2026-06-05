#ifndef __AUDIO_H
#define __AUDIO_H

#include "stm32l4xx_hal.h"

// WAV 文件头
// typedef __packed struct{        //固定字节布局
//     char riff[4];               //固定为"RIFF"，即0x46464952
//     uint32_t file_size;         //集合大小，文件总大小-8
//     char wave[4];               //格式WAVE，即0x45564157
//     char fmt_id[4];             //固定为"fmt"，即0x20746D66
//     uint32_t fmt_size;          //子集合大小
//     uint16_t audio_format;      //音频格式，1表示线性PCM
//     uint16_t channels;          //1表示单声道，2表示双声道
//     uint32_t sample_rate;       //采样率
//     uint32_t byte_rate;         //字节速率
//     uint16_t block_align;       //块对齐
//     uint16_t bits_per_sample;   //单个采样数据大小
//     char data_id[4];            //固定为"data"，即0x5453494C
//     uint32_t data_size;         //子集合大小（不包括id和size）
// }WavHeader_t;

// 播放状态
// typedef enum{
//     AUDIO_IDLE = 0,
//     AUDIO_PLAYING,
//     AUDIO_PAUSED
// }AudioState_t;


//HAL_StatusTypeDef Audio_Play(const uint8_t *wav, uint32_t size);
void Audio_Play(void);
void Audio_Init(void);

#endif 
