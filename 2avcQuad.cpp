#include <stdio.h>
#include "/home/pi/Desktop/MYLibrary/LibE101/E101.h"
#include <time.h>
#include <sys/time.h>
#include <fstream>
#include <iostream>

int main(){
	init();
	bool seenRed = false;
	int pixel;
	int row = 120;
	int maxWhite = 0;
	int minWhite = 0;
	double whiteThreshold = 0;
	double error = 0;
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
	int motor1Speed = 75;
	int motor2Speed = 175;
	
	std::ofstream testlogs;
	testlogs.open("testlogs.txt", std::ios_base::app);

	while (!seenRed){
		error = 0;
		numWhitePixels = 0;
		
		gettimeofday(&time, 0);
		time1 = time.tv_sec+(time.tv_usec/1000000.0);

		//printf("Time difference: %f", time1-time2);

		if (time1-time2>0.25){
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
				if (i==0){
					maxWhite = pixel;
					minWhite = pixel;
				}
				else{
					if (pixel>maxWhite){
						maxWhite = pixel;
					}
					else if (pixel<minWhite){
						minWhite = pixel;
					}
				}
			}

			whiteThreshold = (maxWhite + minWhite) / 1.5;
			//printf("\nwhite_threshold = %f", whiteThreshold);

			for(int i=0; i<320; i++){
				pixel = get_pixel(row, i, 3);//row = 120

				if(pixel>whiteThreshold){
					//printf("%d", white);
					pixel = 1; //Sets pixel to 1 if it passes the threshold
					numWhitePixels++; //Incrementing number of white pixels if the pixel passes the threshold

				}else{
					pixel = 0;//Sets pixel to 0 if it does not pass the threshold
					//printf("%d", black);
				}

				error += (i-160)*pixel; //Error is the distance of the white line to the central pixel

				if(testRowCount == 20){
					//printf("\n"); //Creates new line
					testRowCount = 0;
				}

				testRowCount++;
			}

			int dV;
			double kP = 1.3;
			if (numWhitePixels!=0){
				error /= numWhitePixels;

				//printf("\nnumber_white_pixels = %d", numWhitePixels);
				//printf("\nnormalized error = %f", error);

				//1 = right
				//2 = left
				
				dV = (int) (((double) error)*kP);
				
				set_motor(1, motor1Speed-dV);
				set_motor(2, motor2Speed+dV);
				
				//printf("\n Speed dV = %d", dV);
			}
			else{
				//printf("\nSpeed 1/2: %d/%d", motor1Speed, motor2Speed);
				set_motor(1,-motor1Speed);
				set_motor(2,-motor2Speed);
			}

			gettimeofday(&time, 0);
			time2 = time.tv_sec+(time.tv_usec/1000000.0);

			testlogs << "\n**** START LOG ****";
			testlogs << "\nerror: \t" << error << "";
			testlogs << "\npixel \t" << pixel <<"";
			testlogs << "\nwhite_threshold = \t" << whiteThreshold << "";
			testlogs << "\n#### END LOG ####";
			testlogs << "\n";
		}
	}
	return 0;
}

