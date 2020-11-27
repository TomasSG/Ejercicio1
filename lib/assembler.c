#include "../include/assembler.h"



void generar_assembler(const char *path_assembler, const t_lista_polaca *p_polaca, const t_lista_ts *p_ts)
{
	FILE *pf = fopen(path_assembler, TEXTO_ESCRITURA);
	if(pf == NULL)
	{
		printf("No se pudo abrir el archivo %s\n", path_assembler);
		exit(ERROR);
	}
	
	generar_encabezado(pf);
	generar_declaraciones(pf, p_ts);
	generar_codigo(pf, p_polaca);
	generar_final(pf);
	
	fclose(pf);
}

void generar_encabezado(FILE *pf)
{
	fprintf(pf, "include number.asm\n");
	fprintf(pf, "include macros2.asm\n\n");
	fprintf(pf, ".MODEL LARGE\n");
	fprintf(pf, ".386\n");
	fprintf(pf, ".STACK 200h\n");
}

void generar_declaraciones(FILE *pf, const t_lista_ts *pl)
{
	fprintf(pf, "\n.DATA\n");
	while(*pl)
    {
		if(es_constante((*pl)->dato.lexema))
		{
			if(strcmp((*pl)->dato.tipo, LEXICO_TIPO_STRING) == 0)
			{
				fprintf(pf, "%-35s\t%-2s\t%-35s, \'$\', %d dup (?)\n",(*pl)->dato.lexema, PRECISION_STRING, (*pl)->dato.valor, (*pl)->dato.longitud);
			}
			else
			{
				if(strcmp((*pl)->dato.tipo, LEXICO_TIPO_INTEGER) == 0)
				{
					fprintf(pf, "%-35s\t%-2s\t%s.00\n",(*pl)->dato.lexema, PRECISION_INTEGER, (*pl)->dato.valor);
				}
				else
				{
					fprintf(pf, "%-35s\t%-2s\t%s\n",(*pl)->dato.lexema, PRECISION_FLOAT, (*pl)->dato.valor);
				}
			}
		}
		else
		{
			fprintf(pf, "%-35s\t%-2s\t?\n", (*pl)->dato.lexema, PRECISION_VARIABLE);
		}

        pl=&(*pl)->psig;
    }
}

void generar_codigo(FILE *pf, const t_lista_polaca *pl)
{
	fprintf(pf, "\n.CODE\n");
	fprintf(pf, "START:\n");
	fprintf(pf, "MOV EAX, @DATA\n");
	fprintf(pf, "MOV DS, EAX\n");
	fprintf(pf, "MOV ES, EAX\n\n");

	while(*pl)
    {
		
        if(es_operador_aritmetico((*pl)->dato.s1))
		{
			operacion_aritmetica(pf, (*pl)->dato.s1, (*pl)->dato.s2, (*pl)->dato.s3);
		} 
		else if(es_etiqueta((*pl)->dato.s1))
		{
			fprintf(pf, "%s:\n", (*pl)->dato.s1);
		}
		else if(es_factor((*pl)->dato.s2, (*pl)->dato.s3))
		{
			fprintf(pf, "%s %s\n", CMD_PUSH, (*pl)->dato.s1);
		}
		else if(es_asignacion((*pl)->dato.s1))
		{
			operacion_asignacion(pf, (*pl)->dato.s2, (*pl)->dato.s3);
		}
		else if(es_salida((*pl)->dato.s1))
		{
			operacion_salida(pf, (*pl)->dato.s2);
		}
		else if(es_entrada((*pl)->dato.s1))
		{
			fprintf(pf, "%s %s\n", CMD_IN_FLOAT, (*pl)->dato.s2);
		}
		else if(es_comparacion((*pl)->dato.s1))
		{
			operacion_comparacion(pf, (*pl)->dato.s2);
		}
		else if(es_salto((*pl)->dato.s1))
		{
			fprintf(pf, "%s %s\n", obtener_cmd_salto((*pl)->dato.s1), transformar_a_etiqueta((*pl)->dato.s2));
		}
		
        
		pl=&(*pl)->psig;
    }
}

void generar_final(FILE *pf)
{
	fprintf(pf, "\nMOV EAX, 4C00H\n");
	fprintf(pf, "INT 21h\n");
	fprintf(pf, "END START");
}


void operacion_aritmetica(FILE *pf, const char *op, const char *s1, const char *s2)
{
	if(*s1 != '[')
	{
		fprintf(pf, "%s %s\n", CMD_PUSH, s1);
	}
	if(*s2 != '[')
	{
		fprintf(pf, "%s %s\n", CMD_PUSH, s2);
	}
	if(strcmp(op, SIGNO_SUMAR) == 0)
	{
		fprintf(pf, "%s\n", CMD_SUMAR);
	}
	else if(strcmp(op, SIGNO_RESTAR) == 0)
	{
		fprintf(pf, "%s\n", CMD_RESTAR);
	}
	else if(strcmp(op, SIGNO_DIVISION) == 0)
	{
		fprintf(pf, "%s\n", CMD_DIVIDIR);
	}
	else if(strcmp(op, SIGNO_MULT) == 0)
	{
		fprintf(pf, "%s\n", CMD_MULTIPLICAR);
	} 
	
}

void operacion_salida(FILE *pf, const char *s)
{
	if(es_constante(s))
	{
		fprintf(pf, "%s %s\n", CMD_OUT_STRING, s);
	}
	else
	{	
		fprintf(pf, "%s %s, 2\n", CMD_OUT_FLOAT, s);
	}
	fprintf(pf, "%s\n", CMD_NUEVA_LINEA);
}

void operacion_comparacion(FILE *pf, const char *s2)
{
	if(*s2 != '[')
	{
		fprintf(pf, "%s %s\n", CMD_PUSH, s2);
	}
	fprintf(pf, "%s\n", CMD_XCH);
	fprintf(pf, "%s\n", CMD_CMP);
	fprintf(pf, "%s\n", CMD_STSW);
	fprintf(pf, "%s\n", CMD_SAHF);
	fprintf(pf, "%s\n", CMD_LIBERAR);
}

void operacion_asignacion(FILE *pf, const char *s1, const char *s2)
{
	if(*s2 != '[')
	{
		fprintf(pf, "%s %s\n", CMD_PUSH, s2);
	}
	fprintf(pf, "%s %s\n", CMD_POP, s1);
}

int es_constante(const char *s)
{
	return *s == '_';
}

int es_operador_aritmetico(const char *s)
{
	return strcmp(s, SIGNO_SUMAR) == 0 || strcmp(s, SIGNO_RESTAR) == 0 || strcmp(s, SIGNO_DIVISION) == 0 || strcmp(s, SIGNO_MULT) == 0; 
}

int es_etiqueta(const char *s)
{	
	return strncmp(s, ETIQUETA, strlen(ETIQUETA)) == 0;
}

int es_factor(const char *s1, const char *s2)
{
	return strcmp(s1, SIGNO_VACIO) == 0 && strcmp(s2, SIGNO_VACIO) == 0;
}

int es_asignacion(const char *s)
{
	return strcmp(s, SIGNO_IGUAL) == 0;
}

int es_salida(const char *s)
{
	return strcmp(s, SALIDA) == 0;
}

int es_entrada(const char *s)
{
	return strcmp(s, ENTRADA) == 0;
}

int es_comparacion(const char *s)
{
	return strcmp(s, CMP) == 0;
}
int es_salto(const char *s)
{
	return strcmp(s, BI) == 0 || strcmp(s, BLT) == 0 || strcmp(s, BLE) == 0 || strcmp(s, BGT) == 0 || strcmp(s, BGE) == 0 || strcmp(s, BEQ) == 0 || strcmp(s, BNE) == 0; 
}


char* obtener_cmd_salto(const char *s)
{
	if(strcmp(s, BI) == 0)
	{
		return CMD_BI;
	}
	else if(strcmp(s, BLT) == 0)
	{
		return CMD_BLT;
	}
	else if(strcmp(s, BLE) == 0)
	{
		return CMD_BLE;
	}
	else if(strcmp(s, BGT) == 0)
	{
		return CMD_BGT;
	}
	else if(strcmp(s, BGE) == 0)
	{
		return CMD_BGE;
	}
	else if(strcmp(s, BEQ) == 0)
	{
		return CMD_BEQ;
	}
	else if(strcmp(s, BNE) == 0)
	{
		return CMD_BNE;
	}
	return NULL;
}

char* transformar_a_etiqueta(const char *s)
{
	char *resultado, *paux;
	int len_etiqueta = strlen(ETIQUETA);
	resultado = (char*) malloc(sizeof(char) * (len_etiqueta + strlen(s) - CANTIDAD_CORCHETES) + 1);
	if(resultado == NULL)
	{
		return NULL;
	}
	strcpy(resultado, ETIQUETA);
	paux = resultado + len_etiqueta;
	s++;
	while(*s != ']' && *s != '\0')
	{
		*paux = *s;
		paux++;
		s++;
	}
	*paux = '\0';
	return resultado;
}