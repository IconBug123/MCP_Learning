#include "types.h"
#include "bsp_timer0.h"
#include "scheduler.h"

#include "svc_display.h"
#include "svc_countdown.h"
#include "svc_key.h"
#include "app_countdown.h"

void main(void)
{
    u32 t_disp = 0;
    u32 t_cd   = 0;
    u32 t_key  = 0;
    u32 t_app  = 0;

    BSP_Timer0_Init_1ms();
    Display_Service_Init();
    Key_Service_Init();
    App_Countdown_Init();

    while(1)
    {
        u32 now = BSP_GetTickMs();

        if (task_due(now, &t_disp, 1))
            Display_Service_Task();

        if (task_due(now, &t_key, 10))
            Key_Service_Task_10ms();

        if (task_due(now, &t_cd, 10))
            Countdown_Task_10ms();

        if (task_due(now, &t_app, 20))
            App_Countdown_Task();
    }
}
