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
	res = (char*) malloc(strlen(ETIQUETA) * sizeof(char) + CANTIDAD_DIGITOS_NUMERO + 1);
	if(res == NULL)
	{
		return NULL;
	}
	sprintf(res,"%s%d", ETIQUETA, nro_celda_prev + 1);
	return res;
}

char* agregar_fin_etiqueta(const char *s)
{
	char *res;
	res = (char*) malloc(strlen(s) * sizeof(char) + strlen(FIN_ETIQUETA) + 1);
	if(res == NULL)
	{
		return NULL;
	}
	strcpy(res, s);
	strcat(res, FIN_ETIQUETA);
	return res;
}

void agregar_valos_contador_ts(int contador, t_lista_ts *pts)
{
	char s_aux[CANTIDAD_ITOA];
	int i;
	for(i = 1; i <= contador; i++)
	{
		itoa(contador, s_aux, 10);
		insertar_ts(agregar_guion_bajo(s_aux), INTEGER, s_aux, SIN_LONGITUD, pts);
	}
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

// Operaciones
void operacion_output(const char *s, int *pnumeracion, t_lista_polaca *ppolaca)
{
	insertar_polaca(OUTPUT, pnumeracion, ppolaca);
	insertar_polaca(s, pnumeracion, ppolaca);
}

void operacion_asignacion(const char *s1, const char *s2, int *pnumeracion, t_lista_polaca *ppolaca)
{
	insertar_polaca(s2, pnumeracion, ppolaca);
	insertar_polaca(OP_ASIGNACION, pnumeracion, ppolaca);
	insertar_polaca(s1, pnumeracion, ppolaca);
}

void operacion_exit(int *pnumeracion, t_lista_polaca *ppolaca)
{
	insertar_polaca(BI, pnumeracion, ppolaca);
	insertar_polaca(ELEMENTO_VACIO, pnumeracion, ppolaca);
}

void algoritmo_busqueda_aparicion(const char *cte, int *pcontador, int *pnumeracion, t_lista_polaca *ppolaca)
{
	char s_aux[CANTIDAD_ITOA];
	
	// @contador = @contador + 1
	(*pcontador)++;
	// if(@es_primera_aparicion == 0 and @aux == #n)
	insertar_polaca(VAR_ES_PRI, pnumeracion, ppolaca);
	insertar_polaca(INI_VAR_ES_PRI_LEXEMA, pnumeracion, ppolaca);
	insertar_polaca(CMP, pnumeracion, ppolaca);
	insertar_polaca(BNE, pnumeracion, ppolaca);
	insertar_polaca(crear_etiqueta((*pnumeracion) + SALTO_VERIFICACION_VAR_ES_PRI), pnumeracion, ppolaca);
	insertar_polaca(VAR_AUX, pnumeracion, ppolaca);
	insertar_polaca(cte, pnumeracion, ppolaca);
	insertar_polaca(CMP, pnumeracion, ppolaca);
	insertar_polaca(BNE, pnumeracion, ppolaca);
	insertar_polaca(crear_etiqueta((*pnumeracion) + SALTO_VERIFICACION_VAR_AUX), pnumeracion, ppolaca);
	// @posicion = @contador
	itoa((*pcontador), s_aux, 10);
	operacion_asignacion(VAR_POS, agregar_guion_bajo(s_aux), pnumeracion, ppolaca);
	// @es_primera_aparicion = 1
	operacion_asignacion(VAR_ES_PRI, FIN_VAR_ES_PRI_LEXEMA, pnumeracion, ppolaca);
	// Creamos etiqueta para el salto
	insertar_polaca(agregar_fin_etiqueta(crear_etiqueta((*pnumeracion))), pnumeracion, ppolaca);
}