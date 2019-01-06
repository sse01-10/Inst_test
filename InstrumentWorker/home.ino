
void drawHome()
{
  InitState();
  
  tft.fillRect(0, 0, 240, 320, ILI9341_BLACK);
  
  tft.fillRect(80, 80, 100, 80, ILI9341_WHITE);
  tft.setCursor(22 + 80, 22 + 80);
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_BLUE);
  tft.println("CALC");

  isDrawHome = true;
}

void ExecHome()
{
   waitTouch();

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
