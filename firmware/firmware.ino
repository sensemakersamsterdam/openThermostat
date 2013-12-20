// Open Thermostat software; written by Hans Crijns [cloudsensor.us]
//
// Graphincs based on: Adafruit_ST7735 > graphicstest_highspeed

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// tft display
#define cs       9
#define dc       8
#define rst      0  // Reset is hardcode; so used

#define tempPin  5  // temperature sensor DS18B20
#define upPin    6
#define downPin  7
#define heatPin  3  // Relay and LED

OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

int change = 1;
int heat = 0;
float temp, oldtemp, settemp;
char buffer[10];
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

void setup(void) {
  Serial.begin(9600);
  Serial.println("Open Thermostat v1\n");

  pinMode(upPin, INPUT);
  digitalWrite(upPin, HIGH);
  pinMode(downPin, INPUT);
  digitalWrite(downPin, HIGH);
  pinMode(heatPin, OUTPUT);

  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_WHITE);
  tft.setRotation(1);
  
  sensors.begin();
  if (!sensors.getAddress(insideThermometer, 0)) 
    Serial.println("Unable to find address for Device 0"); 
  sensors.requestTemperatures();
  temp = sensors.getTempC(insideThermometer);
  settemp = temp;

  delay(1000);
}

void loop() {
  readTemp();
  
  if (!digitalRead(upPin)) {
    settemp += 0.5;
    change = 1;
    delay(200);
  }
  if (!digitalRead(downPin)) {
    settemp -= 0.5;
    change = 1;
    delay(200);
  }

  if(change) {
    updateDisplay();
    change = 0;
  }

  if (temp < settemp) {
    heat = 1;
    heater();
    heat = 0;
    change = 1;
  }

  delay(100);
}

void updateDisplay(void) {
  drawtext("Open Thermostat", 30, 10, ST7735_RED, 1);
  drawtext("Current:", 25, 30, ST7735_BLACK, 1);
  drawtext("Set:", 105, 30, ST7735_BLACK, 1);

  String tempStr = dtostrf(temp, 3, 1, buffer);
  tft.fillRoundRect(20, 40, 60, 40, 5, ST7735_BLUE);
  drawtext(tempStr, 25, 50, ST7735_WHITE, 2);
  
  String settempStr = dtostrf(settemp, 3, 1, buffer);
  tft.fillRoundRect(90, 40, 60, 40, 5, ST7735_WHITE);
  tft.drawRoundRect(90, 40, 60, 40, 5, ST7735_BLUE);
  drawtext(settempStr, 98, 50, ST7735_BLUE, 2);
}

void readTemp(void) {
  sensors.requestTemperatures();
  temp = sensors.getTempC(insideThermometer);
  //temp = DallasTemperature::toFahrenheit(temp);    // Uncomment for Fahrenheit
  if (temp != oldtemp) {
    change = 1;
    oldtemp = temp;
  }
  
  Serial.print("Current: ");
  Serial.print(temp);
  Serial.print("; Set: ");
  Serial.println(settemp);
}

void heater(void) {
  Serial.println("Heater on");
  digitalWrite(heatPin, HIGH);
  delay(3000);
  digitalWrite(heatPin, LOW);
  settemp = temp;
}

void drawtext(String text, int x, int y, int color, int large) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(large);
  tft.print(text);
}
