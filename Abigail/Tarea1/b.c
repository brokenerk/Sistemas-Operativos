// 04 de Octubre 2018
// Para generar muchos procesos HIJO
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
int i = 10;
int main(void)
{
	int id_proc;
	for(i = 0; i<5; i++) // CREAR 5 PROCESOS HORIZONTALES
	{
		id_proc = fork();
		if(id_proc == 0)
		{
			printf("Soy el proceso hijo %i\n", i);
			if(i == 0)	// PARA EL PRIMER HIJO
			{
				for(j = 0; j<3; j++) // CREAR 3 PROCESOS HORIZONTALES
				{
					id_proc = fork();
					if(id_proc == 0)
					{
						printf("Soy el proceso hijo\n");
						if(j == 0)
						{
							for(k = 0; k<2; k++) // CREA 2 PROCESOS VERTICALES
							{
								id_proc = fork();
								if(id_proc == 0)
								{
									printf("Soy el proceso hijo %i\n", i);
									if(k == 1) // EN EL ULTIMO PROCESO
									{
										for(l = 0; l<3; l++) // CREA  PROCESOS HORIZONTALES
										{
											if( l == 1) // EN EL SEGUNDO HIJO
											{
												id_proc = fork();
												if(id_proc == 0)
												{
													printf("Soy el proceso hijo %i\n", i);

												} 
												else
												{
													break; // Sale del ciclo 
												}
											}
										}
									}
								} 
								else
								{
									break; // Sale del ciclo 
								}	
							}
						}
					}
				}
			} // Fin if - Hijo 0
			if()
		}  
	}	// Fin 5 procesos horizontales
	exit(0);
}

