/*
IMPLEMENTACIONES DE EVALUCIÓN Y VALIDACIÓN DE UNA EXPRESIÓN INFIJA 
AUTOR(ES): 	Nicolás Sayago Abigail
			Salgado Zaragoza Gustavo
			Sanchez Merlín Ana Luisa
VERSIÓN: 1.0

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

	//Se pide al usuario que ingrese la ecuación que desea evaluar
	printf("******************************************\n");
	printf("****EVALUACIÓN DE EXPRESIONES INFIJAS*****\n");
	printf("******************************************\n\n");
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
	
	// CONVERSIÓN DE INFIJA A POSFIJA
	for(i=0;i<n;i++) //Recorre la posición desde que i vale 0 hasta que i es menor que n
		//EVALUA POR ORDEN DE OPERADORES
	{
		E.x=ecuacion[i]; 
		if(E.x=='^' || E.x=='(')  //Encuentra un operador de potencia
			push(E,&A); //Empila el elemento
		else if(E.x=='*' || E.x=='/') //Encuentra un operador de multipliacion
		{
			if(empty(&A)==FALSE) //Si la pila no está vacía
				Ant=top(&A); //Asignale a Ant el valor del último elemento empilado

			//Sí el último elemento (Ant) es diferente de  una suma, una resta, un parentesís que abre y además no esta vacia...
			while(Ant.x!='+' && Ant.x!='-' && Ant.x!='(' && empty(&A)==FALSE) 
			{
				Ant=pop(&A); // Desempila el ultimo elemento
				//cambia el tamaño del arreglo para que vaya guardando mas caracteres con forme se va solicitando sin gastar memoria de más
				post_fijo=(char*)realloc(post_fijo,(l+1)*sizeof(char)); 
				post_fijo[l]=Ant.x; 
				l++;
				if(empty(&A)==FALSE) //Si la pila no está vacía 
					Ant=top(&A); //Asignale a Ant el valor del último elemento empilado
			}
			push(E,&A); //Empila el elemento E
		}
		else if(E.x=='+' || E.x=='-') //Si encuentra el operador suma
		{ 
			if(empty(&A)==FALSE) //Y la pila  no está vacía 
				Ant=top(&A); // Asignale a Ant el valor del último elemento empilado
			while(empty(&A)==FALSE && Ant.x!='(') //Sí la pila no esta vacía  y el último elemento es diferente del parentesis que abre entonces..
			{
				Ant=pop(&A); //Desempila el último elemento
				//cambia el tamaño del arreglo para que vaya guardando mas caracteres con forme se va solicitando sin gastar memoria de más
				post_fijo=(char*)realloc(post_fijo,(l+1)*sizeof(char)); 
				post_fijo[l]=Ant.x;
				l++;
				if(empty(&A)==FALSE) //Si la pila no está vacía
					Ant=top(&A); // Asignale a Ant el valor del último elemento empilado
			}
			push(E,&A); //Empila el elemento E
		}
		else if(E.x==')') //En caso de que el elemento sea un paréntesis que cierra
		{
			Ant=pop(&A); //Desempila el último elemento
			while(Ant.x!='(') //Si éste último elemento es diferente de un paréntesis que abre
			{
				//cambia el tamaño del arreglo para que vaya guardando mas caracteres con forme se va solicitando sin gastar memoria de más
				post_fijo=(char*)realloc(post_fijo,(l+1)*sizeof(char));
				post_fijo[l]=Ant.x;
				l++;
				Ant=pop(&A); //Desempila el último elemento
			}
		}
		else //Sino ocurre ninguna condición anterior
		{
			//cambia el tamaño del arreglo para que vaya guardando mas caracteres con forme se va solicitando sin gastar memoria de más
			post_fijo=(char*)realloc(post_fijo,(l+1)*sizeof(char));
			post_fijo[l]=E.x;
			l++;
		}
	}
	while(empty(&A)==FALSE) //Sí la pila no está vacía
	{
		E=pop(&A); //Saca el elemento E de la pila
		//cambia el tamaño del arreglo para que vaya guardando mas caracteres con forme se va solicitando sin gastar memoria de más
		post_fijo=(char*)realloc(post_fijo,(l+1)*sizeof(char)); 
		post_fijo[l]=E.x;
		l++;
	}
	post_fijo[l]='\0'; //Igualar la posición l del arreglo post_fijo a terminador.
	printf("%s\n",post_fijo); //Imprimir el arreglo post_fijo

	//EVALUACIÓN DE LA EXPRESIÓN CON VALORES

	for(i=0;i<l;i++) //Recorrer el arreglo desde la posición 0 hasta la posición l.
	{
		if(post_fijo[i]=='^') //Sí el valor del arreglo es '^' (Operador potencia)
		{
			E=pop(&A); //El elemento E se desempila
			E2=pop(&A);//El elemento E2 se desempila
			R=pow(E2.r,E.r); //Se realiza la operación de E2 elevado a la E
			E.r=R; //Se iguala el valor de E a R.
			push(E,&A); //Empila el elemento E
		}
		else if(post_fijo[i]=='*') //En caso de que el valor de i sea '*'(Operador de multiplicación)
		{
			E=pop(&A); //El elemento E se desempila
			E2=pop(&A);//El elemento E2 se desempila
			R=E2.r*E.r; //Se realiza el producto de E2 por E
			E.r=R; //Se iguala el valor de E a R.
			push(E,&A);//Empila el elemento E
		}
		else if(post_fijo[i]=='/')
		{
			E=pop(&A);//El elemento E se desempila
			E2=pop(&A);//El elemento E2 se desempila
			R=E2.r/E.r;//Se realiza el cociente de E2 entre E
			E.r=R;//Se iguala el valor de E a R.
			push(E,&A);//Empila el elemento E
		}
		else if(post_fijo[i]=='+')
		{
			E=pop(&A);//El elemento E se desempila
			E2=pop(&A);//El elemento E2 se desempila
			R=E2.r+E.r; //Se realiza la suma de E y E2
			E.r=R;//Se iguala el valor de E a R.
			push(E,&A);//Empila el elemento E
		}
		else if(post_fijo[i]=='-')
		{
			E=pop(&A);//El elemento E se desempila
			E2=pop(&A);//El elemento E2 se desempila
			R=E2.r-E.r;//Se realiza la resta de E2 menos E1
			E.r=R;//Asigna el valor de R a E
			push(E,&A);//Empila el elemento E
		}
		else
		{
			x=post_fijo[i]; //Asigna el valor de post_fijo a x
			if(valores[x-65]==-1) //Sí en la posición "x-65" el arreglo de valores es igual a -1
			{
				printf("Ingrese el valor de %c\n",post_fijo[i]);//Imprime instrucción
				scanf("%lf",&R);//Solicita el valor de R
				valores[x-65]=R; //Asigna el valor de R a valores[x-65]
			}
			E.r=valores[x-65];//Asigna el valr de valores[x-65] a E
			push(E,&A);//Empila el elemento E
		}
	}

	E=pop(&A);//Desempila el elemento E
	printf("%lf\n", E.r); //Imprime E
	return 0;
}