/**
 * @author Michael Granberry
*/


#ifndef AXI_GPIO_RGB_LED   /* prevent circular inclusions */
#define AXI_GPIO_RGB_LED

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"
#include "sleep.h"
#include "scu_timer.h"

#define GPIO_CHANNEL 1
#define GPIO_PIN_DIR_OUT (0x7 & 0x0)
#define LED_SLEEP_US 300000

#define RED_RGB_LED 0x4
#define GREEN_RGB_LED 0x2
#define BLUE_RGB_LED 0x1
#define YELLOW_RGB_LED 0x6
#define PURPLE_RGB_LED 0x5
#define WHITE_RGB_LED 0x7
#define OFF_RGB_LED 0x0

void rgb_led_init(void);
void rgb_led_set_output(u32 rgb_color);
void rgb_led_set_output_flash(u32 rgb_color);

#endif  /* end of protection macro */
