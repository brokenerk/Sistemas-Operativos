#include <windows.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;
int main(){
	string line;
  ifstream myfile ("salidaS.txt");
  printf("Resultado de la suma\n\n");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }
  ifstream mi ("salidaR.txt");
  printf("Resultado de la Resta: \n\n");
  if (mi.is_open())
  {
    while ( getline (mi,line) )
    {
      cout << line << '\n';
    }
    mi.close();
  }
  ifstream mifile ("salidaM.txt");
  printf("Resultado de la Multiplicaion: \n\n");
  if (mifile.is_open())
  {
    while ( getline (mifile,line) )
    {
      cout << line << '\n';
    }
    mifile.close();
  }
  ifstream myfileo ("salidaT.txt");
  printf("Transpuestas: \n\n");
  if (myfileo.is_open())
  {
  	int q=0;
    while ( getline (myfileo,line) )
    {
      cout << line << '\n';
      q++;
      if(q==10)
      	printf("\n");
    }
    myfileo.close();
  }

}