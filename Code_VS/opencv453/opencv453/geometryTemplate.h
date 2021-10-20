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


// ���� ab �� ���� ac ��ɵ��������������������
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
// �жϵ� c ������ ab �����
bool Left(tPointi a, tPointi b, tPointi c) {
    return Area2(a, b, c) > 0;
}
// �жϵ� c ������ ab ����߻�����
bool LeftOn(tPointi a, tPointi b, tPointi c) {
    return Area2(a, b, c) >= 0;
}
// �� a, b, c ���㹲��
bool Collinear(tPointi a, tPointi b, tPointi c) {
    return Area2(a, b, c) == 0;
}
// �߶� ab �� cd ǡ���ཻ
bool IntersectProp(tPointi a, tPointi b, tPointi c, tPointi d) {
    if (Collinear(a, b, c) || Collinear(a, b, d) ||
        Collinear(c, d, a) || Collinear(c, d, b))
        return false;
    return (Left(a, b, c) ^ Left(a, b, d)) &&
        (Left(c, d, a) ^ Left(c, d, b));
}
// �� c ���߶� ab ��
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
// �ж��߶� ab �� cd �Ƿ��ཻ
// ����ֵΪ 2 ��ǡ���ཻ, 1 �Ƿ�ǡ�����ཻ, 0 �ǲ��ཻ
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
// �ж��߶� ab �������εı��ཻ
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
// �ж��߶� ab �ڶ�����ڲ�
bool InCone(tVertex a, tVertex b) {
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