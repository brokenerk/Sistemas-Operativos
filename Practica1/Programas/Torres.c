/*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Contador de numero de movimientos
int v = 0;

// Prototipo de funciones

void hanoi(int n, int disco, int **M, int origen, int destino, int aux);
void mover(int disco, int **M, int o, int d);

// Funcion principal
int main(void)
{
	int i, j, n, **A;
	printf("\nIngrese el numero de discos: ");
	scanf("%d", &n);

	// Arreglo que contiene el numero de discos	
	A = malloc(3*sizeof(int*));
	for(i=0; i<3; i++)
		A[i] = calloc(n, sizeof(int));
	for(i=0; i<n; i++)
		A[0][i] = i + 1;

	// Llamada a la función que resuelve el caso de n discos
	hanoi(n, n, A, 0, 2, 1);

	printf("\n \n Movimientos realizados %d \n", v);
	return 0;
}

/*
	Resuelve el problema de hanoi de forma recursiva, 
	recibe el numero total de discos, el numero de 
	discos que solucionara, la matriz en la que se 
	guardan los numeros de los discos, la torre donde 
	estan los discos, la torre a donde se quiere mover 
	los disco y la torre auxiliar.
*/
void hanoi(int n, int disco, int **M, int origen, int destino, int aux)
{
	// Caso base: Solucion al caso de un disco.
	if (disco == 1)
		mover(disco, M, origen, destino);
	
	else // Caso recursivo
	{
		/* 
			Se llama recursivamente la funcion bajando
			el numero de discos a mover y cambiando el
			destino por el auxiliar, representa el mover
			todos los discos que hay sobre el disco base
			para poder mover el disco base.
		*/
		hanoi(n, disco-1, M, origen, aux, destino);

		// Mueve el disco del origen al destino
		mover(disco, M, origen, destino);

		/*
			Se llama recursivamente bajando el numero de
			discos a mover y cambiando el origen por el
			auxiliar.
		*/
		hanoi(n, disco-1, M, aux, destino, origen);
	}
	return;
}

void mover(int disco, int **M, int o, int d)
{
	int i = 0;
	// Imprime el movimiento
	printf("%d Mover de %c a %c \n ", v, o+65, d+65);
	v++;
	// Coloca el movimiento del disco en la matriz
	while(M[o][i]!=disco)
		i++;
	M[d][i] = disco;
}








