#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_SCORE 10e2
#define Z_SCORE 1.959963984540
#define CONFIDENCE 0.95

//Returns a score between 0 and 1
float score(int positiveRatings, int totalRatings) {
	if (totalRatings == 0 || positiveRatings == 0) return 0;	
	float phat = 1.0*positiveRatings/totalRatings;
	float z = Z_SCORE;
	return ( phat + z*z/(2*positiveRatings) - z * sqrt( (phat*(1-phat)+z*z/(4*totalRatings)) / totalRatings ) ) /(1+z*z/totalRatings);
}

int main(int argc, char *argv[]) {	
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {				
		int positiveRatings = 0;
		int totalRatings = 0;
		
		int x = (int)rand() % (int)MAX_SCORE;
		int y = (int)rand() % (int)MAX_SCORE;
		if (x > y) {
			totalRatings = x;
			positiveRatings = y;
		} else {
			totalRatings = y;
			positiveRatings = x;
		}
		
		float s = score(positiveRatings, totalRatings);
		printf("Positive Ratings: %d\tTotal Ratings: %d\tAverage Score: %.2f%%\tWilson Score: %.2f%%\n", positiveRatings, totalRatings, 1.0*positiveRatings/totalRatings*100 ,s*100);
	}
}