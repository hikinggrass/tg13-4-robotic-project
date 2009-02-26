/********************************************
Böses, dummes Projekt.
*********************************************
Soll einfach stupide der Linie folgen,
bis er ins Laby wechselt,
dann blöd rumbouncen und so weiter.
*********************************************
Hierfür wird es sicher keinen Kuchen geben.
*********************************************
Autor: Matthias Holoch
********************************************/

#include "asuro.h"
#include "inc.c"

/********************************************
Includes done. Cake plz? :X
********************************************/



int main(void)
{
	Init(); //Asuros Initfunktion ... is a lie!
	
	int devNull = asuro_init(); //unsre init-Funktion
	unsigned int data[2];
	int mode = 0; //Zustandsvariable. 0 = Linie folgen, 1 = Linienfolge-Korretur, 2 = Gerades Stück!..., 3 = im Labyirinth gerade aus
	int mode_alt = 0; //braucht man, um die Linie-Labyrinth-übergänge sauber zu erkennen.
	unsigned long zeit = 0; //Hilfsvariable, damit die Zustand nur in bestimmten Zeitabständen geändert werden kann. Damit reagiert all das nicht mehr so giftig.
	int l = 0;
	int r = 0;
	
	MotorDir(FWD,FWD);
	MotorSpeed(msl - 80,msr - 80);
	FrontLED(ON);
	
	LineData(data);			//ein Startwert!
	
	
	while(mode == 0 || mode == 1 || mode == 2) //Solang man im Labyrinthteil ist...
	{
		LineData(data);		//ein neuer Wert!
				
		if(data[0] >= white_l - 20 && data[1] >= white_r - 20)	//FALLS: Mit beiden Sensoren auf weiß?
		{
			if(mode_alt == 1 || mode_alt == 0)		//FALLS: Zuvor schräg? ODER schon in Korrektur gewesen?
			{
				MotorDir(RWD,RWD);		//Dann rückwärts und
				mode = 1;				//in den Korrektur-Modus (1) ... Bedeutet so viel wie: Linie verloren! ;_;   (this should never happen :P )
			}
			/*else						//FALLS: Zuvor gerade?
			{
				MotorDir(FWD,FWD);		//Dann brav weiterfahren. Hier müssten wir am Dreieck vom Labyrinth sein. --> Einfach gerade aus fahren.
				mode = 3;
			}*/
		}
		
		if(data[0] >= white_l - 20 && data[1] <= black_r + 20)	//FALLS: links von der Linie
		{
			if(Gettime() - zeit <= 700 && Gettime() - zeit >= 500)	//VERSUCH der Labyrinth-Eintritts-Abfrage... (tut noch nicht wirklich ganz)
			{															//FALLS: Länger als 500 und kürzer als 700 ms gerade aus auf schwarz gefahren (=Dreieck!) ... (hier muss man evtl noch dran drehen)
				MotorDir(FWD,FWD);
				zeit = Gettime();
				
				while(Gettime() - zeit <= 200)							//Mit neuer Zeit eine Sicherheitsüberprüfung. Wird innerhalb von zwei Sekunden jeder der Sensoren mindestens einmal (wieder) schwarz? 
				{														//(Damit ist der dünne schwarze Strich gemeint!
					LineData(data);
					
					if(l == 0)
						if(data[0] <= black_l + 20)
							l = 1;
					if(r == 0)
						if(data[1] <= black_r + 20)
							r = 1;
				}
				
				if(l == 1 && r == 1)
					mode = 3;											//DANN: Modus 3, also "im Labyrinth"
				else
					MotorDir(RWD,RWD);
			}
			else
			{
				MotorDir(FWD,RWD);		//Dann Korrektur nach rechts
				mode = 0;
				zeit = 0;
			}
		}
		
		if(data[0] <= black_l + 20 && data[1] >= white_r - 20)	//FALLS: rechts von der Linie
		{
			if(Gettime() - zeit <= 700 && Gettime() - zeit >= 500)	//Siehe oben, bei dem "links von der Linie-Fall" ... ist auch die Labyrinth-Eintritts-Abfrage.
			{
				MotorDir(FWD,FWD);
				zeit = Gettime();
				
				while(Gettime() - zeit <= 100)
				{
					LineData(data);
					
					if(l == 0)
						if(data[0] <= black_l + 20)
							l = 1;
					if(r == 0)
						if(data[1] <= black_r + 20)
							r = 1;
				}
				
				if(l == 1 && r == 1)
					mode = 3;
				else
					MotorDir(RWD,RWD);
			}
			else
			{
				MotorDir(RWD,FWD);		//Dann Korrektur nach links
				mode = 0;
				zeit = 0;
			}
		}
		
		if(data[0] <= black_l + 20 && data[0] <= black_r + 20)	//FALLS: Beide Sensoren auf der Linie (auf Schwarz)?
		{
			MotorDir(FWD,FWD);		//Dann einfach gerade aus fahren
			if(mode != 2)			
			{
				zeit = Gettime();	//Zeit wird gespeichert, für die Labyirinthseintrittsabfrage (s.o.)
				mode = 2;
			}
		}
	}
	
	//MotorSpeed(0,0);
	
	return 0;
}