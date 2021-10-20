#pragma once

#include<bits/stdc++.h>

using namespace std;
#define X 0
#define Y 1
#define DIM 2
typedef int tPointi[DIM];
typedef struct tVertexStructure tsVertex;
typedef tsVertex* tVertex;
int nvertices;
struct tVertexStructure {
    int vnum;
    tPointi v;
    bool ear;
    tVertex next, prev;
};
tVertex vertices;

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


// 向量 ab 和 向量 ac 组成的三角形有向面积的两倍
int Area2(tPointi a, tPointi b, tPointi c) {
    return (b[X] - a[X]) * (c[Y] - a[Y]) -
        (c[X] - a[X]) * (b[Y] - a[Y]);
}
int AreaPoly2() {
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
// 判断点 c 在向量 ab 的左边
bool Left(tPointi a, tPointi b, tPointi c) {
    return Area2(a, b, c) > 0;
}
// 判断点 c 在向量 ab 的左边或其上
bool LeftOn(tPointi a, tPointi b, tPointi c) {
    return Area2(a, b, c) >= 0;
}
// 点 a, b, c 三点共线
bool Collinear(tPointi a, tPointi b, tPointi c) {
    return Area2(a, b, c) == 0;
}
// 线段 ab 与 cd 恰当相交
bool IntersectProp(tPointi a, tPointi b, tPointi c, tPointi d) {
    if (Collinear(a, b, c) || Collinear(a, b, d) ||
        Collinear(c, d, a) || Collinear(c, d, b))
        return false;
    return (Left(a, b, c) ^ Left(a, b, d)) &&
        (Left(c, d, a) ^ Left(c, d, b));
}
// 点 c 在线段 ab 上
bool Between(tPointi a, tPointi b, tPointi c) {
    if (!Collinear(a, b, c))
        return false;
    if (a[X] != b[X])
        return ((a[X] <= c[X]) && (c[X] <= b[X])) ||
        ((a[X] >= c[X]) && (c[X] >= b[X]));
    else
        return ((a[Y] <= c[Y]) && (c[Y] <= b[Y])) ||
        ((a[Y] >= c[Y]) && (c[Y] >= b[Y]));
}
// 判断线段 ab 与 cd 是否相交
// 返回值为 2 是恰当相交, 1 是非恰当的相交, 0 是不相交
int Intersect(tPointi a, tPointi b, tPointi c, tPointi d) {
    if (IntersectProp(a, b, c, d))
        return 2;
    else if (Between(a, b, c) ||
        Between(a, b, d) ||
        Between(c, d, a) ||
        Between(c, d, b))
        return 1;
    else return 0;
}
// 判断线段 ab 不与多边形的边相交
bool Diagonalie(tVertex a, tVertex b) {
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
// 判断线段 ab 在多边形内部
bool InCone(tVertex a, tVertex b) {
    tVertex a0, a1;
    a1 = a->next;
    a0 = a->prev;
    // 若 a 是凸点
    if (LeftOn(a->v, a1->v, a0->v))
        return Left(a->v, b->v, a0->v) &&
        Left(b->v, a->v, a1->v);
    // 若 a 是凹点
    else
        return !(LeftOn(a->v, b->v, a1->v) &&
            LeftOn(b->v, a->v, a0->v));
}
bool Diagonal(tVertex a, tVertex b) {
    return InCone(a, b) && InCone(b, a) && Diagonalie(a, b);
}
void EarInit() {
    tVertex v0, v1, v2;
    v1 = vertices;
    do {
        v2 = v1->next;
        v0 = v1->prev;
        v1->ear = Diagonal(v0, v2);
        v1 = v1->next;
    } while (v1 != vertices);
}
void PrintDiagonal(tVertex a, tVertex b) {
    printf("%d %d\n", a->vnum, b->vnum);
}
void Triangulate() {
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
tVertex head;
tVertex p;
void ReadVertices() {
    head = NULL;
    cin >> nvertices;
    int x, y;
    for (int i = 0; i < nvertices; i++) {
        cin >> x >> y;
        NEW(p, tsVertex);
        p->vnum = i;
        p->v[X] = x;
        p->v[Y] = y;
        ADD(head, p);
    }
    vertices = head;
}
void PrintVertices() {

}