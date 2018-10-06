section .data								;Segmento de datos
	msg1 db "Ingresa la cadena 1:",0XA,0XD	;Imprimir cadena
	len1 equ $ - msg1						;Longitud de cadena a imprimir
	msg2 db "Ingresa la cadena 2:",0XA,0XD
	len2 equ $ - msg2
	msg3 db "Ingresa la cadena 3:",0XA,0XD
	len3 equ $ - msg3
	msg4 db "La cadena 4 es:",0XA,0XD
	len4 equ $ - msg4

section .bss			;Segmento de datos
	cadena1 resb 20		;Espacio de memoria para la cadena almacenar
	lencad1 resb 2		;Espacio de memoria para la longitud de cadena
	cadena2 resb 20
	cadena3 resb 20
	cadena4 resb 60

section .text		;Segmento de codigo
global _start		;Punto de entrada al programa (usando en el enlazador Id)

_start:				;Inicio del programa
	mov eax,4 		;Imprimir en pantalla
	mov ebx,1		;Salida estandar
	mov ecx,msg1	;Msg1 a escribir
	mov edx,len1 	;Longitud de msg1
	int 0x80		;Interrupcion de llamadas al sistema del kernel de Linux
	mov eax,3 		;Leer de teclado la cadena 1
	mov ebx,0		;Entrada estandar
	mov ecx,cadena1	;Cadena1 a escribir
	mov edx,20		;Longitud de la cadena a escribir
	int 0x80
	mov eax,4 		;Imprimir en pantalla
	mov ebx,1
	mov ecx,msg2
	mov edx,len2
	int 0x80
	mov eax,3 		;Leer de teclado el valor 2
	mov ebx,0
	mov ecx,cadena2
	mov edx,20
	int 0x80
	mov eax,4 		;Imprimir en pantalla
	mov ebx,1
	mov ecx,msg3
	mov edx,len3
	int 0x80
	mov eax,3 		;Leer de teclado el valor 3
	mov ebx,0
	mov ecx,cadena3
	mov edx,20
	int 0x80
	mov ecx,20
	mov edx,0
	mov edi,cadena4

ciclo:					;Ciclo para recorrer las cadenas
	mov esi,cadena1 	;Recorrer caracteres cadena1
	add esi,edx			;Sumamos aritmeticamente edx a esi
	mov eax,[esi]		;eax = esi
	mov [edi],eax		;edi = eax Concatenamos
	INC edi				;Incrementa edi

	mov esi,cadena2		;Recorrer caracteres cadena2
	add esi,edx
	mov eax,[esi]
	mov [edi],eax
	INC edi

	mov esi,cadena3		;Recorrer caracteres cadena2
	add esi,edx
	mov eax,[esi]
	mov [edi],eax
	INC edi

	INC edx				;Incrementamos edx
	CMP edx,ecx			;edx es el valor de mi contador, comparamos si ya llegamos al final de la cadena
	JLE ciclo 			;si aun no hemos llegado, repetimos 

	mov eax,4 			;Imprimir en pantalla
	mov ebx,1			;Salida estandar
	mov ecx,cadena4		;Cadena 4 a imprimir
	mov edx,60			;Longitud de cadena4
	int 0x80			;Interrupcion de llamadas al sistema del kernel de Linux
	mov eax,1			;Numero de llamada al sistema "sys_exit"
	int 0x80