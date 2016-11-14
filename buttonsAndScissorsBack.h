#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#define BORRA_BUFFER while (getchar() != '\n')
#define VERDADERO 0==0
#define FALSO 1==0
#define MovValido(i,j,x,y,dim) ((((i+(x))<0) || ((i+(x))>=dim) || ((j+(y))<0) || ((j+(y))>=dim) )? FALSO:VERDADERO)
#define AgrandarTabla(cont,bloque) (((cont%bloque)==0)?VERDADERO:FALSO)
#define direccionBuena(df,dc) ((!(df==dc && dc==0) && !(df==0 && dc==-1))?VERDADERO:FALSO)
#define MAX_DIM 30
#define bloque 10

/*Estructura que registra datos importantes del juego*/
typedef struct {
    int turno;
    int ptsjug1;
    int ptsjug2;
    char **tablero;
    int dim;
    int jugadores;
}tPartida;

/*Estructura con posiciones iniciales y finales de un movimiento*/
typedef struct {
    int F1;
    int C1;
    int F2;
    int C2;
}tMovimiento;


/*Basandose en la dimension seleccionada, busca en el directorio actual un tablero con el formato "DIMxDIM"*/
/*En caso de encontrarse un error en el contenido del archivo o al no encontrar el mismo, retorna 0*/
int AbrirTablero(tPartida* partida);

/*Retorna un entero aleatorio entre sus parametros izq y der*/
int aleatorio(int izq, int der);

/*Completa una estructura tMovimiento con los parametros recibidos*/
void asignacionTabla(tMovimiento * tabla, int pos,int F1,int C1,int F2,int C2);

/*Busca, mediante saltos, desde una posicon inicial, otro boton del mismo color*/
int Buscarmismo(char ** matriz,int F1, int C1, int df, int dc, int dim);

/*Carga una partida guardada. Si no existe el archivo "filename", retorna 0*/
int CargarPartida(const char* filename, tPartida *partida);

/*Se busca, mediante saltos, donde se encuentra el boton mas cercano distinto de la posicon inicial y del mismo color.*/
int contarsaltos(char ** matriz,int F1,int C1, int df, int dc, int dim, int * posfx, int * posfy );

/*Crea la base para una matriz que luego se llenara con los botones del tablero*/
char** crearMatriz(int n);

/*Verifica en una matriz, desde una posicion inicial con un desplazamiento en x,y sea '0'*/
int Escero(char **matriz,int F1,int C1,int df,int dc,int salto);

/*Verifica si dos direciones de una matriz,caracterizados por un desplazamiento son iguales*/
int EsIgual(char **matriz,int F1,int C1,int df,int dc,int salto);

/*Revisa si existe una partida guardada bajo el nombre filename*/
int ExisteArchivo(const char* filename);

/*Revisa si existe un archivo de texto con el nombre filename*/
int ExisteTablero(const char* filename);

/*Guarda los datos de la partida actual en el archivo binario filename. Lo sobreescribe si es necesario*/
int GuardarPartida( const char* filename, tPartida* partida);

/*Realiza un movimiento sobre el tablero, borrando los botones que se cortaron*/
int hacerjugada(tPartida *partida,tMovimiento * movimiento );

/*Indica si aun hay un movimiento posible. Una vez encontrado, retorna 0*/
int HayJugada(tPartida* partida);

/*Recibiendo dos puntos del tablero, revisa si es posible realizar ese movimiento particular*/
int InvalidMove(tPartida* partida, tMovimiento* coordenadas);

/*En el arreglo de tMovimientos se guardaran los posibles movimientos con la mayor cantidad de botones cortados posible.*/
void Maximo(tPartida * partida,tMovimiento * movimiento);

/*En el arreglo de tMovimientos se guardaran los posibles movimientos con la menor cantidad de botones cortados posible.*/
void Minimo(tPartida * partida,tMovimiento * movimiento);

/*La computadora realiza un movimiento. Aleatoriamente elige si cortar la menor o la mayor cantidad de botones posible*/
void MovPc(tPartida *partida, tMovimiento * movimiento);
