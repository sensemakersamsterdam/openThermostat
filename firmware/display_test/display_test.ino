// Based on: Adafruit_ST7735 > graphicstest_highspeed
// And: http://www.instructables.com/id/Arduino-Watch-Build-Instructions/

#include <Arduino.h>        // To ensure this compiles on OS X with Arduino 1.0.5 IDE
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

//#define sclk 13
//#define mosi 11
#define cs   9
#define dc   8
#define rst  0  // you can also connect this to the Arduino reset

#define slow_color ST7735_BLUE
#define med_color ST7735_BLUE
#define fast_color ST7735_RED
#define plate_color ST7735_WHITE
#define border_color ST7735_BLACK

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
float p = 3.1415926;
float sec = 0;
float usec = 0;
float minute = 0;
float uminute = 0;
float hour = 1;
float uhour = 0;

void setup(void) {
  Serial.begin(9600);
  Serial.print("ClockDemo CloudSensor v1");
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_WHITE);
  
  float clock_size = tft.width()/2.2;  //40.0;
  float x_clock = tft.width()/2;  //64.0; 
  float y_clock = tft.height()/2;  //64.0;
  
  tft.fillCircle(x_clock, y_clock, clock_size, border_color);
  tft.fillCircle(x_clock, y_clock, clock_size - 10, plate_color);
  
//  // large block of text
//  tft.fillScreen(ST7735_BLACK);
//  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST7735_WHITE);
//  delay(1000);
//
//  // tft print function!
//  tftPrintTest();
//  delay(4000);
}

void loop() {
  clockanalog(sec, usec, minute, uminute, hour, uhour);
  usec = sec; 
  sec++;
  if((int)sec%60 == 0) {
    uminute = minute;
    minute++;
    if((int)minute%60 == 0) {
      uhour = hour;
      hour++;
    }
  }
  delay(100);
  
}

void clockanalog(float sec, float usec, float minute, float uminute, float hour, float uhour) {
  
  float Pi = 3.14159;
  float clock_size = tft.width()/2.2;  //40.0;
  float x_clock = tft.width()/2;  //64.0; 
  float y_clock = tft.height()/2;  //64.0;
  
  tft.drawLine(x_clock, y_clock, x_clock + 0.6 * clock_size  * sin(Pi * (float(uminute)/60.0 + float(uhour))/6.0), y_clock - 0.6 * clock_size * cos(Pi * (float(uminute)/60.0 + float(uhour))/6.0), plate_color);
  tft.drawLine(x_clock, y_clock, x_clock + 0.8 * clock_size * sin(Pi * float(uminute)/30.0), y_clock - 0.8 * clock_size * cos(Pi * float(uminute)/30.0), plate_color);
  tft.drawLine(x_clock, y_clock, x_clock + 0.8 * clock_size * sin(Pi * float(usec)/30.0), y_clock - 0.8 * clock_size * cos(Pi * float(usec)/30.0), plate_color);
  tft.drawLine(x_clock, y_clock, x_clock + 0.6 * clock_size  * sin(Pi * (float(minute)/60.0 + float(hour))/6.0), y_clock - 0.6 * clock_size * cos(Pi * (float(minute)/60.0 + float(hour))/6.0), slow_color);
  tft.drawLine(x_clock, y_clock, x_clock + 0.8 * clock_size * sin(Pi * float(minute)/30.0), y_clock - 0.8 * clock_size * cos(Pi * float(minute)/30.0), med_color);
  tft.drawLine(x_clock, y_clock, x_clock + 0.8 * clock_size * sin(Pi * float(sec)/30.0), y_clock - 0.8 * clock_size * cos(Pi * float(sec)/30.0), fast_color);
  for(int i = 1; i < 13; i++)
  {
    tft.drawLine(x_clock + 0.9 * clock_size * sin(Pi * float(i)/6.0), y_clock - 0.9 * clock_size * cos(Pi * float(i)/6.0), x_clock + clock_size * sin(Pi * float(i)/6.0), y_clock - clock_size * cos(Pi * float(i)/6.0), plate_color);
  }
}

void testlines(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST7735_BLACK);
  int color = 0xF800;
  int t;
  int w = 63;
  int x = 159;
  int y = 0;
  int z = 127;
  for(t = 0 ; t <= 15; t+=1) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(ST7735_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = 127;
    int h = 159;
    for(i = 0 ; i <= 24; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST7735_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST7735_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST7735_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST7735_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}
