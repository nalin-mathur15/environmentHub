# Arduino Environment Hub

A compact Arduino-based project that monitors temperature and humidity, logs data to EEPROM for offline storage for weekly analysis, and saves power by using a motion detector system for the display.

## Features

- Temperature & humidity readings with DHT11 sensor
- Data logging to EEPROM every hour
- Power-saving mode using IR + Ultrasonic motion detection
- Up to 7 days of offline storage in internal EEPROM
- Data export over serial in CSV format
- Ideal for weather forecasting via machine learning

## Hardware Used

| Component              | Description                       |
|------------------------|-----------------------------------|
| Arduino Uno R3         | Microcontroller board             |
| DHT11                  | Temp & humidity sensor            |
| LCD1602                | Displays environment data         |
| IR Sensor              | Detects human presence via infrared     |
| Ultrasonic Sensor (HC-SR04) | Detects human presence via distance sensing |
| EEPROM (internal)      | Used for hourly data logging      |

## Pin Mapping

| Component         | Arduino Pin |
|------------------|-------------|
| DHT11             | D8          |
| LCD RS, E, D4–D7  | D2–D7       |
| IR Sensor         | D9          |
| Ultrasonic Trig   | D10         |
| Ultrasonic Echo   | D11         |

##  EEPROM Storage Format

Each reading uses **3 bytes**:
\[hour_index, temp, humidity\]
- Address `0`: pointer to next write location
- Up to 170 readings (~1 week of hourly data)

## Power Saving

- LCD turns off after **30 minutes** of no presence
- Wakes up as soon as **either IR or ultrasonic** detects presence

## Future Improvements
- Combine with something like a Raspberry Pi for temperature prediction and home automation (turn on the air conditioner, etc.)
- Add real-time clock (RTC) for timestamps
- Include brightness sensor, air quality sensor, etc.
