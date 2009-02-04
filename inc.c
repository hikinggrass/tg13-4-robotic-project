/*****************************************************************************
 * inc.c : Includes, functions etc.
 *****************************************************************************
 * Copyright (C) 2009 the tg13-4-robotic-project Team
 *
 * Authors: Kai Hermann <kai -dot- uwe -dot- hermann -at- googlemail -dot- com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include "asuro.h"
#include "defines.c"
#include "globals.c"
#include <avr/eeprom.h>

//evtl....
#include <stdio.h> 
#include <stdlib.h> 

/*****************************************************************************
 * uint8_t KeyPressed(void)
 *****************************************************************************
 * zeigt, ob eine Taste des ASUROs gedrueckt ist.
 *
 * Die Funktion nutzt nicht den AD-Wandler wie die Funktion Pollswitch,
 * sondern fragt die Tasten direkt digital ab.
 * Grund: Funktion Pollswitch arbeitet nicht zuverlaessig.
 *
 * 23.5.2007 ch
 *
 * Quelle: http://www.roboterclub-freiburg.de/asuro/zufall/zufall.html
 *****************************************************************************/
uint8_t KeyPressed(void)
{
        uint8_t flag;

        DDRD &= ~SWITCHES; // High Impedance ( Input )
        DDRC |= (1<<PC4); // ADC-Switch-Pin to Output
        PORTC |=  (1<<PC4); // load capacitor / Pull up
        Msleep(1);
        DDRC &= ~(1<<PC4); // Set ACD-Switch to Input
        PORTC &=  ~(1<<PC4); // High Impedance

        Msleep(1);

        if(PIND&SWITCHES) flag=FALSE;
        else flag=TRUE;

        return flag;
}

/*****************************************************************************
 * uint8_t getkey(void)
 *****************************************************************************
 * liefert die Nummer des gedrückten tasters
 * 0 = Kein Taster gedrueckt
 *****************************************************************************/
uint8_t getKey(void)
{
	uint8_t pressed,key;
	while(1) {
		pressed = KeyPressed();
		key = PollSwitch();
		
		if(pressed) {
			switch(key) {
				case 0x01:
					return 1;
				case 0x02:
					return 2;
				case 0x04:
					return 3;
				case 0x08:
					return 4;
				case 0x10:
					return 5;
				case 0x20:
					return 6;
				default:
					return 0;
			}
		}
   }
}


/*****************************************************************************
 * uint8_t line_init(void)
 *****************************************************************************
 * Kalibriert die Line-Sensoren
 *****************************************************************************/
void line_init(void)
{
	uint8_t wait = 0;
	unsigned int data[2]; //Speicher für linedata bereitstellen
	FrontLED(ON);
	
	SerPrint("\r\nKalibriere Line-Sensor\r\n");
	SerPrint("ASURO auf schwarzen Untergrund stellen und T1 druecken\r\n");
	
	while(wait<1)
	{
		if(getKey() == 1)
		{
			SerPrint("Kalibriere...\r\n");
			
			LineData(data);
			
			_EEPUT(EE_BLACK_L,data[LEFT]);		//Schwarzwerte in EEPROM schreiben
			_EEPUT(EE_BLACK_R,data[RIGHT]);
			
			SerPrint("L: ");
			PrintInt(data[LEFT]);
			SerPrint(" R: ");
			PrintInt(data[RIGHT]);
			SerPrint("\r\n");
			SerPrint("Kalibrierung 1/2 - Abgeschlossen\r\n");
			
			wait = 1;
		}	
	}
	
	wait = 0;
	
	SerPrint("ASURO auf weissen Untergrund stellen und T1 druecken\r\n");
	
	while(wait<1)
	{
		if(getKey() == 1)
		{
			SerPrint("Kalibriere...\r\n");
			
			LineData(data);
			
			_EEPUT(EE_WHITE_L,data[LEFT]);		//Weisswerte in EEPROM schreiben
			_EEPUT(EE_WHITE_R,data[RIGHT]);
			
			SerPrint("L: ");
			PrintInt(data[LEFT]);
			SerPrint(" R: ");
			PrintInt(data[RIGHT]);
			SerPrint("\r\n");
			SerPrint("Kalibrierung 2/2 - Abgeschlossen\r\n");
			
			
			wait = 1;
		}	
	}
	
	FrontLED(OFF);
	SerPrint("THX\r\n");
	
    
}

void readEEPROM(void)
{
	_EEGET(black_l,EE_BLACK_L);
	_EEGET(black_r,EE_BLACK_R);
	_EEGET(white_l,EE_WHITE_L);
	_EEGET(white_r,EE_WHITE_R);
	_EEGET(msl,EE_MSL);
	_EEGET(msr,EE_MSR);
}


/*****************************************************************************
 * void info(void)
 *****************************************************************************
 * gib EEPROM infos aus
 *****************************************************************************/
void info(void)
{
	readEEPROM();
	SerPrint("\r\nInfos:\r\nEEPROM:\r\n-Schwarzwerte-\r\nL: ");
	PrintInt(black_l);
	SerPrint(" R: ");
	PrintInt(black_r);
	SerPrint("\r\n-Weisswerte-\r\nL: ");
	PrintInt(white_l);
	SerPrint(" R: ");
	PrintInt(white_r);
	SerPrint("\r\n-Motorspeed-\r\nL: ");
	PrintInt(msl);
	SerPrint(" R: ");
	PrintInt(msr);
	SerPrint("\r\n-DONE-\r\n");
}
/*****************************************************************************
 * void setMS(void)
 *****************************************************************************
 * setze Motorgeschwindigkeit
 *****************************************************************************/
void setMS(void)
{
	unsigned char serIn[1]; //input an der seriellen schnittstelle
	
	int tmsl = msl;
	int tmsr = msr;
	int wait = 0;

	SerPrint("\r\n-Motorspeed links +1 mit a -1 mit s - ende mit d-\r\n");
	while(wait<1)
	{
		
		SerRead(serIn,1,0);
	
		switch(serIn[0])
		{
			case 'a': //+1
				tmsl += 1;
				break;
			case 's': //-1
				tmsl -= 1;
				break;
			case 'd': //fertig
				msl = tmsl;
				wait = 1;
				break;
		}
		
		PrintInt(tmsl);
		SerPrint(" ");	
	}
	SerPrint("\r\n-Done: MSL: ");
	PrintInt(msl);
	
	wait = 0;
	
	SerPrint("\r\n-Motorspeed rechts +1 mit a -1 mit s - ende mit d-\r\n");
	while(wait<1)
	{
		
		SerRead(serIn,1,0);
	
		switch(serIn[0])
		{
			case 'a': //+1
				tmsr += 1;
				break;
			case 's': //-1
				tmsr -= 1;
				break;
			case 'd': //fertig
				msr = tmsr;
				wait = 1;
				break;
		}
		
		PrintInt(tmsr);
		SerPrint(" ");	
	}
	SerPrint("\r\n-Done: MSR: ");
	PrintInt(msr);
	
	SerPrint("\r\nWriting holy shit to EEPROM\r\n");
	
	_EEPUT(EE_MSL,msl);
	_EEPUT(EE_MSR,msr);
	
	SerPrint("\r\n-DONE!!!!!!!!!!!!!!\r\n");
}

/*****************************************************************************
 * int asuro_init(void)
 *****************************************************************************
 * initialisiert den Asuro
 *****************************************************************************/
int asuro_init(void) 
{
	unsigned char serIn[1]; //input an der seriellen schnittstelle
	
	while(42)
	{
		SerRead(serIn,1,1); //warten auf Startzeichen
		switch(serIn[0])
		{
			case START:		//startprozedur einleiten
				readEEPROM();
				return 0; 
			case C_LINE:	//line-sensor konfigurieren
				line_init();
				break;
			case INFO:		//Infos ausgeben (atm aus EEPROM auslesen)
				info();
				break;
			case SETMS:		//Motorspeed per SeriellerSchnittstelle setzen
				setMS();	//atm nicht vorhanden
				break;
		}
				
	}
}