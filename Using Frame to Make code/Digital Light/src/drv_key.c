// drv_key.c
#include <REG52.H>
#include "drv_key.h"

// ====== 你按硬件改这里 ======
sbit KEY1 = P3^0;     // P3.2
// 假设：按下=0，松开=1

void DRV_Key_Init(void)
{
    KEY1 = 1;         // 准双向口，上拉（8051常见写法）
}

bool DRV_Key_IsPressed(void)
{
    return (KEY1 == 0) ? true : false;
}
