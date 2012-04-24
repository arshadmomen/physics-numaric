#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>
#include <time.h>

#define MATSIZE 100
#define RAND_RANGE 10
#define EIGENDATAFILE "eval.dat"

double complex mat[MATSIZE][MATSIZE];

void
gen_mat ()
{
  int i = 0, j;
  int real;
  int img;
  for (; i < MATSIZE; i++)
    {
      real = rand () % RAND_RANGE + 1;
      img = rand () % RAND_RANGE + 1;
      for (j = MATSIZE; j != i; j--)
	{
	  mat[i][j] = real + img * I;
	  mat[j][i] = conj (mat[i][j]);
	}
      if (i == j)
	mat[i][i] = rand () % RAND_RANGE + 0 * I;
    }
}

void
print_mat ()
{
  int i, j;
  for (i = 0; i < MATSIZE; i++)
    {
      for (j = 0; j < MATSIZE; j++)
	{
	  printf ("%f + %f *i", creal (mat[i][j]), cimag (mat[i][j]));
	  printf ("    ");
	}
      puts ("\n");
    }
}

void
lapacke_wrapper ()
{
  FILE * fp;
  int i,j;
  int i, j;
  char JOBZ = 'V';
  char UPLO = 'U';
  int N = MATSIZE;
  int LDA = MATSIZE;
  double W[MATSIZE];
  double complex WORK[2 * MATSIZE];
  double complex A[MATSIZE * MATSIZE];
  int LWORK = 2 * MATSIZE;
  double RWORK[3 * MATSIZE - 2];
  int INFO;
  fp = fopen(EIGENDATAFILE,"w");
  for (i = 0; i < MATSIZE; i++)
    for (j = 0; j < MATSIZE; j++)
      A[(j + MATSIZE * i)] = mat[j][i];
  zheev_ (&JOBZ, &UPLO, &N, A, &LDA, W, WORK, &LWORK, RWORK, &INFO);
  if (!INFO)
  {
    printf("OK\n");
    for(i = 0; i < MATSIZE; i++)
    {
      fprintf(fp,"%g\n", W[i]);
    }
  }
  else printf("Not OK\n");
    {
      printf ("OK\n");
      for (i = 0; i < MATSIZE; i++)
	printf ("%f\n", W[i]);
    }
  else
    printf ("Not OK\n");
}

int
main ()
{
  srand (time (NULL));
  gen_mat ();
  print_mat ();
  lapacke_wrapper ();
  return 0;
}
