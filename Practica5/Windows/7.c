//Compilar: gcc 7.c -o 7
//Ejecutar: 7 [RutaOrigen] [RutaDestino]

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

//Estructura para manejar la ruta origen y destino
typedef struct r RUTA;
struct r
{
	char Origen[400];
	char Destino[400];
};

int esDirectorio(WIN32_FIND_DATA ruta)
{
	//Revisamos si lo que se encontro en el escaneo es un directorio
	if (ruta.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		return 1;
	else
		return 0;
}

int ignorarPuntos(char nombre[])
{
	//Al escanear un directorio, aparecen puntos
	//Con este funcion, los eliminamos para trabajar solo con directorios/archivos
	if(strcmp(nombre, ".") && strcmp(nombre, ".."))
		return 1;
	else
		return 0;
}


void concatenar(char dir[], char aux[], char nombre[])
{
	//Concatener directorio y archivo
	strcpy(dir, aux);
	strcat(dir, "\\");
	strcat(dir, nombre);
}

void copiarArchivo(char origen[], char destino[])
{
	//Handle para leer
    HANDLE o = CreateFile(origen,                     //ruta del archivo
                        GENERIC_READ,	//abrir para leer-escribir
                        FILE_SHARE_READ,             //no compartir
                        NULL,                       // seguridad por default
                        OPEN_EXISTING,              //crear siempre
                        FILE_ATTRIBUTE_NORMAL,   //archivo normal
                        NULL);          

	if (o == INVALID_HANDLE_VALUE)
    {
    	perror(origen);
        exit(EXIT_FAILURE);
    }

    //Handle para escribir
    HANDLE d = CreateFile(destino,                     //ruta del archivo
                        GENERIC_WRITE,          //abrir para escribir
                        0,                      //no compartir
                        NULL,                       // seguridad por default
                        CREATE_ALWAYS,              //crear siempre
                        FILE_ATTRIBUTE_NORMAL,   //archivo normal
                        NULL);          

	if (d == INVALID_HANDLE_VALUE)
    {
    	perror(destino);
        exit(EXIT_FAILURE);
    }

    DWORD bytesEscritos = 0;
   	char *contenido = (char *)calloc(1000000, sizeof(char));
   
	//Leemos el archivo origen y lo escribimos en el destino
	if(ReadFile(o, contenido, 1000000, &bytesEscritos, NULL))
	{
		BOOL escribir = WriteFile(d,           		// abrir handle del archivo
                    			contenido,      			// informacion a escribir
                    			(DWORD)strlen(contenido),  // tamaño de bytes a escribir
                   				&bytesEscritos, 			// tamaño de bytes escrit
                   				NULL);
		if(!escribir)
		{
			perror(destino);
    		exit(EXIT_FAILURE);
		}
		//memset(contenido, '\0', (int)bytesEscritos);
		printf("%s ..... COPIADO", destino);
		printf("\n\n");

	}
	free(contenido);
	CloseHandle(o);
	CloseHandle(d);
}

//FUNCION PRINCIPAL HILO
//Funciones que ejecutaran los hilos creados
DWORD WINAPI hilo(LPVOID lpParam)
{
	char* buscar=(char*)calloc(4000,sizeof(char));
    HANDLE h; //Handle para manejar los directorios leidos

    //Nos sirve para leer todos los directorios contenidos en una ruta   
    WIN32_FIND_DATA wfd;
    int i = 0, t = 0, num = 0;

	//Utilizamos la estructura que creamos
	RUTA *directorios, *raices = (RUTA*)lpParam;

	//Creamos un hilo
	DWORD *id_hilo = (DWORD*)calloc(1, sizeof(DWORD));
	HANDLE *manHilo = (HANDLE*)calloc(1, sizeof(HANDLE));

	//Concatenamos a una cadena limpia para evitar errores
	strcpy (buscar, raices->Origen);
    strcat (buscar, "\\*.*");

    //Leemos la ruta origen en busca de directorios
    h = FindFirstFile (buscar, &wfd);

	if(h == INVALID_HANDLE_VALUE)
	{
		perror(raices->Origen);
	    exit(-1);
	}
	else
	{
		do{ num++; } //Aqui primero contamos cuantos directorios hay
		while(FindNextFile (h, &wfd));

		//Reasignamos memoria para guardar los directorios encontrados
		directorios = (RUTA*)calloc(num, sizeof(RUTA));
		//Nuevamente leemos la ruta origen en busca de directorios
		h = FindFirstFile (buscar, &wfd);
		
		do
		{
			//Vamos construyendo las rutas de los directorios origen
			concatenar(directorios[i].Origen, raices->Origen, wfd.cFileName);
			//wfd es una especie de estructura que posee toda la info de los directorios
			if(esDirectorio(wfd)) 
			{
				//wfd.cFileName es el nombre de cada directorio/archivo
				if(ignorarPuntos(wfd.cFileName)) 
				{
					printf("Soy el hilo %d. Encontre: %s", t, directorios[i].Origen);
					printf("\n");

					//Solo nos quedamos con directorios y construimos las rutas de destino
					concatenar(directorios[i].Destino, raices->Destino, wfd.cFileName);
					printf("Soy el hilo %d. Creare: %s", t, directorios[i].Destino);
					printf("\n\n");

					//Creamos los directorios destino
					if(!CreateDirectory(directorios[i].Destino, NULL))
					{
						perror(directorios[i].Destino);
       					exit(-1);
    				}
    				//Vamos creando un nuevo hilo por cada directorio encontrado
    				id_hilo = (DWORD*)realloc(id_hilo, sizeof(DWORD)*(t+1));
    				manHilo = (HANDLE*)realloc(manHilo, sizeof(HANDLE)*(t+1));
    				manHilo[t] = CreateThread(NULL, 0, hilo, &directorios[i], 0, &id_hilo[t]);
    				t++;
				}
			}
			else
			{
				//Ahora, creamos las rutas para los archivos dentro de cada directorio
				concatenar(directorios[i].Destino, raices->Destino, wfd.cFileName);
				printf("\n");
				printf("Copiare el archivo: %s", directorios[i].Origen);
				printf("\n");
				//Leemos y escribimos los archivos
				copiarArchivo(directorios[i].Origen, directorios[i].Destino);
			}
			i++;
		}
		while (FindNextFile (h, &wfd));//Leemos hasta que no existan directorios
		//Esperamos a que todos los hilos acaben
		WaitForMultipleObjects(t, manHilo, TRUE, INFINITE);

		FindClose (h);
		free(directorios);
		CloseHandle(manHilo);
	}
}

int main(int argc, char *argv[])
{
	//Creamos las rutas origen y destino
	RUTA rutas;
	DWORD id_hilo;
	HANDLE manHilo;
	WIN32_FIND_DATA wdata;
	
	//Si no se ingresaron rutas por linea de comandos, tomamos las predeterminadas
	if(argc != 3)
	{
		strcpy(rutas.Origen, "C:\\Users\\YaKerTaker\\Desktop\\origen");
		strcpy(rutas.Destino, "C:\\Users\\YaKerTaker\\Desktop\\destino");
	}
	else
	{
		strcpy(rutas.Origen, argv[1]);
		strcpy(rutas.Destino, argv[2]);
	}

	printf("Ruta Origen: %s",rutas.Origen);
	printf("\n");
	printf("Ruta Destino: %s",rutas.Destino);
	printf("\n\n\n");
	
	HANDLE handl = FindFirstFile (rutas.Origen, &wdata);
	if(handl == INVALID_HANDLE_VALUE)
	{
		perror(rutas.Origen);
	    exit(-1);
	}

	/*Revisamos la ruta ingresada es un directorio, y que los directorios de origen
	no existan en la ruta destino*/
	if(esDirectorio(wdata))
	{
		if(!CreateDirectory(rutas.Destino, NULL))
		{
			perror(rutas.Destino);
	        exit(-1);
	    }
	    else
	    {
	    	//Creamos un hilo y enviamos las rutas
	    	manHilo = CreateThread(NULL, 0, hilo, &rutas, 0, &id_hilo);
	    	WaitForSingleObject(manHilo, INFINITE);
	    }
	}
	return 0;
}