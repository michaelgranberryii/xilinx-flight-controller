/**
 * @author Michael Granberry
*/

#include "axi_timer_ppm_receiver.h"

XTmrCtr ppm;


u32 ch[NUM_OF_CH];
u32 pulse = 0;
float captured_count_value = 0;
float captured_time_Sec = 0;
float captured_time_mSec = 0;
u32 captured_time_uSec = 0;
u32 t1, t2, delta_t;
u32 too_long = 2100;

void ppm_init(){
	int status = 0;
	status = XTmrCtr_Initialize(&ppm, XPAR_AXI_TIMER_PPM_DEVICE_ID);
	if(status == XST_SUCCESS)
		xil_printf("TMR PPM Init Successful\n\r");
	else
		xil_printf("TMR PPM Init Failed\n\r");
	 status = XTmrCtr_SelfTest(&ppm, XTC_TIMER_0);
	if(status == XST_SUCCESS) {
		xil_printf("TMR PPM SELF TEST SUCCUSSFUL\n\r");
	} else {
		xil_printf("TMR PPM SELF TEST FAILED\n\r");
	}

	tmr_ppm_setup();
}

void tmr_ppm_setup() {
	XTmrCtr_Stop(&ppm, XTC_TIMER_0);
	u32 Count = (100e6)*1;
	XTmrCtr_SetResetValue(&ppm, XTC_TIMER_0, Count);
	XTmrCtr_SetOptions(&ppm, XTC_TIMER_0, XTC_INT_MODE_OPTION | XTC_CAPTURE_MODE_OPTION);
	XTmrCtr_Start(&ppm, XTC_TIMER_0);
}

void trm_ppm_intr_init(XScuGic *gic) {
	// Connect and enable GIC
	XScuGic_Connect(gic, XPAR_FABRIC_AXI_TIMER_PPM_INTERRUPT_INTR, (Xil_InterruptHandler)tmrHandler, &ppm);
	XScuGic_Enable(gic, XPAR_FABRIC_AXI_TIMER_PPM_INTERRUPT_INTR);
}

void tmrHandler(){
	if (XTmrCtr_IsExpired(&ppm, XTC_TIMER_0)){
		captured_count_value = (float)XTmrCtr_GetCaptureValue(&ppm, XTC_TIMER_0);
		captured_time_Sec = (captured_count_value)*(1/100e6);
		captured_time_mSec = captured_time_Sec*1000;
		captured_time_uSec = (u32)(captured_time_mSec*1000);
		t1 = t2;
		t2 = captured_time_uSec;
		delta_t = (t2-t1);
//		xil_printf("delta_t: %d\n\r", delta_t);
		if (delta_t > too_long) {
			pulse = 0;
			ch[pulse] = delta_t;
			pulse = 1;
		} else {
			ch[pulse] = delta_t;
			pulse = (pulse + 1) % NUM_OF_CH;
		}
	}
	XTmrCtr_Reset(&ppm, XTC_TIMER_0);
}

u32 get_ch1() {
	return ch[1];
}

u32 get_ch2() {
	return ch[2];
}

u32 get_ch3() {
	return ch[3];
}

u32 get_ch4() {
	return ch[4];
}

u32 get_ch5() {
	return ch[5];
}

u32 get_ch6() {
	return ch[6];
}

u32 get_ch7() {
	return ch[7];
}

u32 get_ch8() {
	return ch[8];
}

void print_channel_time() {
	char channels[][20] = {"IDLE-HIGH", "ROLL", "PITCH", "THROTTLE", "YAW", "SWB", "VrB", "SWA", "VrA"};
	for (int i = 0; i < NUM_OF_CH; ++i) {
		(i != NUM_OF_CH-1) ? printf("%s[%d]: %lu\t", channels[i], i, ch[i]) : printf("%s[%d]: %lu\n\r", channels[i], i, ch[i]);
	}
}

