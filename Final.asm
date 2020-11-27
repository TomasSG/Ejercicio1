include number.asm
include macros2.asm

.MODEL LARGE
.386
.STACK 200h

.DATA
@aux                               	dd	?
@es_primera_aparicion              	dd	?
@posicion                          	dd	?
_0                                 	dd	0.00
_1                                 	dd	1.00
_120                               	dd	120.00
_2                                 	dd	2.00
_45                                	dd	45.00
_El_valor_debe_ser____1            	db	"El valor debe ser >= 1"           , '$', 22 dup (?)
_Elemento_no_encontrado            	db	"Elemento no encontrado"           , '$', 22 dup (?)
_La_lista_esta_vacia               	db	"La lista esta vacia"              , '$', 19 dup (?)
a                                  	dd	?
b                                  	dd	?

.CODE
START:
MOV EAX, @DATA
MOV DS, EAX
MOV ES, EAX


MOV EAX, 4C00H
INT 21h
END START