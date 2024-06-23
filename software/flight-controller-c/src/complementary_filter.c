/**
 * @author Michael Granberry
*/

#include "complementary_filter.h"

float phiHat_rad = 0.0f;
float thetaHat_rad = 0.0f;

void comp_filter_print() {

	float ax_mps2 = mpu_6050_get_accel_x_cal();
	float ay_mps2 = mpu_6050_get_accel_y_cal();
	float az_mps2 = mpu_6050_get_accel_z_cal();
	float p_rps = mpu_6050_get_gyro_x_cal(); // x
	float q_rps = mpu_6050_get_gyro_y_cal(); // y

	float rollx = mpu_6050_get_angle_roll(ay_mps2, ax_mps2, az_mps2);
	float pitchy = mpu_6050_get_angle_pitch(ax_mps2, ay_mps2, az_mps2);

	float comp_filer_roll_result = comp_filter_get_roll(rollx, p_rps);
	float comp_filer_pitch_result = comp_filter_get_pitch(pitchy, q_rps);

	// print
	printf("comp_filer_roll_result: %f, \t comp_filer_pitch_result: %f\n\r", comp_filer_roll_result, comp_filer_pitch_result);

	usleep(1000*COMP_FILT_SAMPLE_TIME);
}

float comp_filter_get_roll(float rollx, float gx) {
	phiHat_rad = COMP_FILT_ALPHA * rollx
			+ (1.0f - COMP_FILT_ALPHA) * (phiHat_rad + (COMP_FILT_SAMPLE_TIME / 1000.0f) * gx); // roll
	return phiHat_rad;
}

float comp_filter_get_pitch(float pitchy, float gy) {
	thetaHat_rad = COMP_FILT_ALPHA * pitchy
			+ (1.0f - COMP_FILT_ALPHA) * (thetaHat_rad + (COMP_FILT_SAMPLE_TIME / 1000.0f) * gy); // pitch
	return thetaHat_rad;
}
