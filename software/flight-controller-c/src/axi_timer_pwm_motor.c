/**
 * @author Michael Granberry
*/
// esc calibration: https://www.rcelectricparts.com/classic-esc-user-guide.html#04

#include "axi_timer_pwm_motor.h"

int current_pulse_width_nSec = 0;
int previous_pulse_width_nSec = 0;

XTmrCtr pwm1, pwm2, pwm3, pwm4;

void pwm_init_all() {
	pwm_init(&pwm1, XPAR_AXI_TIMER_PWM_1_DEVICE_ID);
	pwm_init(&pwm2, XPAR_AXI_TIMER_PWM_2_DEVICE_ID);
	pwm_init(&pwm3, XPAR_AXI_TIMER_PWM_3_DEVICE_ID);
	pwm_init(&pwm4, XPAR_AXI_TIMER_PWM_4_DEVICE_ID);
}

void pwm_init(XTmrCtr *tmr_pwm_ptr, u16 DeviceID) {
	int status = XTmrCtr_Initialize(tmr_pwm_ptr, DeviceID);
	if(status == XST_SUCCESS) {
		xil_printf("TMR PWM%u INIT SUCCUSSFUL\n\r", DeviceID);
	} else {
		xil_printf("TMR PWM%u INIT FAILED\n\r", DeviceID);
	}
	status = XTmrCtr_SelfTest(tmr_pwm_ptr, XTC_TIMER_0);
	if(status == XST_SUCCESS) {
		xil_printf("TMR PWM%u  SELF TEST SUCCUSSFUL\n\r", DeviceID);
	} else {
		xil_printf("TMR PWM%u  SELF TEST FAILED\n\r", DeviceID);
	}

	pwm_setup(tmr_pwm_ptr);
}

void pwm_setup(XTmrCtr *tmr_pwm_ptr) {
	XTmrCtr_Stop(tmr_pwm_ptr, XTC_TIMER_0);
	u32 tmrctr0_option = XTmrCtr_GetOptions(tmr_pwm_ptr, XTC_TIMER_0);
	tmrctr0_option |= XTC_DOWN_COUNT_OPTION;
	XTmrCtr_SetOptions(tmr_pwm_ptr, XTC_TIMER_0, tmrctr0_option);
	XTmrCtr_PwmConfigure(tmr_pwm_ptr, PWM_PERIOD_nSEC, ONE_mSec);
	XTmrCtr_PwmEnable(tmr_pwm_ptr);
	XTmrCtr_Start(tmr_pwm_ptr, XTC_TIMER_0);
}

// Function to map a value from one range to another
int pwm_map_range(float value, float in_min, float in_max, float out_min, float out_max) {
	float result = (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return (int)result;
}

void pwm_update_pwm1(int input_channel_value) {
	pwm_update(&pwm1, input_channel_value);
}

void pwm_update_pwm2(int input_channel_value) {
	pwm_update(&pwm2, input_channel_value);
}

void pwm_update_pwm3(int input_channel_value) {
	pwm_update(&pwm3, input_channel_value);
}

void pwm_update_pwm4(int input_channel_value) {
	pwm_update(&pwm4, input_channel_value);
}

void pwm_update(XTmrCtr *tmr_pwm_ptr, int input_channel_value) {
	current_pulse_width_nSec = pwm_map_range((float)input_channel_value, IN_MIN, IN_MAX, OUT_MIN, OUT_MAX);
	pwm_set_new_duty_cycle(tmr_pwm_ptr, current_pulse_width_nSec);
	previous_pulse_width_nSec = current_pulse_width_nSec;
}

void pwm_set_new_duty_cycle(XTmrCtr *tmr_pwm_ptr, int pulse_width_nSec) {
	XTmrCtr_PwmDisable(tmr_pwm_ptr);
	XTmrCtr_PwmConfigure(tmr_pwm_ptr, PWM_PERIOD_nSEC, pulse_width_nSec);
	XTmrCtr_PwmEnable(tmr_pwm_ptr);
}

void pwm_enable() {
	XTmrCtr_PwmEnable(&pwm1);
	XTmrCtr_PwmEnable(&pwm1);
	XTmrCtr_PwmEnable(&pwm3);
	XTmrCtr_PwmEnable(&pwm4);
}

void pwm_disable() {
	XTmrCtr_PwmDisable(&pwm1);
	XTmrCtr_PwmDisable(&pwm1);
	XTmrCtr_PwmDisable(&pwm3);
	XTmrCtr_PwmDisable(&pwm4);
}

void pwm_minimun_output() {
	// IN_MIN = 1mSec = 1000uSec
	pwm_update_pwm1(IN_MIN);
	pwm_update_pwm2(IN_MIN);
	pwm_update_pwm3(IN_MIN);
	pwm_update_pwm4(IN_MIN);
}

void pwm_minimun_throttle_idle(u32 ch1, u32 ch2, u32 ch3, u32 ch4) {
	// set idle throttle
	if (ch1 < MOTOR_THROTTLE_IDLE_MIN) pwm_update_pwm1(MOTOR_THROTTLE_IDLE_MIN);
	if (ch2 < MOTOR_THROTTLE_IDLE_MIN) pwm_update_pwm2(MOTOR_THROTTLE_IDLE_MIN);
	if (ch3 < MOTOR_THROTTLE_IDLE_MIN) pwm_update_pwm3(MOTOR_THROTTLE_IDLE_MIN);
	if (ch4 < MOTOR_THROTTLE_IDLE_MIN) pwm_update_pwm4(MOTOR_THROTTLE_IDLE_MIN);
}

