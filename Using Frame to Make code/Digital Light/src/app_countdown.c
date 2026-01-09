// app_countdown.c
#include "app_countdown.h"
#include "svc_countdown.h"
#include "svc_display.h"
#include "svc_key.h"

typedef enum {
    APP_IDLE = 0,
    APP_RUN,
    APP_PAUSE,
    APP_DONE
} AppState;

static AppState s_state = APP_IDLE;
static u16 s_start_sec = 50;  //倒计时时间

static void app_reset_to_idle(void)
{
    Countdown_Reset(s_start_sec);
    Countdown_Stop();
    Display_SetNumber(s_start_sec);
    s_state = APP_IDLE;
}

void App_Countdown_Init(void)
{
    app_reset_to_idle();
}

void App_Countdown_Task(void)
{
    KeyEvent ev = Key_Service_GetEvent();

    // 长按：全局复位优先级最高
    if (ev == KEY_EVENT_LONG)
    {
        app_reset_to_idle();
        return;
    }

    switch (s_state)
    {
        case APP_IDLE:
            // 显示起始值，短按开始
            if (ev == KEY_EVENT_SHORT)
            {
                Countdown_Start();
                s_state = APP_RUN;
            }
            break;

        case APP_RUN:
        {
            u16 sec = Countdown_GetRemainSec();
            Display_SetNumber(sec);

            if (Countdown_IsFinished())
            {
                Display_SetNumber(0);
                s_state = APP_DONE;
                break;
            }

            // 短按暂停
            if (ev == KEY_EVENT_SHORT)
            {
                Countdown_Stop();
                s_state = APP_PAUSE;
            }
        }
        break;

        case APP_PAUSE:
            // 暂停：保持当前显示
            Display_SetNumber(Countdown_GetRemainSec());

            // 短按继续
            if (ev == KEY_EVENT_SHORT)
            {
                Countdown_Start();
                s_state = APP_RUN;
            }
            break;

        case APP_DONE:
            // 完成：显示0，短按重新开始
            Display_SetNumber(0);

            if (ev == KEY_EVENT_SHORT)
            {
                Countdown_Reset(s_start_sec);
                Countdown_Start();
                s_state = APP_RUN;
            }
            break;

        default:
            app_reset_to_idle();
            break;
    }
}
