/**
 * @author Michael Granberry
*/

#include "scu_timer.h"

XScuTimer_Config *tC;
XScuTimer tI;
u64 micros = 0;
u64 milliseconds = 0;
u32 toggle_500_ms = 0;

void scuTmrHandler(){
	XScuTimer_DisableInterrupt(&tI);

	if(XScuTimer_IsExpired(&tI))
	{
//		xil_printf("We have an Interrupt at 0.999 uSec\n\r");
		scu_timer_inc_micros();
		scu_timer_inc_millisec();
		if (micros % (1000*500) == 0)
		{
			toggle_500_ms = !toggle_500_ms;
		}
	}

	XScuTimer_ClearInterruptStatus(&tI);
	XScuTimer_EnableInterrupt(&tI);
//	XScuTimer_RestartTimer(&tI);
}


void tmrInit(){
	int status = 0;
	tC = XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID);
	status = XScuTimer_CfgInitialize(&tI,tC,tC->BaseAddr);
	if(status == XST_SUCCESS)
		xil_printf("Scu Timer Init Successful\n\r");
	else
		xil_printf("Scu Timer Init Failed\n\r");

	XScuTimer_Stop(&tI);
	XScuTimer_LoadTimer(&tI,325); //// 0.999 uSec
//	XScuTimer_DisableAutoReload(&tI);
	XScuTimer_EnableAutoReload(&tI);
}

void scuTmrHandler_intrInit(XScuGic *gic){
	XScuGic_Connect(gic, XPAR_SCUTIMER_INTR, (Xil_InterruptHandler)scuTmrHandler, &tI);
	XScuGic_Enable(gic, XPAR_SCUTIMER_INTR);
	XScuTimer_EnableInterrupt(&tI);
}

void scu_timer_start()
{
	XScuTimer_Start(&tI);
}

void scu_timer_stop()
{
	XScuTimer_Stop(&tI);
}
u32 scu_timer_get_curr_micros()
{
	return micros;
}

u32 scu_timer_inc_micros(){
	micros++;
	return micros;
}


u32 scu_timer_inc_millisec()
{
	if (scu_timer_get_curr_micros() % (1000) == 0)
	{
		++milliseconds;
	}
	return milliseconds;
}

u32 scu_timer_get_toggle_500_ms()
{
	return toggle_500_ms;
}

u32 scu_timer_get_millisec()
{
	return milliseconds;
}

