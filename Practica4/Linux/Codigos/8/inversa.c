#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

// Declaracion de funciones
void imprimir(double **m, int n);
void llenar(double **m, int n);
int inversa(double **matriz, double **resultado, int n);
int potencia(int base, int pot);
double determinante(double **matriz, int n);
void crearArchivo(double **matriz, int n, char *directorio);

int main(int argc, char const *argv[])
{
    int i, n;
    double **matriz1, **matriz2, **inversa1, **inversa2;
    time_t t;
    srand((unsigned) time(&t));
    n = 10;
    // Inicializa las matrices.
    matriz1 = (double**)calloc(n,sizeof(double*));
    for (i = 0; i < n; i++)
        matriz1[i] = (double*)calloc(n,sizeof(double));

    matriz2 = (double**)calloc(n,sizeof(double*));
    for (i = 0; i < n; i++)
        matriz2[i] = (double*)calloc(n,sizeof(double));

    inversa1 = (double**)calloc(n,sizeof(double*));
    for (i = 0; i < n; i++)
        inversa1[i] = (double*)calloc(n,sizeof(double));

    inversa2 = (double**)calloc(n,sizeof(double*));
    for (i = 0; i < n; i++)
        inversa2[i] = (double*)calloc(n,sizeof(double));

    // CREAR DIRECTORIO
    char* path1 = (char*)calloc(2000,sizeof(char));
    char* path2 = (char*)calloc(2000,sizeof(char));
    path1 = "/home/enrike/Escritorio/P4-SO/8/Resultados/inv_1.txt";
    path2 = "/home/enrike/Escritorio/P4-SO/8/Resultados/inv_2.txt";


    // Llena matriz 1 y matriz 2
    llenar(matriz1, n);
    llenar(matriz2, n);

    printf("MATRIZ 1\n"); imprimir(matriz1, n);
    printf("MATRIZ 2\n"); imprimir(matriz2, n);

     
    inversa(matriz1, inversa1, n); 
    inversa(matriz2, inversa2, n); 
    crearArchivo(inversa1, n, path1);
    crearArchivo(inversa2, n, path2);
    
    printf("ARCHIVOS INVERSAS ESCRITO\n");
    printf("%s", path1);
    printf("\n");
    printf("%s", path2);
    printf("\n");

    return 0;
}

void crearArchivo(double **matriz, int n, char *directorio)
{
    int i,j;
    char num[15];

    if(creat(directorio, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
        perror(directorio);
        exit(EXIT_FAILURE);
    }
    else
    {
        int a = open(directorio, O_WRONLY | O_APPEND);
        if(a == -1)
        {
            perror(directorio);
            exit(EXIT_FAILURE);
        }
        else
        {
            for (i = 0; i < n; i++)
            {
                for(j = 0; j< n; j++)
                {
                    sprintf(num, "%.3f\t", matriz[i][j]);
                    if(!write(a, num, strlen(num)) == strlen (num))
                    {
                        perror(directorio);
                        exit(EXIT_FAILURE);
                    }
                }
                if(!write(a, "\n", strlen("\n")) == strlen ("\n"))
                    {
                        perror(directorio);
                        exit(EXIT_FAILURE);
                    }
            }
        }
        close(a);
    }
}

void imprimir(double **m, int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            printf("%.3f\t", m[i][j]);                  
        printf("\n");
    }
    printf("\n");
}

// Llena con numeros random 
void llenar(double **m, int n)
{
    int i, j;
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++)
         {
            m[i][j] = (rand()%11);
        }
    }
}

void transpuesta(double **m, double **resultado, int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            resultado[i][j] = m[j][i];
    }
}

bool esCero(double x)
{
    return fabs(x) < 1e-8;
}

double determinante(double **m, int n)
{  
    double det = 0, aux = 0;
    int c;
    //Si el orden es de 2, multiplica cruzadon directamente
    if(n==2)
        return m[0][0]*m[1][1] - m[1][0]*m[0][1];
    else
    {
        for(int j=0; j<n; j++)
        {
            //Crea arreglo dinamico temporal
            double **menor = (double **)malloc(sizeof(double)*(n-1));
            //Redimensiona
            for(int i=0; i<(n-1); i++) 
                menor[i] = (double *)malloc(sizeof(double)*(n-1));
            for(int k=1; k<n; k++)
            {
                c = 0;
                    for(int l=0; l<n; l++)
                    {
                        if(l!=j)
                        {
                            /*Parte matriz principal en matrices de 3 
                            y multiplica cruzado*/
                            menor[k-1][c] = m[k][l];
                            c++;
                        }
                    }
            }
        //Recursividad, repite la funcion
        aux = potencia(-1, 2+j)*m[0][j]*determinante(menor, n-1);
        det += aux;

        for(int x = 0; x<(n-1); x++)
            free(menor[x]);//Libera espacio en memoria     
        free(menor);
        }
    return det;//Devuelve resultado
    }
}

// Usando definicion de la adjunta
int inversa(double **A, double **resultado, int n)
{
    int tieneInversa;
    if(determinante(A, n) == 0)
    {
        tieneInversa=0;
        printf("La matriz no tiene inversa. Determinante = 0\n\n");
    }
    else{
        tieneInversa=1;
        int i, j, k, l; 
        double *tmp;
        tmp = (double*)malloc(sizeof(double)*n);

        for(i = 0; i < n; ++i)
            resultado[i][i] = 1;
        i = 0; j = 0;
        while(i < n && j < n)
        {
            if(esCero(A[i][j]))
            {
                for(k = i + 1; k < n; ++k)
                {
                    if(!esCero(A[k][j]))
                    {
                        tmp = A[i];
                        A[i] = A[k];
                        A[k] = tmp;
                        tmp = resultado[i];
                        resultado[i] = resultado[k];
                        resultado[k] = tmp;
                        break;
                    }
                }
            }
            if(!esCero(A[i][j]))
            {
                for(l = 0; l < n; ++l)
                    resultado[i][l] /= A[i][j];
                for(l = n - 1; l >= j; --l)
                    A[i][l] /= A[i][j];
                for(k = 0; k < n; ++k)
                {
                    if(i == k) continue;
                    for(l = 0; l < n; ++l)
                        resultado[k][l] -= resultado[i][l] * A[k][j];
                    for(l = n; l >= j; --l)
                        A[k][l] -= A[i][l] * A[k][j];
                }
                ++i;
            }
            ++j;
        }
    }
    return tieneInversa;
}

int potencia(int base, int pot)
{
    int i, resultado = 1;
    for(i = 0; i < pot; i++)
        resultado = base * resultado;

    return resultado;
}
