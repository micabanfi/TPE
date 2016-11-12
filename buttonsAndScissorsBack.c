#include "buttonsAndScissorsBack.h"



char** crearMatriz(int n);
int ExisteTablero(const char* filename);
int ExisteArchivo(const char* filename);
int Buscarmismo(char **matriz,int i, int j, int t, int s, int dim);


int AbrirTablero(tPartida* partida)
{
//Asigno suficiente memoria para que entre el nombre del archivo.

  char* filename;
  if (partida->dim < 10)
    filename=malloc(10*sizeof(char));
  else
    filename=malloc(12*sizeof(char));
  sprintf(filename, "./%dx%d.txt", partida->dim, partida->dim);

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

int aleatorio(int izq, int der)
{
    int num;
    srand(time(NULL));
    num = izq+(rand()%(der-izq+1));
    return num;
}

int Buscarmismo(char **matriz,int i, int j, int t, int s, int dim)
{
    int salto;
    for (salto=1;(MovValido(i,j,t*salto,s*salto,dim)) && ((matriz[i+t*salto][j+s*salto]=='0')||( matriz[i][j]==matriz[i+t*salto][j+s*salto]));salto++)
    /*cuenta la cantidad de saltos en una posicion hasta encontrar el mismo*/
    {
        if (matriz[i][j]==matriz[i+t*salto][j+s*salto])
        return salto;
    }
    return 0;/*retorna 0 si encontro uno que no es o se va de los limites*/
}

int CargarPartida(const char* filename, tPartida *partida)
{
  if (!(ExisteArchivo(filename)))
    return 0;
  char ubicacion[strlen(filename)+3];
  snprintf(ubicacion, sizeof(ubicacion), "./%s", filename);
  FILE* archivo = fopen(ubicacion, "rb");

  fread(&partida->jugadores, sizeof(partida->jugadores), 1, archivo);
  fread(&partida->turno, sizeof(partida->turno), 1, archivo);
  fread(&partida->dim, sizeof(partida->dim), 1, archivo);

  partida->tablero=crearMatriz(partida->dim);
  for (int i = 0; i < (partida->dim); ++i)
    for (int j = 0; j < (partida->dim); ++j)
      partida->tablero[i][j]=fgetc(archivo);
  fclose(archivo);
  return 1;
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

void GuardarPartida( const char* filename, tPartida* partida)
{
  //Sumo 3 para asegurarme de que entren el "./" y el 0
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
}

int hacerjugada(tPartida *partida,tMovimiento * movimiento )
{
  int dx,dy,x=movimiento->F1,y=movimiento->C1, cont=0 ;
    if ((movimiento->F2-movimiento->F1)==0)
        dx=0;
    else
        dx= (movimiento->F2) > (movimiento->F1) ? 1 : -1;

    if ((movimiento->C2-movimiento->C1)==0)
        dy=0;
    else
        dy = (movimiento->C2) > (movimiento->C1) ? 1 : -1;

  for (; x!=(movimiento->F2) || y!=movimiento->C2; x+= dx, y+=dy)
  {
    if ( partida->tablero[x][y]!='0')
    {
        partida->tablero[x][y]='0';
        cont++;
    }
  }
  partida->tablero[movimiento->F2][movimiento->C2]='0';
    cont++;
return cont;
}

int HayJugada(int N, char **tablero)
{
    int F1,C1,df,dc,mov;
   for (F1 = 0; F1 < N; F1++)
    {
    for (C1 = 0; C1 < N; C1++)
       {
         if (tablero[F1][C1] != '0')
         {
                for (df=0; df<2;df++)
                {
                    for (dc=-1; dc<2;dc++)
                    {
                        if (!(df==dc && dc==0)&& !(df==0 && dc==-1))
                        {
                            mov=Buscarmismo(tablero,F1,C1,df,dc,N);
                            if (mov>0)
                            {
                                return 0;//hay jugada

                            }

                        }
                    }
                }
            }
        }
     }
    return 1;
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


    if (partida->tablero[coordenadas->F1][coordenadas->C1] == ' ' || partida->tablero[coordenadas->F2][coordenadas->C2] == ' ')
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
