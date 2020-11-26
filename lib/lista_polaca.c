#include "../include/lista_polaca.h"

void crear_lista_polaca(t_lista_polaca *pl)
{
    *pl=NULL;
}

void vaciar_lista_polaca(t_lista_polaca *pl)
{
    t_nodo_lista_polaca *pnodo;
    while(*pl)
    {
        pnodo=*pl;
        *pl=pnodo->psig;
        free(pnodo);
    }
}

int insertar_ordenado_polaca(t_lista_polaca *pl, const t_dato_lista_polaca *pd,t_cmp_polaca cmp)
{
    t_nodo_lista_polaca *pnodo;
    while(*pl && cmp(pd,&(*pl)->dato)>0)
        pl=&(*pl)->psig;
    if(*pl && cmp(pd,&(*pl)->dato)==0)
        return LISTA_DUPLICADO;
    pnodo=(t_nodo_lista_polaca*)malloc(sizeof(t_nodo_lista_polaca));
    if(!pnodo)
        return LISTA_LLENA;
    pnodo->dato=*pd;
    pnodo->psig=*pl;
    *pl=pnodo;
    return TODO_BIEN;
}

int comparacion_polaca(const t_dato_lista_polaca *pd1, const t_dato_lista_polaca *pd2)
{
    return pd1->nro - pd2->nro;
}

void guardar_lista_en_archivo_polaca(t_lista_polaca *pl, const char *path)
{
	t_dato_lista_polaca *pd;
	FILE *pf = fopen(path, TEXTO_ESCRITURA);
	if(pf == NULL)
	{
		printf("No se pudo abrir el archivo %s\n", path);
		return;
	}

    while(*pl)
    {
        pd =  &(*pl)->dato;
		fprintf(pf,"[%d] %s\n", pd->nro, pd->s);
        pl = &(*pl)->psig;
    }
	fclose(pf);
}

char* buscar_elemento(const t_lista_polaca *pl, int nro_celda, int nro_elemento)
{
	while(*pl)
    {
        if( (*pl)->dato.nro - nro_celda == 0)
		{
			return (*pl)->dato.s;
		}
        pl=&(*pl)->psig;
    }
	return NULL;
}

void cambiar_elemento(const t_lista_polaca *pl, int nro_celda, const char *s)
{
	
	while(*pl)
    {
        if((*pl)->dato.nro - nro_celda == 0)
		{
			free((*pl)->dato.s);
			if(((*pl)->dato.s = strdup(s)) == NULL)
			{
				puts("Problemas de memoria");
				exit(ERROR);
			}
			return;
			
		}
        pl=&(*pl)->psig;
    }
}