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
	char usuarios [3][12] = {"Propietario", "Grupo", "Otros"};
	char permisos [3][20] = {"lectura", "escritura", "ejecucion/busqueda"};
	char* archivo = leerNombreArchivo();

	if(open(archivo, O_RDWR) == -1){
		perror(archivo);
    	exit(EXIT_FAILURE);
	}
	else
	{
		printf("\nIngrese 1 para responde SI e ingrese 0 para responder NO\n\n");

		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				printf("¿%s tiene pemiso de: %s? ", usuarios[i], permisos[j]);
				scanf("%d", &r);
				if(r==1)
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
			//Vamos multiplicando por 10 cuando los usuarios sean propietarios y grupos
			if(i<2) permiso=permiso*010; 
			
		}
		printf("Permisos: %o\n", permiso);

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