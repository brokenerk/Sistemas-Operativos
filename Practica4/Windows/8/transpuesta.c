#include <windows.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double mat1[10][10];
double mat2[10][10];
double res1[10][10];
double res2[10][10];

void CrearMatriz()
{
	srand(time(NULL));
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			mat1[i][j]=rand()%11;
			mat2[j][i]=rand()%11;
		}
	}
}

void TranspuestaMatriz()
{

	int i, j;
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			res1[i][j] = mat1[j][i];
			res2[i][j] = mat2[j][i];
		}
	}
}

void crearArchivo(char* ruta, double m[10][10])
{
	int i,j;
    char num[15];

    HANDLE h = CreateFile(ruta,						//ruta del archivo
						GENERIC_WRITE,			//abrir para escribir
						0,						//no compartir
						NULL,						// seguridad por default
						CREATE_ALWAYS,				//crear siempre
						FILE_ATTRIBUTE_TEMPORARY,	//archivo normal
						NULL);					//sin tributos

    if (h == INVALID_HANDLE_VALUE)
    {
    	perror(ruta);
        exit(EXIT_FAILURE);
    }
    else
    {
    	DWORD bytesEscritos = 0;

		for(i=0 ; i<10 ; i++) // Escribimos 5 veces el texto en el archivo
		{
			for(j=0 ; j<10 ; j++) // Escribimos 5 veces el texto en el archivo
			{
				sprintf(num, "%.3f\t", m[i][j]);
		        /*Funcion WrifeFile recibe los parametros a continuacion y devuelve un true si no existieron errores*/
				BOOL escribir = WriteFile( 
		                    h,           				// abrir handle del archivo
		                    num,      					// informacion a escribir
		                    (DWORD)strlen(num),  		// tamaño de bytes a escribir
		                    &bytesEscritos, 			// tamaño de bytes escrit
		                    NULL);           			// no overlapped structure

				if(!escribir)
    			{
    				perror(ruta);
        			exit(EXIT_FAILURE);
    			}
    		}
    		BOOL espacio = WriteFile( 
		                    h,           				// abrir handle del archivo
		                    "\n",      					// informacion a escribir
		                    (DWORD)strlen("\n"),  		// tamaño de bytes a escribir
		                    &bytesEscritos, 			// tamaño de bytes escrit
		                    NULL);           			// no overlapped structure
			if(!espacio)
    		{
    			perror(ruta);
        		exit(EXIT_FAILURE);
    		}
    	}
	    //Llamada al sistema CloseHandle recibe un descriptor de archivo y retorna un valor cero si han habido errores
	    if(CloseHandle(h) == 0)
	    {
	    	perror(ruta);
	    	exit(EXIT_FAILURE);
	    }
	}
}

void imprimir(double m[10][10])
{
	int i, j;
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
			printf("%.3f\t", m[i][j]);					
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	CrearMatriz();
	imprimir(mat1);
	imprimir(mat2);
	TranspuestaMatriz();
	char* dir1 = (char*)calloc(2000,sizeof(char));
	dir1 = 
	"C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\Resultados\\transpuesta1.txt";
	crearArchivo(dir1, res1);

	char* dir2 = (char*)calloc(2000,sizeof(char));
	dir2 = 
	"C:\\Users\\YaKerTaker\\Google Drive\\5to SEMESTRE\\Sistemas-Operativos\\Practica4\\Windows\\8\\Resultados\\transpuesta2.txt";
	crearArchivo(dir2, res2);
	//LOS ARCHIVOS NO DEBEN EXISTIR, SINO ARROJARA ERROR Y NO ESCRIBIRA NADA

	printf("ARCHIVOS TRANSPUESTAS ESCRITO\n");
    printf("%s", dir1);
    printf("\n");
    printf("%s", dir2);
    printf("\n");

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	int i;
	ZeroMemory(&si, sizeof(si));
	si.cb=sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if(argc!=2)
	{
		//printf(/*Usar: %s */"Soy el proceso hijo \n"/*, argv[0]*/);
		return 0;
	}
	//Creacion proceso hijo

		if(!CreateProcess(NULL, argv[0],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
		{
			printf("Fallo al invocar CreateProcess(%d)\n",GetLastError());
			return 0;
		}
	//Proceso Padre
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	//Terminacion controlada del proceso e hilo asociado de ejecucion
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}