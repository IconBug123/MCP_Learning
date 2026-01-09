// scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "types.h"

bool task_due(u32 now_ms, u32 *last_ms, u16 period_ms);

#endif
