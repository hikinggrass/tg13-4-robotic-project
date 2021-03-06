/*****************************************************************************
 * inc.c : Includes, functions etc.
 *****************************************************************************
 * Copyright (C) 2009 the tg13-4-robotic-project Team
 *
 * Authors: Kai Hermann <kai -dot- uwe -dot- hermann -at- gmail -dot- com>
 *			Matthias Holoch <MHoloch -at- gmail -dot- com>
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

/*****************************************************************************
 * void angekommen(void)
 *****************************************************************************
 * Wird ausgef�hrt, wenn wir im Ziel angekommen sind.
 *
 * Diese Funktion sendet �ber die Infrarotschnittstelle ein "x"-Singal, um an-
 * zuzeigen, dass unser Asuro im Ziel angekommen ist.
 * Irgendwelches Geblinke, Gedudle, o�. w�re dann auch hier einzuf�gen. ;)
 *****************************************************************************/
void angekommen(void)
{
	while(42)
	{
		//SerPrint("\r\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\nI wonder if there will be cake...\r\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
		SerPrint("x");
	}
}

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

	if(PIND&SWITCHES) flag = FALSE;
	else flag = TRUE;

	return flag;
}

/*****************************************************************************
 * uint8_t getkey(void)
 *****************************************************************************
 * liefert die Nummer des gedr�ckten Tasters
 * 0 = Kein Taster gedr�ckt
 * 1 = Taster aussen rechts
 * 6 = Taster aussen links
 *****************************************************************************/
uint8_t getKey(void)
{
	uint8_t key;
	//uint8_t pressed;
	while(1)
	{
		//pressed = KeyPressed();
		key = PollSwitch();
		
		//if(pressed)
		//{
			switch(key) 
			{
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
		//}								Die hier auskommentierten Dinger scheinen �berfl�ssig zu sein. Falls was nichts mehr tut, d�rft ihr mich hauen. ;)
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
	unsigned int data[2]; //Speicher f�r linedata bereitstellen
	
	FrontLED(ON);
	
	SerPrint("\r\nKalibriere Line-Sensor\r\nASURO auf schwarzen Untergrund stellen und T1 druecken\r\n");
	
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
			SerPrint("\r\nKalibrierung 1/2 - Abgeschlossen\r\n");
			
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
			SerPrint("\r\nKalibrierung 2/2 - Abgeschlossen\r\n");
			
			
			wait = 1;
		}	
	}
	
	FrontLED(OFF);
	
	SerPrint(done);
}

/*****************************************************************************
 * void readEEPROM(void)
 *****************************************************************************
 * liest werte aus dem EEPROM aus und speichert diese in den
 * dazugeh�rigen Variablen.
 *****************************************************************************/
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
	
	SerPrint(done);
}
/*****************************************************************************
 * void setMS(void)
 *****************************************************************************
 * setze Motorgeschwindigkeit
 *****************************************************************************/
void setMS(void)
{
	unsigned char serIn[1]; //input an der seriellen schnittstelle
	
	readEEPROM();
	
	int tmsl = msl;
	int tmsr = msr;
	int wait = 0;

	SerPrint("\r\n-Motorspeed einstellen-\r\na = +1\r\ns = -1\r\nd = speichern\r\nLinks:\r\n");
	
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
	
	SerPrint("\r\nDone: MSL: ");
	PrintInt(msl);
	
	wait = 0;
	
	SerPrint("\r\nRechts:");
	
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
	
	SerPrint("\r\nDone: MSR: ");
	PrintInt(msr);
	
	SerPrint("\r\nWriting holy shit to EEPROM\r\n");
	
	_EEPUT(EE_MSL,msl);
	_EEPUT(EE_MSR,msr);
	
	SerPrint(done);
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
				setMS();
				break;
		}
		if(getKey() != 0) //Alternativ durch Knopfdruck zu starten
			{
			Msleep(1000); //Zeit, um die Grabscherchen aus dem Weg zu tun. :-P
			readEEPROM();
			return 0;
			}
	}
}