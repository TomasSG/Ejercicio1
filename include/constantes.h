#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/* ARCHIVOS */
#define TEXTO_LECTURA "rt"
#define TEXTO_ESCRITURA "wt"

#define PATH_ARCHIVO_INTERMEDIO "./Intermedia.txt"
#define PATH_ARCHIVO_ASSEMBLER "./Final.asm"
#define PATH_ARCHIVO_TS "./ts.txt" //Solo para testing

/* RETORNO GENERAL */
#define ERROR 1
#define TODO_BIEN 0

/* LISTA */
#define LISTA_LLENA -1
#define LISTA_DUPLICADO -2

/* GENERAL */
#define CANTIDAD_ITOA 500

/* TIPOS DE DATOS */
#define INTEGER "int"
#define STRING "String"

/* LEXICO */ 
#define CANTIDAD_GUIONES_BAJOS 1
#define CANTIDAD_COMILLAS 2 
#define SIN_LONGITUD 0

#define ASCII_0 48
#define ASCII_9 57
#define ASCII_A 65
#define ASCII_Z 90
#define ASCII_a 97
#define ASCII_z 122


#define MARCADOR_CONSTANTE "_"
#define CARACTER_COMILLA '\"'
#define CARACTER_ESTANDARIZAR '_'

/* POLACA */
#define OP_ASIGNACION "="

#define ELEMENTO_VACIO " "

#define INPUT "READ"
#define OUTPUT "WRITE"

#define ETIQUETA "_ET_"

#define OPERADOR_LE "<"
#define OPERADOR_LEQ "<="
#define OPERADOR_GE	">"
#define OPERADOR_GEQ ">="
#define OPERADOR_NE	"<>"
#define OPERADOR_IGUAL "=="

#define CMP "CMP"

#define BI "BI"
#define BLT "BLT"
#define BLE "BLE"
#define BGT "BGT"
#define BGE "BGE"
#define BEQ "BEQ"
#define BNE "BNE"

#define CANTIDAD_DIGITOS_NUMERO 5


#define VAR_AUX "@aux"
#define VAR_POS "@posicion"
#define VAR_ES_PRI "@es_primera_aparicion"

#define INI_VAR_POS_VALOR "0"
#define INI_VAR_ES_PRI_VALOR "0"
#define FIN_VAR_ES_PRI_VALOR "1"
#define VALOR_CRITICO_PIVOT_VALOR "1"

#define INI_VAR_POS_LEXEMA "_0"
#define INI_VAR_ES_PRI_LEXEMA "_0"
#define FIN_VAR_ES_PRI_LEXEMA "_1"
#define VALOR_CRITICO_PIVOT_LEXEMA "_1"

#define MSJ_ERROR_PIVOT_VALOR "\"El valor debe ser >= 1\""
#define MSJ_ERROR_LISTA_VACIA_VALOR "\"La lista esta vacia\""
#define MSJ_ERROR_NO_ENCONTRADO_VALOR "\"Elemento no encontrado\""

#define MSJ_ERROR_PIVOT_LEXEMA "El_valor_debe_ser____1"
#define MSJ_ERROR_LISTA_VACIA_LEXEMA "La_lista_esta_vacia"
#define MSJ_ERROR_NO_ENCONTRADO_LEXEMA "Elemento_no_encontrado"

#endif