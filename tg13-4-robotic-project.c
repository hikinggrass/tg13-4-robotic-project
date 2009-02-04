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
//unsigned int data[2]; //Speicher bereitstellen

	Init(); //Init-Funktion der Lib
	
	asuro_init(); //unsre init-Funktion
	
	


  while (1);
  return 0;
}
