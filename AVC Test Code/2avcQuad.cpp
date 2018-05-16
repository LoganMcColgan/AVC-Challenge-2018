#include <stdio.h>
#include "/home/pi/Desktop/MYLibrary/LibE101/E101.h"
#include <time.h>
#include <sys/time.h>

int main(){
	init();
	bool seenRed = false;
	int pixel;
	int row = 120;
	int maxWhite = 0;
	int minWhite = 0;
	double whiteThreshold = 0;
	double error = 0;
	double motorRatio = 0;
	int numWhitePixels = 0;
	int redPixel = 0;
	int bluePixel = 0;
	int greenPixel = 0;
	int black = 0;
	int white = 1;
	int testRowCount = 0;
	struct timeval time;
	double time1;
	double time2 = 0;
	
	set_motor(1,-100);
	set_motor(2,-175);

	while (!seenRed){
		error = 0;
		
		gettimeofday(&time, 0);
		time1 = time.tv_sec+(time.tv_usec/1000000.0);

		//printf("Time difference: %f", time1-time2);

		if (time1-time2>0.5){
			take_picture();

			for (int i = 0; i<320; i++){
				redPixel = get_pixel(row, i, 0);
				greenPixel = get_pixel(row, i, 1);
				bluePixel = get_pixel(row, i, 2);
				if (redPixel > 200 && greenPixel < 50 && bluePixel < 50){
					break;
				}
			}

			for(int i =0; i<320; i++){
				pixel = get_pixel(row, i, 3);
				if (pixel > maxWhite){
					maxWhite = pixel;
				}

				if(pixel < minWhite){
					minWhite = pixel;
				}
			}

			whiteThreshold = (maxWhite - minWhite) / 2;
			//printf("\nwhite_threshold = %f", whiteThreshold);

			for(int i=0; i<320; i++){
				pixel = get_pixel(row, i, 3);//row = 120

				if(pixel>whiteThreshold){
					printf("%d", white);
					pixel = 1; //Sets pixel to 1 if it passes the threshold
					numWhitePixels++; //Incrementing number of white pixels if the pixel passes the threshold

				}else{
					pixel = 0;//Sets pixel to 0 if it does not pass the threshold
					printf("%d", black);
				}

				error += (i-160)*pixel; //Error is the distance of the white line to the central pixel

				if(testRowCount == 20){
					printf("\n"); //Creates new line
					testRowCount = 0;
				}

				testRowCount++;
			}

			if (error!=0){
				error /= numWhitePixels;
			}
			
			motorRatio = 3200/error;

			//printf("\nnumber_white_pixels = %d", numWhitePixels);
			//printf("\nnormalized error = %f", error);
			
			int newMotorSpeed;
			int constant = 30;
			if (error < 0){
				newMotorSpeed = 175+(constant*-motorRatio);
				set_motor(2, -newMotorSpeed);
			}
			else if (error > 0){
				newMotorSpeed = 100+(constant*motorRatio);
				set_motor(1, -newMotorSpeed);
			}
			printf("\n Speed = %d", newMotorSpeed);
			
			gettimeofday(&time, 0);
			time2 = time.tv_sec+(time.tv_usec/1000000.0);
		}
	}
	return 0;
}

