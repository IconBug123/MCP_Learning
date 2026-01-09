// svc_key.c
#include "svc_key.h"
#include "drv_key.h"

// 10ms节拍下的参数
#define DEBOUNCE_TICKS   3    // 30ms 认为稳定
#define LONGPRESS_TICKS  80   // 800ms 长按（你可改成100=1s）

typedef enum {
    KS_IDLE = 0,
    KS_DEBOUNCE_DOWN,
    KS_DOWN,
    KS_DEBOUNCE_UP
} KeyState;

static KeyState s_state = KS_IDLE;

static u8  s_db_cnt = 0;
static u16 s_down_ticks = 0;
static bool s_long_fired = false;

static volatile KeyEvent s_event = KEY_EVENT_NONE;

void Key_Service_Init(void)
{
    DRV_Key_Init();
    s_state = KS_IDLE;
    s_db_cnt = 0;
    s_down_ticks = 0;
    s_long_fired = false;
    s_event = KEY_EVENT_NONE;
}

KeyEvent Key_Service_GetEvent(void)
{
    KeyEvent e = s_event;
    s_event = KEY_EVENT_NONE;
    return e;
}

void Key_Service_Task_10ms(void)
{
    bool pressed = DRV_Key_IsPressed();

    switch (s_state)
    {
        case KS_IDLE:
            if (pressed)
            {
                s_state = KS_DEBOUNCE_DOWN;
                s_db_cnt = 0;
            }
            break;

        case KS_DEBOUNCE_DOWN:
            if (pressed)
            {
                s_db_cnt++;
                if (s_db_cnt >= DEBOUNCE_TICKS)
                {
                    s_state = KS_DOWN;
                    s_down_ticks = 0;
                    s_long_fired = false;
                }
            }
            else
            {
                s_state = KS_IDLE; // 抖动回去
            }
            break;

        case KS_DOWN:
            if (pressed)
            {
                if (s_down_ticks < 0xFFFF) s_down_ticks++;

                // 达到长按阈值：立刻触发一次
                if (!s_long_fired && s_down_ticks >= LONGPRESS_TICKS)
                {
                    s_long_fired = true;
                    s_event = KEY_EVENT_LONG;
                }
            }
            else
            {
                s_state = KS_DEBOUNCE_UP;
                s_db_cnt = 0;
            }
            break;

        case KS_DEBOUNCE_UP:
            if (!pressed)
            {
                s_db_cnt++;
                if (s_db_cnt >= DEBOUNCE_TICKS)
                {
                    // 松开稳定：如果没触发过长按，则算短按
                    if (!s_long_fired)
                        s_event = KEY_EVENT_SHORT;

                    s_state = KS_IDLE;
                }
            }
            else
            {
                s_state = KS_DOWN; // 又按回去了
            }
            break;

        default:
            s_state = KS_IDLE;
            break;
    }
}
