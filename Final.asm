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
_elemento_encontrado_en_posicion__ 	db	"Elemento encontrado en posicion: ", '$', 33 dup (?)
_ingrese_un_valor_pivot_mayor_o_igual_a_1__	db	"Ingrese un valor pivot mayor o igual a 1: ", '$', 42 dup (?)
pivot                              	dd	?
resul                              	dd	?

.CODE
START:
MOV EAX, @DATA
MOV DS, EAX
MOV ES, EAX

DisplayString _ingrese_un_valor_pivot_mayor_o_igual_a_1__
newline 1
GetFloat pivot
FLD pivot
FSTP @aux
FLD @aux
FLD _1
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNB _ET_17
DisplayString _El_valor_debe_ser____1
newline 1
JMP _ET_126
_ET_17:
FLD _0
FSTP @posicion
FLD _0
FSTP @es_primera_aparicion
FLD @es_primera_aparicion
FLD _0
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_40
FLD @aux
FLD _1
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_40
FLD _1
FSTP @posicion
FLD _1
FSTP @es_primera_aparicion
_ET_40:
FLD @es_primera_aparicion
FLD _0
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_57
FLD @aux
FLD _584
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_57
FLD _2
FSTP @posicion
FLD _1
FSTP @es_primera_aparicion
_ET_57:
FLD @es_primera_aparicion
FLD _0
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_74
FLD @aux
FLD _6
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_74
FLD _3
FSTP @posicion
FLD _1
FSTP @es_primera_aparicion
_ET_74:
FLD @es_primera_aparicion
FLD _0
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_91
FLD @aux
FLD _9
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_91
FLD _4
FSTP @posicion
FLD _1
FSTP @es_primera_aparicion
_ET_91:
FLD @es_primera_aparicion
FLD _0
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_108
FLD @aux
FLD _6
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_108
FLD _5
FSTP @posicion
FLD _1
FSTP @es_primera_aparicion
_ET_108:
FLD @posicion
FLD _0
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_118
DisplayString _Elemento_no_encontrado
newline 1
JMP _ET_126
_ET_118:
FLD @posicion
FSTP resul
DisplayString _elemento_encontrado_en_posicion__
newline 1
DisplayFloat resul, 2
newline 1
_ET_126:

MOV EAX, 4C00H
INT 21h
END START