#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CuTest.h"
#include <time.h>

typedef struct{
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

void pruebasave(CuTest * cuTest);
int ingrese_comando(char *comando);
void pruebaquit(CuTest * cuTest);
void pruebacomando(CuTest * cuTest);
void pruebaerror(CuTest * cuTest);
void pruebaAbrirTablero1(CuTest *cuTest);
void pruebaAbrirTablero2(CuTest *cuTest);
void pruebaGuardarPartida1(CuTest* cuTest);
void pruebaGuardarPartida2(CuTest* cuTest);
void pruebaCargarPartida(CuTest *cuTest);
char** crearMatriz(int n);
int AbrirTablero(tPartida* partida);
int ingrese_comando(char *comando);
int aleatorio(int izq, int der);
int ExisteTablero(const char* filename);
int ExisteArchivo(const char* filename);
int GuardarPartida( const char* filename, tPartida* partida);
int CargarPartida(const char* filename, tPartida *partida);

CuSuite * FrontTestSuite(void)
{
	CuSuite * cuSuite = CuSuiteNew();
	SUITE_ADD_TEST(cuSuite, pruebasave);
	SUITE_ADD_TEST(cuSuite,pruebaquit);
	SUITE_ADD_TEST(cuSuite,pruebacomando);
	SUITE_ADD_TEST(cuSuite,pruebaerror);
	SUITE_ADD_TEST(cuSuite,pruebaAbrirTablero1);
    SUITE_ADD_TEST(cuSuite,pruebaAbrirTablero2);
    SUITE_ADD_TEST(cuSuite,pruebaGuardarPartida1);
    SUITE_ADD_TEST(cuSuite,pruebaGuardarPartida2);
    SUITE_ADD_TEST(cuSuite,pruebaCargarPartida);

	return cuSuite;
}

//Todos los del ingrese_comando
void pruebasave(CuTest * cuTest)
{
	char * entrada = "save ";
	int actual = ingrese_comando(entrada);
	int esperado = 1;
	char * mensaje = "No entro a save";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

void pruebaquit(CuTest * cuTest)
{
    char *entrada="quit";
    int actual=ingrese_comando(entrada);
    int esperado=2;
    char *mensaje="No entro a quit";
    CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);

}

void pruebacomando(CuTest * cuTest)
{
    char *entrada="[0,0][0,0]";
    int actual=ingrese_comando(entrada);
    int esperado=0;
    char *mensaje="Comando ingresado incorrecto";
    CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

void pruebaerror(CuTest * cuTest)
{
    char * entrada="Cualquier cosa";
    int actual=ingrese_comando(entrada);
    int esperado=3;
    char *mensaje="No entro a error";
    CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

void pruebaAbrirTablero1(CuTest *cuTest)
{
    tPartida * partida;
    partida=malloc(sizeof(tPartida));
    partida->dim=5;//defino esto para poder probarlo;
	int actual = AbrirTablero(partida);
	int esperado = 1;
	char * mensaje = "Existe archivo y no deberia existir";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

void pruebaAbrirTablero2(CuTest *cuTest)
{
    tPartida * partida;
    partida=malloc(sizeof(tPartida));
    partida->dim=18;//defino esto para poder probarlo;
    int actual = AbrirTablero(partida);
    int esperado = 0;
    char * mensaje = "Existe archivo y no deberia existir";
    CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

void pruebaGuardarPartida1(CuTest* cuTest)
{
    tPartida * partida;
    partida=malloc(sizeof(tPartida));
    partida->dim=5;
    partida->tablero=crearMatriz(partida->dim);

    int actual = GuardarPartida("5x5", partida);
    int esperado = 0;
    char * mensaje = "Guardó cuando no debería poder";
    CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

void pruebaGuardarPartida2(CuTest* cuTest)
{
    tPartida * partida;
    partida=malloc(sizeof(tPartida));
    partida->dim=5;
    partida->tablero=crearMatriz(partida->dim);

    int actual = GuardarPartida("testSave", partida);
    int esperado = 1;
    char * mensaje = "No guardó cuando debería poder";
    CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

void pruebaCargarPartida(CuTest *cuTest)
{
    char * entrada = "testSave";//prueba si existe este archivo en el CWD
    tPartida * partida;
    partida=malloc(sizeof(tPartida));

	int actual = CargarPartida(entrada,partida);
	int esperado = 0;
	char * mensaje = "No carga la partida que deberia cargar";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

int AbrirTablero(tPartida* partida)
{
    char* filename;
    if (partida->dim < 10)
        filename=malloc(6*sizeof(char));
    else
        filename=malloc(8*sizeof(char));
    sprintf(filename, "./%dx%d", partida->dim, partida->dim);

//Veo si ese archivo existe
  if (!ExisteTablero(filename))
    return 0;
  FILE* archivo = fopen(filename, "r");
//Elijo un tablero al azar
  int opciones;

  opciones = (fgetc(archivo)-'0');
  int eleccion = aleatorio(1, opciones);


  char c=fgetc(archivo);
//Me paro sobre el primer tablero y busco el seleccionado
  for (int i = 0; i != (eleccion-1)*(2 + partida->dim*(partida->dim+1)); ++i)
    c=fgetc(archivo);

//Creo la matriz
  partida->tablero=crearMatriz(partida->dim);
  for (int i = 0; i < (partida->dim); ++i)
  {
    for (int j = 0; j < (partida->dim); ++j)
    {
      c=fgetc(archivo);
      if (c==' ')
        c='0';
      partida->tablero[i][j]=c;

      //Verifico que este pasando valores adecuados.
      //Si c fuese un espacio o un ENTER, fallaria el programa.
      if (c!='A' && c!='B' && c!='C' && c!='D' && c!='E' && c!='0')
      {
        return 0;
      }
    }
    c=fgetc(archivo);
  }
  return 1;
}

int ingrese_comando(char *comando)
{
    tMovimiento *movimiento=malloc((sizeof(tMovimiento)));
    //char comando[MAX_DIM]={0};
    //int cont=0,c;
    char *nombre_partida=malloc(sizeof(char)*20);
    int terminado=0;
    //printf("\nIngrese el comando: ");
    while(terminado==0)
    {       //de la funcion original,que le pide al usuario que ingrese el comando,
            //lo cambio yo para poder probar los diferentes casos
            /*cont = 0;
            for(cont = 0; (c = getchar())!='\n' && cont<MAX_DIM-1 ; cont++)
            {
                comando[cont]=c;
            }
            if(c != '\n')
                BORRA_BUFFER;
            comando[cont] = 0;*/

            if(strncmp(comando, "save ", 5)==0)
            {
                sscanf(comando,"save %s",nombre_partida);
                //comanto guardar partida ya que no estamos interesados en que guarde la partida
                //en este test
                //GuardarPartida(nombre_partida,partida);
                printf("\nLa partida se guardo exitosamente!\n");
                return 1;
            }
            else if (strncmp(comando, "quit", 4)==0 && comando[4]==0)
            {
                //quit(movimiento, partida);
                return 2;
            }
            else if((sscanf(comando,"[%d,%d][%d,%d]%s", &movimiento->F1, &movimiento->C1, &movimiento->F2, &movimiento->C2))==4)
            {
                terminado=1;
                return 0;//ver return 1;
            }
            else
            {
                printf("Error! Comando incorrecto, ingrese nuevamente: ");
                return 3;
            }
    }

  return 0;
}

int aleatorio(int izq, int der)
{
    int num;
    srand(time(NULL));
    num = izq+(rand()%(der-izq+1));
    return num;
}


int ExisteTablero(const char* filename)
{
    FILE* archivo;
    archivo = fopen(filename, "r");
    if (archivo != NULL)
    {
     fclose(archivo);
     return 1;
    }
    return 0;
}

int ExisteArchivo(const char* filename)
{
    char ubicacion[strlen(filename)+3];
    snprintf(ubicacion, sizeof(ubicacion), "./%s", filename);
    FILE* archivo;

    if ((archivo = fopen(ubicacion, "rb")) != NULL)
    {
     fclose(archivo);
     return 1;
    }
    return 0;
}


char** crearMatriz(int n)
{
    int flag=1;
    char** tablero=NULL;

    //Crear tantos arreglos como dimension
    tablero=malloc(sizeof(*tablero)*n);
    if(tablero!=NULL)
    {
        for (int i = 0; i < n  &&  flag; ++i)
        {
            //Para cada elemento del arreglo, darle otro arreglo de la misma dimension
            tablero[i]=malloc(sizeof(**tablero)*n);

            //Si no hay memoria, cancelar todo el proceso.
            if (tablero[i] == NULL)
            {
                flag=0;
                for (int j = 0; j >= 0; j--)
                    free(tablero[j]);
                free(tablero);
            }
        }
    }
    return tablero;
}

int CargarPartida(const char* filename, tPartida *partida)
{
	if (!(ExisteArchivo(filename)))
		return 0;
	char ubicacion[strlen(filename)+3];
	snprintf(ubicacion, sizeof(ubicacion), "./%s", filename);
	FILE* archivo = fopen(ubicacion, "rb");

	fread(&partida->jugadores, sizeof(partida->jugadores), 1, archivo);
	if (partida->jugadores != 0 && partida->jugadores != 1)
		return 0;

	fread(&partida->turno, sizeof(partida->turno), 1, archivo);
	if (partida->turno != 1 && partida->turno != 2)
		return 0;

	fread(&partida->dim, sizeof(partida->dim), 1, archivo);
	if (partida->dim < 5 || partida->dim > 30)
		return 0;

	partida->tablero=crearMatriz(partida->dim);
	for (int i = 0; i < (partida->dim); ++i)
		for (int j = 0; j < (partida->dim); ++j)
		{
			partida->tablero[i][j]=fgetc(archivo);
		}
	if (fgetc(archivo) != EOF)
	{
		return 0;
	}

	fclose(archivo);
	return 1;
}

int GuardarPartida( const char* filename, tPartida* partida)
{
  //Sumo 3 para asegurarme de que entren el "./" y el 0
  int aux1;
  int aux2;
  sscanf(filename, "%dx%d", &aux1, &aux2);

  if ((aux1 == aux2) && (aux1 >= 5 && aux1 <= 30))
  {
    return 0;
  }

  char ubicacion[strlen(filename)+3];
  snprintf(ubicacion, sizeof(ubicacion), "./%s", filename);
  FILE* archivo = fopen(ubicacion, "wb");

  // 0 = 2 players
  // 1 = CPU
  fwrite(&partida->jugadores, sizeof(partida->jugadores), 1, archivo);
  // Modo
  fwrite(&partida->turno, sizeof(partida->turno), 1, archivo);
  // Dimension del tablero
  fwrite(&partida->dim, sizeof(partida->dim), 1, archivo);
  // Tablero
  for (int i = 0; i < (partida->dim); ++i)
    for (int j = 0; j < (partida->dim); ++j)
      fwrite((&partida->tablero[i][j]), sizeof(char), 1, archivo);
  fclose(archivo);
  return 1;
}
