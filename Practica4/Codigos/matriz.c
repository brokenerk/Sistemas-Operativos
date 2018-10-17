#include <stdio.h>
#include <stdlib.h>
#define n 3

// Declaracion de funciones
void Imprimir(int m[][n]);
void sumar(int m1[][n], int m2[][n], int resultado[][n]);
void restar(int m1[][n], int m2[][n], int resultado[][n]);
void multiplicar(int m1[][n], int m2[][n], int resultado[][n]);
void transpuesta(int m[][n], int resultado[][n]);
int determinante(int m[][n]);
void inversa(int matriz1[][n]);


int main(int argc, char const *argv[])
{
	int i, j, k, aux;
	int suma[n][n], resta[n][n], multiplica[n][n], trans[n][n], inversa[n][n];
	
	int matriz1[n][n] = {{2, 0, 1}, {3, 0, 0}, {5, 1, 1}};
	int matriz2[n][n] = {{1, 0, 1}, {1, 2, 1}, {1, 1, 0}};	

	printf("MATRIZ 1\n");
	Imprimir(matriz1);

	printf("MATRIZ 2\n");
	Imprimir(matriz2);

	sumar(matriz1, matriz2, suma);
	printf("SUMA:\n");
	Imprimir(suma);


	restar(matriz1, matriz2, resta);
	printf("RESTA:\n");
	Imprimir(resta);

	multiplicar(matriz1, matriz2, multiplica);
	printf("MULTIPLICACION\n");
	Imprimir(multiplica);

	transpuesta(matriz1, trans);
	printf("TRANSPUESTA\n");
	Imprimir(trans);

	int deter = determinante(matriz1);
	printf("DETERMINANTE = %d\n", deter);

	// inversa(matriz1);

	return 0;
}

/****************************************************************
							FUNCIONES
/****************************************************************/
void Imprimir(int m[][n])
{
	int aux;
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf(" %d, ", m[i][j]);					
			if(j == 2)
			{
				printf("\n");
			}
		}
	}
	printf("\n");
}

void sumar(int m1[][n], int m2[][n], int resultado[][n])
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			resultado[i][j] = m1[i][j] + m2[i][j]; 			
		}
	}
}


void restar(int m1[][n], int m2[][n], int resultado[][n])
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			resultado[i][j] = m1[i][j] - m2[i][j]; 			
		}
	}
}
void multiplicar(int m1[][n], int m2[][n], int resultado[][n])
{
	int i, j, k, aux;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			aux = 0;
			for(k = 0; k < n; k++)
			{
				aux = m1[i][k] * m2[k][j] + aux;
			}
			resultado[i][j] = aux;
		}
	}
}

void transpuesta(int m[][n], int resultado[][n])
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			resultado[i][j] = m[j][i];
		}
	}
}

int determinante(int m[][n])
{
	int i, j, producto1, producto2, col, fil, sumapos, sumaneg, suma;
	sumapos = 0;
	sumaneg = 0;
	suma = 0;
	for(i = 0; i < n; i++)
	{
		producto1 = 1;
		producto2 = 1;
		for(j = 0; j < n; j++)
		{
			col = j + i;
			if( col >= n )
				col = col - n;

			producto1 = producto1 * m[j][col];
			producto2 = producto2 * m[n-(j+1)][col];
		}
		sumapos = sumapos + producto1;
		sumaneg = sumaneg + producto2;
	}
	suma = sumapos - sumaneg;
	return suma;
}

void inversa(int m[][n])
{
	printf("ALOOOO\n");
	/*int i, j, k, z, determ;
	int trans[n][n];

	determ = determinante(matriz1);

	if(determ == 0)
		printf("La matriz inversa no existe\n");
	else
	{
		float a[10][10],resulta[10][10],identidad[10][10];
	   	 float s=0,q;
	   	   	 
	   	 for(i=0;i<10;i++)
	   	 {
	   		 for(j=0;j<10;j++)
	   		 {
	   			 a[i][j]=(float)matriz1[i][j];
	   			 if(j==i)
	   				 identidad[i][j]=1;
	   			 else
	   				 identidad[i][j]=0;
	   		 }
	   	 }
	   	 
	   	 printf("\nMatriz A:\n");
	   	 for(i=0;i<10;i++)
	   	 {
	   		 for(j=0;j<10;j++)
	   		 {
	   			 printf("%.2f  ",a[i][j]);
	   		 }
	   		 printf("\n");
	   	 }
	   	 printf("\nMatriz I:\n");
	   	 for(i=0;i<10;i++)
	   	 {
	   		 for(j=0;j<10;j++)
	   		 {
	   			 printf("%.2f  ",identidad[i][j]);
	   		 }
	   		 printf("\n");
	   	 }
	   	 for(k=0;k<10;k++)
	   	 {
	   		 for(i=0;i<10;i++)
	   		 {
	   			 for(j=0;j<10;j++)
	   			 {
	   				 resulta[i][j]=0;
	   			 }
	   		 }
	   		 for(i=0;i<10;i++)
	   		 {
	   			 for(j=0;j<10;j++)
	   			 {
	   				 for(z=0;z<10;z++)
	   				 {
	   					 resulta[i][j]+=(a[i][z]*identidad[z][j]);
	   				 }
	   			 }
	   		 }
	   		 printf("\nMatriz C(%d):\n",k);
	   		 for(i=0;i<10;i++)
	   		 {
	   			 for(j=0;j<10;j++)
	   			 {
	   				 printf("%.2f  ",resulta[i][j]);
	   			 }
	   			 printf("\n");
	   		 }
	    
	   		 for(i=0;i<10;i++)
	   		 {
	   			 for(j=0;j<10;j++)
	   			 {
	   				 if(i==j)
	   				 {

	   					 s+=resulta[i][j];
	   				 }
	   			 }
	   		 }
	   		 q=s/k;
	   	 
	   		 for(i=0;i<10;i++)
	   		 {
	   			 for(j=0;j<10;j++)
	   			 {
	   				 if(i==j)
	   				 {

	   					 identidad[i][j]=resulta[i][j]-q;
	   				 }
	   				 else
	   						 identidad[i][j]=resulta[i][j];
	   			 }
	   		 }    
	   		 s=0;
	   		 
	   	 }
	    
	   	 for(i=0;i<10;i++)
	   	 {
	   		 for(j=0;j<10;j++)
	   		 {
	   			 resulta[i][j]=0;
	   		 }
	   	 }
	   	 for(i=0;i<10;i++)
	   	 {
	   		 for(j=0;j<10;j++)
	   		 {
	   			 for(z=0;z<10;z++)
	   			 {
	   				 resulta[i][j]+=(a[i][z]*identidad[z][j]);
	   			 }
	   		 }
	   	 }

	   	 for(i=0;i<10;i++)
	   	 {
	   		 for(j=0;j<10;j++)
	   		 {
	   			 if(i==j)
	   				 s+=resulta[i][j];
	   		 }
	   	 }
	   	 if(s/10!=0)
	   	 {
	   		 for(i=0;i<10;i++)
	   		 {
	   			 for(j=0;j<10;j++)
	   			 {
	   				 identidad[i][j]=identidad[i][j]/(float)(s/10);
	   			 }
	   		 }    
	   	 }
	   	 printf("\nresult:\n");
	   	 for(i=0;i<10;i++)
	   	 {
	   		 for(j=0;j<10;j++)
	   		 {
	   			 printf("%d\t",(int)identidad[i][j]);
	   		 }
	   		 printf("\n");
	   	 }
	   	 


	}
*/

}
