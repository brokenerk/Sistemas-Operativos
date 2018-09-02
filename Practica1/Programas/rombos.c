#include<stdio.h>

void archivo(int N){
	//Creamos el tipo de dato FILE
	FILE* archivo;
	archivo=fopen("salida.txt","w"); 
	if(archivo!=NULL)
	{	
		int aux,aux1, ini, fin;
		if(N%2==0)
			N+=1;
		aux1=N;
		aux=aux1;
		ini=N/2;
		fin=ini;
		for(int i=0;i<aux/2;i++){
			for (int j=0;j<aux;j++){
				if (j==ini || j==fin){
					fprintf(archivo, "*");
				}
				else{
					fprintf(archivo, " ");
				}
			}
			for(int j=1;j<=aux;j++){
				if (j>=ini+1 && j<=fin+1){
						fprintf(archivo, "*");
				}
				else{
					fprintf(archivo, " ");
				}
			}
			ini--;
			fin++;
			fprintf(archivo, "\n");
		}
		for(int i=0;i<2*aux;i++){
			fprintf(archivo, "*");
		}
		ini++;
		fin--;
		fprintf(archivo, "\n");
		for(int i=0;i<aux/2;i++){
			for (int j=0;j<aux;j++){
				if (j==ini || j==fin){
					fprintf(archivo, "*");
				}
				else{
					fprintf(archivo, " ");
				}
			}
			for(int j=1;j<=aux;j++){
				if (j>=ini+1 && j<=fin+1){
						fprintf(archivo, "*");
				}
				else{
					fprintf(archivo, " ");
				}
			}
			ini++;
			fin--;
			fprintf(archivo, "\n");
		}
		fclose(archivo);
		printf("\nArchivo guardado como 'salida.txt'");
	}
	else
		printf("\nError");

}

void asteriscos(int N){
	int aux,aux1, ini, fin;
	if(N%2==0)
		N+=1;
	aux1=N;
	aux=aux1;
	ini=N/2;
	fin=ini;
	for(int i=0;i<aux/2;i++){
		for (int j=0;j<aux;j++){
			if (j==ini || j==fin){
				printf("*");
			}
			else{
				printf(" ");
			}
		}
		for(int j=1;j<=aux;j++){
			if (j>=ini+1 && j<=fin+1){
					printf("*");
			}
			else{
				printf(" ");
			}
		}
		ini--;
		fin++;
		printf("\n");
	}
	for(int i=0;i<2*aux;i++){
		printf("*");
	}
	ini++;
	fin--;
	printf("\n");
	for(int i=0;i<(aux/2);i++){
		for (int j=0;j<aux;j++){
			if (j==ini || j==fin){
				printf("*");
			}
			else{
				printf(" ");
			}
		}
		for(int j=1;j<=aux;j++){
			if (j>=ini+1 && j<=fin+1){
					printf("*");
			}
			else{
				printf(" ");
			}
		}
		ini++;
		fin--;
		printf("\n");
	}
}

int main (){
	int N, resp;

	printf("Ingresa el numero (entre 0 y 40) de asteriscos que tendra: ");
	scanf("%d", &N);

	while(N%2 || !((N/2)%2) || N<0 || N>40){
		printf("Imposible dibujar o fuera del rango. Ingrese otro numero: ");
		scanf("%d", &N);
	}
	
	asteriscos(N/2);
	printf("\nGuardar en archivo? Si=1/No=0: ");
		scanf("%d",&resp);
		if(resp==1)
			archivo(N/2);
}