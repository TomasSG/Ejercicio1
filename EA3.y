%{
#include "./include/cabecera.h"
%}

%union
{
	char *string;
}

/* PALABRAS RESERVADAS */
%token WRITE									
%token POSICION								
%token READ								

/* ELEMENTOS DE PUNTUACIÓN Y OTROS */
%token PARA								
%token PARC								
%token CA								
%token CC								
%token COMA								
%token PYC								

/* OPERADORES */
%token ASIGNA							

/* TOKENS CON FAMILIAS DE LEXEMAS */
%token <string> ID								
%token <string> CTE								
%token <string> CTE_S	

%start s

%%

s: prog 
{
	puts("R0: S -> PROG");
	puts("COMPILACION EXITOSA");
	int nro_celda;
	
	
	/* INSERTAMOS EN TODOS LOS EXIT LOS SALTOS A ESTA ETIQUETA */
	
	// Creamos etiqueta para el salto
	insertar_polaca(agregar_fin_etiqueta(crear_etiqueta(numeracion)), &numeracion, &polaca);
	// Por cada elemento en la pila, escribimos en nro de celda actual en dicha celda
	while(desapilar(&pila_celdas, &nro_celda) != PILA_VACIA)
	{
		// Restamos uno a la numeracion porque internamente crear_etiqueta() suma uno a la numeriación. Entonces, si no restaramos
		// encontrariamos las etiquetas desfasados por uno.
		cambiar_elemento(&polaca, nro_celda, crear_etiqueta(numeracion - 1));
	}
}
;

prog: sent
{
	puts("R1: PROG -> SENT");
}

| prog sent
{
	puts("R2: PROG -> PROG SENT");
}
;

sent: read		{puts("R3: SENT -> READ");}
| write			{puts("R3: SENT -> WRITE");}
| asig			{puts("R3: SENT -> ASIG");}
;

read: READ ID
{
	puts("R4: READ -> read id");
	
	insertar_polaca(INPUT, &numeracion, &polaca);
	insertar_polaca($2, &numeracion, &polaca);
}
;

asig: ID ASIGNA posicion
{
	puts("R5: ASIG -> id asigna POSICION");
	
	operacion_asignacion($1, VAR_POS, &numeracion, &polaca);
}
;

posicion: POSICION PARA ID PYC CA lista CC PARC
{
	puts("R6: POSICION -> posicion para id pyc ca LISTA cc parc");
	
	/* VERIFICACION DE QUE NO SE ENCONTRO EL ELEMENTO */
	
	// if(@posicion == 0)
	insertar_polaca(VAR_POS, &numeracion, &polaca);
	insertar_polaca(INI_VAR_POS_LEXEMA, &numeracion, &polaca);
	insertar_polaca(CMP, &numeracion, &polaca);
	insertar_polaca(BNE, &numeracion, &polaca);
	insertar_polaca(crear_etiqueta(numeracion + SALTO_VERIFICACION_VAR_POS), &numeracion, &polaca);
	// WRITE "Elemento no encontrado"
	operacion_output(MSJ_ERROR_NO_ENCONTRADO_LEXEMA, &numeracion, &polaca);
	// exit
	operacion_exit(&numeracion, &polaca);
	apilar(&pila_celdas, &numeracion);
	// Creamos etiqueta para el salto
	insertar_polaca(agregar_fin_etiqueta(crear_etiqueta(numeracion)), &numeracion, &polaca);
	
	
	// Escribir en nro_celda_aux el nro de celda actual
	cambiar_elemento(&polaca, _nro_celda_aux, $3);
}

| POSICION PARA ID PYC CA CC PARC
{
	puts("R7: POSICION -> posicion para id pyc ca cc parc");
	
	/* ERROR DE LISTA ES VACIA */
	
	// WRITE "La lista esta vacia"
	operacion_output(MSJ_ERROR_LISTA_VACIA_LEXEMA, &numeracion, &polaca);
	// exit
	operacion_exit(&numeracion, &polaca);
	apilar(&pila_celdas, &numeracion);
}
;

lista: CTE
{
	puts("R8: LISTA -> cte");
	
	/* INICIALIZACION DE @AUX */
	
	// @aux = pivot
	insertar_polaca(ELEMENTO_VACIO, &numeracion, &polaca);
	_nro_celda_aux = numeracion;
	insertar_polaca(OP_ASIGNACION, &numeracion, &polaca);
	insertar_polaca(VAR_AUX, &numeracion, &polaca);
	
	/* VERIFICACION DE PIVOT */
	
	// if(@aux < 1)
	insertar_polaca(VAR_AUX, &numeracion, &polaca);
	insertar_polaca(VALOR_CRITICO_PIVOT_LEXEMA, &numeracion, &polaca);
	insertar_polaca(CMP, &numeracion, &polaca);
	insertar_polaca(BGE, &numeracion, &polaca);
	insertar_polaca(crear_etiqueta(numeracion + SALTO_VERIFICACION_PIVOT), &numeracion, &polaca);
	// WRITE "El valor debe ser >= 1"
	operacion_output(MSJ_ERROR_PIVOT_LEXEMA, &numeracion, &polaca);
	// exit
	operacion_exit(&numeracion, &polaca);
	apilar(&pila_celdas, &numeracion);
	// Creamos etiqueta para el salto
	insertar_polaca(agregar_fin_etiqueta(crear_etiqueta(numeracion)), &numeracion, &polaca);
	
	/* INICIALIZACION DE RESTOS DE VARIABLES */
	
	// @posicion = 0
	operacion_asignacion(VAR_POS, INI_VAR_POS_LEXEMA, &numeracion, &polaca);
	// @contador = 0
	_contador = 0;
	// @es_primera_poiscion = 0;
	operacion_asignacion(VAR_ES_PRI, INI_VAR_ES_PRI_LEXEMA, &numeracion, &polaca);
	
	/* ALGORITMO PARA ENCONTRAR POSICION */
	
	algoritmo_busqueda_aparicion($1, &_contador, &numeracion, &polaca);
}

| lista COMA CTE
{
	puts("R9: LISTA -> LISTA coma cte");
	
	/* ALGORITMO PARA ENCONTRAR POSICION */
	
	algoritmo_busqueda_aparicion($3, &_contador, &numeracion, &polaca);
	
}
;

write: WRITE CTE_S
{
	puts("R10: WRITE -> write cte_s");
	
	operacion_output($2, &numeracion, &polaca);
}

| WRITE ID
{
	puts("R11: WRITE -> write id");
	
	operacion_output($2, &numeracion, &polaca);
}
;

%%

int main(int argc, char **argv)
{
	yyin = fopen(argv[1], TEXTO_LECTURA);
	if(yyin == NULL)
	{
		printf("No se pudo abrir el archivo en %s", argv[1]);
		return ERROR;
	}
	
	// Inicialización de estructuras y variables
	crear_lista_ts(&ts);
	crear_pila(&pila_celdas);
	
	insertar_ts(MSJ_ERROR_PIVOT_LEXEMA, STRING, MSJ_ERROR_PIVOT_VALOR, strlen(MSJ_ERROR_PIVOT_VALOR) - CANTIDAD_COMILLAS, &ts);
	insertar_ts(MSJ_ERROR_LISTA_VACIA_LEXEMA, STRING, MSJ_ERROR_LISTA_VACIA_VALOR, strlen(MSJ_ERROR_LISTA_VACIA_VALOR) - CANTIDAD_COMILLAS, &ts);
	insertar_ts(MSJ_ERROR_NO_ENCONTRADO_LEXEMA, STRING, MSJ_ERROR_NO_ENCONTRADO_VALOR, strlen(MSJ_ERROR_NO_ENCONTRADO_VALOR) - CANTIDAD_COMILLAS, &ts);
	
	insertar_ts(VAR_AUX, NULL, NULL, SIN_LONGITUD, &ts);
	insertar_ts(VAR_POS, NULL, NULL, SIN_LONGITUD, &ts);
	insertar_ts(VAR_ES_PRI, NULL, NULL, SIN_LONGITUD, &ts);
	
	insertar_ts(INI_VAR_POS_LEXEMA, INTEGER, INI_VAR_POS_VALOR, SIN_LONGITUD, &ts);
	insertar_ts(INI_VAR_ES_PRI_LEXEMA, INTEGER, INI_VAR_ES_PRI_VALOR, SIN_LONGITUD, &ts);
	insertar_ts(FIN_VAR_ES_PRI_LEXEMA, INTEGER, FIN_VAR_ES_PRI_VALOR, SIN_LONGITUD, &ts);
	insertar_ts(VALOR_CRITICO_PIVOT_LEXEMA, INTEGER, VALOR_CRITICO_PIVOT_VALOR, SIN_LONGITUD, &ts);
	
	crear_lista_polaca(&polaca);
	numeracion = 0;
	
	yyparse();
	
	
	// Esto es para asegurarme que todos los valores que toma _contador esten en la ts
	for(i = 1; i <= _contador; i++)
	{
		itoa(_contador, s_aux, 10);
		insertar_ts(agregar_guion_bajo(s_aux), INTEGER, s_aux, SIN_LONGITUD, &ts);
	}
	
	// Cierre de estructuras y variables
	guardar_lista_en_archivo_polaca(&polaca, PATH_ARCHIVO_INTERMEDIO);
	vaciar_lista_polaca(&polaca);
	
	guardar_lista_en_archivo_ts(&ts, PATH_ARCHIVO_TS); // Solo para testing
	vaciar_lista_ts(&ts);
	
	vaciar_pila(&pila_celdas);
	
	fclose(yyin);
	
	return TODO_BIEN;
}

int yyerror(void)
{
	puts("***************************");
	puts("ERROR SINTACTICO");
	printf("Linea %d\n", yylineno);	
	puts("***************************");
}