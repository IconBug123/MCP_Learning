// scheduler.c
#include "scheduler.h"

bool task_due(u32 now_ms, u32 *last_ms, u16 period_ms)
{
    if ((u32)(now_ms - *last_ms) >= period_ms)
    {
        *last_ms = now_ms;
        return true;
    }
    return false;
}
