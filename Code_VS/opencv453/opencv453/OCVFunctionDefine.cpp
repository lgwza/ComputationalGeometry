#include "OpenCV.h"
using namespace cv;

void MyLine(const Mat& img, const Point& start, const Point& end, const Scalar& color) {
    int thickness = 1;
    int lineType = LINE_8;
    Point move(0, 0);
    line(img, start + move, end + move, color, thickness, lineType);
}