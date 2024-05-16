#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definition du monome
typedef struct monome
{
    int deg;
    float coef;
} monome_t;

// Definition du polynome
typedef struct polynome
{
    monome_t *data;
    struct polynome *next, *prev;
} polynome_t;

// Definition de la liste des polynomes
typedef struct Polynome_List
{
    polynome_t *poly;
    struct Polynome_List *next;
} Polynome_List_t;

// Creer un noeud
polynome_t *createMonome(int deg, float coef)
{
    monome_t *m = (monome_t *)malloc(sizeof(monome_t));
    m->coef = coef;
    m->deg = deg;
    polynome_t *resp = (polynome_t *)malloc(sizeof(polynome_t));
    resp->prev = resp->next = NULL;
    resp->data = m;
    return resp;
}

// Enchainer un noeud dans le polynome
void addMonome(polynome_t *head, int deg, float coef)
{
    polynome_t *copy = head;
    while (copy->next)
        copy = copy->next;

    polynome_t *newPoly = createMonome(deg, coef);
    newPoly->prev = copy;
    copy->next = newPoly;
}

// Afficher le polynome a partir de sa tete
void DisplayPolynome(polynome_t *head)
{
    polynome_t *copy = head;
    while (copy)
    {
        if (copy->data->coef >= 0)
            printf("+%.3fx^%d ", copy->data->coef, copy->data->deg);
        else if (copy->data->coef < 0)
            printf("%.3fx^%d ", copy->data->coef, copy->data->deg);
        copy = copy->next;
    }
}

// Permet de resoudre les erreurs de polynomes
void FixPolynome(polynome_t *head)
{
    // Trier le polynome par degre
    if (!head || !head->next)
        return;
    int SwapDone = 1;
    int DeletionDone = 1;
    polynome_t *copy;
    while (SwapDone)
    {
        SwapDone = 0;
        copy = head;
        while (copy)
        {
            if (copy->prev)
            {
                if (copy->prev->data->deg < copy->data->deg)
                {
                    monome_t *tmp = copy->prev->data;
                    copy->prev->data = copy->data;
                    copy->data = tmp;
                    SwapDone++;
                }
            }
            copy = copy->next;
        }
    }
    // Simplifier le polynome
    while (DeletionDone)
    {
        DeletionDone = 0;
        copy = head;
        while (copy->next)
        {
            if (copy->prev)
            {
                if (copy->prev->data->deg == copy->data->deg)
                {
                    copy->prev->data->coef += copy->data->coef;
                    copy->next->prev = copy->prev;
                    copy->prev->next = copy->next;
                    DeletionDone++;
                }
            }
            copy = copy->next;
        }
        if ((copy->next == NULL && copy->prev->data->deg == copy->data->deg))
        {
            copy->prev->data->coef += copy->data->coef;
            copy->prev->next = NULL;
            DeletionDone++;
        }
    }
}

// Genere une version moins de polynome
polynome_t *Poly_Reversed(polynome_t *head)
{
    polynome_t *copy = head;
    polynome_t *resp = createMonome(copy->data->deg, -copy->data->coef);
    copy = copy->next;
    while (copy)
    {
        addMonome(resp, copy->data->deg, -copy->data->coef);
        copy = copy->next;
    }
    return resp;
}

// Calcule la longueur de polynome
int Polynome_Len(polynome_t *head)
{
    int resp = 0;
    while (head)
    {
        head = head->next;
        resp++;
    }

    return resp;
}

// Addition de deux polynomes
polynome_t *Addition(polynome_t *head1, polynome_t *head2)
{
    polynome_t *resp = createMonome(head1->data->deg, head1->data->coef);
    polynome_t *copy = head1->next;
    while (copy)
    {
        addMonome(resp, copy->data->deg, copy->data->coef);
        copy = copy->next;
    }
    copy = head2;
    while (copy)
    {
        addMonome(resp, copy->data->deg, copy->data->coef);
        copy = copy->next;
    }

    FixPolynome(resp);

    return resp;
}

// Soustraction de deux polynomes
polynome_t *Soustraction(polynome_t *head1, polynome_t *head2)
{
    polynome_t *resp = createMonome(head1->data->deg, head1->data->coef);
    polynome_t *copy = head1->next;
    while (copy)
    {
        addMonome(resp, copy->data->deg, copy->data->coef);
        copy = copy->next;
    }
    copy = Poly_Reversed(head2);
    while (copy)
    {
        addMonome(resp, copy->data->deg, copy->data->coef);
        copy = copy->next;
    }

    FixPolynome(resp);

    return resp;
}

// Comaparaison de deux polynomes
int Poly_Compare(polynome_t *head1, polynome_t *head2)
{
    FixPolynome(head1);
    FixPolynome(head2);
    for (int i = 0; i < Polynome_Len(head1); i++)
    {
        if (head2)
        {
            if (!(head1->data->coef == head2->data->coef && head1->data->deg == head2->data->deg))
                return 0;
        }
        else
            return 0;
        head1 = head1->next;
        head2 = head2->next;
    }
    return 1;
}

// Calcule le derive
polynome_t *Derivative(polynome_t *head)
{
    polynome_t *resp = createMonome(head->data->deg - 1, head->data->deg * head->data->coef);
    polynome_t *copy = head->next;
    while (copy)
    {
        addMonome(resp, copy->data->deg - 1, copy->data->deg * copy->data->coef);
        copy = copy->next;
    }
    FixPolynome(resp);

    return resp;
}

// Calcule la valeur de polynome en un point
float polynome_x(polynome_t *head, float X)
{
    float resp = 0;
    while (head)
    {
        resp += head->data->coef * powf(X, head->data->deg);
        head = head->next;
    }
    return resp;
}

// Tracer la courbe representative
void Plot_Polynome(Polynome_List_t *p, int a, int b)
{
    FILE *dataFile = fopen("data.txt", "w");
    float diff = (float)(b - a) / 500;
    while (p)
    {
        float Start = a;
        for (int i = 0; i < 500; i++)
        {
            fprintf(dataFile, "%f\n", polynome_x(p->poly, Start));
            Start += diff;
        }
        fputs("\n\n", dataFile);
        p = p->next;
    }
    fclose(dataFile);
}
