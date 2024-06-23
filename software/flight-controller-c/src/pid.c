/**
 * @author Michael Granberry
*/

#include "pid.h"
// Initialize PID controller
PIDController pid_roll_angle = { KP_ROLL_ANGLE, KI_ROLL_ANGLE, KD_ROLL_ANGLE,
						PID_TAU,
						PID_LIM_MIN, PID_LIM_MAX,
			PID_LIM_MIN_INT, PID_LIM_MAX_INT,
						SAMPLE_TIME_PID };

// Initialize PID controller
PIDController pid_pitch_angle = { KP_PITCH_ANGLE, KI_PITCH_ANGLE, KD_PITCH_ANGLE,
						PID_TAU,
						PID_LIM_MIN, PID_LIM_MAX,
			PID_LIM_MIN_INT, PID_LIM_MAX_INT,
						SAMPLE_TIME_PID };


// Initialize PID controller
PIDController pid_roll = { KP_ROLL, KI_ROLL, KD_ROLL,
						PID_TAU,
						PID_LIM_MIN, PID_LIM_MAX,
			PID_LIM_MIN_INT, PID_LIM_MAX_INT,
						SAMPLE_TIME_PID };


// Initialize PID controller
PIDController pid_pitch = { KP_PITCH, KI_PITCH, KD_PITCH,
						PID_TAU,
						PID_LIM_MIN, PID_LIM_MAX,
			PID_LIM_MIN_INT, PID_LIM_MAX_INT,
						SAMPLE_TIME_PID };


// Initialize PID controller
PIDController pid_yaw = { KP_YAW, KI_YAW, KD_YAW,
						PID_TAU,
						PID_LIM_MIN, PID_LIM_MAX,
			PID_LIM_MIN_INT, PID_LIM_MAX_INT,
						SAMPLE_TIME_PID };

Motor motor = {0,0,0,0};
Input input = {0,0,0,0};
SetPoint setpoint = {0,0,0,0,0,0};
Gyro gyro = {0,0,0};
Angle angle = {0,0};


FIRFilter fir_roll;
FIRFilter fir_pitch;
FIRFilter fir_yaw;

u32 loop_start;

void pid_dual_loop_stabilize() {
	loop_start = scu_timer_get_curr_micros();
	// Reading sensor **********************************************************
	float ax_mps2 = mpu_6050_get_accel_x_cal();
	float ay_mps2 = mpu_6050_get_accel_y_cal();
	float az_mps2 = mpu_6050_get_accel_z_cal();

	gyro.x_rps = mpu_6050_get_gyro_x_cal(); // x
	gyro.y_rps = mpu_6050_get_gyro_y_cal(); // y
	gyro.z_rps = mpu_6050_get_gyro_z_cal();

//	gyro.x_rps = FIRFilter_Update(&fir_roll, mpu_6050_get_gyro_x_cal());
//	gyro.y_rps = FIRFilter_Update(&fir_pitch, mpu_6050_get_gyro_y_cal());
//	gyro.z_rps = FIRFilter_Update(&fir_yaw, mpu_6050_get_gyro_z_cal());

	float rollx = mpu_6050_get_angle_roll(ay_mps2, ax_mps2, az_mps2);
	float pitchy = mpu_6050_get_angle_pitch(ax_mps2, ay_mps2, az_mps2);

	//	angle.angle_roll = kalman_filter_get_angle_roll(ax_mps2, rollx);
	//	angle.angle_pitch = kalman_filter_get_angle_pitch(ay_mps2, pitchy);
	angle.angle_roll = comp_filter_get_roll(rollx, gyro.x_rps);
	angle.angle_pitch = comp_filter_get_pitch(pitchy, gyro.y_rps);

	// Outer PID Loop **********************************************************
	setpoint.DesiredAngleRoll = transformation(get_ch1(), 0.05); // +- 50 degrees
	setpoint.DesiredAnglePitch = transformation(get_ch2(), -0.05); // +- 50 degrees
	input.throttle = (float)get_ch3();
	setpoint.desired_rate_yaw = transformation(get_ch4(), 0.15); // +- 75 degrees

//	printf("angle.k_angle_roll: %f, angle.k_angle_pitch: %f, ", angle.angle_roll, angle.angle_pitch);
//	printf("setpoint.DesiredAngleRoll: %f, setpoint.DesiredAnglePitch: %f\n\r", setpoint.DesiredAngleRoll, setpoint.DesiredAnglePitch);

	pid_controller_update(&pid_roll_angle, setpoint.DesiredAngleRoll, angle.angle_roll);
	pid_controller_update(&pid_pitch_angle, setpoint.DesiredAnglePitch, angle.angle_pitch);

	// Inner PID Loop **********************************************************
	setpoint.desired_rate_roll = pid_roll_angle.out;
	setpoint.desired_rate_pitch = pid_pitch_angle.out;

//	printf("%f, %f\n\r", pid_pitch_angle.out, setpoint.DesiredAnglePitch);

	pid_controller_update(&pid_roll, setpoint.desired_rate_roll, gyro.x_rps);
	pid_controller_update(&pid_pitch, setpoint.desired_rate_pitch, gyro.y_rps);
	pid_controller_update(&pid_yaw, setpoint.desired_rate_yaw, gyro.z_rps);

	// PID Out **********************************************************
	input.roll = pid_roll.out;
	input.pitch = pid_pitch.out;
	input.yaw = pid_yaw.out;

	motor_update(input, motor);

//	printf("diff: %lu\n\r", scu_timer_get_curr_micros()-loop_start);
	while(scu_timer_get_curr_micros()-loop_start < 4000);
}


void pid_single_loop_rate() {
	loop_start = scu_timer_get_curr_micros();

//	printf("pid_pitch_angle.Kp: %.2f, pid_pitch.Ki: %.2f, pid_pitch.Kd: %.2f\n\r", pid_pitch.Kp, pid_pitch.Ki, pid_pitch.Kd);

	gyro.x_rps = mpu_6050_get_gyro_x_cal(); // x
	gyro.y_rps = mpu_6050_get_gyro_y_cal(); // y
	gyro.z_rps = mpu_6050_get_gyro_z_cal();

//	gyro.x_rps = FIRFilter_Update(&fir_roll, mpu_6050_get_gyro_x_cal());
//	gyro.y_rps = FIRFilter_Update(&fir_pitch, mpu_6050_get_gyro_y_cal());
//	gyro.z_rps = FIRFilter_Update(&fir_yaw, mpu_6050_get_gyro_z_cal());

	printf("Gx: %f, \t Gy: %f \n\r", gyro.x_rps, gyro.y_rps);

	setpoint.desired_rate_roll = transformation(get_ch1(), 0.05); // +- 50 degrees
	setpoint.desired_rate_pitch = transformation(get_ch2(), -0.05); // +- 50 degrees
	input.throttle = (float)get_ch3();
	setpoint.desired_rate_yaw = transformation(get_ch4(), 0.15); // +- 75 degrees

	printf("Sx: %f,\t Sy: %f\n\r", setpoint.desired_rate_roll , setpoint.desired_rate_pitch);

	pid_controller_update(&pid_roll, setpoint.desired_rate_roll, gyro.x_rps);
	pid_controller_update(&pid_pitch, setpoint.desired_rate_pitch, gyro.y_rps);
	pid_controller_update(&pid_yaw, setpoint.desired_rate_yaw, gyro.z_rps);


//	printf("%f,%f\n\r", pid_pitch.out, setpoint.desired_rate_pitch);

	// PID Out
	input.roll = pid_roll.out;
	input.pitch = pid_pitch.out;
	input.yaw = pid_yaw.out;

	motor_update(input, motor);

//	printf("diff: %lu\n\r", scu_timer_get_curr_micros()-loop_start);
	while(scu_timer_get_curr_micros()-loop_start < 4000);
}

void motor_update(Input input, Motor motor) {

	// limit throttle to 1800
	if (input.throttle > MOTOR_MAX_THROTTLE) input.throttle = MOTOR_MAX_THROTTLE;

	// motor linear equation
	float scale_factor1 = 1.0f;
	float scale_factor2 = 1.0f;
	float scale_factor3 = 1.0f;
	float scale_factor4 = 1.0f;
	motor.pwm_out1 = (int)(scale_factor1 * (input.throttle - input.pitch - input.roll - input.yaw));
	motor.pwm_out2 = (int)(scale_factor2 * (input.throttle + input.pitch - input.roll + input.yaw));
	motor.pwm_out3 = (int)(scale_factor3 * (input.throttle + input.pitch + input.roll - input.yaw));
	motor.pwm_out4 = (int)(scale_factor4 * (input.throttle - input.pitch + input.roll + input.yaw));

	// limit pwm signal
	if (motor.pwm_out1 > MOTOR_MAX_PWM_2000US) motor.pwm_out1 = MOTOR_MAX_PWM_LIMIT;
	if (motor.pwm_out2 > MOTOR_MAX_PWM_2000US) motor.pwm_out2 = MOTOR_MAX_PWM_LIMIT;
	if (motor.pwm_out3 > MOTOR_MAX_PWM_2000US) motor.pwm_out3 = MOTOR_MAX_PWM_LIMIT;
	if (motor.pwm_out4 > MOTOR_MAX_PWM_2000US) motor.pwm_out4 = MOTOR_MAX_PWM_LIMIT;

	// set idle throttle
	if (motor.pwm_out1 < MOTOR_THROTTLE_IDLE_MIN) motor.pwm_out1 = MOTOR_THROTTLE_IDLE_MIN;
	if (motor.pwm_out2 < MOTOR_THROTTLE_IDLE_MIN) motor.pwm_out2 = MOTOR_THROTTLE_IDLE_MIN;
	if (motor.pwm_out3 < MOTOR_THROTTLE_IDLE_MIN) motor.pwm_out3 = MOTOR_THROTTLE_IDLE_MIN;
	if (motor.pwm_out4 < MOTOR_THROTTLE_IDLE_MIN) motor.pwm_out4 = MOTOR_THROTTLE_IDLE_MIN;

	// update pwm signal == motor speed
	pwm_update_pwm1(motor.pwm_out1);
	pwm_update_pwm2(motor.pwm_out2);
	pwm_update_pwm3(motor.pwm_out3);
	pwm_update_pwm4(motor.pwm_out4);
}



float transformation(u32 channel_pwm, float coef)
{
	float ch_pwm = (float)channel_pwm;
	float result = coef * (ch_pwm - 1500);
	return result;
}

void pid_reset()
{
	pid_controller_init(&pid_roll_angle);
	pid_controller_init(&pid_pitch_angle);
	pid_controller_init(&pid_roll);
	pid_controller_init(&pid_pitch);
	pid_controller_init(&pid_yaw);
}


void pid_controller_init(PIDController *pid) {

	// Clear controller variables
	pid->integrator = 0.0f;
	pid->prevError  = 0.0f;

	pid->differentiator  = 0.0f;
	pid->prevMeasurement = 0.0f;

	pid->out = 0.0f;

}

float pid_controller_update(PIDController *pid, float setpoint, float measurement) {

	//	Error signal
    float error = setpoint - measurement;

    // Proportional
    float proportional = pid->Kp * error;

    // Integral
    pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);

    // Anti-wind-up via integrator clamping
    if (pid->integrator > pid->limMaxInt) {
        pid->integrator = pid->limMaxInt;
    } else if (pid->integrator < pid->limMinInt) {
        pid->integrator = pid->limMinInt;
    }

    // Derivative (band-limited differentiator)
    pid->differentiator = -(2.0f * pid->Kd * (measurement - pid->prevMeasurement)	// Initialize PID controllerNote: derivative on measurement, therefore minus sign in front of equation!
                        + (2.0f * pid->tau - pid->T) * pid->differentiator)
                        / (2.0f * pid->tau + pid->T);


    // Compute output and apply limits
    pid->out = proportional + pid->integrator + pid->differentiator;
    if (pid->out > pid->limMax) {
        pid->out = pid->limMax;
    } else if (pid->out < pid->limMin) {
        pid->out = pid->limMin;
    }

    // Store error and measurement for later use
    pid->prevError       = error;
    pid->prevMeasurement = measurement;

	// Return controller output
    return pid->out;
}

// Function to map a value from one range to another
float pid_map_range(float input_value, float in_min, float in_max, float out_min, float out_max) {
	float result = (input_value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return result;
}

