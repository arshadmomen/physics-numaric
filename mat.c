#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>
#include <time.h>

#define MATSIZE 5
#define RAND_RANGE 100

double complex mat[MATSIZE][MATSIZE];

void gen_mat()
{
  int i =0,j;
  int real;
  int img;
  for( ;i < MATSIZE; i++)
  {
    real = rand()%RAND_RANGE + 1;
    img = rand()%RAND_RANGE + 1;
    for(j = MATSIZE; j != i ; j--) 
    { mat[i][j] = real + img * I;
      mat[j][i] = conj(mat[i][j]);
    }
    if(i == j)
      mat[i][i] = rand()%RAND_RANGE + 0*I;
  }
}

void print_mat()
{
  int i,j;
  for(i = 0; i < MATSIZE; i++)
  {
    for(j = 0; j < MATSIZE; j++)
    {
      printf("%f + %f *i", creal(mat[i][j]), cimag(mat[i][j]));
      printf("    ");
    }
    puts("\n");
  }
}

int main()
{
  srand(time(NULL));
  gen_mat();
  print_mat();
  return 0;
}
