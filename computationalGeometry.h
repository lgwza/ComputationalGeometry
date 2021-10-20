#pragma once
#ifndef computationalGeometry
#define computationalGeometry

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <set>
#define w 400.0
using namespace cv;
using namespace std;


#define EXIT FAILURE 1
#define NEW(p, type) \
        if((p = (type *) malloc(sizeof(type))) == NULL){\
        printf("NEW: Out of Memory!\n");\
        exit(1);\
    }

#define ADD(head, p) if(head){\
        p->next = head;\
        p->prev = head->prev;\
        head->prev = p;\
        p->prev->next = p;\
    }\
    else{\
        head = p;\
        head->next = head->prev = p;\
    }

#define FREE(p) if(p) {free((char *)p); p = NULL;}

#define INF 1e100
#define X 0
#define Y 1
#define DIM 2
typedef int tPointi[DIM];
typedef class tVertexStructure tsVertex;
typedef tsVertex* tVertex;
class tVertexStructure {
public:
    int vnum;
    tPointi v;
    bool ear;
    tVertex next, prev;
};
void MyLine(Mat& img, const Point& start, const Point& end, const Scalar& color);
// 三角形 abc 有向面积的两倍
int Area2(const tPointi& a, const tPointi& b, const tPointi& c);
// 判断点 c 在向量 ab 的左边
bool Left(const tPointi& a, const tPointi& b, const tPointi& c);
// 判断点 c 在向量 ab 的左边或其上
bool LeftOn(const tPointi& a, const tPointi& b, const tPointi& c);
// 点 a, b, c 三点共线
bool Collinear(const tPointi& a, const tPointi& b, const tPointi& c);
// 线段 ab 与 cd 恰当相交
bool IntersectProp(const tPointi& a, const tPointi& b, const tPointi& c, const tPointi& d);
// 点 c 在线段 ab 上
bool Between(const tPointi& a, const tPointi& b, const tPointi& c);
// 判断线段 ab 与 cd 是否相交
// 返回值为 2 是恰当相交, 1 是非恰当的相交, 0 是不相交
int Intersect(const tPointi& a, const tPointi& b, const tPointi& c, const tPointi& d);

class Polygon {
public:
    tVertex head;
    tVertex vertices;
    vector <pair<double, double>> pInput;
    vector <pair<double, double>> pTransformed;
    int nvertices;
    pair<double, double> maxCoor;
    pair<double, double> minCoor;
    set<pair<int, int>> pSet;
    
    Polygon() {
        head = NULL;
        vertices = NULL;
        maxCoor = { -INF, -INF };
        minCoor = { INF, INF };
    }
    // 多边形面积的两倍
    int AreaPoly2();
    // 判断线段 ab 不与多边形的边相交
    bool Diagonalie(const tVertex& a, const tVertex& b) const;
    // 判断线段 ab 在多边形内部
    bool InCone(const tVertex& a, const tVertex& b) const;
    // 判断线段 ab 是不是多边形的对角线
    bool Diagonal(const tVertex& a, const tVertex& b) const;
    // 初始化耳朵相关信息
    void EarInit();
    // 打印对角线
    void PrintDiagonal(const tVertex& a, const tVertex& b) const;
    // 切耳朵三角剖分
    void Triangulate();
    // 读入多边形点，重点去重
    void ReadVertices();
    // 坐标变换，使其适应于 opencv 作图
    void CoordinatesTransformation();
};

#endif // !computationalGeometry