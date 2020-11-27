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
_3                                 	dd	3.00
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

FLD b
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
JMP _ET_84
_ET_13:
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
JNE _ET_36
FLD @aux
FLD _45
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_36
FLD _1
FSTP @posicion
FLD _1
FSTP @es_primera_aparicion
_ET_36:
FLD @es_primera_aparicion
FLD _0
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_53
FLD @aux
FLD _120
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_53
FLD _2
FSTP @posicion
FLD _1
FSTP @es_primera_aparicion
_ET_53:
FLD @es_primera_aparicion
FLD _0
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_70
FLD @aux
FLD _2
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_70
FLD _3
FSTP @posicion
FLD _1
FSTP @es_primera_aparicion
_ET_70:
FLD @posicion
FLD _0
FXCH
FCOM
FSTSW AX
SAHF
FFREE
JNE _ET_80
DisplayString _Elemento_no_encontrado
newline 1
JMP _ET_84
_ET_80:
FLD @posicion
FSTP a
_ET_84:

MOV EAX, 4C00H
INT 21h
END START