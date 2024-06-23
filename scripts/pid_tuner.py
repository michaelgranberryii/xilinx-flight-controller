import tkinter as tk
from tkinter import ttk

gui_title = 'Slider PID GUI'
kp_label = 'Kp'
ki_label = 'Ki'
kd_label = 'Kd'
slider_orient = 'vertical'
slider_length = 200  # Set the desired length of the sliders
slider_step = 0.01  # Set the desired step size for the sliders
stepper_min = 0.0
stepper_max = 5.0

def round_to_step(value, step):
    res = round(value / step) * step
    return round(res,2)

def update_label(event=None):
    value1 = round_to_step(slider1.get(), slider_step)
    value2 = round_to_step(slider2.get(), slider_step)
    value3 = round_to_step(slider3.get(), slider_step)
    label.config(text=f"{kp_label}: {value1}, {ki_label}: {value2}, {kd_label}: {value3}")
    print(f"{kp_label}: {value1}, {ki_label}: {value2}, {kd_label}: {value3}")

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

root = tk.Tk()
root.title(gui_title)

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

update_label()

root.mainloop()

