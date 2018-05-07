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
 * -For quadrant 2, there will be some intersections. Implement code so that if 3 pixels
 * are of the color white at the central row, go straight?
 *
 * */

/*Method to read the image in memory*/
int read_image(){/*#### Need to discuss what this method should return ####*/

	/* ##### This variable will be set to true later when the camera sees the red strip at the
	 * end of quadrant 2 (since we are using sensors for quadrant 3 instead of camera right?)####*/
	bool seen_red = false;

	/*Initializing some variables*/
	unsigned char pixel = 0;
	int row = 120; // #### Middle row, should we scan any other rows?
	unsigned char maximum_level = 0;
	unsigned char minimum_level = 255;
	unsigned char white_threshold = 0;
	int error = 0;


	while(seen_red == false){

		/*#### Need to think about the threshhold of 'white'. What value of white can we
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

		/*A for loop to detect the level of white for the pixels in the center row*/
		for(int i=0; i<320; i++){
			pixel = get_pixel(row, i, 3);

			/*Uses the idea of negation to give an approximate distance of how far the robot
			 * is from the white line. The smaller the value of error, the closer to the
			 * white line*/
			error += (i-160)*pixel;
		}
	}
}


int main(){
	init();

	return 0;
}
