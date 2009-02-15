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
 * f�hrt den ASURO vom Start (rechts neben der schwarzen Linie)
 * zum Labyrintheingang
 *****************************************************************************/
void cake1(void)
{	
	unsigned int data[2]; //Speicher f�r Linien-Sensoren bereitstellen
	
	FrontLED(ON);
	
	MotorDir(FWD,FWD);
	MotorSpeed(msl-100,msr-100);
	
	
	LineData(data);
	while(data[LEFT] >= white_l - 20 || data[RIGHT] >= white_r - 20) //Bis zu der kreuzenden schwarzen Linie
		LineData(data);
	
	MotorDir(RWD,RWD);
	MotorSpeed(msl,msr);
	
	Msleep(40);  //Ruck zur�ck!
	MotorDir(FWD,RWD);  //Drehung
	Msleep(200);
	FrontLED(OFF);	
}


/*****************************************************************************
 * void labAbschnitt_Rechtsdrehung(void)
 *****************************************************************************
 * erm�glicht eine Drehung nach RECHTS im Labyrinth
 *****************************************************************************/
void labAbschnitt_Rechtsdrehung(void)
{
	while(getKey() != 2 && getKey() != 3 && getKey() != 4 && getKey() != 5);  //Bis er an der Wand h�ngt (vorw�rts)
	
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
 * erm�glicht eine Drehung nach LINKS im Labyrinth
 *****************************************************************************/
void labAbschnitt_Linksdrehung(void)
{
	while(getKey() != 2 && getKey() != 3 && getKey() != 4 && getKey() != 5);  //Bis er an der Wand h�ngt (vorw�rts)
	
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
 * f�hrt den ASURO durchs Labyrinth (hinweg)
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
 * f�hrt vom Labyrinth zum Wendekreis (hinweg)
 *****************************************************************************/
void cake3(void)
{
	unsigned char companionCube = 0;
	int n_msl = msl - 120;
	int n_msr = msr - 120;
	unsigned int data[2];
	
	FrontLED(ON);
	//--sp�ter wieder rausl�schbar, nur n�tig, solang NUR cake3 ausgef�hrt wird-------
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
			//companionCube = 1; ---------------------------------------> Diese Bedingung muss noch irgendwie ein bisschen vercoolert werden, damit die richtig tut. So h�rt er sofort auf, wenn er mal kuuuuurz 
			//															  was wei�es sieht. Irgendwie noch n bisschen mehr "time" muss dazwischen sein. Msleep ist aber keine Option, sonst f�hrt er ja v�llig falsch.
	}
	
	//--sp�ter wieder rausl�schbar, nur n�tig, solang NUR cake3 ausgef�hrt wird-------
	MotorSpeed(0,0);
	Msleep(1000);
	MotorSpeed(msl,msr);
	//--------------------------------------------------------------------------------
	
	FrontLED(OFF);
}
/******************************************************************************
*B�ser Zeit- und Odometrietest.. FRISST EINE SEKUNDE! (bissl mehr eigentlich)
*******************************************************************************/
int anzScheibenwechsel(void)
{
	unsigned int odoData_neu[2];
	unsigned int odoData_alt[2];
	unsigned long zeit_alt;
	unsigned long zeit_neu = 1000;
	unsigned int wechsel[2];
	wechsel[0] = 0;
	wechsel[1] = 0;
	
	OdometryData(odoData_alt);
	zeit_alt = Gettime();
	while(zeit_alt >= (zeit_neu - 100)) //h�ngt eine zehntels Sekunde hier drin
		{
		zeit_neu = Gettime();
		OdometryData(odoData_neu);
		if(odoData_alt[0] >= odoData_neu[0] + 100 || odoData_alt[0] <= odoData_neu[0]  - 100) //falls ein �bergang geschehen ist... (links)
			{
			odoData_alt[0] = odoData_neu[0];
			wechsel[0] += 1;
			}
		if(odoData_alt[1] >= odoData_neu[1] + 100 || odoData_alt[1] <= odoData_neu[1]  - 100) //falls ein �bergang geschehen ist... (rechts)
			{
			odoData_alt[1] = odoData_neu[1];
			wechsel[1] += 1;
			}
		}
	return wechsel[0] - wechsel[1];
}
//*****************************************************************************
int main(void)
{
	Init(); //Init-Funktion der Lib
	
	int devNull = asuro_init(); //unsre init-Funktion
//***********Test... soll die Geschw. beider Motoren gleichhalten. Tut aber nicht. :D****/
	int geschwDifferenz;
	
	int n_msl = msl;
	int n_msr = msr;
	
	MotorDir(FWD,FWD);
	MotorSpeed(n_msl,n_msr);
	
	while(42)
	{
		geschwDifferenz = anzScheibenwechsel();
	
		if(geschwDifferenz > 0)
			{
			n_msl -= 1;
			n_msr += 1;
			}
		if(geschwDifferenz < 0)
			{
			n_msl += 1;
			n_msr -= 1;
			}
		MotorSpeed(n_msr,n_msr);
	}
//***********************************************Test: ENDE******************************/
	//cake1();

	//cake2();

	//cake3();
	
	//cake4();
	
	//cake5();
	
	//cake6();
	
	while(getKey() == 0);
	
	MotorSpeed(0,0);
	
	angekommen();

	while (1);
	return 0;
}
