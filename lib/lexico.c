#include "../include/lexico.h"

void error_lexico(const char *msj, int nro_linea)
{
	puts("***************************");
	puts("ERROR LEXICO");
	printf("Linea %d: %s\n", nro_linea, msj);	
	puts("***************************");
}

char* agregar_guion_bajo(const char *s)
{
	char *resultado;
	resultado =(char*) malloc(sizeof(char) * strlen(s) + CANTIDAD_GUIONES_BAJOS + 1);
	if(resultado == NULL)
	{
		return NULL;
	}
	strcpy(resultado, MARCADOR_CONSTANTE);
	strcat(resultado, s);
	return resultado;
}

char* sacar_comillas(const char *s)
{
	int i, largo = strlen(s);
	char *inicio, *resultado;
	resultado = (char*) malloc(sizeof(char) * largo - CANTIDAD_COMILLAS + 1);
	if(resultado == NULL)
	{
		return NULL;
	}
	inicio = resultado;
	while(*s) {
		if( *s != CARACTER_COMILLA)
		{		
			*resultado = *s;
			resultado++;
			s++;
		}
		else 
		{
			s++;
		}
	}
	*resultado = '\0';
	return inicio;		
}

char* estandarizar_cadena(const char *s)
{
	char *resultado, *paux;
	resultado = (char*) malloc(sizeof(char)* strlen(s) + 1);
	if(resultado == NULL)
	{
		return NULL;
	}
	strcpy(resultado, s);
	paux = resultado;
	while(*paux != '\0')
	{
		if(!es_caracter_valido(*paux))
		{
			*paux = CARACTER_ESTANDARIZAR;
		} 
		else if(es_letra_mayus(*paux))
		{
			*paux = tolower(*paux);
		}
		paux++;
	}
	return resultado;
}


void insertar_ts(const char *lexema, const char *tipo, const char *valor, int longitud, t_lista_ts *ptabla_simbolos)
{
	int resultado = -1;
	t_dato_lista_ts *pd;
	
	// Reservamos memoria para el t_dato_lista_ts
	pd = (t_dato_lista_ts*) malloc(sizeof(t_dato_lista_ts));
	if(pd == NULL)
	{
		puts("Problemas de memoria");
		exit(ERROR);
	}

	// El lexema lo copiamos tal cual
	if( (pd->lexema = strdup(lexema)) == NULL)
	{
		puts("Problemas de memoria");
		exit(ERROR);
	}

	// El tipo hay que validar que no sea NULL porque hay casos en que no se completa este campo
	if(tipo != NULL)
	{
		if( (pd->tipo = strdup(tipo)) == NULL)
		{
			puts("Problemas de memoria");
			exit(ERROR);
		}
	}
	else
	{
		pd->tipo = NULL;
	}
	
	// El valor hay que validar que no sea NULL porque hay casos en que no se completa este campo
	if(valor != NULL)
	{
		if( (pd->valor = strdup(valor)) == NULL)
		{
			puts("Problemas de memoria");
			exit(ERROR);
		}
	}
	else
	{
		pd->valor = NULL;
	}

	// La longitud la copiamos tal cual
	pd->longitud = longitud;
	
	// Ya armado el t_dato_lista_ts insertamos en la tabla
	resultado = insertar_ordenado_ts(ptabla_simbolos, pd, comparacion_ts);
	if(resultado == LISTA_DUPLICADO)
	{
		free(pd);
	}
	else if(resultado == LISTA_LLENA)
	{
		free(pd);
		puts("Probelmas de memoria");
		exit(ERROR);
	}
}

int es_caracter_valido(const char c)
{
	return es_numero(c) || es_letra_min(c) || es_letra_mayus(c) || c == '_';
}	

int es_numero(const char c)
{
	return c >= ASCII_0 && c <= ASCII_9;
}

int es_letra_min(const char c)
{
	return c >= ASCII_a && c <= ASCII_z;
}

int es_letra_mayus(const char c)
{
	return c >= ASCII_A && c <= ASCII_Z;
}