%{
#include "./include/cabecera.h"
%}

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
%token ID								
%token CTE								
%token CTE_S	

%start s

%%

s: prog 
{
	puts("S -> PROG");
	puts("COMPILACION EXITOSA");
}
;

prog: sent
{
	puts("PROG -> SENT");
}

| prog sent
{
	puts("PROG -> PROG SENT");
}
;

sent: read		{puts("SENT -> READ");}
| write			{puts("SENT -> WRITE");}
| asig			{puts("SENT -> ASIG");}
;

read: READ ID
{
	puts("READ -> read id");
}
;

asig: ID ASIGNA posicion
{
	puts("ASIG -> id asigna POSICION");
}
;

posicion: POSICION PARA ID PYC CA lista CC PARC
{
	puts("POSICION -> posicion para id pyc ca LISTA cc parc");
}

| POSICION PARA ID PYC CA CC PARC
{
	puts("POSICION -> posicion para id pyc ca cc parc");
}
;

lista: CTE
{
	puts("LISTA -> cte");
}

| lista COMA CTE
{
	puts("LISTA -> LISTA coma cte");	
}
;

write: WRITE CTE_S
{
	puts("WRITE -> write cte_s");
}

| WRITE ID
{
	puts("WRITE -> write id");
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