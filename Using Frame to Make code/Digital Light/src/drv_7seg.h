// drv_7seg.h
#ifndef DRV_7SEG_H
#define DRV_7SEG_H

#include "types.h"

// 初始化IO（可选：看你硬件是否需要）
void DRV_7Seg_Init(void);

// 显示：选择第几位(0~3) + 段码
void DRV_7Seg_Output(u8 digit_index, u8 seg_code);

#endif
