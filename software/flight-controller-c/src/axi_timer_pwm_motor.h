/**
 * @author Michael Granberry
*/

#ifndef AXI_TIMER_PWM_MOTOR_H   /* prevent circular inclusions */
#define AXI_TIMER_PWM_MOTOR_H

#include "xtmrctr.h"
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtmrctr.h"
#include "xparameters.h"

// Tmr clk is set to 100 MHz in Vivado
#define ONE_mSec 1e6 // 1000000 nSec = 1 mSec duty cycle
#define PWM_PERIOD_nSEC 4e6 // 4 mSec pwm period
#define IN_MIN 1000 // 0000
#define IN_MAX 2000 // 1111
#define OUT_MIN 1e6 // 1_000_000 nSec = 1 mSec
#define OUT_MAX 2e6 // 2_000_000 nSec = 2 mSec
#define NUM_OF_PWM_TIMERS 4
#define MOTOR_THROTTLE_IDLE_MIN 1180

void pwm_init(XTmrCtr *tmr_pwm_ptr, u16 DeviceID);
void pwm_setup(XTmrCtr *tmr_pwm_ptr);
int pwm_map_range(float value, float in_min, float in_max, float out_min, float out_max);
void pwm_update(XTmrCtr *tmr_pwm, int input_channel_value);
void pwm_set_new_duty_cycle(XTmrCtr *tmr_pwm, int pulse_width_nSec);
void pwm_init_all();
void pwm_update_pwm1(int input_channel_value);
void pwm_update_pwm2(int input_channel_value);
void pwm_update_pwm3(int input_channel_value);
void pwm_update_pwm4(int input_channel_value);

void pwm_enable();
void pwm_disable();
void pwm_minimun_output();
void pwm_minimun_throttle_idle();
void pwm_minimun_throttle_idle(u32 ch1, u32 ch2, u32 ch3, u32 ch4);
#endif  /* end of protection macro */
