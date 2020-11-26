#include "../include/gci.h"

// Para un operador de comparación devuelve la instrucción de assembler necesaria
char* obtener_branch(const char *op)
{
	if(strcmp(op, OPERADOR_LE) == 0)
	{
		return BGE;
	}

	if(strcmp(op, OPERADOR_LEQ) == 0)
	{
		return BGT;
	}

	if(strcmp(op, OPERADOR_GE) == 0)
	{
		return BLE;
	}

	if(strcmp(op, OPERADOR_GEQ) == 0)
	{
		return BLT;
	}

	if(strcmp(op, OPERADOR_NE) == 0)
	{
		return BEQ;
	}

	if(strcmp(op, OPERADOR_IGUAL) == 0)
	{
		return BNE;
	}

	return NULL;
}


char* crear_etiqueta(int nro_celda_prev)
{
	char *res;
	res = (char*) malloc(strlen(ETIQUETA) * sizeof(char) + CANTIDAD_DIGITOS_NUMERO);
	if(res == NULL)
	{
		return NULL;
	}
	sprintf(res,"%s%d", ETIQUETA, nro_celda_prev + 1);
	return res;
}


int insertar_polaca(const char *p1, int *pnumero, t_lista_polaca *pl)
{
	t_dato_lista_polaca *pd;
	int resultado = -60;
	
	pd = (t_dato_lista_polaca*) malloc(sizeof(t_dato_lista_polaca));
	if(pd == NULL)
	{
		puts("Problemas de memoria");
		exit(ERROR);
	}
	
	// Primero aumento la numeración
	(*pnumero)++;

	if((pd->s = strdup(p1)) == NULL)
	{
		puts("Problemas de memoria");
		exit(ERROR);
	}

	pd->nro = *pnumero;
	
	
	// Una vez armado el dato insertamos
	resultado = insertar_ordenado_polaca(pl, pd, comparacion_polaca);
	if(resultado == LISTA_DUPLICADO)
	{
		free(pd);
	}
	else if(resultado == LISTA_LLENA)
	{
		puts("Probelmas de memoria");
		exit(ERROR);
	}
	
	return *pnumero;
}