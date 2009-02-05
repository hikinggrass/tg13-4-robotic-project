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

//Gute Motorspeed-Werte vom 04.02.09 (achtung, Wetter, Luftfeuchtigkeit usw. beachten!) waren: 252 bei beiden Motoren!
//*****************************************************************************
void cake1(void)  //Vom Start bis zum Labyrintheingang
{
	unsigned int data[2]; //Speicher f�r Linien-Sensoren bereitstellen
	
	FrontLED(ON);
	
	MotorDir(FWD,FWD);
	MotorSpeed(msl-100,msr-100);
	
	LineData(data);
	while(data[LEFT] >= white_l - 10 || data[RIGHT] >= white_r - 10) //Bis zu der kreuzenden schwarzen Linie
		LineData(data);

	MotorDir(RWD,RWD);
	MotorSpeed(msl,msr);
	
	Msleep(40);  //Ruck zur�ck!
	
	MotorDir(FWD,RWD);  //Drehung
	Msleep(200);
	
	FrontLED(OFF);	
}


//*****************************************************************************
void labAbschnitt_Rechtsdrehung(void)
{
	while(getKey() == 0);  //Bis er an der Wand h�ngt (vorw�rts)
	
	MotorSpeed(0,0);   //Damit die Motoren stillstehen
	Msleep(100);
	
	MotorDir(FWD,RWD);
	MotorSpeed(msl,msr);   //Drehung
	Msleep(200);
	
	MotorDir(FWD,FWD);	//gerade aus weitergurken
	MotorSpeed(msl,msr);
}

//*****************************************************************************
void labAbschnitt_Linksdrehung(void)
{
	while(getKey() == 0);  //Bis er an der Wand h�ngt (vorw�rts)
	
	MotorSpeed(0,0);  //Damit die Motoren stillstehen
	Msleep(100);
	
	MotorDir(RWD,FWD);
	MotorSpeed(msl,msr);   //Drehung
	Msleep(200);
	
	MotorDir(FWD,FWD);  //gerade aus weitergurken
	MotorSpeed(msl,msr);
}

//*****************************************************************************
void cake2(void)  //Durchs Labyrinth (hinweg)
{
	MotorDir(FWD,FWD);

	labAbschnitt_Rechtsdrehung();
	
	labAbschnitt_Linksdrehung();
	
	labAbschnitt_Linksdrehung();
	
	labAbschnitt_Linksdrehung();
	
	labAbschnitt_Rechtsdrehung();

	labAbschnitt_Linksdrehung();
	
	while(getKey() == 0);
	
	MotorSpeed(0,0);
}


//*****************************************************************************
int main(void)
{
	Init(); //Init-Funktion der Lib
	
	int devNull = asuro_init(); //unsre init-Funktion

	cake1();
	
	cake2();
	
	//cake3();
	
	//cake4();
	
	//cake5();
	
	//cake6();

	angekommen();

	while (1);
	return 0;
}
