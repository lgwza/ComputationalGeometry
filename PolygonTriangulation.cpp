#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include "OpenCV.h"
#include "computationalGeometry.h"

using namespace std;
using namespace cv;


int main() {
    Polygon polyTriangulated;

    Mat triangulationImage = Mat::zeros(w, w, CV_64FC3);
    triangulationImage = Scalar(255, 255, 255);

    freopen("inputExtreme2.txt", "r", stdin);
    

    polyTriangulated.ReadVertices();

    cout << "Area: " << polyTriangulated.AreaPoly2() / 2.0 << "\n";

    freopen("OutputData.txt", "w", stdout);

    polyTriangulated.Triangulate();
    polyTriangulated.CoordinatesTransformation();
    
    for (int i = 0; i < polyTriangulated.nvertices; i++) {
        auto vnow = polyTriangulated.pTransformed[i], vnext = polyTriangulated.pTransformed[(i + 1) % polyTriangulated.nvertices];
        double X1, X2, Y1, Y2;
        X1 = vnow.first;
        X2 = vnext.first;
        Y1 = vnow.second;
        Y2 = vnext.second;
        MyLine(triangulationImage, Point(X1, Y1), Point(X2, Y2), (0, 0, 255));
    }
    cin.clear();
    freopen("OutputData.txt", "r", stdin);
    vector<pair<int, int>> vp;
    int x, y;
    while (cin >> x >> y) {
        vp.emplace_back(x, y);
    }
    int vpSize = vp.size();
    for (int i = 0; i < vpSize; i++) {
        auto vnow = polyTriangulated.pTransformed[vp[i].first], vnext = polyTriangulated.pTransformed[vp[i].second];
        double X1, X2, Y1, Y2;
        X1 = vnow.first;
        X2 = vnext.first;
        Y1 = vnow.second;
        Y2 = vnext.second;
        MyLine(triangulationImage, Point(X1, Y1), Point(X2, Y2), (255, 0, 0));
    }
    namedWindow("triangulationImage", WINDOW_FREERATIO);
    imshow("triangulationImage", triangulationImage);
    waitKey(0);
    return 0;
}