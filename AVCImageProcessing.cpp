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

int open_gate(){

	/*Makes connection with server - returns 0 if connection is succesful*/
	int make_connection = connect_to_server("130.195.6.196", 1024);

	/*#### Test print to see if the connection is successful. 0 means connection is
	 * established with server ####*/
	printf("\nmake_connection = %d", make_connection);

	/*Sends message 'Please' to server. value stored in message variable should be
	 * 0 after transmitting message*/
	int message = send_to_server("Please");

	/*Server transmits password back. Password stored in variable*/
	int password = receive_from_server("");

	/*Send password back to server*/
	message = send_to_server("");

	return 0;

}

/*Method used to follow the white lines using error values and PID concepts*/
int follow_white_line(double error){

	/*Defining and initialising some variables*/
	const int slow_motor_compensate = 75;
	const double kp = 0.0; //Estimate this value later
	const double kd = 0.0; //Estimate this value later
	int velocity = 100;
	double difference_velocity;
	int velocity_right = 0;
	int velocity_left = 0;

	/*Calculating the difference in motor velocities by taking into account the
	 * error and the kp*/
	difference_velocity = error * kp; //Calculates the dv - result is a double
	//difference_velocity_unsigned = (unsigned char)difference_velocity; //casting back to unsigned char for use in set_motor methods

	/*Calculating velocities of the motors which scales with the error and kp*/
	velocity_left = velocity + difference_velocity;
	velocity_right = (velocity+slow_motor_compensate) - difference_velocity;

	/*Moving the motors based on the calculated velocities*/
	set_motor(1, velocity_left);
	set_motor(2, velocity_right);

	return 0;
}

/*Method to read the image in memory*/
void read_image(){/*#### Need to discuss what this method should return ####*/

	/* ##### This variable will be set to true later when the camera sees the red strip at the
	 * end of quadrant 2 (since we are using sensors for quadrant 3 instead of camera right?)####*/
	bool seen_red = false;

	/*Initializing some variables*/
	int pixel = 0;
	int row = 120; // #### Middle row, should we scan any other rows?
	int maximum_level = 0;
	int minimum_level = 255;
	double white_threshold = 0;
	double error = 0;
	double ratio = 0;
	int number_white_pixels = 0;
	int red_pixel = 0;

	/*#### Variables used for test print purposes in the for loops below ####*/
	int black = 0;
	int white = 0;
	int row_count = 0;

	while(seen_red == false){

		/*Takes picture, saves into memory*/
		take_picture();

		/*Looks for a red in the center row*/
		for(int i = 0; i<320; i++){
			red_pixel = get_pixel(row, i, 3);
			if(red_pixel > 200){ //if red exceeds estimated red threshold, red strip detected, exit method
				break;
			}
		}

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
		printf("\nwhite_threshold = %f", white_threshold);

		/*A for loop to detect the level of white for the pixels in the center row*/
		for(int i=0; i<320; i++){
			pixel = get_pixel(row, i, 3);//row = 120

			if(pixel>white_threshold){
				printf("%d", white);
				pixel = 1; //Sets pixel to 1 if it passes the threshold
				number_white_pixels++; //Incrementing number of white pixels if the pixel passes the threshold

			}else{
				pixel = 0;//Sets pixel to 0 if it does not pass the threshold
				printf("%d", black);
			}

			/*Uses the idea of negation to give an approximate distance of how far the robot
			 * is from the white line. The smaller the value of error, the closer to the
			 * white line*/
			error += (i-160)*pixel; //Error is the distance of the white line to the central pixel


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
		printf("\nnumber_white_pixels = %d", number_white_pixels);
		printf("\nnormalized error = %f", error);

		/*Calls follow_white_line method passing error as argument*/
		follow_white_line(error);
	}

	return;
}

int main(){
	init();
	open_gate(); //Opens gate for (Quadrant 1)
	read_image();//Reads and follows the path (Quadrant 2 and 3)


	return 0;
}
