from itertools import count
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

file_name = 'filter-vs-non-filter-imu3'
file_path = '../csv/' + file_name + '.csv'

plt.style.use('fivethirtyeight')

fig, ax = plt.subplots()
line1, = ax.plot([], [], label='Live Data', linewidth=0.5, alpha=0.7)
line2, = ax.plot([], [], label='Set Point', linewidth=0.5, alpha=0.7)

def animate(i, x, y1, y2):
    line1.set_data(x, y1)
    line2.set_data(x, y2)
    
    ax.set_xlim(x.min(), x.max())  # Adjust x-axis limits based on data
    ax.set_ylim(min(y1.min(), y2.min()), max(y1.max(), y2.max()))  # Adjust y-axis limits based on data

def init():
    return line1, line2

def get_data():
    data = pd.read_csv(file_path)
    x = data['time']
    y1 = data['y1']
    y2 = data['y2']
    return x, y1, y2

def update(frame):
    x, y1, y2 = get_data()
    animate(frame, x, y1, y2)
    return line1, line2

ani = FuncAnimation(fig, update, frames=None, init_func=init, blit=True, interval=1000)

plt.legend()
plt.tight_layout()
plt.show()
