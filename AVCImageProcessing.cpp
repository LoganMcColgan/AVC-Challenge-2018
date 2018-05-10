#include <stdio.h>
#include "E101.h"
#include <time.h>

/*Notes - Delete this before hand in
 * - Comments with '####' denotes comments that should be deleted before hand in or replace with
 * more formal comment.
 *
 * -Camera image is 320x240 (in the form width x height or columns x rows)
 * (160,120) is the center pixel
 *
 * -There are 2 ways of attaining an image , take_picture() method which takes
 * a picture of the current image on the camera and stores in memory, or
 * 'int save_picture(char file_name[5])'which captures the image and saves it to
 * the same folder as the program (this consumes hard drive space)
 *
 * - get_pixel(int row, int column, int color) gets the color of one pixel in memory.
 * This returns an unsigned char which represents the level of a color present
 * in that pixel. 0 = Red, 1 = Green, 2 = Blue, 3 = White for color arguments.
 *
 * -  */

/*#### Moving methods used for quadrant 3 and 4 - Work on these later ####*/
void turn_left(){
	unsigned char velocity = 60;
	unsigned char difference_motors_velocity;
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
	set_motor(1, -100); //Left motor
	set_motor(2, -170); //Right motor
}

/*Method used to follow the white lines using error values and PID concepts*/
int followWhiteLine(double error){

	/*Defining and initialising some variables*/
	const unsigned char slow_motor_compensate = -75;
	const double kp = 0.0; //Estimate this value later
	const double kd = 0.0; //Estimate this value later
	unsigned char velocity = -100;
	double difference_velocity;
	unsigned char difference_velocity_unsigned = 0;
	unsigned char velocity_right;
	unsigned char velocity_left;

	/*Calculating the difference in motor velocities by taking into account the
	 * error and the kp*/
	difference_velocity = error * kp; //Calculates the dv - result is a double
	difference_velocity_unsigned = (unsigned char)difference_velocity; //casting back to unsigned char for use in set_motor methods

	/*Calculating velocities of the motors which scales with the error and kp*/
	/*#### We are subtracting difference_motors_velocity in here since the way the robot
	 * is wired makes it so that negative values move the robot forward####*/
	velocity_left = velocity - difference_velocity_unsigned;
	velocity_right = (velocity+slow_motor_compensate) + difference_velocity_unsigned;

	/*Moving the motors based on the calculated velocities*/
	set_motor(1, velocity_left);
	set_motor(2, velocity_right);

}

/*Method to read the image in memory*/
void read_image(){/*#### Need to discuss what this method should return ####*/

	/* ##### This variable will be set to true later when the camera sees the red strip at the
	 * end of quadrant 2 (since we are using sensors for quadrant 3 instead of camera right?)####*/
	bool seen_red = false;

	/*Initializing some variables*/
	unsigned char pixel = 0;
	int row = 120; // #### Middle row, should we scan any other rows?
	unsigned char maximum_level = 0;
	unsigned char minimum_level = 255;
	double white_threshold = 0;
	double error = 0;
	double ratio = 0;
	int number_white_pixels = 0;

	/*#### Variables used for test print purposes in the for loops below ####*/
	int black = 0;
	int white = 0;
	int row_count = 0;

	while(seen_red == false){

		/*#### Need to think about the threshold of 'white'. What value of white can we
		 * consider reasonable to pass as 'white'. Need to think about the levels of lighting
		 * etc. ####*/

		/*Takes picture, saves into memory*/
		take_picture();

		/*A for loop to determine the max and min values of white which can be used to
		 * calculate the threshold*/
		for(int i =0; i<320; i++){

			pixel = get_pixel(row, i, 3);

			/*First time the for loop runs, the maximum_level is set to the
			 * first pixel by default. As the for loop continues for the remaining columns in the
			 * row, max level and min level is set accordingly if the current pixel in iteration
			 * meets the conditions*/
			if (pixel < maximum_level){
				maximum_level = pixel;
			}

			if(pixel < minimum_level){
				minimum_level = pixel;
			}
		}

		/*Calculating threshold*/
		white_threshold = (maximum_level - minimum_level) / 2;
		printf("white_threshold = %f", white_threshold);

		/*A for loop to detect the level of white for the pixels in the center row*/
		for(int i=0; i<320; i++){
			pixel = get_pixel(row, i, 3);//row = 120

			/*Uses the idea of negation to give an approximate distance of how far the robot
			 * is from the white line. The smaller the value of error, the closer to the
			 * white line*/
			error += (i-160)*pixel; //Error is the distance of the white line to the central pixel

			/*#### Test print statement to determine if we are detecting white
			 * on the image correctly ####*/
			if(pixel>white_threshold){
				printf("%d", white);
				number_white_pixels++; //Incrementing number of white pixels if the pixel passes the threshold

			}else{
				printf("%d", black);
			}

			/*#### For testing purposes, prints 1s and 0s on multiple lines instead of being
			 * just printed on one big line*/
			if(row_count == 20){
				printf("\n"); //Creates new line
				row_count = 0;
			}
			row_count++;
		}

		/* #### Getting ratio to determine which side to increase - See pseudocode ####*/
		double ratio = 3200/error;

		/*Normalising error so we can find out how far out the white lines relative to the
		 * central pixel*/
		error /= number_white_pixels;

		/*#### Test print some stuff here to see if the code above actually works.... ####*/
		printf("number_white_pixels = %d", number_white_pixels);
		printf("normalized error = %f", error);

		/*Calls intFollowWhiteLine passing error as argument*/
		followWhiteLine(error);
	}

	return; /*Move to next method (quadrant 3)*/
}

int main(){
	init();
	//read_image();
	//call next method after read_image while loop breaks
	return 0;
}
