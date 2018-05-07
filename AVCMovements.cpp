#include <stdio.h>
#include "E101.h"
#include <time.h>

/*#### Need to discuss how we want the robot to turn. All code in here is
 * subject to change ####*/

/*#### An alternative way of turning is completely stopping one motor while the other
	 * motor continues. This will make the bot turn at a pivot. All methods right now
	 * makes the robot turn at the center point ####*/

void turn_left(){
	set_motor(1, 60); //Left motor
	set_motor(2, 120); //Right motor
}

void turn_right(){
	set_motor(1, 120); //Left motor
	set_motor(2, 60); //Right motor
}

void move_straight(){
	set_motor(1, 120); //Left motor
	set_motor(2, 120); //Right motor
}

int main(){
	init();
	return 0;
}
