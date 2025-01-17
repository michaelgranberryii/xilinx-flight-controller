//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.1 (lin64) Build 3865809 Sun May  7 15:04:56 MDT 2023
//Date        : Sun Jun 23 12:19:27 2024
//Host        : mg running 64-bit Ubuntu 22.04.4 LTS
//Command     : generate_target subsystem_bd_wrapper.bd
//Design      : subsystem_bd_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module subsystem_bd_wrapper
   (DDR_addr,
    DDR_ba,
    DDR_cas_n,
    DDR_ck_n,
    DDR_ck_p,
    DDR_cke,
    DDR_cs_n,
    DDR_dm,
    DDR_dq,
    DDR_dqs_n,
    DDR_dqs_p,
    DDR_odt,
    DDR_ras_n,
    DDR_reset_n,
    DDR_we_n,
    FIXED_IO_ddr_vrn,
    FIXED_IO_ddr_vrp,
    FIXED_IO_mio,
    FIXED_IO_ps_clk,
    FIXED_IO_ps_porb,
    FIXED_IO_ps_srstb,
    capturetrig_ppm,
    iic_imu_out_scl_io,
    iic_imu_out_sda_io,
    pwm_motor_out_1,
    pwm_motor_out_2,
    pwm_motor_out_3,
    pwm_motor_out_4,
    rgb_led_tri_o);
  inout [14:0]DDR_addr;
  inout [2:0]DDR_ba;
  inout DDR_cas_n;
  inout DDR_ck_n;
  inout DDR_ck_p;
  inout DDR_cke;
  inout DDR_cs_n;
  inout [3:0]DDR_dm;
  inout [31:0]DDR_dq;
  inout [3:0]DDR_dqs_n;
  inout [3:0]DDR_dqs_p;
  inout DDR_odt;
  inout DDR_ras_n;
  inout DDR_reset_n;
  inout DDR_we_n;
  inout FIXED_IO_ddr_vrn;
  inout FIXED_IO_ddr_vrp;
  inout [53:0]FIXED_IO_mio;
  inout FIXED_IO_ps_clk;
  inout FIXED_IO_ps_porb;
  inout FIXED_IO_ps_srstb;
  input capturetrig_ppm;
  inout iic_imu_out_scl_io;
  inout iic_imu_out_sda_io;
  output pwm_motor_out_1;
  output pwm_motor_out_2;
  output pwm_motor_out_3;
  output pwm_motor_out_4;
  output [2:0]rgb_led_tri_o;

  wire [14:0]DDR_addr;
  wire [2:0]DDR_ba;
  wire DDR_cas_n;
  wire DDR_ck_n;
  wire DDR_ck_p;
  wire DDR_cke;
  wire DDR_cs_n;
  wire [3:0]DDR_dm;
  wire [31:0]DDR_dq;
  wire [3:0]DDR_dqs_n;
  wire [3:0]DDR_dqs_p;
  wire DDR_odt;
  wire DDR_ras_n;
  wire DDR_reset_n;
  wire DDR_we_n;
  wire FIXED_IO_ddr_vrn;
  wire FIXED_IO_ddr_vrp;
  wire [53:0]FIXED_IO_mio;
  wire FIXED_IO_ps_clk;
  wire FIXED_IO_ps_porb;
  wire FIXED_IO_ps_srstb;
  wire capturetrig_ppm;
  wire iic_imu_out_scl_i;
  wire iic_imu_out_scl_io;
  wire iic_imu_out_scl_o;
  wire iic_imu_out_scl_t;
  wire iic_imu_out_sda_i;
  wire iic_imu_out_sda_io;
  wire iic_imu_out_sda_o;
  wire iic_imu_out_sda_t;
  wire pwm_motor_out_1;
  wire pwm_motor_out_2;
  wire pwm_motor_out_3;
  wire pwm_motor_out_4;
  wire [2:0]rgb_led_tri_o;

  IOBUF iic_imu_out_scl_iobuf
       (.I(iic_imu_out_scl_o),
        .IO(iic_imu_out_scl_io),
        .O(iic_imu_out_scl_i),
        .T(iic_imu_out_scl_t));
  IOBUF iic_imu_out_sda_iobuf
       (.I(iic_imu_out_sda_o),
        .IO(iic_imu_out_sda_io),
        .O(iic_imu_out_sda_i),
        .T(iic_imu_out_sda_t));
  subsystem_bd subsystem_bd_i
       (.DDR_addr(DDR_addr),
        .DDR_ba(DDR_ba),
        .DDR_cas_n(DDR_cas_n),
        .DDR_ck_n(DDR_ck_n),
        .DDR_ck_p(DDR_ck_p),
        .DDR_cke(DDR_cke),
        .DDR_cs_n(DDR_cs_n),
        .DDR_dm(DDR_dm),
        .DDR_dq(DDR_dq),
        .DDR_dqs_n(DDR_dqs_n),
        .DDR_dqs_p(DDR_dqs_p),
        .DDR_odt(DDR_odt),
        .DDR_ras_n(DDR_ras_n),
        .DDR_reset_n(DDR_reset_n),
        .DDR_we_n(DDR_we_n),
        .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
        .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
        .FIXED_IO_mio(FIXED_IO_mio),
        .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
        .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
        .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb),
        .capturetrig_ppm(capturetrig_ppm),
        .iic_imu_out_scl_i(iic_imu_out_scl_i),
        .iic_imu_out_scl_o(iic_imu_out_scl_o),
        .iic_imu_out_scl_t(iic_imu_out_scl_t),
        .iic_imu_out_sda_i(iic_imu_out_sda_i),
        .iic_imu_out_sda_o(iic_imu_out_sda_o),
        .iic_imu_out_sda_t(iic_imu_out_sda_t),
        .pwm_motor_out_1(pwm_motor_out_1),
        .pwm_motor_out_2(pwm_motor_out_2),
        .pwm_motor_out_3(pwm_motor_out_3),
        .pwm_motor_out_4(pwm_motor_out_4),
        .rgb_led_tri_o(rgb_led_tri_o));
endmodule
