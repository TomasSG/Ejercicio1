# Ejercicio1
Primer ejercicio de la EA3 de LyC 2020 - segundo cuatrimestre

# Consigna 
Sea un lenguaje sencillo que permite tres tipos de sentencias

Este lenguaje permite tres sentencias

1) WRITE
2) READ
3) POSICION

**READ**

Permite la lectura de una o varias variables numéricas

**WRITE**

Permite la escritura de una variable numérica y de una constante string

**POSICION**

La sentencia permite encontrar en que posición de una lista de constantes enteras positivas se encuentra un elemento pivot.

La lista de constantes puede ser cambiada alterando los valores y su cantidad en el programa test.txt.

El elemento pivot deberá ser mayor o igual a uno y será ingresado por el usuario, si no cumpliese con la validación deberá mostrar un mensaje “El valor debe ser >=1” Si el elemento pivot estuviera varias veces en la lista, el resultado de la sentencia es la primera posición en la que aparece. En caso de que no sea encontrado se emitirá el mensaje “Elemento no encontrado”

Se deberá verificar que el pivot no sea mayor a la longitud de la lista. Si este fuera el caso se deberá emitir un mensaje “La lista tiene menos elementos que el indicado.” La lista de constantes podría ser vacía en cuyo caso se emitirá un mensaje “La lista está vacía”

Por ejemplo:

resul =posicion (4;[10,20,30,40,5,4]) Elemento Encontrado en posición 6

resul =posicion (5;[2,2,2,4]) Elemento no encontrado

resul =posicion (51;[2,2,2,4]) Elemento no encontrado

resul =posicion (1;[2,1,1,4]) Elemento Encontrado en posición 2

resul =posicion (1;[]) La lista está vacía

**Gramática**

Gramática < {S, POSICION, LISTA, WRITE, PROG, SENT, READ, ASIG}, {cte,id,asigna,para,parc,cte_s,write,posicion,pyc,ca,cc, coma, read } , S , Reglas }

Reglas:

0. S → PROG
1. PROG → SENT
2. PROG → PROG SENT
3. SENT → READ | WRITE | ASIG
4. READ → read cte
5. ASIG → id asigna POSICION
6. POSICION → posicion para id pyc ca LISTA cc parc
7. POSICION → posicion para id pyc ca cc parc
8. LISTA → cte
9. LISTA → LISTA coma cte
10. WRITE → write cte_s
11. WRITE → write id


## Ejercicio 1

Hacer un compilador completo que solo se base en la gramática dada y con los siguientes
requisitos

1) Los elementos léxicos son los indicados como terminales en la definición de la gramática

* CTE : secuencia de dígitos (Solo representa ctes enteras positivas)
* ID: letra seguida de letras o dígitos o una letra sola.
* WRITE, POSICION, READ : representan las palabras reservadas correspondientes
* ASIGNA: =
* PARA: (
* PARC: )
* CA: [
* CC: ]
* COMA: ,
* PYC: ;
* CTE_S: texto de letras y símbolos únicamente, encerrados entre comillas.

2) El programa test.txt debe ser el siguiente

WRITE “Ingrese un valor pivot mayor o igual a 1: “

READ pivot

resul = posicion ( pivot ; [x1…..xn] )

WRITE “Elemento encontrado en posición: “

WRITE resul

donde x1…..xn son cada una de las constantes. La variable pivot es elegida por el usuario y tendrá un valor entero y positivo. Toda la semántica deberá traducirse a notación intermedia
