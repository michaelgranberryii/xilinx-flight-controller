/**
 * @author Michael Granberry
*/

#ifndef PID   /* prevent circular inclusions */
#define PID

#include "xuartlite.h"
#include "xparameters.h"
#include "xil_printf.h"
#include "axi_timer_ppm_receiver.h"
#include "axi_timer_pwm_motor.h"
#include "scu_timer.h"
#include "mpu_6050.h"
#include "sleep.h"
#include "complementary_filter.h"
#include "fir.h"
#include "axi_timer_ppm_receiver.h"

#define KP_ROLL_ANGLE  2.0f
#define KI_ROLL_ANGLE  0.0f
#define KD_ROLL_ANGLE  0.0f

#define KP_PITCH_ANGLE  KP_ROLL_ANGLE
#define KI_PITCH_ANGLE  KI_ROLL_ANGLE
#define KD_PITCH_ANGLE  KD_ROLL_ANGLE

#define KP_ROLL  1.43f
#define KI_ROLL  3.15f
#define KD_ROLL  0.27f

#define KP_PITCH  KP_ROLL
#define KI_PITCH  KI_ROLL
#define KD_PITCH  KD_ROLL

#define KP_YAW  2.0f
#define KI_YAW  3.0f
#define KD_YAW  0.0f // D term is not needed for yaw.

// Low pass filter tau
#define PID_TAU 0.02f

// PID Limits
#define PID_LIM_MIN -400.0f
#define PID_LIM_MAX  400.0f

#define PID_LIM_MIN_INT -400.0f
#define PID_LIM_MAX_INT  400.0f

// PID sample rate
#define SAMPLE_TIME_PID 0.004f

// Maximum run-time of simulation
#define SIMULATION_TIME_MAX 4.0f


#define MOTOR_MAX_PWM_2000US 2000
#define MOTOR_MAX_PWM_LIMIT 1999
#define MOTOR_MAX_THROTTLE 1800


typedef struct PIDController {

	/* Controller gains */
	float Kp;
	float Ki;
	float Kd;

	/* Derivative low-pass filter time constant */
	float tau;

	/* Output limits */
	float limMin;
	float limMax;

	/* Integrator limits */
	float limMinInt;
	float limMaxInt;

	/* Sample time (in seconds) */
	float T;

	/* Controller "memory" */
	float integrator;
	float prevError;			/* Required for integrator */
	float differentiator;
	float prevMeasurement;		/* Required for differentiator */

	/* Controller output */
	float out;

} PIDController;

typedef struct Motor {

	int pwm_out1;
	int pwm_out2;
	int pwm_out3;
	int pwm_out4;

} Motor;

typedef struct Input {

	float roll;
	float pitch;
	float throttle;
	float yaw;

} Input;

typedef struct SetPoint {

	float DesiredAngleRoll;
	float DesiredAnglePitch;

	float desired_rate_roll;
	float desired_rate_pitch;
	float desired_rate_throttle;
	float desired_rate_yaw;

} SetPoint;

typedef struct Gyro {

	float x_rps;
	float y_rps;
	float z_rps;

} Gyro;

typedef struct Angle {

	float angle_roll;
	float angle_pitch;

} Angle;


void pid_dual_loop_stabilize();
void pid_single_loop_rate();
void pid_loop_outer();
float transformation(u32 channel, float coef);
void pid_reset();
void motor_update(Input input, Motor motor);
float pid_controller_update(PIDController *pid, float setpoint, float measurement);
void  pid_controller_init(PIDController *pid);


// Function to map a value from one range to another
float pid_map_range(float value, float in_min, float in_max, float out_min, float out_max);
#endif  /* end of protection macro */
