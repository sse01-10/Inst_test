#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
#define RETRY_COUNT 10
#define MOTOR_STEP 500
#define DEG_MAX 360
#define DEG_MIN -360

void Init()
{
  mySerial.begin(9600);
}

bool WriteDeg(int deg)
{
  bool isError = true;

  if(deg > DEG_MAX)
  {
    deg = DEG_MAX;
  }
  else if(deg < DEG_MIN)
  {
    deg = DEG_MIN;
  }
  
  for(uint16_t i = 0; i < RETRY_COUNT; i++)
  {
    if(mySerial.available())
    {
      String keyword = "CH01P";
      deg *= MOTOR_STEP;
      keyword += deg;
      mySerial.println(keyword);
      
      isError = false;
      break;
    }
  }
  return isError;
}

float ReadDeg()
{
  float retVal = 0xFFFF;
  for(uint16_t i = 0; i < RETRY_COUNT; i++)
  {
    if(mySerial.available())
    { 
      retVal = mySerial.read();

      retVal /= (float)MOTOR_STEP;
    }
    
  }

  return retVal;
}
