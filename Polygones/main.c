#include <stdio.h>
#include <stdlib.h>
#include "polygones.h"

void Generate_PlottingScript(const int numPls)
{
    int Random_Color[3] = {0};
    FILE *plotScript = fopen("plotter.gpl", "w");
    for (int i = 0; i < numPls; i++)
    {
        Random_Color[0] = rand() % 240;
        Random_Color[1] = rand() % 240;
        Random_Color[2] = rand() % 240;
        fprintf(plotScript, "set style line %d lc rgb 0x%x%x%x lw 2 pt %d ps 1.5\n", i + 1, Random_Color[0], Random_Color[1], Random_Color[2], 1 + rand() % 6);
    }
    fputs("\nset datafile separator \"\t\" \n", plotScript);
    fputs("plot 'C:\\Users\\ilyas\\C Lang\\Polygones\\Points.txt' ", plotScript);
    if (numPls > 1)
    {
        int i;
        for (i = 1; i < numPls; i++)
        {
            if (i == 1)
                fprintf(plotScript, "index %d with linespoints linestyle %d, \\\n", i - 1, i);
            else
                fprintf(plotScript, "     ''                   index %d with linespoints linestyle %d, \\\n", i - 1, i);
        }
        fprintf(plotScript, "     ''                   index %d with linespoints linestyle %d\n", i - 1, i);
    }
    else
        fprintf(plotScript, " index 0 with linespoints linestyle 1\n");

    fclose(plotScript);
}

int main(int argc, char **argv)
{
    // le 1er argument presente le nombres de polygones
    // le 2eme argument presente le nombre de points par polygone
    srand(time(NULL));
    if (argc <= 1)
        return EXIT_FAILURE;
    int numPts = atoi(argv[2]), numPls = atoi(argv[1]);
    Generate_PlottingScript(numPls);
    polygones a;
    Init_Polygone(&a, numPts);
    Save_Poly(a);
    for (size_t i = 1; i < numPls; i++)
    {
        Init_Polygone(&a, numPts);
        Add_to_Save(a);
    }

    FILE *plotting = popen("gnuplot -p", "w");
    fprintf(plotting, "load 'C:\\Users\\ilyas\\C Lang\\Polygones\\plotter.gpl'\n");
    fclose(plotting);
    return EXIT_SUCCESS;
}