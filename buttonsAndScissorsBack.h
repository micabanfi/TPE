#ifndef botonesytijeras_h
#define botonesytijeras_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "getnum.h"
#define BORRA_BUFFER while (getchar() != '\n')
#define VERDADERO 0==0
#define FALSO 1==0
#define MovValido(i,j,x,y,dim) ((((i+(x))<0) || ((i+(x))>=dim) || ((j+(y))<0) || ((j+(y))>=dim) )? FALSO:VERDADERO)
#define AgrandarTabla(cont,bloque) (((cont%bloque)==0)?VERDADERO:FALSO)
#define direccionBuena(df,dc) ((!(df==dc && dc==0) && !(df==0 && dc==-1))?VERDADERO:FALSO)
#define MAX_DIM 30
#define bloque 10

typedef struct {
    int turno;
    int ptsjug1;
    int ptsjug2;
    char **tablero;
    int dim;
    int jugadores;
}tPartida;

typedef struct {
    int F1;
    int C1;
    int F2;
    int C2;
}tMovimiento; /*estructura con posiciones iniciales y finales de movimientos*/


int AbrirTablero(tPartida* partida); //
int aleatorio(int izq, int der);//

int CargarPartida(const char* filename, tPartida *partida);//

void GuardarPartida( const char* filename, tPartida* partida);//
int hacerjugada(tPartida *partida,tMovimiento * movimiento );//
int HayJugada(int N, char **tablero);//
int InvalidMove(tPartida* partida, tMovimiento* coordenadas);//



#endif
