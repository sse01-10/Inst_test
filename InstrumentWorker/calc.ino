String Key[4][4] = {
  { "7", "8", "9", "W" },
  { "4", "5", "6", "R" },
  { "1", "2", "3", "-" },
  { "C", "0", ".", "H" }
};

String N1, N2, ShowSC, opt;
bool updata = false;
float answers = -1;

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
      tft.setCursor(22 + (60 * x), 100 + (60 * y));
      tft.setTextSize(3);
      tft.setTextColor(ILI9341_BLACK);
      tft.println(Key[y][x]);
    }
  }

  isDrawCalc = true;
}

void ExecCalculator()
{
  waitTouch();

  if(axisX_old != axisX || axisY_old != axisY)
  {
    updata = false;
    for (int i1=0;i1<4;i1++) 
    {
      for (int i2=0;i2<4;i2++) 
      {          
        if ((axisX>=240-((i1+1)*60)+1&&axisX<=240-(i1*60)-1)&&(axisY>=(i2*60)+1&&axisY<=((i2+1)*60)-1)) 
        {
          if(Key[i1][i2] == "W")  //write
          {
            WriteDeg(answers);

            ResetValue();
          }
          else if(Key[i1][i2] == "R") //read
          {
            answers = ReadDeg();
            ShowSC = answers;
          }
          else if (Key[i1][i2] == "H")  //home
          {
            ResetValue();
            isDrawHome = false;
            currentMODE = HOME;
          }
          else if (Key[i1][i2] == "-" || Key[i1][i2] == ".")
          {
            N1 = N1 + Key[i1][i2];
            ShowSC = N1;
          }
          else if ((i1<=2 && i2<=2) || (i1==3 && i2==1)) 
          {
            if (opt==0) 
            {
              if (answers != -1) answers = -1;
              N1 = N1 + Key[i1][i2];
              ShowSC = N1;
            } 
            else 
            {
              N2 = N2 + Key[i1][i2];
              ShowSC = opt + N2;
            }
          }
          else 
          {
            if (Key[i1][i2] == "C") ResetValue();
            else if (i2==3) 
            {
              if (N1 == "") N1 = String(answers);
              opt = Key[i1][i2];
              ShowSC = Key[i1][i2];
            }
          }
          
          updata = true;
        }
      }
    }

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

void ResetValue()
{
  N1 = N2 = "";
  opt = "";
  answers = 0;
  ShowSC = N1;
}
