#ifndef GCI_H
#define GCI_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./constantes.h"
#include "./lista_ts.h"
#include "./lista_polaca.h"
#include "./lexico.h"

char* obtener_branch(const char*);
void invertir_branch(t_lista_polaca*, int);
char* crear_etiqueta(int);
char* agregar_fin_etiqueta(const char*);
int insertar_polaca(const char*, int*, t_lista_polaca*);

// Operaciones
void operacion_output(const char*, int*, t_lista_polaca*);
void operacion_asignacion(const char*, const char*, int*, t_lista_polaca*);
void operacion_exit(int*, t_lista_polaca*);
void algoritmo_busqueda_aparicion(const char*, int*, int*, t_lista_polaca*);

#endif