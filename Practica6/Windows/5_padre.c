#include <windows.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
  STARTUPINFO si;       //Estructura de informacion inicial para windows
  PROCESS_INFORMATION pi;  //Estructura de informacion del admn. de procesos
  int i;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));
  if (argc != 2)
  {
    return;
  }
  //Creacion proceso hijo
  if (!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
  {
    printf("Fallo al invocar CreateProcess (%d)\n",GetLastError() );
    return;
  }
  //Proceso padre
  printf("Soy el padre del proceso hilador\n");
  WaitForSingleObject(pi.hProcess,INFINITE);
  //Terminacion controlada del proceso e hilo asociado de ejecucion
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}
