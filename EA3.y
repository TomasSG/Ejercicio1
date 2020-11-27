%{
#include "./include/cabecera.h"
%}

%union
{
	char *string;
}

/* PALABRAS RESERVADAS */
%token WRITE									
%token POSICION								
%token READ								

/* ELEMENTOS DE PUNTUACIÓN Y OTROS */
%token PARA								
%token PARC								
%token CA								
%token CC								
%token COMA								
%token PYC								

/* OPERADORES */
%token ASIGNA							

/* TOKENS CON FAMILIAS DE LEXEMAS */
%token <string> ID								
%token <string> CTE								
%token <string> CTE_S	

%start s

%%

s: prog 
{
	puts("R0: S -> PROG");
	puts("COMPILACION EXITOSA");
}
;

prog: sent
{
	puts("R1: PROG -> SENT");
}

| prog sent
{
	puts("R2: PROG -> PROG SENT");
}
;

sent: read		{puts("R3: SENT -> READ");}
| write			{puts("R3: SENT -> WRITE");}
| asig			{puts("R3: SENT -> ASIG");}
;

read: READ ID
{
	puts("R4: READ -> read id");
	
	insertar_polaca($2, &numeracion, &polaca);
	insertar_polaca(INPUT, &numeracion, &polaca);
}
;

asig: ID ASIGNA posicion
{
	puts("R5: ASIG -> id asigna POSICION");
}
;

posicion: POSICION PARA ID PYC CA lista CC PARC
{
	puts("R6: POSICION -> posicion para id pyc ca LISTA cc parc");
}

| POSICION PARA ID PYC CA CC PARC
{
	puts("R7: POSICION -> posicion para id pyc ca cc parc");
}
;

lista: CTE
{
	puts("R8: LISTA -> cte");
	char aux[CANTIDAD_ITOA];
	
	insertar_polaca(VAR_AUX, &numeracion, &polaca);
	insertar_polaca(ELEMENTO_VACIO, &numeracion, &polaca);
	_nro_celda_aux = numeracion;
	insertar_polaca(OP_ASIGNACION, &numeracion, &polaca);
	
	insertar_polaca(VAR_AUX, &numeracion, &polaca);
	insertar_polaca(VALOR_CRITICO_PIVOT, &numeracion, &polaca);
	insertar_polaca(CMP, &numeracion, &polaca);
	insertar_polaca(BGE, &numeracion, &polaca);
	insertar_polaca(crear_etiqueta(numeracion + 5), &numeracion, &polaca);
	insertar_polaca(MSJ_ERROR_PIVOT, &numeracion, &polaca);
	insertar_polaca(OUTPUT, &numeracion, &polaca);
	insertar_polaca(BI, &numeracion, &polaca);
	insertar_polaca(ELEMENTO_VACIO, &numeracion, &polaca);
	//Falta apilar
	
	insertar_polaca(VAR_POS, &numeracion, &polaca);
	insertar_polaca(INI_VAR_POS, &numeracion, &polaca);
	insertar_polaca(OP_ASIGNACION, &numeracion, &polaca);
	_contador = 0;
	insertar_polaca(VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(INI_VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(OP_ASIGNACION, &numeracion, &polaca);
	
	_contador++;
	insertar_polaca(VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(INI_VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(CMP, &numeracion, &polaca);
	insertar_polaca(BNE, &numeracion, &polaca);
	insertar_polaca(crear_etiqueta(numeracion + 12), &numeracion, &polaca);
	insertar_polaca(VAR_AUX, &numeracion, &polaca);
	insertar_polaca($1, &numeracion, &polaca);
	insertar_polaca(CMP, &numeracion, &polaca);
	insertar_polaca(BNE, &numeracion, &polaca);
	insertar_polaca(crear_etiqueta(numeracion + 7), &numeracion, &polaca);
	insertar_polaca(VAR_POS, &numeracion, &polaca);
	
	itoa(_contador, aux, 10);
	insertar_polaca(aux, &numeracion, &polaca);
	insertar_polaca(OP_ASIGNACION, &numeracion, &polaca);
	insertar_polaca(VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(FIN_VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(OP_ASIGNACION, &numeracion, &polaca);
}

| lista COMA CTE
{
	puts("R9: LISTA -> LISTA coma cte");
	char aux[CANTIDAD_ITOA];	
	
	_contador++;
	insertar_polaca(VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(INI_VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(CMP, &numeracion, &polaca);
	insertar_polaca(BNE, &numeracion, &polaca);
	insertar_polaca(crear_etiqueta(numeracion + 12), &numeracion, &polaca);
	insertar_polaca(VAR_AUX, &numeracion, &polaca);
	insertar_polaca($3, &numeracion, &polaca);
	insertar_polaca(CMP, &numeracion, &polaca);
	insertar_polaca(BNE, &numeracion, &polaca);
	insertar_polaca(crear_etiqueta(numeracion + 7), &numeracion, &polaca);
	insertar_polaca(VAR_POS, &numeracion, &polaca);
	
	itoa(_contador, aux, 10);
	insertar_polaca(aux, &numeracion, &polaca);
	insertar_polaca(OP_ASIGNACION, &numeracion, &polaca);
	insertar_polaca(VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(FIN_VAR_ES_PRI, &numeracion, &polaca);
	insertar_polaca(OP_ASIGNACION, &numeracion, &polaca);
}
;

write: WRITE CTE_S
{
	puts("R10: WRITE -> write cte_s");
	
	insertar_polaca($2, &numeracion, &polaca);
	insertar_polaca(OUTPUT, &numeracion, &polaca);
}

| WRITE ID
{
	puts("R11: WRITE -> write id");
	
	insertar_polaca($2, &numeracion, &polaca);
	insertar_polaca(OUTPUT, &numeracion, &polaca);
}
;

%%

int main(int argc, char **argv)
{
	yyin = fopen(argv[1], TEXTO_LECTURA);
	if(yyin == NULL)
	{
		printf("No se pudo abrir el archivo en %s", argv[1]);
		return ERROR;
	}
	
	// Inicialización de estructuras y variables
	crear_lista_ts(&ts);
	
	crear_lista_polaca(&polaca);
	numeracion = 0;
	
	yyparse();
	
	
	
	// Cierre de estructuras y variables
	guardar_lista_en_archivo_polaca(&polaca, PATH_ARCHIVO_INTERMEDIO);
	vaciar_lista_polaca(&polaca);
	
	guardar_lista_en_archivo_ts(&ts, PATH_ARCHIVO_TS); // Solo para testing
	vaciar_lista_ts(&ts);
	
	fclose(yyin);
	
	return TODO_BIEN;
}

int yyerror(void)
{
	puts("***************************");
	puts("ERROR SINTACTICO");
	printf("Linea %d\n", yylineno);	
	puts("***************************");
}