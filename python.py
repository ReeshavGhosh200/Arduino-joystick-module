import serial
import time
from pynput.keyboard import Controller as KeyboardController, Key
from pynput.mouse import Controller as MouseController, Button

# Initialize serial connection
ser = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # Wait for the connection to establish

# Initialize keyboard and mouse controllers
keyboard = KeyboardController()
mouse = MouseController()

# Mapping for key presses
key_map = {
    'W': 'w',
    'A': 'a',
    'S': 's',
    'D': 'd',
    'R': 'right_click'
}

def press_key(key):
    keyboard.press(key)
    keyboard.release(key)

def right_click():
    mouse.click(Button.right, 1)

try:
    while True:
        if ser.in_waiting > 0:
            data = ser.read().decode('utf-8')
            if data in key_map:
                if key_map[data] == 'right_click':
                    right_click()
                else:
                    press_key(key_map[data])

except KeyboardInterrupt:
    print("Exiting...")
finally:
    ser.close()
