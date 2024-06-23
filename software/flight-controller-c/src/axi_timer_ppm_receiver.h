/**
 * @author Michael Granberry
*/

#ifndef AXI_TIMER_PPM_RECEIVER_H   /* prevent circular inclusions */
#define AXI_TIMER_PPM_RECEIVER_H

#include <stdio.h>
#include "platform.h"
#include "xtmrctr.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "xparameters.h"

#define NUM_OF_CH 9
u32 get_ch1();
u32 get_ch2();
u32 get_ch3();
u32 get_ch4();
u32 get_ch5();
u32 get_ch6();
u32 get_ch7();
u32 get_ch8();
void ppm_init();
void tmr_ppm_setup();
void trm_ppm_intr_init(XScuGic *gic);
void print_channel_time();
void tmrHandler();

#endif  /* end of protection macro */
