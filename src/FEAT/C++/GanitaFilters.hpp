// 2d Sobel operator
int sobelg2d[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
// 3d Sobel operator
int sobelg3d[3][3][3] = {{{-1,0,1},{-3,0,3},{-1,0,1}},
			 {{-3,0,3},{-6,0,6},{-3,0,3}},
			 {{-1,0,1},{-3,0,3},{-1,0,1}}};

// Dimension used for modified Sobel operator.
// pdim=2 is L2
double pdim = 1;

// Threshold
double threshg1 = 2;

// number of statistics to track
#ifndef NUM_STATS
#define NUM_STATS 2
#endif

