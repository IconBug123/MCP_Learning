// svc_display.c
#include "svc_display.h"
#include "drv_7seg.h"

// 段码表（共阴，a b c d e f g dp）
// 0~9 + 空白
static const u8 SEG_TAB[11] = {
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x07, //7
    0x7F, //8
    0x6F, //9
    0x00  //blank
};

static volatile u8 g_buf[4] = {0,0,0,0};
static u8 g_scan_idx = 0;

void Display_Service_Init(void)
{
    DRV_7Seg_Init();
    Display_SetNumber(0);
}

// void Display_SetRaw(const u8 seg4[4])
// {
//     u8 i;
//     for(i=0;i<4;i++) g_buf[i] = seg4[i];
// }

void Display_SetNumber(u16 num)
{
    u8 d0, d1, d2, d3;

    if (num > 9999) num = 9999;

    d0 = (u8)(num / 1000);
    d1 = (u8)((num / 100) % 10);
    d2 = (u8)((num / 10) % 10);
    d3 = (u8)(num % 10);

    // 前导零处理：比如 12 显示 "  12"
    g_buf[0] = (d0==0) ? SEG_TAB[10] : SEG_TAB[d0];
    g_buf[1] = (d0==0 && d1==0) ? SEG_TAB[10] : SEG_TAB[d1];
    g_buf[2] = (d0==0 && d1==0 && d2==0) ? SEG_TAB[10] : SEG_TAB[d2];
    g_buf[3] = SEG_TAB[d3];
}

void Display_Service_Task(void)
{
    // 每次刷一位：scan_idx 0~3
    DRV_7Seg_Output(g_scan_idx, g_buf[g_scan_idx]);
    g_scan_idx++;
    if (g_scan_idx >= 4) g_scan_idx = 0;
}
