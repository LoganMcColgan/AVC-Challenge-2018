#include <stdio.h>
#include "E101.h"
#include <time.h>

/*#### Need to discuss how we want the robot to turn. All code in here is
 * subject to change ####*/

/*#### An alternative way of turning is completely stopping one motor while the other
	 * motor continues. This will make the bot turn at a pivot. All methods right now
	 * makes the robot turn like a car.... ####*/

/*#### Should these methods be called in AVCImageProcessing.cpp file. Pass in error variable
 * as an argument? ####*/
void turn_left(){
	unsigned char velocity = 60;
	unsigned char difference_motors_velocity;
	//must calculate difference_motors_velocity by getting error in image processor and * kp
	//must cast error into double then * by kp (which is already a double) - this gives diff_motors in double
	//must cast diff_motors back into unsigned char to give correct value with addition with vel_right and vel_left
	unsigned char velocity_right;
	unsigned char velocity_left;
	set_motor(1, 60); //Left motor
	set_motor(2, 120); //Right motor
}

/*Method called to make robot turn right*/
void turn_right(){ //Left motor velocity > Right motor velocity
	//velocity_left = velocity + difference_motors_velocity;
	set_motor(1, 120); //Left motor
	set_motor(2, 60); //Right motor
}

/*Method called to make robot go straight*/
void move_straight(){
	set_motor(1, 120); //Left motor
	set_motor(2, 120); //Right motor
}

int main(){
	init();
	return 0;
}
