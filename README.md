Binary-Graphcut
===============

Binary Image Segmentation using GraphCut

Installation
-----------

    Link openCV

Usage
-----

    GRAPHCUT graphCut;
    graphCut.graphCut(Image, neighboursWeight, windowSize);
    
`neighboursWeight` represents the neighbours influence weight.
`windowSize` represents the window around each pixel, 1 means the first 8 nearst neighbours.