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
}

| lista COMA CTE
{
	puts("R9: LISTA -> LISTA coma cte");	
}
;

write: WRITE CTE_S
{
	puts("R10: WRITE -> write cte_s");
}

| WRITE ID
{
	puts("R11: WRITE -> write id");
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
	
	crear_lista_ts(&ts);
	
	yyparse();
	
	fclose(yyin);
	
	guardar_lista_en_archivo_ts(&ts, PATH_ARCHIVO_TS); // Solo para testing
	vaciar_lista_ts(&ts);
	
	return TODO_BIEN;
}

int yyerror(void)
{
	puts("***************************");
	puts("ERROR SINTACTICO");
	printf("Linea %d\n", yylineno);	
	puts("***************************");
}