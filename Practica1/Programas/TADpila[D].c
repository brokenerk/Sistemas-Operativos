/*
IMPLEMENTACIONES DE LA LIBRERIA DEL TAD PILA DINÁMICA(TADPila[D].h)
AUTOR(ES): 	Nicolás Sayago Abigail
			Salgado Zaragoza Gustavo
			Sanchez Merlín Ana Luisa
VERSIÓN: 1.0

DESCRIPCIÓN: TAD pila.
Estructura de datos en la que se cumple:
Los elementos se añaden y se remueven por un solo extremo. 
Este extremo es llamado "tope" de la pila.

OBSERVACIONES: En este caso hablamos de una Estructura de datos dinámica, a la cual
se le asigna un espacio de memoria a conforme se vaya necesitando en la ejecucion
del programa. La memoria no queda fija durante la compílación.

COMPILACIÓN PARA GENERAR EL CÓDIGO OBJETO: gcc -c TADPila[D].c
*/
//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include "TADpila[D].h"

//DEFINICIÓN DE FUNCIONES

/*
void Initialize(pila *p);
Descripción: Inicializar pila (Iniciar una pila para su uso)
Recibe: int *p (Referencia a la pila "p" a operar)
Devuelve:
Observaciones: El usuario a creado una pila y p tiene la referencia a ella, 
si esto no ha pasado se ocasionara un error.
*/

void initialize(pila *p)
{
	p->tope=NULL; //(*p).tope=-1;
	return;
}
/*
void Push(pila *p, elemento e);
Descripción: Empilar (Introducir un elemento a la pila)
Recibe: pila *p (Referencia a la pila "p" a operar), elemento e
 (Elemento a introducir en la pila)
Observaciones: El usuario a creado una pila y p tiene la referencia a ella, p ya ha sido inicializada.
Ademas no se valida si el malloc() pudo o no apartar memoria, se idealiza que siempre funciona bien 
y no se acaba la memoria
*/
void push(elemento e, pila *p)
{
	nodo *aux;
	aux=malloc(sizeof(nodo));
	aux->e=e;
	aux->abajo=p->tope;
	p->tope=aux;
	return;
}
/*
void Pop(pila *p);
Descripción: Desempilar (Extraer un elemento de la pila)
Recibe: pila *p (Referencia a la pila "p" a operar)
Devuelve: elemento (Elemento e extraido de la pila)
Observaciones: El usuario a creado una pila y p tiene la referencia a ella, p ya ha sido inicializada.
Ademas no se valida si la pila esta vacia antes de desempilar (causa error desempilar si esta esta vacía), 
tampoco se valida si free() pudo o no liberar la memoria, se idealiza que siempre funciona bien 
*/
elemento pop(pila *p)
{
	nodo *aux;
	elemento r;
	r=p->tope->e;
	aux=p->tope;
	p->tope=p->tope->abajo;
	free(aux);
	return r;
}
/*
elemento Top(pila *p);
Descripción: Tope (Obtener el "elemento" del tope de la pila si extraerlo de la pila)
Recibe: pila *p (Referencia a la pila "p" a operar)
Devuelve: elemento (Elemento del tope de la pila)
Observaciones: El usuario a creado una pila y p tiene la referencia a ella, p ya ha sido inicializada.
Ademas no se valida si la pila esta vacia antes de consultar al elemnto del tope (causa error si esta esta vacía).
*/
elemento top(pila *p)
{
	elemento r;
	r = p->tope->e;
	return r;
}
/*
int Size(pila *p);
Descripción: Tamaño de la pila (Obtener el número de elementos en la pila)
Recibe: pila *p (Referencia a la pila "p" a operar)
Devuelve: int (Tamaño de la pila -1->Vacia, 1->1 elemento, 2->2 elementos, ...)
Observaciones: El usuario a creado una pila y p tiene la referencia a ella, p ya ha sido inicializada.
*/
int size(pila *p)
{
	int size=0;
	nodo *aux;
	aux=p->tope;
	while(aux!=NULL)
	{
		aux=aux->abajo;
		size++;
	}
	return size;
}
/*
boolean Empty(pila *p);
Descripción: //Vacia (Preguntar si la pila esta vacia)
Recibe: pila *p (Referencia a la pila "p" a operar)
Devuelve: boolean (TRUE o FALSE según sea el caso)
Observaciones: El usuario a creado una pila y p tiene la referencia a ella, p ya ha sido inicializada.
*/
boolean empty(pila *p)
{
	if(p->tope==NULL)
		return TRUE;
	return FALSE;
}

/*
void Destroy(pila *p);
Descripción: Elimina pila (Borra a todos los elementos en a la pila de memoria)
Recibe: pila *p (Referencia a la pila "p" a operar)
Devuelve: 
Observaciones: El usuario a creado una pila y p tiene la referencia a ella, s ya ha sido inicializada.
*/
void destroy(pila *p)
{
	nodo *aux;
	while(p->tope!=NULL)
	{
		aux=p->tope->abajo;
		free(p->tope);
		p->tope=aux;
	}
	return;
}
