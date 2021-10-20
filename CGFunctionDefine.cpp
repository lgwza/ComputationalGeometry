#include "computationalGeometry.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using namespace cv;

void MyLine(Mat& img, const Point& start, const Point& end, const Scalar& color) {
    int thickness = 1;
    int lineType = LINE_8;
    line(img, start, end, color, thickness, lineType);
}
// ���� ab �� ���� ac ��ɵ��������������������
int Area2(const tPointi& a, const tPointi& b, const tPointi& c) {
    return (b[X] - a[X]) * (c[Y] - a[Y]) -
        (c[X] - a[X]) * (b[Y] - a[Y]);
}

// �жϵ� c ������ ab �����
bool Left(const tPointi& a, const tPointi& b, const tPointi& c) {
    return Area2(a, b, c) > 0;
}

// �жϵ� c ������ ab ����߻�����
bool LeftOn(const tPointi& a, const tPointi& b, const tPointi& c) {
    return Area2(a, b, c) >= 0;
}

// �� a, b, c ���㹲��
bool Collinear(const tPointi& a, const tPointi& b, const tPointi& c) {
    return Area2(a, b, c) == 0;
}

// �߶� ab �� cd ǡ���ཻ
bool IntersectProp(const tPointi& a, const tPointi& b, const tPointi& c, const tPointi& d) {
    if (Collinear(a, b, c) || Collinear(a, b, d) ||
        Collinear(c, d, a) || Collinear(c, d, b))
        return false;
    return (Left(a, b, c) ^ Left(a, b, d)) &&
        (Left(c, d, a) ^ Left(c, d, b));
}

// �� c ���߶� ab ��
bool Between(const tPointi& a, const tPointi& b, const tPointi& c) {
    if (!Collinear(a, b, c))
        return false;
    if (a[X] != b[X])
        return ((a[X] <= c[X]) && (c[X] <= b[X])) ||
        ((a[X] >= c[X]) && (c[X] >= b[X]));
    else
        return ((a[Y] <= c[Y]) && (c[Y] <= b[Y])) ||
        ((a[Y] >= c[Y]) && (c[Y] >= b[Y]));
}

// �ж��߶� ab �� cd �Ƿ��ཻ
// ����ֵΪ 2 ��ǡ���ཻ, 1 �Ƿ�ǡ�����ཻ, 0 �ǲ��ཻ
int Intersect(const tPointi& a, const tPointi& b, const tPointi& c, const tPointi& d) {
    if (IntersectProp(a, b, c, d))
        return 2;
    else if (Between(a, b, c) ||
        Between(a, b, d) ||
        Between(c, d, a) ||
        Between(c, d, b))
        return 1;
    else return 0;
}

int Polygon::AreaPoly2() {
    int sum = 0;
    tVertex p, a;
    p = vertices;
    a = p->next;
    do {
        sum += Area2(p->v, a->v, a->next->v);
        a = a->next;
    } while (a->next != vertices);
    return sum;
}

// �ж��߶� ab �������εı��ཻ
bool Polygon::Diagonalie(const tVertex& a, const tVertex& b) const {
    tVertex c, c1;
    c = vertices;
    do {
        c1 = c->next;
        if ((c != a) && (c1 != a) &&
            (c != b) && (c1 != b) &&
            Intersect(a->v, b->v, c->v, c1->v))
            return false;
        c = c->next;
    } while (c != vertices);
    return true;
}

// �ж��߶� ab �ڶ�����ڲ�
bool Polygon::InCone(const tVertex& a, const tVertex& b) const {
    tVertex a0, a1;
    a1 = a->next;
    a0 = a->prev;
    // �� a ��͹��
    if (LeftOn(a->v, a1->v, a0->v))
        return Left(a->v, b->v, a0->v) &&
        Left(b->v, a->v, a1->v);
    // �� a �ǰ���
    else
        return !(LeftOn(a->v, b->v, a1->v) &&
            LeftOn(b->v, a->v, a0->v));
}
// �ж��߶� ab �ǲ��Ƕ���εĶԽ���
bool Polygon::Diagonal(const tVertex& a, const tVertex& b) const {
    return InCone(a, b) && InCone(b, a) && Diagonalie(a, b);
}
// ��ʼ�����������Ϣ
void Polygon::EarInit() {
    tVertex v0, v1, v2;
    v1 = vertices;
    do {
        v2 = v1->next;
        v0 = v1->prev;
        v1->ear = Diagonal(v0, v2);
        v1 = v1->next;
    } while (v1 != vertices);
}
// ��ӡ�Խ���
void Polygon::PrintDiagonal(const tVertex& a, const tVertex& b) const {
    printf("%d %d\n", a->vnum, b->vnum);
}
// �ж��������ʷ�
void Polygon::Triangulate() {
    tVertex v0, v1, v2, v3, v4;
    int n = nvertices;
    EarInit();
    while (n > 3) {
        v2 = vertices;
        do {
            if (v2->ear) {
                v3 = v2->next; v4 = v3->next;
                v1 = v2->prev; v0 = v1->prev;
                PrintDiagonal(v1, v3);
                v1->ear = Diagonal(v0, v3);
                v3->ear = Diagonal(v1, v4);
                v1->next = v3;
                v3->prev = v1;
                vertices = v3;
                n--;
                break;
            }
            v2 = v2->next;
        } while (v2 != vertices);
    }
}
// �������ε�
void Polygon::ReadVertices() {
    head = NULL;
    int x, y;
    int i = 0;
    while (cin >> x >> y) {
        if (pSet.count(make_pair(x, y))) continue;
        pSet.insert(make_pair(x, y));
        maxCoor = { max(maxCoor.first,  1.0 * x), max(maxCoor.second, 1.0 * y) };
        minCoor = { min(minCoor.first, 1.0 * x), min(minCoor.second, 1.0 * y) };

        pInput.emplace_back(x, y);
        tVertex p;
        NEW(p, tsVertex);
        p->vnum = i++;
        p->v[X] = x;
        p->v[Y] = y;
        ADD(head, p);
    }
    nvertices = pInput.size();
    vertices = head;
}
// ����任��ʹ����Ӧ�� opencv ��ͼ
void Polygon::CoordinatesTransformation() {
    double interspace = w / 5.0;
    maxCoor.first -= minCoor.first;
    maxCoor.second -= minCoor.second;
    double scaleX = (w - 2 * interspace) / maxCoor.first;
    double scaleY = (w - 2 * interspace) / maxCoor.second;
    pTransformed = pInput;

    for (int i = 0; i < nvertices; i++) {
        pTransformed[i].first -= minCoor.first;
        pTransformed[i].second -= minCoor.second;
        pTransformed[i].first = pTransformed[i].first * scaleX + interspace;
        pTransformed[i].second = pTransformed[i].second * scaleY + interspace;
        pTransformed[i].second = w - pTransformed[i].second;
    }
}