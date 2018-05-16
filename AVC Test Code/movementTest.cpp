#include <stdio.h>
#include <time.h>
#include "/home/pi/Desktop/MYLibrary/LibE101/E101.h"

int main(){
	init();

	//backward
	set_motor(1, 100);
	set_motor(2, 175);
	sleep1(1,25000);
	set_motor(1,0);
	set_motor(2,0);
	sleep1(1,0);

	//foreward
	set_motor(1, -100);
	set_motor(2, -165);
	sleep1(1,25000);
	set_motor(1,0);
	set_motor(2, 0);
	sleep1(1,0);

	//hard left
	set_motor(1, 175);
	set_motor(2, -175);
	sleep1(1,25000);
	set_motor(1,0);
	set_motor(2,0);
	sleep1(1,0);

	//hard right
	set_motor(1, -175);
	set_motor(2, 165);
	sleep1(1,25000);
	set_motor(1,0);
	set_motor(2,0);

	return 0;	
}
