/*Program to test the motors - Created 3/5/18*/

/*Used libraries and headers*/
#include <stdio.h>
#include "E101.h"
#include <time.h>

/*Main method*/
int main(){
	
	/*Intializes the RPI*/
	init();
	
	/*For loop to test the motors*/
	for (int i = 0; i < 5; i++){
		set_motor(1, 60);
		set_motor(2, 60);
		sleep1(1, 0); //1 second
	}
	return 0;
}
