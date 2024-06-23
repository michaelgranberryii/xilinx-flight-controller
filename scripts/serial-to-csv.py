# import csv
# import random
# import time
# import serial as sr
# import datetime as dt

# s = sr.Serial('/dev/ttyUSB1', 115200)

# x_value = 0
# total_1 = 1000
# total_2 = 1000

# fieldnames = ["time", "y1", "y2"]

# file_name = 'filter-vs-non-filter-imu3'
# csv_file_path = '../csv/' + file_name + '.csv'

# # Record the start time
# start_time = time.time()

# with open(csv_file_path, 'w') as csv_file:
#     csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
#     csv_writer.writeheader()

# while True:
#     # Calculate the elapsed time since the program started
#     elapsed_time = time.time() - start_time
#     # Convert elapsed time to milliseconds
#     elapsed_time_millis = int(elapsed_time * 1000)

#     with open(csv_file_path, 'a') as csv_file:
#         csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)

#         line = s.readline().decode().strip()
#         parts = line.split(',')
#         t = elapsed_time_millis

#         # t = dt.datetime.now().strftime('%H:%M:%S.%f')[:-3]  # Extract milliseconds and omit microseconds

#         try:
#             info = {
#                 "time": t,
#                 "y1": parts[0],
#                 "y2": parts[1]
#             }
#             csv_writer.writerow(info)
#             print(t, parts[0], parts[1])

#         except:
#             pass

#     time.sleep(0.004)

import csv
import random
import time
import serial as sr
import datetime as dt

s = sr.Serial('/dev/ttyUSB1', 115200)

x_value = 0
total_1 = 1000
total_2 = 1000

fieldnames = ["time", "y1", "y2"]

file_name = 'pid-0'
csv_file_path = '../csv/' + file_name + '.csv'

# Record the start time
start_time = time.time()

with open(csv_file_path, 'w') as csv_file:
    csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
    csv_writer.writeheader()

while True:
    # Calculate the elapsed time since the program started
    elapsed_time = time.time() - start_time
    # Convert elapsed time to milliseconds
    elapsed_time_millis = int(elapsed_time * 1000)

    with open(csv_file_path, 'a') as csv_file:
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)

        line = s.readline().decode().strip()
        parts = line.split(',')
        t = elapsed_time_millis

        try:
            # Check if there are enough elements in parts
            if len(parts) >= 2:
                # Parse the first floating-point number
                y1 = float(parts[0])

                # Parse the second floating-point number
                y2 = float(parts[1])

                info = {
                    "time": t,
                    "y1": y1,
                    "y2": y2
                }
                csv_writer.writerow(info)
                print(t, y1, y2)

        except ValueError:
            # print("Invalid input:", line)
            pass

    time.sleep(0.004)
