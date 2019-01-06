#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
#define RETRY_COUNT 10

void Init()
{
  mySerial.begin(9600);
}

bool WriteDeg(int deg)
{
  bool isError = true;
  for(uint16_t i = 0; i < RETRY_COUNT; i++)
  {
    if(mySerial.available())
    {
      mySerial.write(deg);
      
      isError = false;
      break;
    }
  }
  return isError;
}

int ReadDeg()
{
  int retVal = 0xFFFF;
  for(uint16_t i = 0; i < RETRY_COUNT; i++)
  {
    if(mySerial.available())
    {
      
      retVal = mySerial.read();
    }
    
  }

  return retVal;
}
