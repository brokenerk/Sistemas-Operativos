#include <windows.h>
#include <stdio.h>
DWORD WINAPI Hilos10(LPVOID lpParam);
DWORD WINAPI Hilos5(LPVOID lpParam);
DWORD WINAPI HiloTerminal(LPVOID lpParam);
typedef struct informacion info;
struct informacion
{
    int val1;
};
int i, j, k, l;

int main(void)
{
  DWORD idHilo;
  HANDLE manHilo;
  info argumentos;
  printf("\n Soy el proceso hilador");
  for(i = 0; i < 15; i++)
  {
    printf("\nHe creado %d de 15 hilos",i+1);
    manHilo = CreateThread(NULL, 0, Hilos10,&argumentos,0,&idHilo);
    for(l = 0; l < 15; l++)
    {
      WaitForSingleObject(manHilo, INFINITE);
    }
  }

  CloseHandle(manHilo);
  return 0;
}

DWORD WINAPI Hilos10(LPVOID lpParam)
{
  printf(": id = %d", GetCurrentThreadId());
  DWORD idHilo;
  HANDLE manHilo;
  info argumentos;
  for(k = 0; k < 10; k++)
  {
    printf("\n\tHe creado %d de 10 hilos",k+1);
    manHilo = CreateThread(NULL, 0, Hilos5,&argumentos,0,&idHilo);
    WaitForSingleObject(manHilo, INFINITE);
  }
  CloseHandle(manHilo);
  return 0;
}

DWORD WINAPI Hilos5(LPVOID lpParam)
{
  printf(": id = %d", GetCurrentThreadId());
  DWORD idHilo;
  HANDLE manHilo;
  info argumentos;
  for(j = 0; j < 5; j++)
  {
    printf("\n\t\tHe creado %d de 5 hilos",j+1);
    manHilo = CreateThread(NULL, 0, HiloTerminal,&argumentos,0,&idHilo);
    WaitForSingleObject(manHilo, INFINITE);
  }
  CloseHandle(manHilo);
    return 0;
}

DWORD WINAPI HiloTerminal(LPVOID lpParam)
{
  printf(": id = %d", GetCurrentThreadId());
  printf("\n\t\t\tPractica 5, Este es un Hilo terminal %d", GetCurrentThreadId());
  return 0;
}