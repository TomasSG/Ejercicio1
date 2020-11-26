#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./constantes.h"
#include "./lista_ts.h"

void error_lexico(const char*, int);
char* sacar_comillas(const char*);
char* agregar_guion_bajo(const char*);
char* estandarizar_cadena(const char*);

int es_caracter_valido(const char);
int es_numero(const char);
int es_letra_min(const char);
int es_letra_mayus(const char);

void insertar_ts(const char*, const char*, const char*, int, t_lista_ts*);

#endif