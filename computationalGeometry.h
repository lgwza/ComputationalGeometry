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
// ������ abc �������������
int Area2(const tPointi& a, const tPointi& b, const tPointi& c);
// �жϵ� c ������ ab �����
bool Left(const tPointi& a, const tPointi& b, const tPointi& c);
// �жϵ� c ������ ab ����߻�����
bool LeftOn(const tPointi& a, const tPointi& b, const tPointi& c);
// �� a, b, c ���㹲��
bool Collinear(const tPointi& a, const tPointi& b, const tPointi& c);
// �߶� ab �� cd ǡ���ཻ
bool IntersectProp(const tPointi& a, const tPointi& b, const tPointi& c, const tPointi& d);
// �� c ���߶� ab ��
bool Between(const tPointi& a, const tPointi& b, const tPointi& c);
// �ж��߶� ab �� cd �Ƿ��ཻ
// ����ֵΪ 2 ��ǡ���ཻ, 1 �Ƿ�ǡ�����ཻ, 0 �ǲ��ཻ
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
    // ��������������
    int AreaPoly2();
    // �ж��߶� ab �������εı��ཻ
    bool Diagonalie(const tVertex& a, const tVertex& b) const;
    // �ж��߶� ab �ڶ�����ڲ�
    bool InCone(const tVertex& a, const tVertex& b) const;
    // �ж��߶� ab �ǲ��Ƕ���εĶԽ���
    bool Diagonal(const tVertex& a, const tVertex& b) const;
    // ��ʼ�����������Ϣ
    void EarInit();
    // ��ӡ�Խ���
    void PrintDiagonal(const tVertex& a, const tVertex& b) const;
    // �ж��������ʷ�
    void Triangulate();
    // �������ε㣬�ص�ȥ��
    void ReadVertices();
    // ����任��ʹ����Ӧ�� opencv ��ͼ
    void CoordinatesTransformation();
};

#endif // !computationalGeometry