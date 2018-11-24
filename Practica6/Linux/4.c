#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#define MATRIX_SIZE 10
#define DIR_MATRIX_MUL "matrix_mul.txt"
#define DIR_MATRIX_SUM "matrix_sum.txt"

void imprimeMatriz(double*);
void imprimeMatrizArchivo(char*,double*);
void initMatrizRandom(double*);
void initIdentidad(double*);
void copiarMatriz(double*, double*);
void sumMatriz(double*, double*, double*);
void mulMatriz(double*, double*, double*);
void invMatriz(double*, double*);


int main(void)
{
  int pipefd_0_1[2];
  int pipefd_1_0[2];
  int pipefd_1_2[2];
  int pipefd_2_0[2];
  double matrixA[MATRIX_SIZE*MATRIX_SIZE];
  double matrixB[MATRIX_SIZE*MATRIX_SIZE];
  double res[MATRIX_SIZE*MATRIX_SIZE];

  if (pipe (pipefd_0_1) != 0 || pipe (pipefd_1_0) != 0 || pipe (pipefd_1_2) != 0 || pipe (pipefd_2_0) != 0)
  {
    exit(1);
  }

  if (fork()) 
  { //0
    srand(getpid());
    initMatrizRandom(matrixA);
    initMatrizRandom(matrixB);

    printf("MATRIZ A\n"); imprimeMatriz(matrixA);
    printf("\nMATRIZ B\n"); imprimeMatriz(matrixB);

    write(pipefd_0_1[1], matrixA, sizeof(matrixA)); 
    write(pipefd_0_1[1], matrixB, sizeof(matrixB));

    read(pipefd_1_0[0], res, sizeof(res));
    printf("\nMultiplicacion realizada por el Proceso PADRE:\n");
    imprimeMatriz(res);
    printf("\nEscribiendo archivo TXT de inversa multiplicacion.... %s", DIR_MATRIX_MUL);
    invMatriz(res, matrixA);
    //imprimeMatriz(matrixA);
    imprimeMatrizArchivo(DIR_MATRIX_MUL, matrixA);
    printf(" Listo\n\n");

    read(pipefd_2_0[0], res, sizeof(res));
    printf("Suma realizada por el Proceso HIJO:\n");
    imprimeMatriz(res);
    printf("\nEscribiendo archivo TXT de inversa suma.... %s", DIR_MATRIX_SUM);
    invMatriz(res, matrixA);
    //imprimeMatriz(matrixA);
    imprimeMatrizArchivo(DIR_MATRIX_SUM, matrixA);
    printf(" Listo\n\n");

    exit(0);
  }
  else
	{
      if (fork())
        { // 1
          srand(getpid());
          initMatrizRandom(matrixA);
          initMatrizRandom(matrixB);
          printf("\nMATRIZ C\n"); imprimeMatriz(matrixA);
      	   printf("\nMATRIZ D\n"); imprimeMatriz(matrixB);

        	write(pipefd_1_2[1], matrixA, sizeof(matrixA));
        	write(pipefd_1_2[1], matrixB, sizeof(matrixB));

        	read(pipefd_0_1[0],matrixA, sizeof(matrixA));
        	read(pipefd_0_1[0],matrixB, sizeof(matrixB));

        	mulMatriz(matrixA, matrixB, res);

        	write(pipefd_1_0[1], res, sizeof(res));

        	exit(0);
        }
        else 
        { // 2
          read(pipefd_1_2[0],matrixA, sizeof(matrixA));
          read(pipefd_1_2[0],matrixB, sizeof(matrixB));

          sumMatriz(matrixA, matrixB, res);

          write(pipefd_2_0[1], res, sizeof(res));

          exit(0);
      }
  }
}

void imprimeMatriz(double* matrix)
{
  int i,j;
  for (j = 0; j < 10; j++)
  {
      for (i = 0; i < 10; i++)
      {
          printf("%.3f\t",matrix[i+j*10]);
      }
      printf("\n");
  }
}

void imprimeMatrizArchivo (char *fileDir, double* matrix)
{
  char buff[16];
  int file = creat(fileDir, S_IRWXU | S_IRWXG | S_IRWXO);
  int i;

  if (file != -1)
 	{
    for (i = 0; i <  100; i++)
    {
        
        if ((i+1)%10 == 0)
        {
          sprintf(buff,"\n");
          write(file, buff, strlen(buff));
        }
        else
        {
          sprintf(buff,"%.3f\t",matrix[i]);
          write(file, buff, strlen(buff));
        }
    }
  }
  else
  {
      printf("NO SE PUEDE MANDAR AL ARCHIVO %s\n",fileDir);
  }
  close(file);
}

void initMatrizRandom(double* matrix)
{
  int i,j;
  for (j = 0; j < 10; j++)
  {
      for (i = 0; i < 10; i++)
      {
          matrix[i+j*10] = rand() % 11;
      }
  }
}

void initIdentidad(double* matrix)
{
  int i,j;
  for (j = 0; j < 10; j++)
  {
    	for (i = 0; i < 10; i++)
    {
      matrix[i+j*10] = i==j ? 1 : 0;
    }
	}
}

void copiarMatriz(double* mS, double* mD)
{
  int i;
  for (i = 0; i < 100; i++)
  		mD[i] = mS[i];
}

void sumMatriz(double* mA, double* mB, double* res)
{
	int i;
	for (i = 0; i < 100; i++)
    	res[i] = mA[i] + mB[i];
}

void mulMatriz(double* mA, double* mB, double* res)
{
	int i, c, sum;
	for (i = 0; i < 100; i++)
	{
    sum = 0;
    for (c=0; c<10; c++)
        sum += mA[(i/10)*10 + c] * mB[c*10 + i%10];
    res[i] = sum;
  }
}

void invMatriz(double* mA, double* res)
{
  int n, i, j;
  double pivot;
  double aux[100];
  copiarMatriz(mA, aux);
  initIdentidad(res);
  for (n=0; n<10; n++)
	{
  	pivot = aux[n + n*10];
  	for (i=0; i < 10; i++)
    {
        aux[i + n*10] /= pivot;
        res[i + n*10] /= pivot;
    }

  	for (j=0; j<10; j++)
    {
      if (j != n)
      {
        pivot = aux[n + j*10];
        for (i=0; i<10; i++)
      	{
        	aux[i + j*10] -= pivot*aux[i + n*10];
        	res[i + j*10] -= pivot*res[i + n*10];
      	}
      }
    }
	}
}

