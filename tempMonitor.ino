#include <DHT11.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define DHTPIN   8
#define IRPIN    9
#define TRIGPIN  10
#define ECHOPIN  11

const unsigned long hour = 3600000UL;
const unsigned long lcdTimeout = 1800000UL;

unsigned long prevLogTime = 0;
unsigned long prevMotion = 0;
bool lcdOn = true;

DHT11         dht11(DHTPIN);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("set up...");
  pinMode(IRPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  prevLogTime = millis();
  prevMotion = millis();
  lcd.clear();
}

void loop() {
  checkMotion();

  if (lcdOn && millis() - prevMotion > lcdTimeout) {
    lcd.noDisplay();
    lcdOn = false;
  }

  if (!lcdOn && motionDetected()) {
    lcd.display();
    lcdOn = true;
    prevMotion = millis();
  }

  if (millis() - prevLogTime >= hour) {
    logData();
    prevLogTime = millis();
  }

  if (lcdOn) {
    int humid = 0;
    int temp = 0;
  
    int res = dht11.readTemperatureHumidity(temp, humid);

    if (res == 0) {
      lcd.setCursor(0,0);
      lcd.print("Temp: ");
      lcd.print(temp, 1);
      lcd.print((char)223);
      lcd.print("C");
      lcd.setCursor(0, 1);
      lcd.print("Humid: ");
      lcd.print(humid, 1);
      lcd.print("%");
    } else {
      Serial.println(DHT11::getErrorString(res));
    }
  }   
  
  delay(2000);
}

bool motionDetected() {
  bool irMotion = (digitalRead(IRPIN) == HIGH);
  
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  long duration = pulseIn(ECHOPIN, HIGH, 25000);
  int distance = duration * 0.034 / 2;

  bool usMotion = (distance > 0 && distance < 150); 
  return (irMotion || usMotion);
}

void checkMotion() {
  if (motionDetected()) {
    prevMotion = millis();
  }
}

void logData() {
  int temp = 0;
  int humid = 0;
  int res = dht11.readTemperatureHumidity(temp, humid); 
  if (res != 0) {
    Serial.println(DHT11::getErrorString(res));
    return;
  }

  byte hourIndex;
  byte tempByte = constrain(int(temp), 0, 255);
  byte humidByte = constrain(int(humid), 0, 100);
  byte addr = EEPROM.read(0);
  if (addr > 508) {
    Serial.println("EEPROM Full.");
    return;
  }
  hourIndex = (addr / 3);
  EEPROM.write(addr + 1, hourIndex);
  EEPROM.write(addr + 2, tempByte);
  EEPROM.write(addr + 3, humidByte);
  EEPROM.write(0, addr + 3);
  Serial.print("Logged at hour ");
  Serial.println(hourIndex);
}