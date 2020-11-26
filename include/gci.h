#ifndef GCI_H
#define GCI_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./constantes.h"
#include "./lista_ts.h"
#include "./lista_polaca.h"

char* obtener_branch(const char*);
void invertir_branch(t_lista_polaca*, int);
char* crear_etiqueta(int);
int insertar_polaca(const char*, int*, t_lista_polaca*);

#endif