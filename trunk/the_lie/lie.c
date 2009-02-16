/********************************************
B�ses, dummes Projekt.
*********************************************
Soll einfach stupide der Linie folgen,
bis er ins Laby wechselt,
dann bl�d rumbouncen und so weiter.
*********************************************
Hierf�r wird es sicher keinen Kuchen geben.
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
	int mode = 0; //Zustandsvariable. 0 = Linie folgen, 1 = Linienfolge-Korretur, 2 = Gerades St�ck!...
	int mode_alt = 0; //braucht man, um die Linie-Labyrinth-�berg�nge sauber zu erkennen.
	//unsigned long zeit; //Hilfsvariable, damit die Zustand nur in bestimmten Zeitabst�nden ge�ndert werden kann. Damit reagiert all das nicht mehr so giftig.
	
	MotorDir(FWD,FWD);
	MotorSpeed(msl - 80,msr - 80);
	FrontLED(ON);
	
	LineData(data);			//ein Startwert!
	//zeit = Gettime();		//ein Startwert!
	
	while(mode == 0 || mode == 1 || mode == 2) //Solang man im Labyrinthteil ist...
	{
		LineData(data);		//ein neuer Wert!
		
		/*if(Gettime() >= zeit + 200)
		{
			zeit = Gettime();
			mode_alt = mode;	//Der mode des letzten Durchgangs aufheben
		}*/
		
		if(data[0] >= white_l - 20 && data[1] >= white_r - 20)	//FALLS: Mit beiden Sensoren auf wei�?
		{
			if(mode_alt == 1 || mode_alt == 0)		//FALLS: Zuvor schr�g?
			{
				MotorDir(RWD,RWD);		//Dann r�ckw�rts und
				mode = 1;				//in den Korrektur-Modus (1) ... Bedeutet so viel wie: Linie verloren! ;_;   (this should never happen :P )
			}
			/*else						//FALLS: Zuvor gerade?
			{
				MotorDir(FWD,FWD);		//Dann brav weiterfahren. Hier m�ssten wir am Dreieck vom Labyrinth sein. --> Einfach gerade aus fahren.
				mode = 3;
			}*/
		}
		
		if(data[0] >= white_l - 20 && data[1] <= black_r + 20)	//FALLS: links von der Linie
		{
			MotorDir(FWD,RWD);		//Dann Korrektur nach rechts
			mode = 0;
		}
		
		if(data[0] <= black_l + 20 && data[1] >= white_r - 20)	//FALLS: rechts von der Linie
		{
			MotorDir(RWD,FWD);		//Dann Korrektur nach links
			mode = 0;
		}
		
		if(data[0] <= black_l + 20 && data[0] <= black_r + 20)	//FALLS: Beide Sensoren auf der Linie (auf Schwarz)?
		{
			MotorDir(FWD,FWD);		//Dann einfach gerade aus fahren
			mode = 2;				//und f�r den n�chsten Durchlauf festhalten, dass man gerade war. (siehe "else" oben)
		}
	}
	
	MotorSpeed(0,0);
	
	return 0;
}