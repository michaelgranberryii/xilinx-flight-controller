/**
 * @author Michael Granberry
 * @brief Main program for Zybo Z7-10 flight controller
 * @file main.c
*/

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xil_exception.h"
#include "xscugic.h"

#include "axi_gpio_rgb_led.h"
#include "axi_timer_ppm_receiver.h"
#include "axi_timer_pwm_motor.h"
#include "scu_timer.h"
#include "mpu_6050.h"
#include "pid.h"
#include "complementary_filter.h"
#include "fir.h"

XScuGic_Config *gic_config;
XScuGic gic;

typedef enum State {
	DISARMED,
	IDLE,
	CALIBRATION,
	ARMED,
	RUNNING
} State;

State curr_state = DISARMED;
//State curr_state = CALIBRATION;

u8 is_calibrated = 0;

void gic_init(){
	int status = 0;
	gic_config = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);

	status = XScuGic_CfgInitialize(&gic, gic_config, gic_config->CpuBaseAddress);
	if(status == XST_SUCCESS)
		xil_printf("GIC Init Successful\n\r");
	else
		xil_printf("GIC Init Failed\n\r");

	// Init and enable exception
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler,	&gic);
	Xil_ExceptionEnable();

	trm_ppm_intr_init(&gic);
	scuTmrHandler_intrInit(&gic);
}

void testing() {

//		print_channel_time();
		mpu_6050_print_results();
//		comp_filter_print();
}

void calibration() {
    // Calibration
	printf("Calibrating IMU Accelerometer...\n\r");
	mpu_acceleration_calibration();

	printf("Calibrating IMU Gyroscope...\n\r");
	mpu_gyroscope_calibration();

	printf("Reset PID...\n\r");
	pid_reset();

	print("Calibrated\n\r");
}

void flight_controller_fsm() {
	switch (curr_state) {
	case DISARMED:
			print("Disarmed\n\r");
			rgb_led_set_output(RED_RGB_LED);
			pwm_minimun_output();
			usleep(1000*500);
			curr_state = IDLE;
			is_calibrated = 0;
			usleep(1000*2000);
		break;

		case IDLE:
			if ((get_ch4() > 1995) && (get_ch3() < 1005)) {
				curr_state = CALIBRATION;
			} else {
				curr_state = IDLE;
			}
			break;

		case CALIBRATION:
				if (is_calibrated) {
					if ((get_ch3() < 1001)) {
						curr_state = ARMED;
					} else {

						rgb_led_set_output_flash(PURPLE_RGB_LED);
						curr_state = CALIBRATION;
					}
				} else {
					print("Calibrating...\n\r");
					rgb_led_set_output(PURPLE_RGB_LED);
					calibration();
					is_calibrated = 1;
				}
			break;

		case ARMED:
			print("Armed\n\r");
		 	rgb_led_set_output(GREEN_RGB_LED);
			pwm_enable();
			pwm_minimun_output();
			curr_state = RUNNING;
			usleep(1000*500);
			break;

		case RUNNING:
			 if ((get_ch4() > 1990) && (get_ch3() < 1010)) {
				curr_state = DISARMED;
			 } else {

				 if (get_ch5() < 1500) {
//				 if (0) {
					 print("1\n\r");
					 pid_single_loop_rate();
				 } else {
					 print("2\n\r");
					 pid_dual_loop_stabilize();
				 }

				curr_state = RUNNING;
			 }
			break;

		default:
		 	curr_state = DISARMED;
			break;
	}

}


u8 imu_has_valid_data() {
	float x,y,z;
	mpu_6050_read_measurement();
	x = mpu_6050_get_accel_x_cal();
	y = mpu_6050_get_accel_y_cal();
	z = mpu_6050_get_accel_z_cal();
	if ((x != 0.0f) && (y != 0.0f) && (z != 0.0f)) {
		return 1;
	} else {
		printf("x: %f, y: %f, z: %f\n\r", x, y, z);
		return 0;
	}
}



int main()
{
    init_platform();

//    iic_scan();

    // RGB GPIO
    rgb_led_init();
    rgb_led_set_output(WHITE_RGB_LED);

    // PPM
    ppm_init();

    // PWM
    pwm_init_all();

    // SCU Timer
    tmrInit();

    // IMU
    mpu_6050_init();

    // GIC
    gic_init();
    usleep(1000*2000);

    // Ready
    xil_printf("Launching Flight Controller\n\r");
    rgb_led_set_output(BLUE_RGB_LED);
    scu_timer_start();
    while(1) {
    	flight_controller_fsm();
//    	testing();
    }

    rgb_led_set_output(OFF_RGB_LED);
    xil_printf("Fail Flight Controller\n\r");
    cleanup_platform();
    return 0;
}
