#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) 
{
	int ayuda1;
	int ayuda2;
	int ayuda3;
	int ayuda4;
	int ultimoNum = 10; //Me ayuda para crear la ultima parte de los arboles los ultimos que seran creados por el hijo

	for(int i = 0; i < 10; i++)
  	{  //Creo los primeros diez procesos ---- En horizontal
    	ayuda1 = fork();
    	if(ayuda1)
    	{  //Si es el padre no hago nada, solo imprimo que soy la main
      		printf("M. Soy el main y mi hijo es: %i\n", ayuda1);
    	}
    	else
    	{   //Si soy el hijo, soy del primer nivel asi que debo crear mas hijos
      		printf("1. Soy el hijo numero %i del proceso ->%i\n", i, getpid());
      		for(int x = 1; x <= (10-i); x++)
      		{   //Debo crear 10 procesos primero y luego 9 y asi, dependiendo el valor de i, donde i es mi contador del for anterior
        		ayuda2 = fork();  //Creo el proceso
        		if(ayuda2)
        		{
        			printf("2. Soy padre del proceso %i, y soy hijo del proceso %i\n", ayuda2, getpid());   
        			//Si es el padre, ya no hago nada no me interesa hacer nada mas aqui
        			exit(0);
        		}
        		else
        		{  //Si soy el hijo hago mas hijos para hacer el diagrama hacia abajo
          			printf("3. Soy el hijo %i del proceso %i\n", x-1, getpid());
          			ayuda3 = fork();//Hago mas hijos
	          		if(ayuda3)
	          		{
	            		printf("4. Soy padre del proceso %i y soy hijo del proceso %i\n", ayuda3, getpid() );
	           	 		exit(0);
	          		}
	          		else
	          		{
	            		printf("Yo el hijo %i, y mi padre es el proceso: %i\n", x-1, getpid());
	            		if(x == ultimoNum)
	            		{  //Comparo con 10 porque el primer tiene que ser de 10 elementos
	              			for(int y = 1; y < x; y++)
	              			{
	                			ayuda4 = fork();
	                			if (ayuda4) 
	                			{
	                				printf("4. Soy padre del proceso %i y soy hijo del proceso %i\n", ayuda4, getpid()); 
	                				//Si soy padre solo continuo para crear mas
	                				exit(0);
	                			}	 
	                			else 
	                			{
	                  				printf("5. Soy el hijo %i del proceso %i\n", y, getpid());
	                  				exit(0);
	                    			//Si es hijo solo continuo, no me interesa mas
	                			}
	              			}
	              		ultimoNum--;  
	              		//Decremento este numero porque para la siguiente rama debo crear un hijo menos
	              		exit(0);
	            		}
	          		}
        		}
      		}
    	}
  	}
  	return 0;
}
