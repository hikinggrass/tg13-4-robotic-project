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


int main(void)
{
unsigned int data[2]; //Speicher für Linien-Sensoren bereitstellen

	Init(); //Init-Funktion der Lib
	
	int devNull = asuro_init(); //unsre init-Funktion

	FrontLED(ON);
	
	MotorDir(FWD,FWD);
	MotorSpeed(msl,msr);
	
	LineData(data);
	while(data[LEFT] <= black_l + 10 && data[RIGHT] <= black_r + 10)	//Bis von der schwarzen Linie runter
		LineData(data);
	/*lol
	MotorSpeed(0,0);
	Msleep(1000);
	MotorSpeed(msl,msr);
	lol*/
	
	LineData(data);
	while(data[LEFT] >= white_l - 10 || data[RIGHT] >= white_r - 10) //Bis zu der kreuzenden schwarzen Linie
		LineData(data);
	/*lol
	MotorSpeed(0,0);
	Msleep(1000);
	MotorSpeed(msl,msr);
	lol*/
	Msleep(30); //TESTEN!
	
	MotorDir(FWD,RWD);
	LineData(data);
	while(data[RIGHT] >= white_r - 10) //Drehung vorm Lab
		LineData(data);
		
	MotorDir(FWD,FWD);
	Msleep(500);
	MotorSpeed(0,0);
	
	
	
	

	while (1);
	return 0;
}
