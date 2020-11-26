#ifndef LISTA_POLACA_H_INCLUDED
#define LISTA_POLACA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./constantes.h"

typedef struct
{
	char *s;
	int nro;
}t_dato_lista_polaca;

typedef struct s_nodo_lista_polaca
{
    t_dato_lista_polaca dato;
    struct s_nodo_lista_polaca *psig;
}t_nodo_lista_polaca;

typedef t_nodo_lista_polaca* t_lista_polaca;
typedef int(*t_cmp_polaca)(const t_dato_lista_polaca*, const t_dato_lista_polaca*);


int comparacion_polaca(const t_dato_lista_polaca*, const t_dato_lista_polaca*);

void crear_lista_polaca(t_lista_polaca*);
void vaciar_lista_polaca(t_lista_polaca*);
int insertar_ordenado_polaca(t_lista_polaca*, const t_dato_lista_polaca*, t_cmp_polaca);
void guardar_lista_en_archivo_polaca(t_lista_polaca*, const char*);

char* buscar_elemento(const t_lista_polaca*, int, int);
void cambiar_elemento(const t_lista_polaca*, int, const char*);


#endif // LISTA_POLACA_H_INCLUDED