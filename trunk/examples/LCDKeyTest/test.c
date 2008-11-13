
#include "asuro.h"
#include "lcd.h"
#include "i2c.h"


int main(void)
{
  int keys;

  Init();
  InitI2C();
  InitLCD();

  while(1)
  {
    keys = PollSwitchLCD();
    if (keys & LCD_KEY_YELLOW)
    {
        PrintSetLCD(0,0,"Yellow");
        SerPrint("Yellow\r\n");
    }
    else if (keys & LCD_KEY_RED)
    {
        PrintSetLCD(0,0,"Red   ");
        SerPrint("Red\r\n");
    }
    else if (keys & LCD_KEY_BLUE)
    {
        PrintSetLCD(0,0,"Blue  ");
        SerPrint("Blue\r\n");
    }
    Msleep(100);
  }
  return 0;
}

