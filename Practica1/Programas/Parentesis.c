/*
DESCRIPCIÓN: Programa que evalúa y valida una expresión infija
OBSERVACIONES: 
>Longitud máxima de la expresión aritmética será de 100
cáracteres.
>Los nombres de los operandos en la expresión seran representados con las
letras A,B,C,D,...,Z.
*/

//Crear objeto estatica gcc TADpila[E].c -c
//Crear objeto estatica gcc TADpila[D].c -c

//Ejecucion estatica gcc TADpila[E].c solve.c -o solve
//Ejecucion dinamica gcc TADpila[D].c solve.c -o solve

//LIBRERIAS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "TADpila[E].h" //Libreria que contiene TAD Pila Estática
#include "TADpila[D].h" //Libreria que contiene TAD Pila Dinamica
//PROGRAMA PRINCIPAL
int main(void)
{
	//Se declara una pila "A"
	pila A;
	//Declaro tres elementos "E", "E2", "Ant"
	elemento E, E2, Ant;

	//Declaro un tipo de dato char "c", y dos variables de tipo apuntador 
	char c, *ecuacion, *post_fijo;

	//Declaro un arreglo de tipo de dato double, y una variable doble "R"
	double valores[27], R;
	//Declaro variables de tipo entero
	int i, l=0, n=0, x, t;

	//Se reserva espacio en la memoria para la ecuación a resolver
	ecuacion=(char*)malloc(1*sizeof(char));
	//Se reserva espacio en la memoria para la solución a la ecuación 
	post_fijo=(char*)malloc(1*sizeof(char));

	//Inicialización de la pila "A"
	initialize(&A);

	//Se pone el indice del arreglo valores en -1
	for(i=0;i<27;i++)
		valores[i]=-1;

	printf("Por favor ingrese una ecuacion: \n\n" );
	
	do
	{
		c=getchar(); //Guardar la cadena que se ingresa
		ecuacion[n]=c; 
		n++;
		ecuacion=(char*)realloc(ecuacion,(n+1)*sizeof(char));
	}while(c!='\n');

	ecuacion[n-1]='\0'; //Carácter que finaliza una cadena
	n--;c='0';

	//Imprimir ecuación
	printf("TU ECUACION ES: %s\n",ecuacion);

	//VALIDACIÓN DE PARENTESIS CORRECTOS
	for(i=0;i<n;i++)
	{
		E.x=ecuacion[i];
		//Si encuentra un parentesis que abre en la expresión entonces lo empila
		if(E.x=='(') 
			push(E,&A);

		//Si encuentra un parentesis que cierra 
		if(E.x==')')
		{
			if(empty(&A)==TRUE) //Y si la pila esta vacía
			{
				//Marca el tipo de error 1
				printf("\n>>>>>>Error 1, un parentesis intenta cerrar y no ha sido abierto<<<<<\n");
				exit(1); //Sale porque la evaluación ya no tendría caso
				break;
			}
			else 
				E=pop(&A); //y en la pila hay algun elemento, desempila el elemento
		}
	}

	//Finaliza el ciclo for, es decir, a terminado de evaluar la expresión y...
	if(empty(&A)==FALSE) //...Si la pila A no está vacía indica que la expresión es incorrecta
	{ 
		printf("\n>>>>>Error 2, un parentesis esta abierto y no ha sido cerrado<<<<<\n"); //Imprime el tipo de error 2
		exit(1); //Sale del programa
	}
	else //Si la pila esta vacía entonces la ecuación es correcta
		printf("\n>>>>>Tu ecuacion es correcta<<<<<\n\n"); //Imprime que la ecuación es correcta
	
	destroy(&A); //Destruimos la pila "A"
	initialize(&A); //Inicializamos nuevamente la pila "A"
	E=pop(&A);//Desempila el elemento E
	printf("%lf\n", E.r); //Imprime E
	return 0;
}