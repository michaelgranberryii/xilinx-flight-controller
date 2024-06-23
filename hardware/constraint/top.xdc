# IIC
set_property IOSTANDARD LVCMOS33 [get_ports iic_imu_out_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports iic_imu_out_sda_io]

set_property PACKAGE_PIN U14 [get_ports iic_imu_out_scl_io]
set_property PACKAGE_PIN U15 [get_ports iic_imu_out_sda_io]

# Timers
set_property IOSTANDARD LVCMOS33 [get_ports capturetrig_ppm]
set_property IOSTANDARD LVCMOS33 [get_ports pwm_motor_out_1]
set_property IOSTANDARD LVCMOS33 [get_ports pwm_motor_out_2]
set_property IOSTANDARD LVCMOS33 [get_ports pwm_motor_out_3]
set_property IOSTANDARD LVCMOS33 [get_ports pwm_motor_out_4]

set_property PACKAGE_PIN V15 [get_ports capturetrig_ppm]
set_property PACKAGE_PIN W14 [get_ports pwm_motor_out_1]
set_property PACKAGE_PIN Y14 [get_ports pwm_motor_out_2]
set_property PACKAGE_PIN T12 [get_ports pwm_motor_out_3]
set_property PACKAGE_PIN U12 [get_ports pwm_motor_out_4]
