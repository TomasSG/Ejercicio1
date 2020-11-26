@echo off

:do_while
echo Creando el archivo lex.yy.c.
flex ./EA3.l
pause
echo Creando el archivo de byson.
bison -dyv ./EA3.y
pause
echo Creando el ejecutable ...
gcc  ./lib/lista_ts.c ./lib/lexico.c ./lex.yy.c ./y.tab.c -o ./EA3.exe
pause
cls
echo Ejecutando el Compilador
echo RESULTADOS:
echo -----------------------------------------------------------------
EA3.exe ./test.txt
echo.
echo -----------------------------------------------------------------
pause
del EA3.exe
del lex.yy.c
del y.output
del y.tab.c
del y.tab.h
cls
set /p seguir=Desea seguir con el programa? [s/n]
if "%seguir%"=="s" goto do_while