/*
 * GraphCut.h
 *
 *  Created on: Dec 13, 2014
 *  Author: Karim Tarek
 */

#ifndef GRAPHCUT_H
#define GRAPHCUT_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cvgcgraph.h"

#define NEIGHBOURS_WINDOW						1
#define NEIGHBOURS_WEIGHT						0.1

using namespace std;
using namespace cv;

class GRAPHCUT
{
private:
	void addVertices(GCGraph<float>& graph, Mat& img);
	void addEdges(GCGraph<float>& graph, Mat& img, float neighboursWeight, int windowSize);

public:
	Mat graphCut(Mat img, float neighboursWeight = NEIGHBOURS_WEIGHT, int windowSize = NEIGHBOURS_WINDOW);
	Mat graph2img(GCGraph<float>& graph, int rows, int cols);

	void img2graph(GCGraph<float>& graph, Mat& img, float neighboursWeight, int windowSize);
};

#endif
