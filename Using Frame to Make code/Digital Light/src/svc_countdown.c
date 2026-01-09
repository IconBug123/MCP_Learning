// svc_countdown.c
#include "svc_countdown.h"

static volatile u16 g_start_sec = 10;
static volatile u16 g_remain_sec = 10;
static volatile bool g_running = false;
static volatile bool g_finished = false;

static u16 g_acc_10ms = 0;

void Countdown_Init(u16 start_sec)
{
    Countdown_Reset(start_sec);
    Countdown_Stop();
}

void Countdown_Reset(u16 start_sec)
{
    g_start_sec = start_sec;
    g_remain_sec = start_sec;
    g_finished = false;
    g_acc_10ms = 0;
}

void Countdown_Start(void)
{
    if (g_remain_sec == 0)
        g_remain_sec = g_start_sec;

    g_running = true;
    g_finished = false;
}

void Countdown_Stop(void)
{
    g_running = false;
}

u16 Countdown_GetRemainSec(void)
{
    return g_remain_sec;
}

bool Countdown_IsRunning(void)
{
    return g_running;
}

bool Countdown_IsFinished(void)
{
    return g_finished;
}

// 10ms调用一次：累积到1000ms -> 秒--
void Countdown_Task_10ms(void)
{
    if (!g_running || g_finished) return;

    g_acc_10ms += 10;
    if (g_acc_10ms >= 1000)
    {
        g_acc_10ms = 0;
        if (g_remain_sec > 0)
        {
            g_remain_sec--;
            if (g_remain_sec == 0)
            {
                g_finished = true;
                g_running = false;
            }
        }
    }
}
