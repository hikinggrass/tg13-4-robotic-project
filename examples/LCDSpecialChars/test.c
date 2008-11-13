/*******************************************************************************
*
* File Name:   aufgabe4.c
*
* Lösung zur Aufgabe <ASURO bekommt ein Gesicht> aus Mehr Spaß Mit ASURO, Band II
*
* Project  :   ASURO-LCD extension-module
*
*
* Ver.     Date         Author           Comments
* -------  ----------   --------------   ------------------------------
* 1.00		30.5.06		martin hofmann		build
*
*
* Copyright (c) 2007 Martin Hofmann
*****************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 ***************************************************************************/

#include "asuro.h"
#include "lcd.h"
#include "i2c.h"

const char Bat1[8] PROGMEM = {0X0E,0X1B,0X11,0X11,0X11,0X11,0X11,0X1F};					  
const char Bat2[8] PROGMEM = {0X0E,0X1B,0X11,0X11,0X11,0X11,0X1F,0X1F};
const char Bat3[8] PROGMEM = {0X0E,0X1B,0X11,0X11,0X11,0X1F,0X1F,0X1F};
const char Bat4[8] PROGMEM = {0X0E,0X1B,0X11,0X11,0X1F,0X1F,0X1F,0X1F};
const char Bat5[8] PROGMEM = {0X0E,0X1B,0X11,0X1F,0X1F,0X1F,0X1F,0X1F};
const char Bat6[8] PROGMEM = {0X0E,0X1B,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F};
const char Bat7[8] PROGMEM = {0X0E,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F};

const char Heart1[8] PROGMEM = {0X00,0X00,0X00,0X0A,0X0E,0X04,0X00,0X00};
const char Heart2[8] PROGMEM = {0X00,0X00,0X00,0X1B,0X1F,0X0E,0X04,0X00};					  


const char Line1[8] PROGMEM = {0X00,0X00,0X00,0X1F,0X00,0X00,0X00,0X00};				
const char Line2[8] PROGMEM = {0X00,0X10,0X08,0X04,0X02,0X01,0X00,0X00};
const char Line3[8] PROGMEM = {0X00,0X04,0X04,0X04,0X04,0X04,0X00,0X00};
const char Line4[8] PROGMEM = {0X00,0X01,0X02,0X04,0X08,0X10,0X00,0X00};


void battery_load(void)		//Nötige Sonderzeichen in das Display laden
{
	SetCharLCD_p(0,Bat1);
	SetCharLCD_p(1,Bat2);
	SetCharLCD_p(2,Bat3);
	SetCharLCD_p(3,Bat4);
	SetCharLCD_p(4,Bat5);
	SetCharLCD_p(5,Bat6);
	SetCharLCD_p(6,Bat7);
}

void heart_load(void)		//Nötige Sonderzeichen in das Display laden
{
	SetCharLCD_p(0,Heart1);
	SetCharLCD_p(1,Heart2);
}

void line_load(void)		//Nötige Sonderzeichen in das Display laden
{
	SetCharLCD_p(0,Line1);
	SetCharLCD_p(1,Line2);
	SetCharLCD_p(2,Line3);
	SetCharLCD_p(3,Line4);
}

int main(void)
{
	char i;
  int u;
  Init();										//Initialisiert ASURO
  InitI2C();
	InitLCD();			//Initialisiert das Display Modul
	
	battery_load();
	
	for(i=0;i<7;i++)
  {
  	ClearLCD();
  	SetCursorLCD(7,1);
    WriteLCD(i);
    Msleep(1000);
  }

  line_load();
  while(1)
  {  
	  for(i=0;i<4;i++)
    {
   	  ClearLCD();
  	  SetCursorLCD(7,0);
      WriteLCD(i);
      Msleep(1000);
    }
  }
	return 0;
}


