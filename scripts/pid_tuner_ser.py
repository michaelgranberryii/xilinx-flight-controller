# https://www.youtube.com/watch?v=CB1E4Ir3AV4

# 1. sudo killall rfcomm
# 2. Connected /dev/rfcomm0 to 98:D3:02:96:6E:D4 on channel 1

import tkinter as tk
from tkinter import ttk
import serial
import os

gui_title = 'Slider PID GUI'
kp_label = 'Kp'
ki_label = 'Ki'
kd_label = 'kd'
slider_orient = 'vertical'
slider_length = 200  # Set the desired length of the sliders
slider_step = 0.01  # Set the desired step size for the sliders
stepper_min = 0.00
stepper_max = 5.00


# os.system('sudo rfcomm bind rfcomm0 98:D3:02:96:6E:D4')
# BTserialChannel = serial.Serial("/dev/rfcomm0", baudrate=115200)

# sudo chmod u+rwx /dev/rfcomm0
# Serial port settings
serial_port = "/dev/rfcomm0"  # Change this to the appropriate serial port
baud_rate = 38400

# Initialize serial port
ser = None

def open_serial_port():
    global ser
    try:
        os.system('sudo rfcomm bind rfcomm0 98:D3:02:96:6E:D4')
    except:
        pass
    ser = serial.Serial(serial_port, baud_rate)

def close_serial_port():
    if ser and ser.isOpen():
        ser.close()

def round_to_step(value, step):
    res = round(value / step) * step
    return round(res, 2)

def update_label(event=None):
    value1 = round_to_step(slider1.get(), slider_step)
    value2 = round_to_step(slider2.get(), slider_step)
    value3 = round_to_step(slider3.get(), slider_step)
    formatted_string = "{:.2f},{:.2f},{:.2f}".format(value1, value2, value3)
    # label.config(text=f"{kp_label}: {value1}, {ki_label}: {value2}, {kd_label}: {value3}")
    label.config(text=formatted_string)
    # Output slider values to serial port
    if ser and ser.isOpen():
        # Format values to two decimal places
        

        # Encode and write to serial port
        ser.write(formatted_string.encode())
        # ser.write(f"{value1},{value2},{value3}".encode())
        # BTserialChannel.write(f"{value1}, {value2}, {value3}\n".encode())
    
    # print(f"{kp_label}: {value1}, {ki_label}: {value2}, {kd_label}: {value3}")

def increase_slider1():
    current_value = slider1.get()
    if current_value + slider_step <= stepper_max:
        slider1.set(current_value + slider_step)
        update_label()

def decrease_slider1():
    current_value = slider1.get()
    if current_value - slider_step >= stepper_min:
        slider1.set(current_value - slider_step)
        update_label()

def increase_slider2():
    current_value = slider2.get()
    if current_value + slider_step <= stepper_max:
        slider2.set(current_value + slider_step)
        update_label()

def decrease_slider2():
    current_value = slider2.get()
    if current_value - slider_step >= stepper_min:
        slider2.set(current_value - slider_step)
        update_label()

def increase_slider3():
    current_value = slider3.get()
    if current_value + slider_step <= stepper_max:
        slider3.set(current_value + slider_step)
        update_label()

def decrease_slider3():
    current_value = slider3.get()
    if current_value - slider_step >= stepper_min:
        slider3.set(current_value - slider_step)
        update_label()

def on_closing():
    close_serial_port()
    root.destroy()

def key(event):
    if event.char == 'q':
        on_closing()

root = tk.Tk()
root.title(gui_title)
root.bind('<Key>', key)

slider_frame = ttk.Frame(root)
slider_frame.pack(padx=20, pady=20)

slider1 = ttk.Scale(slider_frame, from_=stepper_max, to=stepper_min, orient=slider_orient, command=update_label, length=slider_length)
slider1.grid(row=0, column=0, padx=10)

slider2 = ttk.Scale(slider_frame, from_=stepper_max, to=stepper_min, orient=slider_orient, command=update_label, length=slider_length)
slider2.grid(row=0, column=1, padx=10)

slider3 = ttk.Scale(slider_frame, from_=stepper_max, to=stepper_min, orient=slider_orient, command=update_label, length=slider_length)
slider3.grid(row=0, column=2, padx=10)

button_frame = ttk.Frame(root)
button_frame.pack(pady=5)

increase_button1 = ttk.Button(button_frame, text="▲", command=increase_slider1)
increase_button1.grid(row=0, column=0)

decrease_button1 = ttk.Button(button_frame, text="▼", command=decrease_slider1)
decrease_button1.grid(row=1, column=0)

increase_button2 = ttk.Button(button_frame, text="▲", command=increase_slider2)
increase_button2.grid(row=0, column=1)

decrease_button2 = ttk.Button(button_frame, text="▼", command=decrease_slider2)
decrease_button2.grid(row=1, column=1)

increase_button3 = ttk.Button(button_frame, text="▲", command=increase_slider3)
increase_button3.grid(row=0, column=2)

decrease_button3 = ttk.Button(button_frame, text="▼", command=decrease_slider3)
decrease_button3.grid(row=1, column=2)

label = ttk.Label(root, text="")
label.pack()

open_serial_port()  # Open serial port when the program starts

root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()

