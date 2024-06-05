import serial
import time
from pynput.keyboard import Controller

# Replace 'COM8' with the appropriate port for your Arduino
ser = serial.Serial('COM8', 9600)
keyboard = Controller()

def press_keys(keys):
    for key in keys:
        keyboard.press(key)
    time.sleep(0.1)
    for key in keys:
        keyboard.release(key)

try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            if line:
                press_keys(line)
except KeyboardInterrupt:
    ser.close()
