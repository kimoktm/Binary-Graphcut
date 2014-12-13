#include "GraphCut.h"

int main()
{
	Mat source, output;
	GRAPHCUT graphCut;

	// Window size around each pixel
	// 1 means first nearst neighbours (8)
	int windowSize = 2;

	// Neighbours influence weight
	float neighboursWeight = 0.06;

	source = imread("Lenna.png");
	output = graphCut.graphCut(source, neighboursWeight, windowSize);

	imshow("Original Image", source);
	imshow("Segmented Image", output);

	waitKey(0);
	return 0;
}
