import serial
import csv
from datetime import datetime

ser = serial.Serial('COM10', 9600, timeout=1)
ser.flush()

with open('dht_data.csv', 'w', newline='') as csvfile:
    fieldnames = ['Time', 'Humidity', 'Temperature', 'Timestamp']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            data = line.split(',')

            if len(data) == 3:
                humidity = data[0]
                temperature = data[1]
                timestamp = data[2]
                current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                print(f"Time: {current_time}, Humidity: {humidity}, Temperature: {temperature}")
                writer.writerow({'Time': current_time, 'Humidity': humidity, 'Temperature': temperature, 'Timestamp': timestamp})
