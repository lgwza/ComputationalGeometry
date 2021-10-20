#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define w 400

using namespace cv;

void MyLine(Mat img, Point start, Point end) {
	int thickness = 2;
	int lineType = LINE_8;

	line(img, start, end, Scalar(0, 0, 0), thickness, lineType);

}
