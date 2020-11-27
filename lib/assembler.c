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


/* FUNIONES GENERAR */

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
			if(strcmp((*pl)->dato.tipo, STRING) == 0)
			{
				fprintf(pf, "%-35s\t%-2s\t%-35s, \'$\', %d dup (?)\n",(*pl)->dato.lexema, PRECISION_STRING, (*pl)->dato.valor, (*pl)->dato.longitud);
			}
			else
			{
				fprintf(pf, "%-35s\t%-2s\t%s.00\n",(*pl)->dato.lexema, PRECISION_INTEGER, (*pl)->dato.valor);
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
		if(es_etiqueta((*pl)->dato.s))
		{
			fprintf(pf, "%s\n", (*pl)->dato.s);
		}
		else if(es_asignacion((*pl)->dato.s))
		{
			pl=&(*pl)->psig;
			fprintf(pf, "%s %s\n", CMD_POP, (*pl)->dato.s);
		}
		else if(es_salida((*pl)->dato.s))
		{
			pl=&(*pl)->psig;
			asm_salida(pf, (*pl)->dato.s);
		}
		else if(es_entrada((*pl)->dato.s))
		{
			pl=&(*pl)->psig;
			fprintf(pf, "%s %s\n", CMD_IN_FLOAT, (*pl)->dato.s);
		}
		else if(es_comparacion((*pl)->dato.s))
		{
			asm_comparacion(pf);
		}
		else if(es_salto((*pl)->dato.s))
		{
			char *cmd_salto = obtener_cmd_salto((*pl)->dato.s);
			pl=&(*pl)->psig;
			fprintf(pf, "%s %s\n", cmd_salto, (*pl)->dato.s);
		}
		else
		{
			fprintf(pf, "%s %s\n", CMD_PUSH, (*pl)->dato.s);
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

/* FUNIONES ES_ */

int es_constante(const char *s)
{
	return strncmp(s, MARCADOR_CONSTANTE, strlen(MARCADOR_CONSTANTE)) == 0;
}

int es_etiqueta(const char *s)
{	
	return strncmp(s, ETIQUETA, strlen(ETIQUETA)) == 0;
}

int es_asignacion(const char *s)
{
	return strcmp(s, OP_ASIGNACION) == 0;
}

int es_salida(const char *s)
{
	return strcmp(s, OUTPUT) == 0;
}

int es_entrada(const char *s)
{
	return strcmp(s, INPUT) == 0;
}

int es_comparacion(const char *s)
{
	return strcmp(s, CMP) == 0;
}

int es_salto(const char *s)
{
	return strcmp(s, BI) == 0 || strcmp(s, BLT) == 0 || strcmp(s, BLE) == 0 || strcmp(s, BGT) == 0 || strcmp(s, BGE) == 0 || strcmp(s, BEQ) == 0 || strcmp(s, BNE) == 0; 
}


/* FUNCIONES OPERACIONES */

void asm_salida(FILE *pf, const char *s)
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


void asm_comparacion(FILE *pf)
{
	fprintf(pf, "%s\n", CMD_XCH);
	fprintf(pf, "%s\n", CMD_CMP);
	fprintf(pf, "%s\n", CMD_STSW);
	fprintf(pf, "%s\n", CMD_SAHF);
	fprintf(pf, "%s\n", CMD_LIBERAR);
}

/* FUNCIONES AUXILIARS */

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