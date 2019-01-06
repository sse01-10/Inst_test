#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <SoftwareSerial.h>

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin
#define MINPRESSURE 55
#define MAXPRESSURE 1000

#define TS_MINX 338
#define TS_MINY 155
#define TS_MAXX 3900
#define TS_MAXY 3600
#define TS_STEPX 975
#define TS_STEPY 900
#define TS_DIVX 15
#define TS_DIVY 13.5

Adafruit_STMPE610 ts = Adafruit_STMPE610(8);
Adafruit_ILI9341 tft = Adafruit_ILI9341(10,9);

enum VIEW_MODE
{
  HOME = 0,
  CALC = 1,
};

VIEW_MODE currentMODE = HOME;
uint16_t axisX,axisY;
uint16_t axisX_old,axisY_old;
bool isDrawHome = false;
bool isDrawCalc = false;

void setup() 
{
  Serial.begin(9600);
  Serial.flush();
  
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);

  if(!ts.begin())
  {
    Serial.println("Unable");
  }
  else
  {
    Serial.println("Start screen");
  }

  Init();
}

void InitState()
{
  isDrawHome = false;
  isDrawCalc = false;

  axisX = 0;
  axisY = 0;
  axisX_old = 0;
  axisY_old = 0;
}

void loop()
{
  // put your main code here, to run repeatedly:
  switch(currentMODE)
  {
    case HOME:
    if(isDrawHome)
    {
      ExecHome();
    }
    else
    {
      drawHome();
    }
    break;

    case CALC:
      if(isDrawCalc)
      {
        ExecCalculator();
      }
      else
      {
        drawCalculator();
      }

    break;
  }
  
  delay(300);
}

void waitTouch() 
{
  int16_t x, y;
  uint8_t z;
  
  if (ts.touched()) {
    // read x & y & z;
    while (! ts.bufferEmpty()) {     
      ts.readData(&x, &y, &z);
  
      if(z > MINPRESSURE)
      {
        //平均化するのもあり
        Serial.print("axisX=");
        Serial.print((y*1.225-220));
        Serial.print(",");
        Serial.println((y*1.225-220)/ TS_DIVY);

        Serial.print("axisY=");
        Serial.print((x*1.0238)-250);
        Serial.print(",");
        Serial.println(((x*1.0238)-250) / TS_DIVX);
        axisX = (float)((y*1.225-220)) / TS_DIVY;   //x/TS_DIVX;
        axisY = (float)(240.0 - (((x*1.0238)-250) / TS_DIVX));  //y/TS_DIVY;
        
        if(axisX > 239)
        {
          axisX = 239;
        }
        else if(axisX < 0)
        {
          axisX = 0;
        }
  
        if(axisY > 239)
        {
          axisY = 239;
        }
        else if(axisY < 0)
        {
          axisY = 0;
        }
      }
    }

    Serial.println("Complete");
    
    ts.writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
  }

  delay(10);
}
