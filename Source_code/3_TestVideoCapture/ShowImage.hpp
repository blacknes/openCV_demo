#include <iostream>
#include <vector>

// Include OpenCV's C++ Interface
#include "opencv2/opencv.hpp"


using namespace cv;
using namespace std;


void cartoonifyImage(Mat srcColor, Mat dst, bool sketchMode, bool alienMode, bool evilMode, int debugType);


// Draw an anti-aliased face outline, so the user knows where to put their face.
void drawFaceStickFigure(Mat dst);


void changeFacialSkinColor(Mat smallImgBGR, Mat bigEdges, int debugType);
void removePepperNoise(Mat &mask);
void drawFaceStickFigure(Mat dst);

