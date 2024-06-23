# import pandas as pd
# import numpy as np
# from scipy.fft import fft, fftfreq
# import matplotlib.pyplot as plt

# # Read CSV data
# file_name = 'filter-vs-non-filter-imu3'
# file_path = '../csv/' + file_name + '.csv'
# data = pd.read_csv(file_path)
# time_ms = data['time']
# noisy_signal = data['y1']

# # Convert time from milliseconds to seconds
# time_s = time_ms / 1000.0  # 1 millisecond = 0.001 seconds

# # Convert noisy_signal to NumPy array and remove NaN values
# noisy_signal = np.array(noisy_signal.dropna())

# # Perform FFT
# n = len(time_s)
# freq = fftfreq(n, time_s[1] - time_s[0])
# y_fft = fft(noisy_signal)
# y_fft_mag = np.abs(y_fft)

# # Plot spectrum
# plt.plot(freq[:n//2], y_fft_mag[:n//2])
# plt.xlabel('Frequency (Hz)')
# plt.ylabel('Magnitude')
# plt.title('Frequency Spectrum')
# plt.grid(True)
# plt.show()

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Load data from CSV file
file_name = 'pid-0'
file_path = '../csv/' + file_name + '.csv'

# Load the data into a DataFrame
data = pd.read_csv(file_path)

# Extract time and MPU data
time_ms = data['time'].values
mpu_data = data['y2'].values

# Calculate the sampling frequency (assuming evenly spaced time points)
sampling_interval_ms = time_ms[1] - time_ms[0]  # Interval between samples in milliseconds
sampling_freq = 1000 / sampling_interval_ms  # Sampling frequency in Hz

# Perform FFT
fft_result = np.fft.fft(mpu_data)
frequencies = np.fft.fftfreq(len(mpu_data), d=sampling_interval_ms / 1000)  # Convert sampling interval to seconds

# Plot FFT
plt.figure(figsize=(10, 6))
plt.plot(frequencies, np.abs(fft_result))
plt.title("FFT of MPU Data")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.show()
