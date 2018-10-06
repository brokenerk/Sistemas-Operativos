segment .data                   ;Segmento de datos
	texto1 db 'cadena: ',0xA    ;Cadena de entrada a imprimir
	lon1 equ $-texto1           ;Longitud texto1
	texto2 db 'longitud: ',0xA  ;Cadena que imprimira el valor de la longitudn de la cadena
	lon2 equ $-texto2           ;Longitud texto2

segment .bss                    ;Segmento de datos
	cadena resb 100             ;Espacio de memoria para la cadena almacenar
	long1 resb 8                ;Espacio de memoria para las longitudes
	long2 resb 8   

segment .text                   ;Segmento de codigo  
global _start                   ;Punto de entrada al programa (usando en el enlazador Id)

_start:                         ;Inicio del programa
	mov byte [long1],0x30       ;Asignamos 48 (0x30 en hex) a long1   
	mov byte [long2],0x30       ;Asignamos 48 (0x30 en hex) a long2
	mov eax,4                   ;Imprimir en pantalla
    mov ebx,1                   ;Salida estandar
    mov ecx,texto1              ;Texto1 a escribir 
    mov edx,lon1                ;Longitud de texto1
    int 0x80                    ;Interrupcion de llamadas al sistema del kernel de Linux
    mov eax,3                   ;Numero de llamada al sistema "sys_read"
    mov ebx,0                   ;Entrada estandar
    mov ecx,cadena              ;Cadena1 a ingresar por teclado
    mov edx,100d                ;Longitud de cadena ingresada
    int 0x80   
    mov esi, cadena             ;Colocar cadena en esi
    mov edi, cadena             ;Colocar cadena en edi

cuenta:                         ;Contar caracteres de cadena
    mov al,[esi]                ;al = esi
    inc esi                     ;Incrementar esi
    mov [edi],al                ;edi = al
    inc edi                     ;Incrementar edi
    cmp byte [long1],0x39       ;Comparamos long1 en forma de byte con 0x39 (57)
    jne sumarA                  ;Si son iguales, vamos a la funcion sumarA
    mov byte [long1],0x30       ;Asignamos 48 (0x30 en hex) a long1  
    cmp byte [long2],0x39        ;Comparamos long2 en forma de byte con 0x39 (57)
    jne sumarB                  
    mov byte [long2],0x30   
    jmp fuera                   ;Destino a fuera

sumarB:   
    add byte [long2],1d         ;Sumamos 1 a long2
    jmp fuera                   ;Destino a fuera

sumarA:   
    add byte [long1],1d         ;Sumamos 1 a long1

fuera:   
    cmp al,0                    ;Comparamos al con 0
    jne cuenta                  ;Si son iguales, vamos a la funcion cuenta
    int 0x80                    ;Interrupcion de llamadas al sistema del kernel de Linux
    mov eax,4                   ;Imprimir en pantalla
	mov ebx,1                   ;Salida estandar
	mov ecx,texto2              ;Texto2 a imprimir
    mov edx,lon2                ;Longitud de texto2
    int 0x80   
    sub byte[long1],2d          ;Restar 2 a long1
    cmp byte[long1],'.'         ;Verificamos que no haya puntos en la cadena
    jne noHacer                 ;Si los hay, vamos a noHacer
    mov byte[long1],'8'   
    mov byte[long2],1d  

noHacer:   
    cmp byte[long1],'/'         ;Revisamos si hay diagonales en la cadena
    jne noHagoNada   
    mov byte[long1],'9'   
    sub byte[long2],1d      

noHagoNada:   
    cmp byte[long2],0x30        
    je imprimoA   
    mov eax,4   
    mov ebx,1   
    mov ecx,long2   
    mov edx,8d   
    int 0x80   

imprimoA:                   ;Imprimimos la longitud de la cadena
    mov eax,4   
    mov ebx,1   
    mov ecx,long1   
    mov edx,8d   
    mov byte[ecx+1],0xA   
    int 0x80   
	mov eax,1   
    int 0x80	 
