// svc_key.h
#ifndef SVC_KEY_H
#define SVC_KEY_H

#include "types.h"

typedef enum {
    KEY_EVENT_NONE = 0,
    KEY_EVENT_SHORT,
    KEY_EVENT_LONG
} KeyEvent;

void Key_Service_Init(void);
void Key_Service_Task_10ms(void);

// 读取并清除事件（事件只消费一次）
KeyEvent Key_Service_GetEvent(void);

#endif
