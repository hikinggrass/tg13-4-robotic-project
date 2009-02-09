/*****************************************************************************
 * tg13-4-robotic-project.c : This is were the "magic" happens...
 *****************************************************************************
 * Copyright (C) 2008-2009 the tg13-4-robotic-project Team
 *
 * Authors: Kai Hermann <kai -dot- uwe -dot- hermann -at- gmail -dot- com>
 *			Matthias Holoch <MHoloch -at- gmail -dot- com>
 *			Emanuel Schrade <>
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


/*****************************************************************************
 * void cake1(void)
 *****************************************************************************
 * fährt den ASURO vom Start (rechts neben der schwarzen Linie)
 * zum Labyrintheingang
 *****************************************************************************/
void cake1(void)
{	
	unsigned int data[2]; //Speicher für Linien-Sensoren bereitstellen
	
	FrontLED(ON);
	
	MotorDir(FWD,FWD);
	MotorSpeed(msl-100,msr-100);
	
	
	LineData(data);
	while(data[LEFT] >= white_l - 20 || data[RIGHT] >= white_r - 20) //Bis zu der kreuzenden schwarzen Linie
		LineData(data);
	
	MotorDir(RWD,RWD);
	MotorSpeed(msl,msr);
	
	Msleep(40);  //Ruck zurück!
	MotorDir(FWD,RWD);  //Drehung
	Msleep(200);
	FrontLED(OFF);	
}


/*****************************************************************************
 * void labAbschnitt_Rechtsdrehung(void)
 *****************************************************************************
 * ermöglicht eine Drehung nach RECHTS im Labyrinth
 *****************************************************************************/
void labAbschnitt_Rechtsdrehung(void)
{
	while(getKey() != 2 && getKey() != 3 && getKey() != 4 && getKey() != 5);  //Bis er an der Wand hängt (vorwärts)
	
	MotorSpeed(0,0);   //Damit die Motoren stillstehen
	Msleep(100);
	
	MotorDir(FWD,RWD);
	MotorSpeed(msl,msr);   //Drehung
	Msleep(200);
	
	MotorDir(FWD,FWD);	//gerade aus weitergurken
	MotorSpeed(msl,msr);
}

/*****************************************************************************
 * void labAbschnitt_Linksdrehung(void)
 *****************************************************************************
 * ermöglicht eine Drehung nach LINKS im Labyrinth
 *****************************************************************************/
void labAbschnitt_Linksdrehung(void)
{
	while(getKey() != 2 && getKey() != 3 && getKey() != 4 && getKey() != 5);  //Bis er an der Wand hängt (vorwärts)
	
	MotorSpeed(0,0);  //Damit die Motoren stillstehen
	Msleep(100);
	
	MotorDir(RWD,FWD);
	MotorSpeed(msl,msr);   //Drehung
	Msleep(200);
	
	MotorDir(FWD,FWD);  //gerade aus weitergurken
	MotorSpeed(msl,msr);
}

/*****************************************************************************
 * void cake2(void)
 *****************************************************************************
 * fährt den ASURO durchs Labyrinth (hinweg)
 *****************************************************************************/
void cake2(void)
{
	MotorDir(FWD,FWD);

	labAbschnitt_Rechtsdrehung();
	
	labAbschnitt_Linksdrehung();
	
	labAbschnitt_Linksdrehung();
	
	labAbschnitt_Linksdrehung();
	
	labAbschnitt_Rechtsdrehung();

	labAbschnitt_Linksdrehung();

}

/*****************************************************************************
 * void cake3(void)
 *****************************************************************************
 * fährt vom Labyrinth zum Wendekreis (hinweg)
 *****************************************************************************/
void cake3(void)
{
	unsigned char companionCube = 0;
	int n_msl = msl - 120;
	int n_msr = msr - 120;
	unsigned int data[2];
	
	FrontLED(ON);
	//--später wieder rauslöschbar, nur nötig, solang NUR cake3 ausgeführt wird-------
	MotorDir(FWD,FWD);
	MotorSpeed(n_msl,n_msr);
	//--------------------------------------------------------------------------------
	
	LineData(data);
	while(data[LEFT] >= white_l - 20 || data[RIGHT] >= white_r - 20) //Bis zum Dreieck
		LineData(data);
	
	MotorSpeed(n_msl,n_msr);
	
	while(companionCube == 0) //soland aktiv, bis er am wendekreis ist
	{
		LineData(data);

		if(data[0] >= white_l - 20 && data[1] >= white_r - 20)
			MotorSpeed(0,n_msr);
		else
			MotorSpeed(n_msl,0);
		
		//if(data[0] >= white_l -10 && data[1] >= white_r - 10)
			//companionCube = 1; ---------------------------------------> Diese Bedingung muss noch irgendwie ein bisschen vercoolert werden, damit die richtig tut. So hört er sofort auf, wenn er mal kuuuuurz 
			//															  was weißes sieht. Irgendwie noch n bisschen mehr "time" muss dazwischen sein. Msleep ist aber keine Option, sonst fährt er ja völlig falsch.
	}
	
	//--später wieder rauslöschbar, nur nötig, solang NUR cake3 ausgeführt wird-------
	MotorSpeed(0,0);
	Msleep(1000);
	MotorSpeed(msl,msr);
	//--------------------------------------------------------------------------------
	
	FrontLED(OFF);
}

//*****************************************************************************
int main(void)
{
	Init(); //Init-Funktion der Lib
	
	int devNull = asuro_init(); //unsre init-Funktion

	//cake1();

	//cake2();

	cake3();
	
	//cake4();
	
	//cake5();
	
	//cake6();
	
	while(getKey() == 0);
	
	MotorSpeed(0,0);
	
	angekommen();

	while (1);
	return 0;
}
