import serial
import time

SERIAL_PORT = 'COM3'
BAUD_RATE = 9600
OUTPUT_FILE = 'eeprom_data.csv'

ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=5)
time.sleep(2)

ser.reset_input_buffer()

print(f'Downloading EEPROM Data from {SERIAL_PORT}')
lines = []
while True:
    try:
        line = ser.readline().decode('utf-8').strip()
        if line:
            print(line)
            lines.append(line)
        else:
            break
    except Exception as e:
        print(f'Error: {e}')
        break

with open(OUTPUT_FILE, 'w') as f:
    f.write('\n'.join(lines))

print(f'Data saved to {OUTPUT_FILE}')
ser.close()