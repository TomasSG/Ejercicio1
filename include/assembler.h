#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./constantes.h"
#include "./lista_ts.h"
#include "./lista_polaca.h"

void generar_assembler(const char*, const t_lista_polaca*, const t_lista_ts*);


void generar_encabezado(FILE*);
void generar_declaraciones(FILE*, const t_lista_ts*);
void generar_codigo(FILE*, const t_lista_polaca*);
void generar_final(FILE*);


void operacion_aritmetica(FILE*, const char*, const char*, const char*);
void operacion_salida(FILE*, const char*);
void operacion_comparacion(FILE*, const char*);
void operacion_asignacion(FILE*, const char*, const char*);

int es_constante(const char*);
int es_operador_aritmetico(const char*);
int es_etiqueta(const char*);
int es_factor(const char*, const char*);
int es_asignacion(const char*);
int es_salida(const char*);
int es_entrada(const char*);
int es_comparacion(const char*);
int es_salto(const char*);

char* obtener_cmd_salto(const char*);
char* transformar_a_etiqueta(const char*);

#endif //ASSEMBLER_H_INCLUDED