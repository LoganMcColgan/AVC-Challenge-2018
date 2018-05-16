#include <stdio.h>
#include <time.h>
#include "/home/pi/Desktop/MYLibrary/LibE101/E101.h"

int main(){
	init();
	//unsigned char pixel = 0;
	int white = 1;
	int black = 0;
	int row = 120;
	double maximum_level = 0;
	double minimum_level = 255;
	double white_threshold = 0;
	double error = 0;
	unsigned char pixel  = 0;
	take_picture();
	for(int i =0; i<320; i++){
		unsigned char pixel = get_pixel(row, i, 3);
		if(pixel < maximum_level){maximum_level = pixel;}
		if(pixel < minimum_level){minimum_level = pixel;}
	}
		white_threshold = (maximum_level - minimum_level)/2;
		printf("\nWhite threshold = %f", white_threshold);
	return 0;
}
