#!/bin/bash

# Run the first Python script in a new terminal window
echo "Running first Python script..."
gnome-terminal -- /bin/python3 serial-to-csv.py

# Run the second Python script in a new terminal window
echo "Running second Python script..."
gnome-terminal -- /bin/python3 plot-live-csv-data.py

# Run the third Python script in a new terminal window
echo "Running second Python script..."
# sudo chmod u+rwx /dev/rfcomm0
gnome-terminal -- /bin/python3 pid_tuner_ser.py

echo "All scripts executed."
