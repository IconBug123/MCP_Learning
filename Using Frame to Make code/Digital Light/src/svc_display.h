// svc_display.h
#ifndef SVC_DISPLAY_H
#define SVC_DISPLAY_H

#include "types.h"

void Display_Service_Init(void);

// 由调度器周期调用（建议 1~2ms）
void Display_Service_Task(void);

// 设置显示为一个0~9999的数
void Display_SetNumber(u16 num);

// 直接设置4位的段码（高级用法）
// void Display_SetRaw(const u8 seg4[4]);

#endif
