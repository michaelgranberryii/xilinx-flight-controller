# Another way to do it without clearing the Axis
from itertools import count
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

file_name = 'pid-0'
file_path = '../csv/' + file_name + '.csv'

plt.style.use('fivethirtyeight')

x_vals = []
y_vals = []

# plt.plot([], [], label='Live Data')
# plt.plot([], [], label='Set Point')

plt.plot([], [], label='Live Data', linewidth=0.5, alpha=0.7)
plt.plot([], [], label='Set Point', linewidth=0.5, alpha=0.7)


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
    ylim_low, ylim_high = ax.get_ylim()

    ax.set_xlim(x.max()/5, (x.max() + (x.max()/4)))
    

    y1max = y1.max()
    y2max = y2.max()
    current_ymax = y1max if (y1max > y2max) else y2max

    y1min = y1.min()
    y2min = y2.min()
    current_ymin = y1min if (y1min < y2min) else y2min

    # ax.set_ylim((current_ymin - 0), (current_ymax + 0))
    ax.set_ylim((-0.50), (0.50))

ani = FuncAnimation(plt.gcf(), animate, interval=4)

plt.legend()
plt.tight_layout()
plt.show()