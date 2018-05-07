/*Program to move robot in straight line endlessly - Created 3/5/18*/

#include <stdio.h>
#include "E101.h"
#include <time.h>

int main(){

	/*Makes the robot move in a straight line endlessly*/
	while (1){
		set_motor(1, 60);
		set_motor(2, 60);
		//sleep1(1,0);
	}


	return 0;
}
