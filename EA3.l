%{

#include "./include/cabecera.h"
	
%}

%option noyywrap
%option yylineno

/* DEFINICIONES BÁSICAS */
DIGITO 									[0-9]
LETRA									[a-zA-Z]

/* PALABRAS RESERVADAS */
WRITE									"WRITE"|"write"
POSICION								"POSICION"|"posicion"
READ									"READ"|"read"

/* ELEMENTOS DE PUNTUACIÓN Y OTROS */
PARA									[(]
PARC									[)]
CA										[[]
CC										[]]
COMA									[,]
PYC										[;]

/* OPERADORES */
ASIGNA									[=]

/* TOKENS CON FAMILIAS DE LEXEMAS */
DELIMITADOR_CTE_S						["]

ID										{LETRA}({LETRA}|{DIGITO})*
CTE										{DIGITO}+
CTE_S									{DELIMITADOR_CTE_S}.*{DELIMITADOR_CTE_S}

%%

{WRITE}									{return WRITE;}
{POSICION}								{return POSICION;}
{READ}									{return READ;}

{PARA}									{return PARA;}
{PARC}									{return PARC;}
{CA}									{return CA;}
{CC}									{return CC;}
{COMA}									{return COMA;}
{PYC}									{return PYC;}

{ASIGNA}								{return ASIGNA;}

{ID}									{
											insertar_ts(yytext, NULL, NULL, SIN_LONGITUD, &ts);
											return ID;
										}
										
{CTE}									{
											insertar_ts(agregar_guion_bajo(yytext), INTEGER, yytext, SIN_LONGITUD, &ts);
											return CTE;
										}

{CTE_S}									{
											char *s_sin_comillas = sacar_comillas(yytext);
											char *s_lexema = estandarizar_cadena(agregar_guion_bajo(s_sin_comillas));
											insertar_ts(s_lexema, STRING, yytext, strlen(s_sin_comillas), &ts);
											return CTE_S;
										}

[ \n\t]
.										{error_lexico("Elemento desconocido", yylineno);}

%%

