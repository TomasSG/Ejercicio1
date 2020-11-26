#include "../include/lista_tercetos.h"

void crear_lista_tercetos(t_lista_tercetos *pl)
{
    *pl=NULL;
}

void vaciar_lista_tercetos(t_lista_tercetos *pl)
{
    t_nodo_lista_tercetos *pnodo;
    while(*pl)
    {
        pnodo=*pl;
        *pl=pnodo->psig;
        free(pnodo);
    }
}

int insertar_ordenado_tercetos(t_lista_tercetos *pl, const t_dato_lista_tercetos *pd,t_cmp_tercetos cmp)
{
    t_nodo_lista_tercetos *pnodo;
    while(*pl && cmp(pd,&(*pl)->dato)>0)
        pl=&(*pl)->psig;
    if(*pl && cmp(pd,&(*pl)->dato)==0)
        return LISTA_DUPLICADO;
    pnodo=(t_nodo_lista_tercetos*)malloc(sizeof(t_nodo_lista_tercetos));
    if(!pnodo)
        return LISTA_LLENA;
    pnodo->dato=*pd;
    pnodo->psig=*pl;
    *pl=pnodo;
    return TODO_BIEN;
}

int comparacion_tercetos(const t_dato_lista_tercetos *pd1, const t_dato_lista_tercetos *pd2)
{
    return pd1->nro - pd2->nro;
}

void guardar_lista_en_archivo_terceto(t_lista_tercetos *pl, const char *path)
{
	t_dato_lista_tercetos *pd;
	FILE *pf = fopen(path, TEXTO_ESCRITURA);
	if(pf == NULL)
	{
		printf("No se pudo abrir el archivo %s\n", path);
		return;
	}

    while(*pl)
    {
        pd =  &(*pl)->dato;
		fprintf(pf,"[%d] (%s, %s, %s)\n", pd->nro, pd->s1, pd->s2, pd->s3);
        pl = &(*pl)->psig;
    }
	fclose(pf);
}

char* buscar_elemento(const t_lista_tercetos *pl, int nro_terceto, int nro_elemento)
{
	while(*pl)
    {
        if( (*pl)->dato.nro - nro_terceto == 0)
		{
			if(nro_elemento == PRIMER_ELEMENTO)
			{
				return (*pl)->dato.s1;
			}
			else if(nro_elemento == SEGUNDO_ELEMENTO)
			{
				return (*pl)->dato.s2;
			}
			else
			{
				return (*pl)->dato.s3;
			}
		}
        pl=&(*pl)->psig;
    }
	return NULL;
}

void cambiar_elemento(const t_lista_tercetos *pl, int nro_terceto, const char *s ,int nro_elemento )
{
	
	while(*pl)
    {
        if((*pl)->dato.nro - nro_terceto == 0)
		{
			if(nro_elemento == PRIMER_ELEMENTO)
			{
				free((*pl)->dato.s1);
				if(((*pl)->dato.s1 = strdup(s)) == NULL)
				{
					puts("Problemas de memoria");
					exit(ERROR);
				}
				return;
			}
			else if(nro_elemento == SEGUNDO_ELEMENTO)
			{
				free((*pl)->dato.s2);
				if(((*pl)->dato.s2 = strdup(s)) == NULL)
				{
					puts("Problemas de memoria");
					exit(ERROR);
				}
				return;
			}
			else
			{
				free((*pl)->dato.s3);
				if(((*pl)->dato.s3 = strdup(s)) == NULL)
				{
					puts("Problemas de memoria");
					exit(ERROR);
				}
				return;
			}
			
		}
        pl=&(*pl)->psig;
    }
}