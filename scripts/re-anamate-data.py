# Another way to do it without clearing the Axis
from itertools import count
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

file_name = 'filter-vs-non-filter-imu2'
file_path = '../csv/' + file_name + '.csv'

plt.style.use('fivethirtyeight')

def animate(i):
    data = pd.read_csv(file_path)
    x = data['time']
    y1 = data['y1']
    y2 = data['y2']

    ax = plt.gca()
    line1, line2 = ax.lines

    line1.set_data(x, y1)
    line2.set_data(x, y2)

    xlim_low, xlim_high = ax.get_xlim()
    ax.set_xlim(x.min(), x.max())

    y1max = y1.max()
    y2max = y2.max()
    current_ymax = max(y1max, y2max)

    y1min = y1.min()
    y2min = y2.min()
    current_ymin = min(y1min, y2min)

    ax.set_ylim(current_ymin - 0.1, current_ymax + 0.1)

fig, ax = plt.subplots()
line1, = ax.plot([], [], label='Live Data', linewidth=0.5, alpha=0.7)
line2, = ax.plot([], [], label='Set Point', linewidth=0.5, alpha=0.7)

ani = FuncAnimation(fig, animate, interval=4)

plt.legend()
plt.tight_layout()
plt.show()
