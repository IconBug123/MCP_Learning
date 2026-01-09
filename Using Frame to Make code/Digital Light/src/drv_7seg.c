#include <REG52.H>
#include "types.h"
#include "drv_7seg.h"

// ===== 按你硬件改 =====
#define DATA_BUS  P0
sbit SEG_LE = P2^6;   // 段码锁存
sbit DIG_LE = P2^7;   // 位选锁存

// 共阴=1（段码1亮）；共阳=0（段码0亮）
#define SEG_ACTIVE_HIGH   1

// 位选高有效=1 / 低有效=0（看你位选驱动）
#define DIG_ACTIVE_HIGH   0

// 如果你位序反了：把 (1u<<idx) 改成 (1u<<(7-idx))
static u8 make_digit_mask(u8 idx)
{
    u8 m = 0x00;
    if (idx < 8) m = (1u << idx);

    if (!DIG_ACTIVE_HIGH) m = (u8)(~m);
    return m;
}

static void latch_seg(u8 seg)
{
    DATA_BUS = seg;
    SEG_LE = 1; SEG_LE = 0;
}

static void latch_dig(u8 dig)
{
    DATA_BUS = dig;
    DIG_LE = 1; DIG_LE = 0;
}

static void all_digits_off(void)
{
    latch_dig(DIG_ACTIVE_HIGH ? 0x00 : 0xFF);
}

void DRV_7Seg_Init(void)
{
    SEG_LE = 0;
    DIG_LE = 0;
    all_digits_off();
    latch_seg(SEG_ACTIVE_HIGH ? 0x00 : 0xFF);
}

void DRV_7Seg_Output(u8 digit_index, u8 seg_code)
{
    u8 seg = seg_code;
    u8 dig;

    // 段码极性处理
    if (!SEG_ACTIVE_HIGH) seg = (u8)(~seg);

    // 先关位选（防重影）
    all_digits_off();

    // 更新段码
    latch_seg(seg);

    // 开指定位
    if (digit_index == 0xFF)
        dig = DIG_ACTIVE_HIGH ? 0x00 : 0xFF;  // 全灭
    else
        dig = make_digit_mask(digit_index);

    latch_dig(dig);
}

