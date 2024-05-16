#include<time.h>
#include<math.h>
#include<stdio.h>

typedef struct
{
    float x,y;
}Point;

void Init_Point(Point *pt){
    pt->x=rand()%9+(float)(rand()%1000)/1000;
    pt->y=rand()%9+(float)(rand()%1000)/1000;
}

void Deplacer_Point(Point *pt,Point dest){
    pt->x=dest.x;
    pt->y=dest.y;
}

double Distance_Points(Point p1,Point p2){
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}