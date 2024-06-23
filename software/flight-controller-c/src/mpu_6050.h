/**
 * @file axi_iic_imu.h
 * @brief Source code for the MPU_6050 driver. Updated for Zybo Z7.
 *
 * This file contains the function definitions for the MPU_6050 driver.
 * It interfaces with the MPU-6050 6-DoF Accelerometer and Gyroscope Sensor module, which uses the I2C communication protocol.
 *  - Product Link: https://www.adafruit.com/product/3886
 *  - Datasheet: http://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
 *  - Register Map: https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *
 *
 * @author Michael Granberry
 *
 */

#ifndef MPU_6050   /* prevent circular inclusions */
#define MPU_6050

#include <stdio.h>
#include "math.h"
#include "platform.h"
#include "xiic.h"
#include "xil_printf.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "xparameters.h"
#include "iic.h"
#include "sleep.h"

// Default I2C address for the MPU-6050
#define MPU_6050_ADDRESS                        0x68

// Register Bit Position Values
#define MPU_REG_SET_BIT_0                       0x01
#define MPU_REG_SET_BIT_1                       0x02
#define MPU_REG_SET_BIT_2                       0x04
#define MPU_REG_SET_BIT_3                       0x08
#define MPU_REG_SET_BIT_4                       0x10
#define MPU_REG_SET_BIT_5                       0x20
#define MPU_REG_SET_BIT_6                       0x40
#define MPU_REG_SET_BIT_7                       0x80

// Clock Source Select Values (CLKSEL[2:0], PWR_MGMT_1 Register)
#define CLKSEL_PLL_INTERNAL_8_MHZ               0x00
#define CLKSEL_PLL_X_AXIS_GYRO_REFERENCE        0x01
#define CLKSEL_PLL_Y_AXIS_GYRO_REFERENCE        0x02
#define CLKSEL_PLL_Z_AXIS_GYRO_REFERENCE        0x03
#define CLKSEL_PLL_EXTERNAL_32_768_KHZ          0x04
#define CLKSEL_PLL_EXTERNAL_19_2_MHZ            0x05
#define CLKSEL_PLL_RESERVED                     0x06
#define CLKSEL_STOP_CLK                         0x07

// Digital Low-Pass Filter Bandwidth Select Values (DLPF_CFG[2:0], CONFIG Register)
#define MPU_6050_DLPF_CFG_BANDWIDTH_260_HZ      0x00
#define MPU_6050_DLPF_CFG_BANDWIDTH_184_HZ      0x01
#define MPU_6050_DLPF_CFG_BANDWIDTH_94_HZ       0x02
#define MPU_6050_DLPF_CFG_BANDWIDTH_44_HZ       0x03
#define MPU_6050_DLPF_CFG_BANDWIDTH_21_HZ       0x04
#define MPU_6050_DLPF_CFG_BANDWIDTH_10_HZ       0x05
#define MPU_6050_DLPF_CFG_BANDWIDTH_5_HZ        0x06
#define MPU_6050_DLPF_CFG_RESERVED              0x07

// Accelerometer Range Select Values (AFS_SEL[1:0], ACCEL_CONFIG Register)
#define MPU_6050_ACCEL_RANGE_2_G                (0x00)
#define MPU_6050_ACCEL_RANGE_4_G                (0x01 << 3)
#define MPU_6050_ACCEL_RANGE_8_G                (0x02 << 3)
#define MPU_6050_ACCEL_RANGE_16_G               (0x03 << 3)

// Gyroscope Range Select Values (FS_SEL[1:0], GYRO_CONFIG Register)
#define MPU_6050_GYRO_RANGE_250_DEG             (0x00)
#define MPU_6050_GYRO_RANGE_500_DEG             (0x01 << 3)
#define MPU_6050_GYRO_RANGE_1000_DEG            (0x02 << 3)
#define MPU_6050_GYRO_RANGE_2000_DEG            (0x03 << 3)

// Register Address Definitions
#define MPU_6050_SMPRT_DIV                      0x19
#define MPU_6050_CONFIG                         0x1A
#define MPU_6050_GYRO_CONFIG                    0x1B
#define MPU_6050_ACCEL_CONFIG                   0x1C
#define MPU_6050_SIGNAL_PATH_RESET              0x68
#define MPU_6050_PWR_MGMT_1                     0x6B
#define MPU_6050_WHO_AM_I                       0x75

#define MPU_6050_ACCEL_XOUT_H                   0x3B
#define MPU_6050_ACCEL_XOUT_L                   0x3C
#define MPU_6050_ACCEL_YOUT_H                   0x3D
#define MPU_6050_ACCEL_YOUT_L                   0x3E
#define MPU_6050_ACCEL_ZOUT_H                   0x3F
#define MPU_6050_ACCEL_ZOUT_L                   0x40

#define MPU_6050_GYRO_XOUT_H                    0x43
#define MPU_6050_GYRO_XOUT_L                    0x44
#define MPU_6050_GYRO_YOUT_H                    0x45
#define MPU_6050_GYRO_YOUT_L                    0x46
#define MPU_6050_GYRO_ZOUT_H                    0x47
#define MPU_6050_GYRO_ZOUT_L                    0x48

#define I2C_MST_CTRL							0x24

#define ONE_HUNDRED_mSec                    			(1000*100)

typedef struct AccCal {
	float x, y, z;
} AccCal;

typedef struct GyroCal {
	float x, y, z;
} GyroCal;

typedef struct MpuOut {
	float gx, gy, gz;
	float ax, ay, az;
	float rollx, pitchy;
} MpuOut;

void mpu_6050_init();
void mpu_6050_whoami();
void mpu_6050_setup();
void mpu_6050_print_results();
MpuOut mpu_6050_read_measurement();
void mpu_acceleration_calibration();
void mpu_gyroscope_calibration();
void mpu_6050_reset();
void mpu_6050_set_clock_source(u8 clock_source_select);
void mpu_6050_set_sample_rate_divider(uint8_t sample_rate_divider);
void mpu_6050_set_dlpf_bandwidth(uint8_t dlpf_cfg);
void mpu_6050_set_sensitiviy_scale(uint8_t gyroscope_range);

// Angles
float mpu_6050_get_angle_roll(float ay, float ax, float az);
float mpu_6050_get_angle_pitch(float ax, float ay, float az);

// Acc
void mpu_6050_set_accelerometer_range(uint8_t accelerometer_range);
int mpu_6050_get_accelerometer_scale(uint8_t accelerometer_range);
u8 mpu_6050_get_accelerometer_range();
uint8_t mpu_6050_get_accel_x_high_byte();
uint8_t mpu_6050_get_accel_x_low_byte();
uint8_t mpu_6050_get_accel_y_high_byte();
uint8_t mpu_6050_get_accel_y_low_byte();
uint8_t mpu_6050_get_accel_z_high_byte();
uint8_t mpu_6050_get_accel_z_low_byte();

int16_t* mpu_6050_get_raw_xyz_acceleration();
float* mpu_6050_get_adjusted_xyz_acceleration();

float mpu_6050_get_accel_x_cal();
float mpu_6050_get_accel_y_cal();
float mpu_6050_get_accel_z_cal();

// Gyro
uint8_t mpu_6050_get_gyroscope_range();
void mpu_6050_set_gyroscope_range(uint8_t gyroscope_range);
float mpu_6050_get_gyroscope_scale(uint8_t gyroscope_range);
float* mpu_6050_get_adjusted_xyz_gyroscope();
int16_t* mpu_6050_get_raw_xyz_gyroscope();

uint8_t mpu_6050_get_gyro_x_high_byte();
uint8_t mpu_6050_get_gyro_x_low_byte();
uint8_t mpu_6050_get_gyro_y_high_byte();
uint8_t mpu_6050_get_gyro_y_low_byte();
uint8_t mpu_6050_get_gyro_z_high_byte();
uint8_t mpu_6050_get_gyro_z_low_byte();

float mpu_6050_get_gyro_x_cal();
float mpu_6050_get_gyro_y_cal();
float mpu_6050_get_gyro_z_cal();

#endif  /* end of protection macro */
