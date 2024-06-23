/**
 * @author Michael Granberry
*/

#ifndef COMPLEMENTARY_FILTER
#define COMPLEMENTARY_FILTER

#include <stdio.h>
#include "math.h"
#include "platform.h"
#include "sleep.h"
#include "mpu_6050.h"

#define COMP_FILT_ALPHA 0.0500000f
#define COMP_FILT_SAMPLE_TIME 4

void comp_filter_print();
float comp_filter_get_roll(float rollx, float gx);
float comp_filter_get_pitch(float pitchy, float gy);
#endif  /* end of protection macro */
