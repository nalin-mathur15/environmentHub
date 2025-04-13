import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('eeprom_data.csv')
df = df.sort_values('hour').reset_index(drop=True)

maxHour = df['hour'].max()
numDays = (maxHour + 1) // 24
numHours = 24

Mtemp = np.full((numDays, numHours), np.nan)
Mhumid = np.full((numDays, numHours), np.nan)

for _, row in df.iterrows():
    hour = int(row['hour'])
    day = hour // 24
    hour_of_day = hour % 24
    if day < numDays:
        Mtemp[day][hour_of_day] = row['temp']
        Mhumid[day][hour_of_day] = row['humidity']

plt.figure(figsize=(12, 6))
for i in range(numDays):
    plt.plot(range(numHours), Mtemp[i], label=f"Day {i}", alpha=0.6)

avg_temp = np.nanmean(Mtemp, axis=0)
plt.plot(range(numHours), avg_temp, color='black', linewidth=3, label="Average")

plt.title("Temperature vs Hour of Day")
plt.xlabel("Hour of Day")
plt.ylabel("Temperature (°C)")
plt.grid(True)
plt.legend(title="Day", bbox_to_anchor=(1.05, 1), loc="upper left")
plt.tight_layout()
plt.show()

plt.figure(figsize=(12, 6))
for i in range(numDays):
    plt.plot(range(numHours), Mhumid[i], label=f"Day {i}", alpha=0.6)

avg_humidity = np.nanmean(Mhumid, axis=0)
plt.plot(range(numHours), avg_humidity, color='black', linewidth=3, label="Average")

plt.title("Humidity vs Hour of Day")
plt.xlabel("Hour of Day")
plt.ylabel("Humidity (%)")
plt.grid(True)
plt.legend(title="Day", bbox_to_anchor=(1.05, 1), loc="upper left")
plt.tight_layout()
plt.show()