#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
/*Permisos:
	Propietario Lectura: 00400
	Propietario Escritura: 00200
	Propietario Ejecucion/Busqueda: 00100

	Grupo Lectura: 00040
	Grupo Escritura: 00020
	Grupo Ejecucion/Busqueda: 00010

	Otros Lectura: 00004
	Otros Escritura: 00002
	Otros Ejecucion/Busqueda: 00001
*/

char* leerNombreArchivo()
{
	char* path = (char*)malloc(2000*sizeof(char));
	printf("Ruta o nombre del archivo: ");
	scanf("%s", path);
	return path;
}

int main()
{
	int permiso = 00, r = 0;
	//Definimos arreglos para cada tipo de usuario y permisos
	char usuarios [3][12] = {"Propietario", "Grupo", "Otros"};
	char permisos [3][20] = {"lectura", "escritura", "ejecucion/busqueda"};
	//Obtenemos el directorio del archivo desde la entrada de teclado
	char* archivo = leerNombreArchivo();
	/*Llamada al sistema open recibe la ruta del archivo a abrir y el modo 
	(lectura, escritura, ejecucion). Devuelve un descriptor de archivo. 
	Si devuelve -1 existieron errores*/
	if(open(archivo, O_RDWR) == -1){
		perror(archivo);
    	exit(EXIT_FAILURE);
	}
	else
	{
		printf("\nIngrese 1 para responde SI e ingrese 0 para responder NO\n\n");
		for(int i=0; i<3; i++){//Con este for recorremos el arreglo de usuarios
			for(int j=0; j<3; j++){//Con este for recorremos el arreglo de permisos
				printf("¿%s tiene pemiso de: %s? ", usuarios[i], permisos[j]);
				scanf("%d", &r);
				if(r==1)//Si la respuesta fue afirmativa
				{
					switch (j)
					{
						case 0: permiso = permiso + 04;//4 para lectura
						break;
						case 1: permiso = permiso + 02;//2 para escritura
						break;
						case 2: permiso = permiso + 01;//1 para ejecucion/busqueda
						break;
					}
				}
			}
			printf("\n");
			/*Vamos multiplicando por 10 cuando los usuarios sean 
			propietarios y grupos*/
			if(i<2) permiso=permiso*010; 
		}
		printf("Permisos: %o\n", permiso);
		/*Llamada al sistema chmod recibe la ruta del archivo y los permisos 
		en bits de modo de archivo. Retorna -1 si existieron errores*/
		if(chmod(archivo, (mode_t)permiso) == -1){
			perror(archivo);
	    	exit(EXIT_FAILURE);
		}
		else{
			printf("Permisos de %s cambiados.\n", archivo);
		}
	}
	return 0;
}