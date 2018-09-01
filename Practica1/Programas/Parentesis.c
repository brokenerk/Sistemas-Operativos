/*
	DESCRIPCIÓN: Programa que evalúa y valida una expresión infija
	COMPILACIÓN:
		Crear objeto gcc TADpila[D].c -c
		Ejecucion dinamica gcc TADpila[D].c Parentesis.c -o Par
*/

//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TADpila[D].h" //Libreria que contiene TAD Pila Dinamica

//PROGRAMA PRINCIPAL
int main(void)
{
	pila A;
	elemento E, Ultimo;	
	char c, *ecuacion, UCaracter;
	int i, n=0, x;

	//Se reserva espacio en la memoria para la ecuación a resolver
	ecuacion = (char*)malloc(1*sizeof(char));
	
	//Inicialización de la pila "A"
	initialize(&A);

	printf("Ingrese una ecuacion: \n\n" );
	do
	{
		c = getchar(); //Guardar la cadena que se ingresa
		ecuacion[n] = c; 
		n++;
		ecuacion = (char*)realloc(ecuacion,(n+1)*sizeof(char));
	}while(c != '\n');

	ecuacion[n-1] = '\0'; //Carácter que finaliza una cadena
	n--; c = '0';

	//VALIDACIÓN DE PARENTESIS CORRECTOS
	for(i=0;i<n;i++)
	{
		E.x = ecuacion[i];
		//Si encuentra un parentesis que abre en la expresión entonces lo empila
		if(E.x == '(' || E.x == '{' || E.x == '[') 
			push(E,&A);
	
		else
		{
			// putchar(UCaracter); printf(" COMPARA"); putchar(E.x); printf("\n"); 				
			if((UCaracter == '(' ) && (E.x == ')') || (UCaracter == '{' ) && (E.x == '}') || (UCaracter == '[' ) && (E.x == ']'))
			{
				if(empty(&A) == TRUE) //Y si la pila esta vacía
				{
					//Marca el tipo de error 1
					printf("\n>>>>>>Error 1, un parentesis intenta cerrar y no ha sido abierto<<<<<\n");
					exit(1); //Sale porque la evaluación ya no tendría caso
					break;
				}
				else 
					E=pop(&A); //y en la pila hay algun elemento, desempila el elemento
			}
			else
			{
				printf("ERROR, Los parentesis no estan bien acomodados\n");
				exit(1); break; // Ya no se sigue evaluando
			}		
		}
		if(empty(&A) !=  TRUE)
		{
			Ultimo = top(&A);
			UCaracter = Ultimo.x;
			// putchar(UCaracter); printf(" ULTIMO en la pila \n");		
		}	
	}

	// Si la pila A no está vacía indica que la expresión es incorrecta
	if(empty(&A) == FALSE) 
	{ 
		printf("\n>>>>>Error 2, un parentesis esta abierto y no ha sido cerrado<<<<<\n"); 
		exit(1); //Sale del programa
	}
	else //Si la pila esta vacía entonces la ecuación es correcta
		printf("\n>>>>>Tu ecuacion es correcta<<<<<\n\n"); 

	destroy(&A); //Destruimos la pila "A"
	return 0;
}
