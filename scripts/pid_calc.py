#/ pid nichols ziegler tuning method calculator
print('Nichols Ziegler PID Tuning Method Calculator\n')
kmax = 5
t_o = 0.130

kp = 0.6*kmax
ki = 2.0*t_o
kd = 0.125/t_o

# PID controller
print('PID controller')
print(kp)
print(ki)
print(kd)

print('\n')

# PI controller, where D = 0 
print('PI controller')
kpp = 0.45*kmax
print(kpp)
print(ki)
print(0)