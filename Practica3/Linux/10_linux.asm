section .data
	msg1 db "Ingresa la cadena 1:",0XA,0XD
	len1 equ $ - msg1
	msg2 db "Ingresa la cadena 2:",0XA,0XD
	len2 equ $ - msg2
	msg3 db "Ingresa la cadena 3:",0XA,0XD
	len3 equ $ - msg3
	msg4 db "La cadena 4 es:",0XA,0XD
	len4 equ $ - msg4

section .bss
	cadena1 resb 20
	lencad1 resb 2
	cadena2 resb 20
	cadena3 resb 20
	cadena4 resb 60

section .text
	global _start

_start:
	mov eax,4			;Prepara las condiciones para imprimir en pantalla 
	mov ebx,1
	mov ecx,msg1
	mov edx,len1
	int 0x80
	
	mov eax,3			;Prepara las condiciones para leer de teclado el valor 1
	mov ebx,0
	mov ecx,cadena1
	mov edx,20
	int 0x80


	mov eax,4			;Prepara las condiciones para imprimir en pantalla 
	mov ebx,1
	mov ecx,msg2
	mov edx,len2
	int 0x80
	
	mov eax,3			;Prepara las condiciones para leer de teclado el valor 2
	mov ebx,0
	mov ecx,cadena2
	mov edx,20
	int 0x80

	mov eax,4			;Prepara las condiciones para imprimir en pantalla 
	mov ebx,1
	mov ecx,msg3
	mov edx,len3
	int 0x80
	
	mov eax,3			;Prepara las condiciones para leer de teclado el valor 3
	mov ebx,0
	mov ecx,cadena3
	mov edx,20
	int 0x80

	;mov ebx,0

	;LEA DI,[cadena1]
	;CLD 		
	;Repetir:
	;LODSB 
	;inc ebx
	;OR AL,AL
	;JNE Repetir
	
	;mov [lencad1],ebx
	mov ecx,20
	mov edx,0
	mov edi,cadena4
	ciclo:
		mov esi,cadena1
		add esi,edx
		mov eax,[esi]
		mov [edi],eax
		INC edi

		mov esi,cadena2
		add esi,edx
		mov eax,[esi]
		mov [edi],eax
		INC edi

		mov esi,cadena3
		add esi,edx
		mov eax,[esi]
		mov [edi],eax
		INC edi
	
		INC edx
		CMP edx,ecx
		JLE ciclo
	
	mov eax,4			;Prepara las condiciones para imprimir en pantalla 
	mov ebx,1
	mov ecx,cadena4
	mov edx,60
	int 0x80

	mov eax,1
	int 0x80
