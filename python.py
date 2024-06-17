import serial
import time
from pynput.keyboard import Controller as KeyboardController
from pynput.mouse import Button, Controller as MouseController

#Please change COM8 to your appropriate serial port
ser = serial.Serial('COM8', 9600)
keyboard = KeyboardController()
mouse = MouseController()

# Adjust mouse sensitivity as needed
mouse_sensitivity = 3

def press_keys(keys):
    for key in keys:
        if key == 'R':
            mouse.click(Button.right, 1)
        elif key == 'L':
            mouse.click(Button.left, 1) 
        elif key == 'i':
            mouse.move(0, -10 * mouse_sensitivity)
        elif key == 'j':
            mouse.move(-10 * mouse_sensitivity, 0)
        elif key == 'k':
            mouse.move(0, 10 * mouse_sensitivity)
        elif key == 'l':
            mouse.move(10 * mouse_sensitivity, 0)
        else:
            keyboard.press(key)

    time.sleep(0.1) 

    for key in keys:
        if key not in ('R', 'L', 'i', 'j', 'k', 'l'):
            keyboard.release(key)

try:
    buffer = ""
    while True:
        if ser.in_waiting > 0:
            buffer += ser.read(ser.in_waiting).decode('utf-8')
            while '\n' in buffer:
                line, buffer = buffer.split('\n', 1)
                line = line.rstrip()
                if line:
                    press_keys(line)
except KeyboardInterrupt:
    ser.close()
