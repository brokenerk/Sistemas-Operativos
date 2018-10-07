section .data 								;Segmento de datos
	msg1 db "Ingresa la cadena 1:",0XA,0XD	;Imprimir cadena
	len1 equ $ - msg1 						;Longitud de cadena a imprimir
	msg2 db "Ingresa la cadena 2:",0XA,0XD
	len2 equ $ - msg2
	msg3 db "Ingresa la cadena 3:",0XA,0XD
	len3 equ $ - msg3
	msg4 db "Ingresa la cadena 4:",0XA,0XD
	len4 equ $ - msg4
	msg5 db "Ingresa la cadena 5:",0XA,0XD
	len5 equ $ - msg5
	msg6 db "Ingresa la cadena 6:",0XA,0XD
	len6 equ $ - msg6
	msg7 db "Ingresa la cadena 7:",0XA,0XD
	len7 equ $ - msg7
	msg8 db "Ingresa la cadena 8:",0XA,0XD
	len8 equ $ - msg8
	msg9 db "Ingresa la cadena 9:",0XA,0XD
	len9 equ $ - msg9
	msg10 db "Ingresa la cadena 10:",0XA,0XD
	len10 equ $ - msg10
	msg11 db 0XD,"La cadena generada es:",0XA,0XD
	len11 equ $ - msg11
	msg12 db 0XA,0XD,"La longitud de la cadena:",0XA,0XD
	len12 equ $ - msg12
	msg13 db 0XA,0XD,"La cadena invertida:",0XA,0XD
	len13 equ $ - msg13
	salto db 0xA,0xD                        ;Salto de linea a imprimir
    len equ $ - salto                       ;Longitud de salto

section .bss				;Segmento de datos
	cadena1 resb 90			;Espacio de memoria para la cadena almacenar
	cadena2 resb 90
	cadena3 resb 90
	cadena4 resb 90
	cadena5 resb 90
	cadena6 resb 90
	cadena7 resb 90
	cadena8 resb 90
	cadena9 resb 90
	cadena10 resb 90
	cadenafinal resb 900
	cadenainv resb 900
	contador resb 1
	auxiliar resb 3

section .text
global _start

_start:				;Vamos llamando a las funciones que se ejecutaran
	call leer_datos
	call concatenar
	call longitud
	call imprimir
	mov ecx,899 	;Nos sirve como contador para invertir la cadena
	mov edx,0 		;Este seria el limite del ciclo
	mov edi,cadenainv ;Enviamos la cadenainv a edi
	call invertir

	mov eax,1		;Numero de llamada al sistema "sys_exit"
	int 0x80		;Interrupcion de llamadas al sistema del kernel de Linux

concatenar:
	;ya use ecx, edx,
	mov ecx, 0			;Contador
	mov edx, 90 		;Longitud de la cadena
	mov edi,cadenafinal ;Colocamos la cadena concatenada a edi
	mov esi,cadena1 	;Colocamos la cadena1 a esi
	
repetir: 	
;Vamos ir colocando cadena por cadena en esi, recorriendo sus caracteres para que se concatenen consecutivamente		
	mov eax,[esi] 		;eax = esi
	mov [edi],eax		;edi = eax
	inc edi				;Incrementa edi
	inc esi 			;Incrementa esi		
	CMP eax,0XA			;eax es el valor de mi contador, comparamos llegamos al final de la cadena
	JE fin_ciclo 		;si ya llegamos, vamos a fin_ciclo
	CMP ecx,edx			;Comparamos ecx y edx
	JLE repetir 		;si aun no hemos llegado, incrementamos y repetimos

fin_ciclo:
	dec edi				;Decremente edi
	mov esi,cadena2 	;Coloca cadena2 en esi

repetir2:
	mov eax,[esi]
	mov [edi],eax
	inc edi
	inc esi
	CMP eax,0XA
	JE fin_ciclo2
	CMP ecx,edx
	JLE repetir2

fin_ciclo2:
	dec edi
	mov ecx,0
	mov esi,cadena3		;Coloca cadena3 en esi

repetir3:
	mov eax,[esi]
	mov [edi],eax
	inc edi
	inc esi
	CMP eax,0XA
	JE fin_ciclo3
	CMP ecx,edx
	JLE repetir3

fin_ciclo3:
	dec edi
	mov ecx,0
	mov esi,cadena4 	;Coloca cadena4 en esi

repetir4:
	mov eax,[esi]
	mov [edi],eax
	inc edi
	inc esi
	CMP eax,0XA
	JE fin_ciclo4
	CMP ecx,edx
	JLE repetir4

fin_ciclo4:
	dec edi
	mov ecx,0
	mov esi,cadena5 	;Coloca cadena5 en esi

repetir5:
	mov eax,[esi]
	mov [edi],eax
	inc edi
	inc esi
	CMP eax,0XA
	JE fin_ciclo5
	CMP ecx,edx
	JLE repetir5

fin_ciclo5:
	dec edi
	mov ecx,0
	mov esi,cadena6 	;Coloca cadena6 en esi

repetir6:
	mov eax,[esi]
	mov [edi],eax
	inc edi
	inc esi
	CMP eax,0XA
	JE fin_ciclo6
	CMP ecx,edx
	JLE repetir6

fin_ciclo6:
	dec edi
	mov ecx,0
	mov esi,cadena7 	;Coloca cadena7 en esi

repetir7:
	mov eax,[esi]
	mov [edi],eax
	inc edi
	inc esi
	CMP eax,0XA
	JE fin_ciclo7
	CMP ecx,edx
	JLE repetir7

fin_ciclo7:
	dec edi
	mov ecx,0
	mov esi,cadena8 	;Coloca cadena8 en esi

repetir8:
	mov eax,[esi]
	mov [edi],eax
	inc edi
	inc esi
	CMP eax,0XA
	JE fin_ciclo8
	CMP ecx,edx
	JLE repetir8

fin_ciclo8:
	dec edi
	mov ecx,0
	mov esi,cadena9 	;Coloca cadena9 en esi

repetir9:
	mov eax,[esi]
	mov [edi],eax
	inc edi
	inc esi
	CMP eax,0XA
	JE fin_ciclo9
	CMP ecx,edx
	JLE repetir9

fin_ciclo9:
	dec edi
	mov ecx,0
	mov esi,cadena10 	;Coloca cadena10 en esi

repetir10:
	mov eax,[esi]
	mov [edi],eax
	inc edi
	inc esi
	CMP eax,0XA
	JE fin_ciclo10
	CMP ecx,edx
	JLE repetir10

fin_ciclo10:
	dec edi
	ret ;Retornamos

leer_datos:
	mov eax,4 		;Imprimir en pantalla msg1
	mov ebx,1		;Salida estandar
	mov ecx,msg1 	;Msg1 a imprimir
	mov edx,len1 	;Longitud de msg1
	int 0x80
	mov eax,3 		;Leer de teclado cadena1
	mov ebx,0		;Entrada estandar
	mov ecx,cadena1 ;Cadena1 a leer
	mov edx,90		;Longitud de cadena1
	int 0x80

	mov eax,4 ;Imprimir en pantalla msg2
	mov ebx,1
	mov ecx,msg2
	mov edx,len2
	int 0x80
	mov eax,3 ;Leer de teclado cadena2
	mov ebx,0
	mov ecx,cadena2
	mov edx,90
	int 0x80

	mov eax,4 ;Imprimir en pantalla msg3
	mov ebx,1
	mov ecx,msg3
	mov edx,len3
	int 0x80
	mov eax,3 ;Leer de teclado cadena3
	mov ebx,0
	mov ecx,cadena3
	mov edx,90
	int 0x80

	mov eax,4 ;Imprimir en pantalla msg4
	mov ebx,1
	mov ecx,msg4
	mov edx,len4
	int 0x80
	mov eax,3 ;Leer de teclado cadena4
	mov ebx,0
	mov ecx,cadena4
	mov edx,90
	int 0x80

	mov eax,4 ;Imprimir en pantalla msg5
	mov ebx,1
	mov ecx,msg5
	mov edx,len5
	int 0x80
	mov eax,3 ;Leer de teclado cadena5
	mov ebx,0
	mov ecx,cadena5
	mov edx,90
	int 0x80

	mov eax,4 ;Imprimir en pantalla msg6
	mov ebx,1
	mov ecx,msg6
	mov edx,len6
	int 0x80
	mov eax,3 ;Leer de teclado cadena6
	mov ebx,0
	mov ecx,cadena6
	mov edx,90
	int 0x80

	mov eax,4 ;Imprimir en pantalla msg7
	mov ebx,1
	mov ecx,msg7
	mov edx,len7
	int 0x80
	mov eax,3 ;Leer de teclado cadena7
	mov ebx,0
	mov ecx,cadena7
	mov edx,90
	int 0x80

	mov eax,4 ;Imprimir en pantalla msg8
	mov ebx,1
	mov ecx,msg8
	mov edx,len8
	int 0x80
	mov eax,3 ;Leer de teclado cadena8
	mov ebx,0
	mov ecx,cadena8
	mov edx,90
	int 0x80

	mov eax,4 ;Imprimir en pantalla msg9
	mov ebx,1
	mov ecx,msg9
	mov edx,len9
	int 0x80
	mov eax,3 ;Leer de teclado cadena9
	mov ebx,0
	mov ecx,cadena9
	mov edx,90
	int 0x80

	mov eax,4 ;Imprimir en pantalla msg10
	mov ebx,1
	mov ecx,msg10
	mov edx,len10
	int 0x80
	mov eax,3 ;Leer de teclado cadena10
	mov ebx,0
	mov ecx,cadena10
	mov edx,90
	int 0x80
	ret 	;Retornamos

longitud:
	mov ecx,900 		;Longitud maxima de la cadena
	mov eax,0			;Contador para recorrer la cadena	
	mov esi,cadenafinal	;Colocamos cadena concatenada en esi

cic: 					;Ciclo para recorrer el arreglo
	mov ebx,[esi] 		; ebx = esi
	CMP ebx,0XA 		;Comparamos si ebx alcanco el final de la cadena
	JE fin_cic 			;Si sí son iguales, terminamos
	INC eax 			;Incrementamos eax 
	INC esi 			;Incrementamos esi, para guardar el caracter
	mov [contador],eax 	;contador=eax
	CMP eax,ecx 		;Comparamos eax con ecx
	JLE cic 			;Si son distintos, repetimos

fin_cic:
	mov eax,[contador]
	mov esi,auxiliar
	mov bl,10
	div bl
	add al,'0'
	add ah,'0'
	mov [esi],al
	inc esi
	mov [esi],ah
	ret

imprimir:
	mov eax,4 ;Imprimir en pantalla msg11
	mov ebx,1
	mov ecx,msg11
	mov edx,len11
	int 0x80
	mov eax,4 ;Imprimir en pantalla cadena concatenada
	mov ebx,1
	mov ecx,cadenafinal
	mov edx,900
	int 0x80
	mov eax,4 ;Imprimir en pantalla msg12
	mov ebx,1
	mov ecx,msg12
	mov edx,len12
	int 0x80
	mov eax,4 ;Imprimir en pantalla auxiliar
	mov ebx,1
	mov ecx,auxiliar
	mov edx,2
	int 0x80
	mov eax,4 ;Imprimir en pantalla msg13
	mov ebx,1
	mov ecx,msg13
	mov edx,len13
	int 0x80
	ret

convertir: 				;Convertir a ASCII para la salida estandar
	mov eax,[contador]
	mov esi,auxiliar
	mov bl,10
	div bl
	add al,'0'
	add ah,'0'
	mov [esi],al
	inc esi
	mov [esi],ah
	ret

invertir: 					;ecx inicia en el ultimo caracter
	mov esi, cadenafinal 	;Enviamos cadenafinal a esi
	add esi, ecx 			;Sumamos aritmeticamente ecx a esi
	mov eax,[esi] 			;eax = esi
	mov [edi],eax 			;edi = eax (Copiamos caracter por caracter)
	INC edi 				;Recorremos la posicion en edi (cadenainv)
	DEC ecx 				;Restamos nuestro contador
	CMP edx,ecx			;Comparamos ecx y edx
	JLE invertir 		;Si aun no hemos llegado al primer caracter, repetimos
	
	mov eax,4 			;Imprimir en pantalla cadena invertida
	mov ebx,1
	mov ecx,cadenainv
	mov edx,900
	int 0x80
	mov eax,4           ;Numero de llamada al sistema "sys_write"
    mov ebx,1           ;Salida estandar
    mov ecx,salto       ;Salto a escribir
    mov edx,len         ;Longitud del salto
    int 0x80            ;Interrupcion de llamadas al sistema del kernel de Linux
	ret
