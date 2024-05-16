#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float **scan_sys(int n);
void print_system(float **system, int n);
void triangularize_sys(float **system, int n);
float *solve_sys(float **system, int n);

void permuter(float **system, int row, int n);
void combiner(float **system, int row, int pivot_row, int n);

int main()
{
  srand(time(NULL));
  const int N = 4;
  float **system = scan_sys(N);
  print_system(system, N);
  printf("\n");

  float *solutions = solve_sys(system, N);
  for (int i = 0; i < N; i++)
  {
    printf("X%d = %.2f \n", i, solutions[i]);
  }

  return 0;
}

float **scan_sys(int n)
{
  float **system = (float **)malloc(sizeof(float *) * n);

  int i, j;
  for (i = 0; i < n; i++)
  {
    system[i] = (float *)malloc(sizeof(float) * (n + 1));
  }

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n + 1; j++)
    {
      system[i][j] = rand() % 100;
    }
  }

  return system;
}

void print_system(float **system, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n + 1; j++)
    {
      if (j < n)
        printf("%2.2f * X%d %s ", system[i][j], j, j != n - 1 ? "+" : "");
      else
        printf("= %.2f", system[i][j]);
    }

    printf("\n");
  }
}

void triangularize_sys(float **system, int n)
{
  float pivot;
  int i, j;
  for (j = 0; j < n; j++)
  {
    pivot = system[j][j];
    if (pivot == 0)
      permuter(system, j, n);

    for (i = j + 1; i < n; i++)
    {
      combiner(system, i, j, n);
    }
  }
}

void permuter(float **system, int row, int n)
{
  int i, j;
  float tmp;
  int target_row = 0, max = system[0][row];

  for (i = 1; i < n; i++)
  {
    if (system[i][row] > max)
    {
      target_row = i;
      max = system[i][row];
    }
  }

  for (j = 0; j < n + 1; j++)
  {
    tmp = system[row][j];
    system[row][j] = system[target_row][j];
    system[target_row][j] = tmp;
  }
}

void combiner(float **system, int row, int pivot_row, int n)
{
  float pivot = system[pivot_row][pivot_row];
  if (pivot == 0)
    return;

  float coeff = system[row][pivot_row] / pivot;
  int i;
  for (i = 0; i < n + 1; i++)
  {
    system[row][i] = system[row][i] - coeff * system[pivot_row][i];
  }
}

float *solve_sys(float **system, int n)
{
  triangularize_sys(system, n);
  float *solutions = (float *)malloc(sizeof(float) * n);

  int i, j;
  float x;

  for (i = n - 1; i >= 0; i--)
  {
    x = system[i][n];
    for (j = n - 1; j > i; j--)
    {
      x -= system[i][j] * solutions[j];
    }

    solutions[i] = x / system[i][i];
  }

  return solutions;
}