/*
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
*/
// Calibrate values
/*
#define TS_MINX 125
#define TS_MINY 85
#define TS_MAXX 965
#define TS_MAXY 905
*/
/*
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
*/

String Key[4][4] = {
  { "7", "8", "9", "W" },
  { "4", "5", "6", "R" },
  { "1", "2", "3", " " },
  { "C", "0", "=", " " }
};

/*
 * default copy
String Key[4][4] = {
  { "7", "8", "9", "/" },
  { "4", "5", "6", "*" },
  { "1", "2", "3", "-" },
  { "C", "0", "=", "+" }
};
*/

/*
//上を下に変えた
String Key[4][4] = {
  { "/", "*", "-", "+" },
  { "9", "6", "3", "=" },
  { "8", "5", "2", "0" },
  { "7", "4", "1", "C" }
};
*/
//その時の動き
/*
String Key[4][4] = {
  { "-", "=", "2", "C" },
  { "-", "3", "2", "?" },
  { "*", "6", "5", "4" },
  { "/", "9", "8", "?" }
};
*/

/*
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
*/
String N1, N2, ShowSC, opt;
bool updata=false;
float answers=-1;

/*
void setup() 
{
  // put your setup code here, to run once:
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

void drawHome()
{
  InitState();
  
  tft.fillRect(0, 0, 240, 320, ILI9341_BLACK);
  
  tft.fillRect(80, 80, 160, 80, ILI9341_WHITE);
  tft.setCursor(22 + 80, 22 + 80);
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_BLUE);
  tft.println("CALC");

  isDrawHome = true;
}
*/

void drawCalculator()
{
  InitState();
  
  tft.fillRect(0, 80, 240, 240, ILI9341_WHITE);
 
  tft.drawFastHLine(0, 80, 240, ILI9341_BLACK);
  tft.drawFastHLine(0, 140, 240, ILI9341_BLACK);
  tft.drawFastHLine(0, 200, 240, ILI9341_BLACK);
  tft.drawFastHLine(0, 260, 240, ILI9341_BLACK);
  tft.drawFastHLine(0, 320-1, 240, ILI9341_BLACK);

  tft.drawFastVLine(0, 80, 240, ILI9341_BLACK);
  tft.drawFastVLine(60, 80, 240, ILI9341_BLACK);
  tft.drawFastVLine(120, 80, 240, ILI9341_BLACK);
  tft.drawFastVLine(180, 80, 240, ILI9341_BLACK);
  tft.drawFastVLine(240-1, 80, 240, ILI9341_BLACK);

   for (int y=0;y<4;y++) 
   {
     for (int x=0;x<4;x++) 
     {
      tft.setCursor(22 + (60*x), 100 + (60*y));
      tft.setTextSize(3);
      tft.setTextColor(ILI9341_BLACK);
      tft.println(Key[y][x]);
    }
  }

  isDrawCalc = true;
}

void drawFrame()
{
  tft.drawRect(5,190,100,50,ILI9341_BLACK);
}

TS_Point p_old;

/*
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
        ExecCalculator2();
      }
      else
      {
        drawCalculator();
      }

    break;
  }
  
  delay(300);
}

void waitTouch2() 
{
  TS_Point p;
  int16_t x, y;

  uint8_t z;
  if (ts.touched()) {
    // read x & y & z;
    while (! ts.bufferEmpty()) {
      
      //Serial.print(ts.bufferSize());
      ts.readData(&x, &y, &z);
      //Serial.print("->("); 
      //Serial.print(x); Serial.print(", "); 
      //Serial.print(y); Serial.print(", "); 
      //Serial.print(z);
      //Serial.println(")");
      
      if(z > MINPRESSURE)
      {
        axisX = (float)y/TS_DIVY;//x/TS_DIVX;
        axisY = (float)(240.0 - (x/TS_DIVX));//y/TS_DIVY;
        
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
    ts.writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
  }

  delay(10);
}

void ExecHome()
{
   waitTouch2();

  if(axisX_old != axisX || axisY_old != axisY)
  {
    Serial.println(axisX);
    Serial.print(axisY);
    //tft.fillRect(80, 80, 160, 80, ILI9341_WHITE);
    if(axisX+1 > 80 && axisX-1 < 240 && axisY+1 > 80 && axisY-1 < 160)
    {
      isDrawCalc = false;
      currentMODE = CALC;
    }   
  }
}
*/

void ExecCalculator()
{
  waitTouch();

  if(axisX_old != axisX || axisY_old != axisY)
  {
    //Serial.println(axisX);
    //Serial.println(axisY);
    updata = false;
    //Serial.println("Loop Start");
    for (int i1=0;i1<4;i1++) 
    {
      for (int i2=0;i2<4;i2++) 
      {          
        if ((axisX>=240-((i1+1)*60)+1&&axisX<=240-(i1*60)-1)&&(axisY>=(i2*60)+1&&axisY<=((i2+1)*60)-1)) 
        {
          if ((i1<=2&&i2<=2)||(i1==3&&i2==1)) 
          {
            if (opt==0) 
            {
              if (answers!=-1) answers = -1;
              N1 = N1 + Key[i1][i2];
              Serial.println(Key[i1][i2]);
              ShowSC = N1;
            } 
            else 
            {
              N2 = N2 + Key[i1][i2];
              //Serial.println(Key[i1][i2]);
              ShowSC = opt + N2;
            }
          }
          else 
          {
            if (Key[i1][i2]=="C") 
            {
              isDrawHome = false;
              currentMODE = HOME;
              //Serial.println(Key[i1][i2]);
              N1 = N2 = "";
              opt = "";
              answers = 0;
              ShowSC = N1;
            }
            else if (i2==3) 
            {
              //Serial.println(Key[i1][i2]);
              if (N1=="") N1 = String(answers);
              opt = Key[i1][i2];
              ShowSC = Key[i1][i2];
            }
            else if (Key[i1][i2]=="=")
            {
              //Serial.println(Key[i1][i2]);
              if (opt=="W") answers = N1.toInt() + N2.toInt();
              else if (opt=="R") answers = N1.toInt() - N2.toInt();
              else if (opt==" ") answers = N1.toInt() * N2.toInt();
              //else if (opt==" ") answers = N1.toInt() / N2.toInt();
              N1 = N2 = opt = "";
              ShowSC = answers;
            }
          }
          updata = true;
        }
      }
    }

    //Serial.println("Loop End");
    
    if (updata) 
    {
      tft.fillRect(0, 0, 240, 80, ILI9341_BLACK);
    
      tft.setCursor(10, 10);
      tft.setTextSize(3);
      tft.setTextColor(ILI9341_WHITE);
      tft.println(ShowSC);

      axisX_old = axisX;
      axisY_old = axisY;
    }
  }
}
