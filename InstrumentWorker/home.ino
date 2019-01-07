
void drawHome()
{
  InitState();
  
  tft.fillRect(0, 0, 240, 320, ILI9341_BLACK);
  
  tft.fillRect(0, 240, 100, 80, ILI9341_WHITE);
  tft.setCursor(0 + 15, 240 + 30);
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
    
    if(axisX+1 > 0 && axisX-1 < 80 && axisY+1 > 0 && axisY-1 < 80)
    {
      isDrawCalc = false;
      currentMODE = CALC;
    }   
  }
}
