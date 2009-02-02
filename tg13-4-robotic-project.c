/*****************************************************************************
 * tg13-4-robotic-project.c : This is were the "magic" happens...
 *****************************************************************************
 * Copyright (C) 2008 the tg13-4-robotic-project Team
 * $Id$
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
const int ls = 255;
const int rs = 249;
const int white = 40;
const int fahrzeit1 = 550; 
const int fahrzeit2 = 230;
const int fahrzeit3 = 650;
const int fahrzeit4 = 150;
const int fahrzeit5 = 100;
const int drehzeit1 = 540; //90°-Drehung mit einem Motor
const int drehzeit2 = 250; //90°-Drehung mit zwei Motoren

int main(void)
{
  unsigned int data[2]; //Speicher bereitstellen
  Init();

MotorDir(FWD, FWD);

MotorSpeed(ls, rs);
Msleep(fahrzeit1); //Fährt zum Eingang des Labyrinths

MotorSpeed(ls, 0); 
Msleep(drehzeit1); //Dreht sich zum Eingang hin
/*
MotorSpeed(ls, rs);
Msleep(fahrzeit2); //Fährt ins Labyrinth hinein

MotorSpeed(ls, 0);
Msleep(drehzeit1); //erste Drehung im Labyrinth

MotorDir(RWD, FWD);
MotorSpeed(ls, rs);
Msleep(drehzeit2); //zweite Drehung im Labyrinth

MotorDir(FWD, FWD);
//MotorSpeed passt
Msleep(fahrzeit3); //fährt das gerade Stück im Labyrinth

MotorSpeed(0, rs);
Msleep(drehzeit1); //dreht am Kopfstück

MotorSpeed(ls,rs);
Msleep(fahrzeit4); //fährt am Kopfstück entlang

MotorSpeed(0, rs);
Msleep(drehzeit1); //dreht am Kopfstück

MotorSpeed(ls, rs);
Msleep(fahrzeit5); //fährt in die bösen Ecke

MotorSpeed(ls, 0);
Msleep(drehzeit1); //dreht in der bösen Ecke

MotorSpeed(0, rs);
Msleep(drehzeit1); //dreht aus der bösen Ecke heraus

MotorSpeed(ls, rs);
Msleep(fahrzeit4); //fährt durchs Endstück
*/
MotorSpeed(0, 0);
 /*
  FrontLED(ON);
  
  MotorDir(FWD, FWD);
  MotorSpeed(ls, rs);
  LineData(data);
  while(data[0] <= white || data[1] <= white)
	LineData(data);
  MotorSpeed(0,0);
  Msleep(1000);
  MotorSpeed(ls, rs);
  while(data[0] > white || data[1] > white)
	LineData(data);
  Msleep(200);
  MotorSpeed(0,0);
  Msleep(200);
  MotorSpeed(ls, rs);
  MotorDir(FWD, RWD);

  //MotorSpeed(0,0);
*/
  while (1);
  return 0;
}
