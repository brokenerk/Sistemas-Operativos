/*
LIBRERIA: Cabecera de el TAD PILA DINÁMICA
AUTORES: Nicolás Sayago Abigail
		Salgado Zaragoza Gustavo
		Sanchez Merlín Ana Luisa
VERSIÓN: 1.0

DESCRIPCIÓN: TAD pila o stack.
Estructura de datos en la que se cumple:
Los elementos se añaden y se remueven por un solo extremo.
Este extremo es llamado “tope” de la pila.

OBSERVACIONES: En este caso hablamos de una Estructura de datos dinámica, a la cual
se le asigna un espacio de memoria a conforme se vaya necesitando en la ejecucion
del programa. La memoria no queda fija durante la compílación.
*/

//DEFINICIÓN CON CONSTANTES

#define TRUE 1
#define FALSE 0


//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;


//Definir un elemento (Se modela con una estructura "elemento")
typedef struct elemento
{
	//Variables de la estructura elemento
	int d;
	double r;
	char x;
} elemento;
/*Definir un nodo que será utilizado para almacenar una posición de la pila
(Nodo), lo que incluira a un elemento y a un apuntador al siguiente nodo*/
typedef struct nodo
{
	//Elemento a almacenar
	elemento e;
	//Aputador al elemento de abajo (Requerido por ser una implementación dinámica)
	struct nodo *abajo;
}nodo;

//Definir una pila (Se modela con estructura)
typedef struct pila
{
	nodo *tope;
}pila;

//DECLARACIÓN DE FUNCIONES
void initialize(pila *p); //Inicializar pila (Iniciar una pila para su uso)
void push(elemento e, pila *p);//Empilar (Introducir un elemento a la pila)
elemento pop(pila *p);//Desempilar (Extraer un elemento de la pila)
elemento top(pila *p);//Tope (Obtener el "elemento" del tope de la pila si extraerlo de la pila)
int size(pila *p);//Tamaño de la pila (Obtener el número de elementos en la pila)
boolean empty(pila *p);//Vacia (Preguntar si la pila esta vacia)
void destroy(pila *p);//Elimina pila (Borra a todos los elementos y a la pila de memoria)
