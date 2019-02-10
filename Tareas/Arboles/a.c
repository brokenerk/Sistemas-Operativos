#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	int id_proc, i, j, k, l, m, w, x, y;

	for(i=0; i<2; i++){//2 procesos
		if((id_proc=fork())==0){//Creo 2 procesos verticales
			printf("Soy el proceso hijo\n");

			if(i==1){//Segundo arbol vertical
				for(j=0; j<3; j++){//3 procesos
					if((id_proc=fork())==0){//Creo 3 procesos horizontales
						printf("Soy el proceso hijo\n");

						if(j==0){//Primer proceso - izquierda
							for(k=0; k<2; k++){//2 procesos
								if((id_proc=fork())==0){//Creo 2 procesos horizontales
									printf("Soy el proceso hijo\n");

									if(k==0){//Primer proceso - izquierda
										if((id_proc=fork())==0){//1 proceso vertical
											printf("Soy el proceso hijo\n");
											exit(0);
										}//ACABAMOS
									}
									else if(k==1){//Segundo proceso - derecha
										if((id_proc=fork())==0){//1 proceso vertical
											printf("Soy el proceso hijo\n");

											for(l=0; l<2; l++){//2 procesos
												if((id_proc=fork())==0){//Creamos 2 procesos horizontales
													printf("Soy el proceso hijo\n");
													exit(0);
												}//ACABAMOS
											}
											exit(0);
										}
									}
									exit(0);
								}
							}
						}
						else if(j==1){//Segundo proceso - centro
							if((id_proc=fork())==0){//1 proceso vertical
								printf("Soy el proceso hijo\n");
								exit(0);
							}//ACABAMOS
							
						}
						else if(j==2){//Tercer proceso - derecha
							for(m=0; m<2; m++){//2 procesos
								if((id_proc=fork())==0){//Creo 2 procesos horizontales
									printf("Soy el proceso hijo\n");

									if(m==0){//Primer proceso - izquierda
										if((id_proc=fork())==0){//1 proceso vertical
											printf("Soy el proceso hijo\n");

											for(l=0; l<2; l++){//2 procesos
												if((id_proc=fork())==0){//Creo 2 procesos horizontales
													printf("Soy el proceso hijo\n");
													exit(0);
												}//ACABAMOS
											}
											exit(0);
										}
									}
									else if(m==1){//Segundo proceso - derecha
										for(w=0; w<2; w++){//2 procesos
											if((id_proc=fork())==0){//Creamos 2 procesos verticales
												printf("Soy el proceso hijo\n");
												if(w==1){//Segundo proceso
													for(x=0; x<4; x++){//4 procesos
														if((id_proc=fork())==0){//Creamos 4 procesos horizontales
															printf("Soy el proceso hijo\n");
															exit(0);
														}//ACABAMOS
													}
												}
											}
											else{
												break;
												exit(0);
											}
										}
									}
									exit(0);
								}
							}
						}
						exit(0);
					}
				}
			}
		}
		else{
			break;
			exit(0);
		}
	}
	exit(0);
}