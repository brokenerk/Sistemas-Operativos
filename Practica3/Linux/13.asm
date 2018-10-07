segment .data   ;Segmento de datos
    titulo db  'Calculadora basica, introduce los operandos: ', 0xA ;Imprimir cadena
    tamtitulo equ $ - titulo        ;Longitud de cadena a imprimir
    operandoA    db  10,'A: ',0
    tamA equ $ - operandoA
    operandoB    db  'B: ',0
    tamB equ $ - operandoB
    SumLabel     db 10,'1: A + B',10,0
    tamSumLabel equ $ - SumLabel
    RestaLabel   db '2: A - B',10,0   
    tamRestaLabel equ $ - RestaLabel
    MulLabel     db '3: A x B',10,0   
    tamMulLabel equ $ - MulLabel
    DivLabel     db '4: A / B',10,0   
    tamDivLabel equ $ - DivLabel
    OpLabel db 10, 'OP: ',0
    tamOpLabel   equ $ - OpLabel
    ResultLabel   db 10,'Resultado: ',0
    tamResLabel   equ $ - ResultLabel
    NotOpLabel   db 10,'Opcion no valida',10,0
    tamNotOpLabel equ $ - NotOpLabel
    salto      db      10,10,0
    tamsalto     equ     $ - salto
    A dd 0
    B dd 0
    Result dd 0
  
segment .bss                ;Segmento de datos
    op         resb    2    ;Espacio de memoria para las variables a usar
    numA       resb    8
    numB       resb    8
    Resultnum  resb    8
  
segment .text       ;Segmento de codigo
global _start       ;Punto de entrada al programa (usando en el enlazador Id)

_start:

leerNums: ;Leer por medio de teclado operandos
  mostrar: ;Mostrar Labels
    mov EAX, 4
    mov EBX, 1
    mov ECX, titulo
    mov EDX, tamtitulo
    int 0x80

  numeroA: ;Imprimir label operando A desde teclado
    mov EAX, 4
    mov EBX, 1
    mov ECX, operandoA
    mov EDX, tamA
    int 0x80
    ;Leer valor de operando A
    mov EAX, 3 
    mov EBX, 0
    mov ECX, numA
    mov EDX, 8
    int 0x80

  numeroB:  ;Imprimir label operando B desde teclado
    mov EAX, 4
    mov EBX, 1
    mov ECX, operandoB
    mov EDX, tamB
    int 0x80
    ;Leer valor de operando B
    mov EAX, 3
    mov EBX, 0
    mov ECX, numB
    mov EDX, 8
    int 0x80

    mov EBX, 10

    mov ESI, numA   ;Colocamos el numA en esi
    mov EAX, 0      
    call convertir  ;Llamamos a la funcion convertir
    mov [A], EAX    ;A = eax

    mov ESI, numB   ;Colocamos el numB en esi
    mov EAX, 0
    call convertir  ;Llamamos a convertir
    mov [B], EAX    ;B = eax

    jmp getOp       ;Salto a getOp

convertir:              ;De string a entero
    mul EBX
    mov ECX, 0
    mov CL, byte[ESI]   
    sub CL, '0'
    add EAX, ECX        ;Sumamos eax más ecx
    inc ESI             ;Incremento esi
    cmp byte[ESI], 0xA  ;Comparamos
    jne convertir       ;Si es verdadera, repetimos
    ret                 ;retorno

getOp:                      ;Desplegar menu
    mov EAX, 4
    mov EBX, 1
    mov ECX, SumLabel       ;Desplegar opcion de suma
    mov EDX, tamSumLabel
    int 0x80

    mov EAX, 4
    mov EBX, 1
    mov ECX, RestaLabel     ;Desplegar opcion de resta 
    mov EDX, tamRestaLabel
    int 0x80
    
    mov EAX, 4
    mov EBX, 1
    mov ECX, MulLabel       ;Desplegar opcion de multiplicacion
    mov EDX, tamMulLabel
    int 0x80
    
    mov EAX, 4
    mov EBX, 1
    mov ECX, DivLabel       ;Desplegar opcion de division
    mov EDX, tamDivLabel
    int 0x80
    
    mov EAX, 4
    mov EBX, 1
    mov ECX, OpLabel        ;Desplegar entrada de opcion del menu
    mov EDX, tamOpLabel 
    int 0x80
  
  getOperacion:     ;Leer la opcion tecleada del menu  
    mov EAX, 3
    mov EBX, 0
    mov ECX, op
    mov EDX, 2
    int 0x80

seleccionar:        ;Seleccionar la opcion tecleada del menu

    mov AH, [op]
    sub AH, '0'
  
  elegirOperacion:
    cmp AH, 1       ;Opcion 1: Suma
    je Sum
  
    cmp AH, 2       ;Opcion 2: Resta
    je Resta
  
    cmp AH, 3       ;Opcion 3: Multiplicacion
    je Mul
  
    cmp AH, 4       ;Opcion 4: Division
    je Div
  
  MostrarOpInvalida:
    mov EAX, 4
    mov EBX, 1
    mov ECX, NotOpLabel
    mov EDX, tamNotOpLabel
    int 0x80
    jmp salir


Operacion:
    Sum:
        mov EAX, [A]        ;eax = A
        add EAX, [B]        ;Sumar operando A y B
        mov EDI, Resultnum
        mov ECX, 0
        mov EDX, 0
        call intAstr        ;Llamar a int to string
      
    Resta:
        mov EAX, [A]        ;eax = A
        sub EAX, [B]        ;Restar A menos B
        mov EDI, Resultnum
        mov ECX, 0
        mov EDX, 0
        call intAstr
      
    Mul:  
        mov EAX, [A]
        mov EBX, [B]
        mul EBX             ;Multiplicar A por B
        mov EDI, Resultnum
        mov ECX, 0
        mov EDX, 0
        call intAstr
      
    Div:  
        mov EAX, [A]
        mov EBX, [B]
        mov EDX, 0
        div EBX             ;Dividir A entre B
        mov EDI, Resultnum
        mov ECX, 0
        mov EDX, 0
        call intAstr

intAstr:            ;Convertir enteros a cadenas de carateres
    mov EBX, 10
    div EBX
    add EDX, '0'
    push EDX
    inc ECX
    mov EDX, 0
    cmp EAX, 0
    jne intAstr
    je guardar
    ret

guardar:            ;Guardar cifras del resultado de la operacion
    pop EDX
    mov [EDI], EDX  ; edi = edx
    inc EDI
    dec ECX
    cmp ECX, 0
    jne guardar

verResultados:      ;Mostrar resultados en la salida estandar
    mov EAX, 4
    mov EBX, 1
    mov ECX, ResultLabel
    mov EDX, tamResLabel
    int 0x80

    mov EAX, 4
    mov EBX, 1
    mov ECX, Resultnum
    mov EDX, 8
    int 0x80

salir:
    mov EAX, 4
    mov EBX, 1
    mov ECX, salto  
    mov EDX, tamsalto  
    int 0x80 

    mov EAX, 1
    mov EBX, 0
    int 0x80