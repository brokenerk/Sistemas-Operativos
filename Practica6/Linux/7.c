//	Compilación:
//	gcc tiempo.c -c
//	gcc 5.c tiempo.o -o 5

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
#include <sys/ipc.h>	
#include <sys/shm.h>
#define TAM_MEM 400

// Declaracion de funciones
char* leerDirectorio();
void imprimir(double **m, int n);
void llenar(double **m, int n);
void sumar(double **m1, double **m2, double **resultado, int n);
void multiplicar(double **m1, double **m2, double **resultado, int n);
int inversa(double **matriz, double **resultado, int n);
double determinante(double **matriz, int n);
void crearArchivo(double **matriz, int n, char *nombre, char *directorio);
int potencia(int base, int pot);
void escribir(double **matriz, int n, int clave);
void leer(double **matriz, int n, int clave);


int *shm, *z, c, d;

int main()
{
	// CREAR DIRECTORIO
	// Obtenemos el directorio desde la entrada de teclado
	char* path = leerDirectorio(); 

	int i, n, shmid, pid;
	double **matriz1, **matriz2, **suma, **mul, **inv1, **inv2;
	srand(time(NULL));
	n = 10; // Tam de la matriz cuadrada
	key_t llave = 5678;

	// Inicializa las matrices.
	matriz1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz1[i] = (double*)calloc(n,sizeof(double));

	matriz2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		matriz2[i] = (double*)calloc(n,sizeof(double));
	
	suma = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		suma[i] = (double*)calloc(n,sizeof(double));

	mul = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		mul[i] = (double*)calloc(n,sizeof(double));

	inv1 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv1[i] = (double*)calloc(n,sizeof(double));

	inv2 = (double**)calloc(n,sizeof(double*));
	for (i = 0; i < n; i++)
		inv2[i] = (double*)calloc(n,sizeof(double));

	//---------Revisamos que se haya creado la mem compartida---------------

	if(shmid = shmget(llave, TAM_MEM, IPC_CREAT | 0666) < 0)
	{
		perror("Error al obtener la memoria compartida: shmget");
		exit(-1);
	}

	if((shm = shmat(shmid, NULL, 0)) == (int *)-1)
	{
		perror("Error al lanzar la memoria compartida: shmat");
		exit(-1);
	}

	//--------------------Creamos los procesos-----------------------------

	if((pid = fork()) == 0)
	{
		if((pid = fork()) == 0)
		{
			//------------------PROCESO HIJO: MULTIPLICACION
			sleep(11);

			printf("------------------------------\n");
			printf("Proceso HIJO leeyendo matriz 1\n");
			leer(matriz1, n, 456);
			sleep(4);

			printf("Proceso HIJO leeyendo matriz 2\n");
			leer(matriz2, n, 678);

			printf("Proceso HIJO sumando matrices\n");
			sumar(matriz1, matriz2, suma, n);
			sleep(2);

			printf("Proceso PADRE escribiendo la suma\n");
			escribir(suma, n, 654);

			exit(0);
		}
		else
		{
			//------------------PROCESO PADRE: SUMA
			printf("------------------------------\n");
			sleep(1);

			printf("Proceso PADRE leeyendo matriz 1\n");
			leer(matriz1, n, 456);
			sleep(3);

			printf("Proceso PADRE leeyendo matriz 2\n");
			leer(matriz2, n, 678);

			printf("Proceso PADRE multiplicando matrices\n");
			multiplicar(matriz1, matriz2, mul, n);
			sleep(2);

			printf("Proceso PADRE escribiendo la multiplicacion\n");
			escribir(mul, n, 654);
			sleep(2);

			printf("Proceso PADRE escribiendo matriz 1\n");
			escribir(matriz1, n, 456);
			sleep(2);

			printf("Proceso PADRE escribiendo matriz 2\n");
			escribir(matriz2, n, 678);

			exit(0);
		}
	}
	else{
		//------------------PROCESO ABUELO: Crea matrices y lee inversas
		printf("Proceso ABUELO creando matriz 1\n");
		llenar(matriz1, n);

		printf("Proceso ABUELO creando matriz 2\n");
		llenar(matriz2, n);

		printf("Proceso ABUELO escribiendo matriz 1\n");
		escribir(matriz1, n, 456);
		sleep(1);

		printf("Proceso ABUELO escribiendo matriz 2\n");
		escribir(matriz1, n, 678);
		sleep(4);

		printf("Proceso ABUELO leeyendo multiplicacion\n");
		leer(mul, n ,678);
		sleep(12);

		printf("Proceso ABUELO leeyendo suma\n");
		leer(suma, n, 654);
		sleep(1);

		printf("Multiplicacion realizada por el Proceso PADRE:\n");
		imprimir(mul, n);

		printf("Suma realizada por el Proceso HIJO:\n");
		imprimir(suma, n);

		printf("Escribiendo archivo de inversa de multiplicacion....");
		inversa(mul, inv1, n);
		crearArchivo(inv1, n, "/inv_mul.txt", path);
		printf("Listo\n");

		printf("Escribiendo archivo de inversa suma....");
		inversa(suma, inv2, n);
		crearArchivo(inv2, n, "/inv_suma.txt", path);
		printf("Listo\n");

		exit(0);
	}
	return 0;
}

void escribir(double **matriz, int n, int clave)
{
	int j, i;
	z = shm;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			*z++ = matriz[i][j];
		}
	}

	*z = clave;
	while(*shm != '*')
		sleep(1);
}

void leer(double **matriz, int n, int clave)
{
	int x = 0, y = 0, valor;
	for(z = shm; *z != clave; z++)
	{
		valor = *z;
		matriz[x][y] = valor;

		if(y == n-1)
		{
			x++;
			y = 0;
		}
		else
			y++;
	}
	*shm = '*';
}

void crearArchivo(double **matriz, int n, char *nombre, char *directorio)
{
    int i,j;
    char* dir = (char *)calloc(2000, sizeof(char));
    char* aux = (char *)calloc(2000, sizeof(char));
    char num[15];
    strcpy(aux, directorio);
    strcat(directorio, nombre);
    strcpy(dir, directorio);

    // LLamada al sistema cret, recibe la ruta del archivo a crear y los permisos
    // Retorna -1 si hay errores
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
    strcpy(directorio, aux);
    free(aux); free(dir); 
}

char* leerDirectorio()
{
	char* directorio = (char*)calloc(2000,sizeof(char));
	printf("Ingrese el nuevo directorio: ");
	scanf("%s", directorio);
	return directorio;
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

void sumar(double **m1, double **m2, double **resultado, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			resultado[i][j] = m1[i][j] + m2[i][j];
	}
}

void multiplicar(double **m1, double **m2, double **resultado, int n)
{
	int i, j, k, aux;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			aux = 0;
			for(k = 0; k < n; k++)
				aux = m1[i][k] * m2[k][j] + aux;
			resultado[i][j] = aux;
		}
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
    // Si el orden es de 2, multiplica cruzadon directamente
    if(n==2)
        return m[0][0]*m[1][1] - m[1][0]*m[0][1];
    else
	{
		for(int j=0; j<n; j++)
		{
			// Crea arreglo dinamico temporal
			double **menor = (double **)malloc(sizeof(double)*(n-1));
			// Redimensiona
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
        // Recursividad, repite la funcion
        aux = potencia(-1, 2+j)*m[0][j]*determinante(menor, n-1);
        det += aux;

        for(int x = 0; x<(n-1); x++)
            free(menor[x]); // Libera espacio en memoria     
        free(menor);
        }
    return det; // Devuelve resultado
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
	else
	{
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
