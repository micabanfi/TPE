#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CuTest.h"
#define VERDADERO 0==0
#define FALSO 1==0
#define MovValido(i,j,x,y,dim) ((((i+(x))<0) || ((i+(x))>=dim) || ((j+(y))<0) || ((j+(y))>=dim) )? FALSO:VERDADERO)
#define AgrandarTabla(cont,bloque) (((cont%bloque)==0)?VERDADERO:FALSO)
#define direccionBuena(df,dc) ((!(df==dc && dc==0) && !(df==0 && dc==-1))?VERDADERO:FALSO)
#define MAX_DIM 30
#define bloque 10

typedef struct{
    int turno;
    int ptsjug1;
    int ptsjug2;
    char **tablero;
    int dim;
    int jugadores;
}tPartida;

typedef struct{
    int F1;
    int C1;
    int F2;
    int C2;
}tMovimiento; /*estructura con posiciones iniciales y finales de movimientos*/


void HorizontalValida(CuTest *cuTest);
void VerticalValida(CuTest *cuTest);
void FueraRango1(CuTest *cuTest);
void FueraRango2(CuTest *cuTest);
void Botonvacio1(CuTest *cuTest);
void Botonvacio2(CuTest *cuTest);
void MismoBotonTest(CuTest *cuTest);
void DiagonalInvalida1(CuTest *cuTest);
void DiagonalInvalida2(CuTest *cuTest);
void DiagonalInvalida3(CuTest *cuTest);
void DiagonalInvalida4(CuTest *cuTest);
void BotonMedio1(CuTest *cuTest);
void BotonMedio2(CuTest *cuTest);
void BotonMedio3(CuTest *cuTest);
void TableroPrueba(tPartida * partida);
int InvalidMove(tPartida* partida, tMovimiento* coordenadas);
void FinalizaTest1(CuTest *cuTest);
void FinalizaTest2(CuTest *cuTest);
void FinalizaTest3(CuTest *cuTest);
int Escero(char **matriz,int F1,int C1,int df,int dc,int salto);
int EsIgual(char **matriz,int F1,int C1,int df,int dc,int salto);
int Buscarmismo(char ** matriz,int F1, int C1, int df, int dc, int dim);
int HayJugada(tPartida * partida);


CuSuite * BackTestSuite()
{
CuSuite *cuSuite=CuSuiteNew();
SUITE_ADD_TEST(cuSuite,HorizontalValida);
SUITE_ADD_TEST(cuSuite,VerticalValida);
SUITE_ADD_TEST(cuSuite,FueraRango1);
SUITE_ADD_TEST(cuSuite,FueraRango2);
SUITE_ADD_TEST(cuSuite,Botonvacio1);
SUITE_ADD_TEST(cuSuite,Botonvacio2);
SUITE_ADD_TEST(cuSuite,MismoBotonTest);
SUITE_ADD_TEST(cuSuite,DiagonalInvalida1);
SUITE_ADD_TEST(cuSuite,DiagonalInvalida2);
SUITE_ADD_TEST(cuSuite,DiagonalInvalida3);
SUITE_ADD_TEST(cuSuite,BotonMedio1);
SUITE_ADD_TEST(cuSuite,BotonMedio2);
SUITE_ADD_TEST(cuSuite,BotonMedio3);
SUITE_ADD_TEST(cuSuite,FinalizaTest1);
SUITE_ADD_TEST(cuSuite,FinalizaTest2);
SUITE_ADD_TEST(cuSuite,FinalizaTest3);
//Eliminacion de fichas no tiene valores que tengan un gran rango de cambio
//Creacion de tablero no tiene valores que tengan un gran rango de cambio
return cuSuite;
}

void HorizontalValida(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=0;
movimiento.C1=0;
movimiento.F2=0;
movimiento.C2=29;
char *mensaje1="Es una horizontal y falla.";
esperado=0;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void VerticalValida(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=0;
movimiento.C1=0;
movimiento.F2=29;
movimiento.C2=0;
char *mensaje1="Es una vertical  y falla";
esperado=0;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void FueraRango1(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=-1;
movimiento.C1=-1;
movimiento.F2=0;
movimiento.C2=29;
char *mensaje1="Primer boton fuera de rango";
esperado=1;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void FueraRango2(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=1;
movimiento.C1=1;
movimiento.F2=30;
movimiento.C2=30;
char *mensaje1="Primer boton fuera de rango";
esperado=2;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void Botonvacio1(CuTest *cuTest)
{
int actual1,esperado1;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=0;
movimiento.C1=1;
movimiento.F2=0;
movimiento.C2=1;
char *mensaje1="segundo boton vacio y lo cuenta";
esperado1=3;
actual1=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado1,actual1);

}

void Botonvacio2(CuTest *cuTest)
{
int actual2,esperado2;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=0;
movimiento.C1=1;
movimiento.F2=0;
movimiento.C2=0;
char *mensaje2="Primer boton vacio y lo cuenta";
esperado2=3;
actual2=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje2,esperado2,actual2);
}

void MismoBotonTest(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=0;
movimiento.C1=0;
movimiento.F2=0;
movimiento.C2=0;
char *mensaje1="No debe cortar al mismo boton";
esperado=4;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void DiagonalInvalida1(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=0;
movimiento.C1=0;
movimiento.F2=1;
movimiento.C2=29;
char *mensaje1="Es un movimiento Incorrecto, y esta andando";
esperado=5;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}



void DiagonalInvalida2(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=0;
movimiento.C1=0;
movimiento.F2=29;
movimiento.C2=28;
char *mensaje1="Es un movimiento Incorrecto, y esta andando";
esperado=5;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void DiagonalInvalida3(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=0;
movimiento.C1=0;
movimiento.F2=29;
movimiento.C2=1;
char *mensaje1="Es un movimiento Incorrecto, y esta andando";
esperado=5;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}


void BotonMedio1(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=1;
movimiento.C1=10;
movimiento.F2=1;
movimiento.C2=14;
char *mensaje1="Hay un boton en el medio. Direccion Horizontal";
esperado=6;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void BotonMedio2(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=1;
movimiento.C1=10;
movimiento.F2=4;
movimiento.C2=13;
char *mensaje1="Hay un boton en el medio. Direccion oblicua";
esperado=6;
actual=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void BotonMedio3(CuTest *cuTest)
{
int actual,esperado;
tPartida *partida;
partida=malloc(sizeof (tPartida));
tMovimiento movimiento;
TableroPrueba(partida);
movimiento.F1=1;
movimiento.C1=10;
movimiento.F2=4;
movimiento.C2=10;
char *mensaje1="Hay un boton en el medio. Direccion Vertical";
actual=6;
esperado=InvalidMove(partida, &movimiento);
CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void FinalizaTest1(CuTest *cuTest)
{
 int actual,esperado;
  tPartida * partida;
  partida=malloc(sizeof (tPartida));
  TableroPrueba(partida);
  char *mensaje1="Hay jugada y corto.";
  actual=0; //Compruebo con el tablero prueba.
  esperado=HayJugada(partida);
  CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
  //Elimino todos menos el ultimo de la matriz

}

void FinalizaTest2(CuTest *cuTest)
{
 tPartida * partida;
  partida=malloc(sizeof (tPartida));
  TableroPrueba(partida);
  int actual=0;
char *mensaje1="Hay jugada y corto.";
for (int p=0; p<partida->dim;p++)//Elimino la linea 29. A excepcion de la punta
  {
    for(int q=0; q<partida->dim;q++)
    {
      if ((q==29) && (p!=29))
        partida->tablero[p][q]='0';
    }
  }
int  esperado=HayJugada(partida);
  CuAssertIntEquals_Msg(cuTest,mensaje1,esperado,actual);
}

void FinalizaTest3(CuTest *cuTest)
{
tPartida * partida;
  partida=malloc(sizeof (tPartida));
  TableroPrueba(partida);
for (int p=0; p<partida->dim;p++)//Elimino todos menos la punta.
  {
    for(int q=0; q<partida->dim;q++)
    {
        partida->tablero[p][q]='0';
    }
  }
  partida->tablero[29][29]='A';
int  actual=1;
int  esperado=HayJugada(partida);
char *  mensaje2="No Hay movimientos, y sigue habiendo juego";
  CuAssertIntEquals_Msg(cuTest,mensaje2,esperado,actual);
}

int InvalidMove(tPartida* partida, tMovimiento* coordenadas)
{
    //ERROR 1      Posicion inicial invalida
    //ERROR 2      Posicion Final invalida
    //ERROR 3      Necesito botones especificos
    //ERROR 4      No vale cortar uno solo
    //ERROR 5      No es una diagonal
    //ERROR 6      Hay botones bloqueando el camino

    //Dominio Original
    if (coordenadas->F1 >= partida->dim || coordenadas->F1 < 0 || coordenadas->C1 >= partida->dim || coordenadas->C1 < 0)
     return 1;


    //Dominio Final
    if (coordenadas->F2 >= partida->dim || coordenadas->F2 < 0 || coordenadas->C2 >= partida->dim || coordenadas->C2 < 0)
     return 2;

    //Uno de ambos botones es igual a vacio
    if (partida->tablero[coordenadas->F1][coordenadas->C1] == '0' || partida->tablero[coordenadas->F2][coordenadas->C2] == '0')
     return 3;


    //Direccion
     //Se queda fijo
     if (coordenadas->F1 == coordenadas->F2 && coordenadas->C1 == coordenadas->C2)
       return 4;

     double my = (double)(coordenadas->C2-coordenadas->C1);
     double mx = (double)(coordenadas->F2-coordenadas->F1);
     //No es diagonal
     if (mx != 0     &&      my != 0     &&      abs(my/mx) != 1)
       return 5;

    //Blocked
     if (partida->tablero[coordenadas->F1][coordenadas->C1] != partida->tablero[coordenadas->F2][coordenadas->C2])
       return 6;

     int x;
     int y;
     int dx = (mx < 0)? -1 : (mx > 0);
     int dy = (my < 0)? -1 : (my > 0);

     for (x = coordenadas->F1, y = coordenadas->C1;    (x != (coordenadas->F2)) || (y != (coordenadas->C2))     ;     x += dx, y += dy   )
         {
         if (partida->tablero[coordenadas->F1][coordenadas->C1] != partida->tablero[x][y]   &&  partida->tablero[x][y] != '0')
           return 6;
         }
    return 0;
}

void TableroPrueba(tPartida * partida)
{
int i,j,k;
partida->dim=30;
partida->tablero=malloc(sizeof(char *)*(partida->dim));
for (k=0; k<(partida->dim);k++)
  partida->tablero[k]=malloc(sizeof(char)*partida->dim);

//Pruebas de movimiento de pendientes
//  01*****2829
//00A********A
//01*********A
//  **********
//28*********A
//29AA******AA

//Prueba de botones en el medio
//*10 11 12 13 14
//1 A  *  *  B  A
//2 *  *  *  *  *
//3 B  *  B  *  *
//4 A  *  *  A  *

for (i=0; i<(partida->dim);i++)//Recorro todas las filas
{
  for (j=0; j<(partida->dim);j++)//Recorro todas las columnas
  {
    if ((i==0 && j==0)|| (i==29 && j==29)) //Solo voy a marcar algunas filas. El resto van a estar con '0'
      partida->tablero[i][j]='A';
    if ((i==29 && j==28)||(i==28 &&j==29))//Para probar pendientes muy chicas en horizontales
      partida->tablero[i][j]='A';
    if ((i==0 && j==29) || (i==1  && j==29))//Para probar horizontales con prendientes chicas
      partida->tablero[i][j]='A';
    if ((j==0 && i==29) || (j==1  && i==29))//Para probar verticales con prendientes chicas
      partida->tablero[i][j]='A';
    if ((i==1 && j==10) || (i==1 && j==14)) //Pruebo con botones en el medios sentido horizontal//
      partida->tablero[i][j]='A';
    if ((i==4 && (j==10 ||j==13)))//Pruebo botones en el medio sentido vertical y oblicuo
      partida->tablero[i][j]='A';
    if (i==3 && (j==10 || j==12))//pongo botones de distinto color en el medio de las lineas
      partida->tablero[i][j]='B';
    if (i==1 && j==13)
      partida->tablero[i][j]='B';
    if (partida->tablero[i][j]!='A' && partida->tablero[i][j]!='B') //Cualquier otro caso relleno de 0
      partida->tablero[i][j]='0';
  }
}
}

int Escero(char **matriz,int F1,int C1,int df,int dc,int salto)
{
  if (matriz[F1+df*salto][C1+dc*salto]=='0')
    return VERDADERO;
  else
    return FALSO;
}

int EsIgual(char **matriz,int F1,int C1,int df,int dc,int salto)
{
  if (matriz[F1][C1]==matriz[F1+df*salto][C1+dc*salto])
    return VERDADERO;
  else
    return FALSO;
}

int Buscarmismo(char ** matriz,int F1, int C1, int df, int dc, int dim)
{
  int salto;
  //Por cada iteracion se verifica si esta dentro de la matriz, es cero o es igual a posicion inicial.
  for (salto=1;MovValido(F1,C1,df*salto,dc*salto,dim) && ((Escero(matriz,F1,C1,df,dc,salto)) || (EsIgual(matriz,F1,C1,df,dc,salto)));salto++)
  {
    // Si en una iteracion encuentra el mismo valor de la posicion incial, retorna la cantidad de saltos hasta ese valor.
     if (EsIgual(matriz,F1,C1,df,dc,salto))
        return salto;
  }
  //Encuentra un char diferente a la posicon inicial o diferente a 0, retorna 0;
  return 0;
}

int HayJugada(tPartida * partida)
{
  int F1,C1,df,dc,mov;
  for (F1 = 0; F1 < (partida->dim); F1++) //Recorre todas las filas
  {
    for (C1 = 0; C1 < (partida->dim); C1++)//Recorre todas las columnas
    {
      if ((!Escero(partida->tablero,F1,C1,0,0,0)))//Verifica que la posicion no sea 0
      {
        for (df=0; df<2;df++)//Barre Las filas adyascentes
        {
          for (dc=-1; dc<2;dc++)//Barre las columnas adyascentes
          {
            if ((direccionBuena(df,dc)))//Verifica que las posiciones del barrido sea de la L inferior
            {
              mov=Buscarmismo(partida->tablero,F1,C1,df,dc,partida->dim);//Manda a buscar ficha desde la posicion F1, C1 en direccion df dc
              if (mov>0)//Si es mayor a 0, significa que hay ficha
              {
                return 0;//hay jugada
              }
            }
          }
        }
      }
    }
  }
  return 1;//Si llego aca, es poque no encontro ficha. NO hay jugada
}
