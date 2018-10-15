#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char arr[1000][5];
int actx,acty;
char acta;
float aux, aux1, res,resaux=0;

void operacion(){
	aux=acta-48;
	if(arr[actx-3][acty]=='('){
		if(resaux!=0)
			aux1=resaux;
		else
			aux1=arr[actx-3][1]-48;
	}
	else{
		aux1=arr[actx-3][acty]-48;
	}
	if(arr[actx-2][0]=='+')
		res=aux+aux1;
	else if(arr[actx-2][0]=='-')
		res=aux1-aux;
	else if(arr[actx-2][0]=='*')
		res=aux*aux1;
	else if(arr[actx-2][0]=='/')
		res=aux1/aux;
	else if(arr[actx-2][0]=='^')
		res=pow(aux1,aux);
	if(arr[actx-3][acty]=='('){
		if(actx-3==0){
			arr[0][0]=res+48;
		}
		else if(arr[actx-4][acty]=='('){
			arr[actx-4][acty+1]=res+48;
			resaux=res;
			actx-=3;
			acta='(';
		}
		else{
			arr[actx-4][acty]=res+48;
			actx-=3;
			acta='1';
		}
	}
	if(arr[actx-4][acty]=='('){
		if(actx-4==0){
			arr[0][0]=res+48;
			actx-=3;
			acta='1';
			return;
		}
		else if(arr[actx-5][acty]=='('){
			arr[actx-5][acty+1]=res+48;
			resaux=res;
			actx=actx-4;
			acta='(';
		}
	}
}	
void estado(char c){
	if(acta=='('){
		if(c=='('){
			arr[actx][acty]=c;
			actx++;
			acta=c;
		}
		else if (c>47 && c<58){
			arr[actx][acty]=c;
			actx++;
			acta=c;
		}
		else if (c=='^' || c=='+' || c=='-' || c=='*' || c=='/'){
			arr[actx][acty]=c;
			actx++;
			acta=c;
		}
	}
	else if(acta>47 && acta<58){
		if (c==')'){
			operacion();
		}
		else if (c=='^' || c=='+' || c=='-' || c=='*' || c=='/'){
			arr[actx][acty]=c;
			actx++;
			acta=c;
		}
	}
	else if(acta=='^' || acta=='+' || acta=='-' || acta=='*' || acta=='/'){
		if (c>47 && c<58){
			arr[actx][acty]=c;
			actx++;
			acta=c;
		}
		else if (c=='('){
			arr[actx][acty]=c;
			actx++;
			acta=c;
		}
	}
	else if(acta==')'){
		if (c=='^' || c=='+' || c=='-' || c=='*' || c=='/'){
			arr[actx][acty]=c;
			actx++;
			acta=c;
		}
	}
	else{
		printf("Caracter no aceptado\n");
	}
}
int main(){
	char c;
	int n=0;
	char *linea = (char*)malloc(1*sizeof(char));
	printf("Ingrese la expresion: ");
	do
	{
		c = getchar(); //Guardar la cadena que se ingresa
		linea[n] = c; 
		n++;
		linea = (char*)realloc(linea,(n+1)*sizeof(char));
	}while(c != '\n');

	linea[n-1] = '\0'; //Carácter que finaliza una cadena
	n--;
	actx=0;
	acty=0;
	arr[actx][acty]=linea[0];
	actx=1;
	acty=0;
	acta=linea[0];
	for(int i=0;i<n;i++){
		estado(linea[i]);
	}
	printf("Resultado: %.2f\n", res);
}