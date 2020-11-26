#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "./constantes.h"
#include "./lexico.h"
#include "./lista_ts.h"
#include "./lista_polaca.h"
#include "../y.tab.h"

extern int yylineno;
extern FILE *yyin;

t_lista_ts ts;
#endif