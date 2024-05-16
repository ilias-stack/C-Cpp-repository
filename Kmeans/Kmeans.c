#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Point
{
    float X, Y;
} Point;

typedef struct dataPoint
{
    Point coords;
    int cluster;
    Point Centeroid;

} dataPoint;

#define randnum(min, max) \
    ((rand() % (int)(((max) + 1) - (min))) + (min))

dataPoint *dataPoints;
int len = 0;
char Global_K;
Point *Centeroids;

void Generate_Dataset(const unsigned short num)
{
    FILE *data = fopen("dataset.csv", "w");
    float x, y;
    Point Origin = {__INT_MAX__, __INT_MAX__};
    len = num;
    dataPoints = (dataPoint *)malloc(sizeof(dataPoint) * len);
    for (unsigned short i = 0; i < num; i++)
    {
        dataPoints[i].cluster = 0;
        Point coords = {(float)(randnum(-101, 99) + (randnum(0, 100) / 100.)), (float)(randnum(-101, 99) + (randnum(0, 100) / 100.))};
        dataPoints[i].coords = coords;
        dataPoints[i].Centeroid = Origin;
        fprintf(data, "%.2f,%.2f\n", coords.X, coords.Y);
    }

    fclose(data);
}

Point Center_Of_Cluster(int cl)
{
    Point resp = {0, 0};
    int count = 0;
    for (size_t i = 0; i < len; i++)
        if (dataPoints[i].cluster == cl)
        {
            resp.X += dataPoints[i].coords.X;
            resp.Y += dataPoints[i].coords.Y;
            count++;
        }
    if (count)
    {
        resp.X /= count;
        resp.Y /= count;
    }
    else
    {
        resp.X = 0;
        resp.Y = 0;
    }

    return resp;
}

double Distance(Point a, Point b)
{
    return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
}

double Min(double dist1, double dist2)
{
    return dist1 < dist2 ? dist1 : dist2;
}

void Kmeans(char k, int epochs)
{
    Global_K = k;

    // random cluster assignement
    for (size_t i = 0; i < len; i++)
        dataPoints[i].cluster = randnum(0, k - 1);

    // initial centroids calculation
    Centeroids = (Point *)malloc(sizeof(Point) * k);
    for (size_t i = 0; i < k; i++)
    {
        Centeroids[i] = Center_Of_Cluster(i);
        printf("%.2f,%.2f\n", Centeroids[i].X, Centeroids[i].Y);
    }

    // kmeans processing
    for (size_t i = 0; i < epochs; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            for (size_t internal_index = 0; internal_index < k; internal_index++)
            {
                if (Distance(dataPoints[j].Centeroid, dataPoints[j].coords) > Distance(dataPoints[j].coords, Centeroids[internal_index]))
                {
                    dataPoints[j].Centeroid = Centeroids[internal_index];
                    dataPoints[j].cluster = internal_index;
                }
            }
        }
        int Breaker = 0;
        for (size_t i = 0; i < k; i++)
        {
            Point newCenter = Center_Of_Cluster(i);
            if (newCenter.X == Centeroids[i].X && newCenter.Y == Centeroids[i].Y)
                Breaker++;
            Centeroids[i] = newCenter;
        }
        // if (Breaker == Global_K)
        //    break;
    }
}

void Generate_Plot_CSV()
{
    FILE *PlotFile = fopen("Plot.csv", "w");
    for (size_t i = 0; i < Global_K; i++)
    {
        fprintf(PlotFile, "%.2f,%.2f\n", Centeroids[i].X, Centeroids[i].Y);
        fputs("\n\n", PlotFile);

        for (size_t j = 0; j < len; j++)
        {
            if (dataPoints[j].cluster == i)
            {
                fprintf(PlotFile, "%.2f,%.2f\n", dataPoints[j].coords.X, dataPoints[j].coords.Y, dataPoints[j].cluster);
            }
        }
        if (i < Global_K - 1)
            fputs("\n\n", PlotFile);
    }
    fclose(PlotFile);
}

void Generate_Plot_File()
{
    FILE *plotScript = fopen("plotter.gpl", "w");
    fputs("set nokey\n", plotScript);
    int Random_Color[3] = {0};
    for (size_t i = 0; i < 2 * Global_K; i = i + 2)
    {
        Random_Color[0] = rand() % 240;
        Random_Color[1] = rand() % 240;
        Random_Color[2] = rand() % 240;
        int rnd = 1 + rand() % 6;
        fprintf(plotScript, "set style line %d lc rgb 0x%x%x%x lw 2 pt %d ps 3\n", i + 1, Random_Color[0], Random_Color[1], Random_Color[2], rnd);
        fprintf(plotScript, "set style line %d lc rgb 0x%x%x%x lw 2 pt %d ps 1.5\n", i + 2, Random_Color[0], Random_Color[1], Random_Color[2], rnd);
    }

    fputs("\nset datafile separator ',' \n", plotScript);
    fputs("plot 'Plot.csv' ", plotScript);
    if (2 * Global_K > 1)
    {
        int i;
        for (i = 1; i < 2 * Global_K; i++)
        {
            if (i == 1)
                fprintf(plotScript, "index %d with points linestyle %d, \\\n", i - 1, i);
            else
                fprintf(plotScript, "     ''                   index %d with points linestyle %d, \\\n", i - 1, i);
        }
        fprintf(plotScript, "     ''                   index %d with points linestyle %d\n", i - 1, i);
    }
    else
        fprintf(plotScript, " index 0 with points linestyle 1\n");

    fclose(plotScript);
}

int main()
{
    srand(time(NULL));
     
    Generate_Dataset(100);
    Kmeans(5, 100);
    Generate_Plot_CSV();
    Generate_Plot_File();

    FILE *PlottingPipe = popen("gnuplot -p", "w");
    fprintf(PlottingPipe, "load 'plotter.gpl'\n");
    free(dataPoints);
    free(Centeroids);
    fclose(PlottingPipe);
    return EXIT_SUCCESS;
}