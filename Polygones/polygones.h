#define NMAX 100
#include "points.h"

typedef struct 
{
    int nbPoints;
    Point ListePoints[NMAX];
}polygones;

void Init_Polygone(polygones *poly,int longeur){
    poly->nbPoints=longeur;
    for (short i = 0; i < poly->nbPoints; i++)
    {
        Init_Point(&(poly->ListePoints[i]));
    }
}

void Save_Poly(polygones poly){
    FILE *Points=fopen("Points.txt","w");
    for (short i = 0; i < poly.nbPoints; i++)
    {
        fprintf(Points,"%f\t%f\n",poly.ListePoints[i].x,poly.ListePoints[i].y);
    }
    fprintf(Points,"%f\t%f\n",poly.ListePoints[0].x,poly.ListePoints[0].y);
    fclose(Points);
}

void Add_to_Save(polygones poly){
    FILE *Points=fopen("Points.txt","a");
    fprintf(Points,"\n\n");
    for (short i = 0; i < poly.nbPoints; i++)
    {
        fprintf(Points,"%f\t%f\n",poly.ListePoints[i].x,poly.ListePoints[i].y);
    }
    fprintf(Points,"%f\t%f\n",poly.ListePoints[0].x,poly.ListePoints[0].y);
    fclose(Points);
}

void Ajouter_Point(polygones *poly,Point p){
    poly->ListePoints[poly->nbPoints]=p;
    poly->nbPoints++;
}

void Supprimer_Point(polygones *poly,int index){
    for (short i = 0; i < NMAX; i++)
    {
        if(i>=index && i+1<NMAX)poly->ListePoints[i]=poly->ListePoints[i+1];
    }
    poly->nbPoints--;
}


