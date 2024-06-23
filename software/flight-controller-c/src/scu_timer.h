/**
 * @author Michael Granberry
*/

#ifndef SCU_TIMER   /* prevent circular inclusions */
#define SCU_TIMER

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xscugic.h"
#include "xparameters.h"
#include "xscutimer.h"
#include "xil_exception.h"
#include "sleep.h"



void scuTmrHandler();
void tmrInit();
void scuTmrHandler_intrInit();
void scu_timer_start();
void scu_timer_stop();
u32 scu_timer_get_curr_micros();
u32 scu_timer_inc_micros();
u32 scu_timer_inc_millisec();
u32 scu_timer_toggle_500_ms();

u32 scu_timer_inc_millisec();
u32 scu_timer_get_millisec();
u32 scu_timer_get_toggle_500_ms();
#endif  /* end of protection macro */
