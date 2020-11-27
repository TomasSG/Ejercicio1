include number.asm
include macros2.asm

.MODEL LARGE
.386
.STACK 200h

.DATA
@aux                               	dd	?
@posicion                          	dd	?
_0                                 	dd	0.00
_1                                 	dd	1.00
_2                                 	dd	2.00
_3                                 	dd	3.00
_4                                 	dd	4.00
_5                                 	dd	5.00
_584                               	dd	584.00
_6                                 	dd	6.00
_9                                 	dd	9.00
_El_valor_debe_ser____1            	db	"El valor debe ser >= 1"           , '$', 22 dup (?)
_Elemento_no_encontrado            	db	"Elemento no encontrado"           , '$', 22 dup (?)
_La_lista_esta_vacia               	db	"La lista esta vacia"              , '$', 19 dup (?)
pivot                              	dd	?
resul                              	dd	?

.CODE
START:
MOV EAX, @DATA
MOV DS, EAX
MOV ES, EAX

FLD pivot
FSTP @aux
FLD @aux
FLD _1
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNB _ET_13
DisplayString _El_valor_debe_ser____1
newline 1
JMP _ET_80
_ET_13:
FLD _0
FSTP @posicion
FLD @aux
FLD _1
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_27
FLD _1
FSTP @posicion
JMP _ET_76
_ET_27:
FLD @aux
FLD _584
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_38
FLD _2
FSTP @posicion
JMP _ET_76
_ET_38:
FLD @aux
FLD _6
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_49
FLD _3
FSTP @posicion
JMP _ET_76
_ET_49:
FLD @aux
FLD _9
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_60
FLD _4
FSTP @posicion
JMP _ET_76
_ET_60:
FLD @aux
FLD _6
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_71
FLD _5
FSTP @posicion
JMP _ET_76
_ET_71:
DisplayString _Elemento_no_encontrado
newline 1
JMP _ET_80
_ET_76:
FLD @posicion
FSTP resul
_ET_80:

MOV EAX, 4C00H
INT 21h
END START