// svc_countdown.h
#ifndef SVC_COUNTDOWN_H
#define SVC_COUNTDOWN_H

#include "types.h"

void Countdown_Init(u16 start_sec);
void Countdown_Start(void);
void Countdown_Stop(void);
void Countdown_Reset(u16 start_sec);

// 由调度器周期调用（建议 10ms 或 1ms都行）
void Countdown_Task_10ms(void);

u16  Countdown_GetRemainSec(void);
bool Countdown_IsRunning(void);
bool Countdown_IsFinished(void);

#endif
