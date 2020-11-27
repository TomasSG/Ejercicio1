#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./constantes.h"
#include "./lexico.h"
#include "./lista_ts.h"
#include "./lista_polaca.h"
#include "./pila.h"
#include "./gci.h"
#include "./assembler.h"
#include "../y.tab.h"

extern int yylineno;
extern FILE *yyin;

t_lista_ts ts;
t_lista_polaca polaca;
t_pila pila_exit, pila_return;
int numeracion;
int _contador;
int _nro_celda_aux;
char s_aux[CANTIDAD_ITOA];
#endif