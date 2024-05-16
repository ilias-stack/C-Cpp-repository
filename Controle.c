#include <stdio.h>
#include <stdlib.h>

typedef struct Diagonale
{
    int len;
    int *data;
} Diagonale_t;

typedef struct Matrix
{
    int len;
    int **mat;
} Matrix_t;

Diagonale_t Get_Dn(Matrix_t mat, int n)
{
    Diagonale_t resp;
    resp.len = mat.len - n;
    resp.data = (int *)malloc(sizeof(int) * resp.len);
    for (int i = 0; i < resp.len; i++)
        resp.data[i] = mat.mat[i + n][i];

    return resp;
}

void Longest(int arr[], int n)
{
    int pos = 0, len;
    int max_len = 1;
    for (int i = 0; i < n; i++)
    {
        len = 1;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
                len++;

            else
            {
                if (max_len < len)
                {
                    max_len = len;
                    pos = i;
                    break;
                }
                else
                    break;
            }
        }
    }
    printf("position = %d\nlongueur = %d", pos, max_len);
}

int main()
{

    return EXIT_SUCCESS;
}