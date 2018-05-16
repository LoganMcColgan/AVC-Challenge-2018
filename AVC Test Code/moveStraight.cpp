#include <stdio.h>
#include <time.h>
#include "/home/pi/Desktop/MYLibrary/LibE101/E101.h"

int main(){
	init();
	int i = 0;
	while(i<10){
		set_motor(1, -100);
		set_motor(2, -175);
		sleep1(1, 0);
		i++;
	}
	return 0;

}
