#include "Polynome.h"
#include <time.h>

void PlotScript_generator(Polynome_List_t *p)
{
    FILE *plotter = fopen("plotter.gpl", "w");
    int len = 0;
    while (p)
    {
        p = p->next;
        len++;
    }
    for (int i = 0; i < len; i++)
    {

        fprintf(plotter, "set style line %d lc rgb 0x%x%x%x lw 2 pt %d ps 1.5\n", i + 1, rand() % 240, rand() % 240, rand() % 240, 1 + rand() % 6);
    }
    fputs("\nset datafile separator \"\t\" \n", plotter);
    fputs("plot 'data.txt' ", plotter);
    if (len > 1)
    {
        int i;
        for (i = 1; i < len; i++)
        {
            if (i == 1)
                fprintf(plotter, "index %d with linespoints linestyle %d, \\\n", i - 1, i);
            else
                fprintf(plotter, "     ''                   index %d with linespoints linestyle %d, \\\n", i - 1, i);
        }
        fprintf(plotter, "     ''                   index %d with linespoints linestyle %d\n", i - 1, i);
    }
    else
        fprintf(plotter, " index 0 with lines linestyle 1\n");

    fclose(plotter);

    FILE *plotting = popen("gnuplot -p", "w");
    fprintf(plotting, "load 'plotter.gpl'\n");
    fclose(plotting);
}

int main()
{
    srand(time(NULL));
    polynome_t *head1 = createMonome(2, -3);
    polynome_t *head2 = createMonome(2, 3);
    addMonome(head1, 3, 4);
    addMonome(head2, 4, 1);
    Polynome_List_t *p = (Polynome_List_t *)malloc(sizeof(Polynome_List_t));
    p->poly = head1;
    p->next = (Polynome_List_t *)malloc(sizeof(Polynome_List_t));
    p->next->poly = head2;
    p->next->next = (Polynome_List_t *)malloc(sizeof(Polynome_List_t));
    p->next->next->poly = Addition(head1, head2);
    p->next->next->next = NULL;
    PlotScript_generator(p);

    Plot_Polynome(p, -10, 10);

    return EXIT_SUCCESS;
}