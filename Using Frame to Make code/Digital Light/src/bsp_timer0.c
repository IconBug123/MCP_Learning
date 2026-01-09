// bsp_timer0.c
#include <REG52.H>
#include "bsp_timer0.h"

static volatile u32 g_tick_ms = 0;

// 以 11.0592MHz 为例：1ms重装值约 65536 - 11059 = 54477 (0xD4BD)
#define T0_RELOAD_H  0xFC
#define T0_RELOAD_L  0x66

void BSP_Timer0_Init_1ms(void)
{
    TMOD &= 0xF0;      // Timer0 mode bits clear
    TMOD |= 0x01;      // Timer0 mode1 (16-bit)

    TH0 = T0_RELOAD_H;
    TL0 = T0_RELOAD_L;

    ET0 = 1;           // enable T0 interrupt
    EA  = 1;           // global interrupt
    TR0 = 1;           // start timer0
}

u32 BSP_GetTickMs(void)
{
    u32 t;
    EA = 0;            // atomic read
    t = g_tick_ms;
    EA = 1;
    return t;
}

void timer0_isr(void) interrupt 1
{
    TH0 = T0_RELOAD_H;
    TL0 = T0_RELOAD_L;
    g_tick_ms++;


}

