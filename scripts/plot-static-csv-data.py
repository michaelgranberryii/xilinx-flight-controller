import pandas as pd
import matplotlib.pyplot as plt

file_name = 'pid-0'
csv_file_path = '../csv/' + file_name + '.csv'

# Read the CSV file
data = pd.read_csv(csv_file_path)
x_label = data.columns[0]
y1_label = data.columns[1]
y2_label = data.columns[2]

# Extract data for x and y axis from the DataFrame
x = data[x_label]
y1 = data[y1_label]
y2 = data[y2_label]

# Plot the data for y1
plt.plot(x, y1, label=y1_label, linewidth=0.5, alpha=0.7)

# Plot the data for y2
plt.plot(x, y2, label=y2_label, linewidth=0.5, alpha=0.7)

plt.xlabel(x_label.capitalize())
plt.ylabel('Values'.capitalize())
plt.title('Plot of y1 and y2')
plt.legend()

# Show the plot
plt.show()
