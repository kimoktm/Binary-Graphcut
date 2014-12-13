/*
 * GraphCut.cpp
 *
 *  Created on: Dec 13, 2014
 *  Author: Karim Tarek
 */
#include "GraphCut.h"

/**
 * GraphCut an image into
 * Binary image
 *
 * @param image			The Source image
 * @param neighboursWeight	Neighbours influence
 * @param windowSize	Neighbours range
 *
 *
 * @return Segmented Image
 */
Mat GRAPHCUT::graphCut(Mat img, float neighboursWeight, int windowSize)
{
	Mat segmentedImg;
	GCGraph<float> graph((img.rows * img.cols), (img.rows * img.cols * 8));

	img2graph(graph, img, neighboursWeight, windowSize);
	graph.maxFlow();
	segmentedImg = graph2img(graph, img.rows, img.cols);

	return segmentedImg;
}



/**
 * Convert a Graph
 * into an image
 *
 * @param graph			The Source graph
 * @param rows			Image Height
 * @param cols			Image Width
 *
 *
 * @return Converted Image
 */
Mat GRAPHCUT::graph2img(GCGraph<float>& graph, int rows, int cols)
{
	Mat img(rows, cols, CV_32F);

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			img.at<float>(r, c) = graph.inSourceSegment(c + img.cols * r);

	return img;
}



/**
 * Convert an Image
 * into a Graph
 *
 * @param graph			The graph pointer
 * @param img			The Source image
 * @param neighboursWeight	Neighbours influence
 * @param windowSize	Neighbours range
 *
 *
 * @return Updates the graph
 */
void GRAPHCUT::img2graph(GCGraph<float>& graph, Mat& img, float neighboursWeight, int windowSize)
{
	cvtColor(img, img, CV_BGR2GRAY);
	normalize(img, img, 0, 1, NORM_MINMAX, CV_32F);

	addVertices(graph, img);
	addEdges(graph, img, neighboursWeight, windowSize);
}



/**
 * Add each pixel as
 * a node in a graph
 *
 * @param graph			The graph pointer
 * @param img			The Source image
 *
 *
 * @return Updates the graph
 */
void GRAPHCUT::addVertices(GCGraph<float>& graph, Mat& img)
{
	for (int r = 0; r < img.rows; r++)
		for (int c = 0; c < img.cols; c++)
		{
			graph.addVtx();
			graph.addTermWeights(c + img.cols * r, img.at<float>(r, c), 1 - img.at<float>(r, c));
		}
}



/**
 * Add edges between
 * nodes in a graph
 *
 * @param graph			The graph pointer
 * @param img			The Source image
 * @param neighboursWeight	Neighbours influence
 * @param windowSize	Neighbours range
 *
 * @return Updates the graph
 */
void GRAPHCUT::addEdges(GCGraph<float>& graph, Mat& img, float neighboursWeight, int windowSize)
{
	for (int r = windowSize; r < img.rows - windowSize; r++)
		for (int c = windowSize; c < img.cols - windowSize; c++)
			for (int i = -windowSize; i <= windowSize; i++)
				for (int j = -windowSize; j <= windowSize; j++)
					if (i != 0 || j != 0)
					{
						float v = abs(img.at<float>(r, c) - img.at<float>(r + i, c + j)) * neighboursWeight;
						graph.addEdges(c + img.cols * r, (c + j) + img.cols * (r + i), v, v);
					}
}
