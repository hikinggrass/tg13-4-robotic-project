/*****************************************************************************
 * tg13-4-robotic-project.c : This is were the "magic" happens...
 *****************************************************************************
 * Copyright (C) 2008-2009 the tg13-4-robotic-project Team
 *
 * Authors: Kai Hermann <kai -dot- uwe -dot- hermann -at- googlemail -dot- com>
 *			Emanuel Schrade <>
 *			Matthias Holoch <>
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
#include "inc.c"

//*****************************************************************************
void cake1(void)
{
	unsigned int data[2]; //Speicher für Linien-Sensoren bereitstellen
	
	FrontLED(ON);
	
	msl = 100;
	msr = 100;
	
	MotorDir(FWD,FWD);
	MotorSpeed(msl,msr);
	
	LineData(data);
	while(data[LEFT] >= white_l - 10 || data[RIGHT] >= white_r - 10) //Bis zu der kreuzenden schwarzen Linie
		{
		PrintInt(data[0]);
		SerPrint(" ");
		PrintInt(data[1]);
		SerPrint("\r\n");
		LineData(data);
		}
	SerPrint("weiss1 end - Jetzt muss er die Drehung beginnen\r\n");

	Msleep(30); //TESTEN!!!
	
	MotorDir(FWD,RWD);
	LineData(data);
	while(data[RIGHT] >= white_r - 10) //Drehung vorm Lab
		{
		PrintInt(data[0]);
		SerPrint(" ");
		PrintInt(data[1]);
		SerPrint("\r\n");
		LineData(data);
		}
	SerPrint("weiss2 _drehung_ end\r\n");
	
	FrontLED(OFF);
	
}


//*****************************************************************************
void cake2(void)
{

	msl = 255;
	msr = 255;

	MotorDir(FWD,FWD);
	MotorSpeed(msl,msr);

	while(getKey() == 0);  //Bis er an der Wand hängt (vorwärts)
	
	MotorSpeed(0,0);
	Msleep(100);
	
	MotorDir(FWD,RWD);
	MotorSpeed(0,255);   //Drehung
	Msleep(500);
	
	MotorDir(FWD,FWD);
	MotorSpeed(255,255);
	
	while(getKey() == 0);
	
	MotorSpeed(0,0);
	
}


//*****************************************************************************
int main(void)
{
	Init(); //Init-Funktion der Lib
	
	int devNull = asuro_init(); //unsre init-Funktion

	//cake1(void);
	
	cake2();
	

	while (1);
	return 0;
}
