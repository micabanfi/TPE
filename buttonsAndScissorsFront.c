#include "buttonsAndScissorsBack.h"


void abrirPartida(tMovimiento *movimiento,tPartida *partida);
void dosplayers(tMovimiento *movimiento,tPartida* partida);
void errores(int a);
void ImprimirTablero(tPartida* partida);
int ingrese_comando(tMovimiento * movimiento, tPartida *partida);
void menu();
int pedirDim();
void quit(tPartida *partida);


void abrirPartida(tMovimiento *movimiento,tPartida *partida)
{
    int resp=2;
    resp=AbrirTablero(partida);
    while (resp==0){
        printf("Archivo no encontrado o corrupto.Ingrese nuevamente: ");
        partida->dim=pedirDim();
        resp=AbrirTablero(partida);
    }
    partida->ptsjug1=0;
    partida->ptsjug2=0;
}

void dosplayers(tMovimiento *movimiento,tPartida* partida)
{
    int hayplay,botones=0,invmov=0,com=2;
    partida->jugadores=0;
    partida->turno=aleatorio(1,2);
    ImprimirTablero(partida);
    hayplay=HayJugada(partida->dim,partida->tablero);
    while(hayplay==0)
    {
    com = ingrese_comando(movimiento,partida);
    invmov=InvalidMove(partida,movimiento);

        while (invmov!=0 && com==0)
        {
            errores(invmov);
            com = ingrese_comando(movimiento,partida);
            invmov=InvalidMove(partida,movimiento);
        }
        if (invmov == 0 && com==0)
        {
            botones=hacerjugada(partida,movimiento);
        }

        if (com == 0)
        {
           if(partida->turno==1)
            {
              partida->ptsjug1+=botones;
              partida->turno=2;
            }
            else
            {
              partida->ptsjug2+=botones;
              partida->turno=1;
            }
        }
        hayplay=HayJugada(partida->dim,partida->tablero);
    }
    if(partida->turno==1)
        printf("\n\nFELICITACIONES JUGADOR 2,HAS GANADO!!\n\n");
    else
        printf("\n\nFELICITACIONES JUGADOR 1,HAS GANADO!!\n\n");
    menu();
}

void errores(int a)
{
    switch(a){
        case(1):printf("Posicion inicial invalida.\n");
                break;
        case(2):printf("Posicion Final invalida.\n");
                break;
        case(3):printf("Necesito botones especificos.\n");
                break;
        case(4):printf("No vale cortar uno solo.\n");
                break;
        case(5):printf("El corte no es diagonal,horizontal ni vertical.\n");
                break;
        case(6):printf("Hay botones bloqueando el camino.\n");
                break;

    }

}

void ImprimirTablero(tPartida* partida)
{
    printf("\n\n");
    printf("Botones J1: %d, J2: %d  \n",partida->ptsjug1,partida->ptsjug2);
    printf("\n\n/");
    for (int k = 0; k < (partida->dim); ++k)
        printf("         ");
    printf("\\\n\n");


    for (int i = 0; i < partida->dim; ++i)
    {
        for (int j = 0; j < partida->dim; ++j)
        {
            if (partida->tablero[i][j] == '0')
                printf("    %c    ", ' ');
            else
                printf("    %c    ", partida->tablero[i][j]);
        }
        if (i < partida->dim-1)
            printf("\n\n\n");
        printf("\n");
    }

    printf("\n\\");
    for (int k = 0; k < (partida->dim); ++k)
        printf("         ");
    printf("/\n\n");

    printf("Turno jugador %d \n",partida->turno);
}

int ingrese_comando(tMovimiento * movimiento, tPartida *partida)
{
    //ver por longitud cuando ponfo el nombre
    char comando[MAX_DIM]={0};
    int cont=0,c;
    char *nombre_partida=malloc(sizeof(char)*20);
    int terminado=0;
    printf("\nIngrese el comando: ");
    while(terminado==0)
    {
            cont = 0;
            for(cont = 0; (c = getchar())!='\n' && cont<MAX_DIM-1 ; cont++)
            {
                comando[cont]=c;
            }
            if(c != '\n')
                BORRA_BUFFER;
            comando[cont] = 0;

            if(strncmp(comando, "save ", 5)==0)
            {
                sscanf(comando,"save %s",nombre_partida);
                GuardarPartida(nombre_partida,partida);
                printf("\nLa partida se guardo exitosamente!\n");
                return 1;
            }
            else if (strncmp(comando, "quit", 4)==0)
            {
                quit(partida);
                return 1;
            }
            else if((sscanf(comando,"[%d,%d][%d,%d]%s", &movimiento->F1, &movimiento->C1, &movimiento->F2, &movimiento->C2))==4)
            {
                terminado=1;
            }
            else
            {
                printf("Error! Comando incorrecto, ingrese nuevamente: ");
            }
    }

  return 0;
}

void menu()
{
    int opcion[2]={0},hayarchivo=0;
    char *nombrearchivo=malloc(sizeof(char)*20);
    tPartida *partida=malloc(sizeof(tPartida));
    tMovimiento *movimiento=malloc((sizeof(tMovimiento)));
    printf("Menu Principal\n1.Juego de dos jugadores\n2.Juego contra computadora\n3.Recuperar un juego grabado\n4.Terminar\n\n");
    printf("Ingrese la opcion: ");
    scanf("%d%c",&opcion[0],&opcion[1]);
    while (opcion[0]<1 || opcion[0]>4 || opcion[1]!='\n')
    {
        BORRA_BUFFER;//problemas
        printf("\nOpcion incorrecta, ingrese opcion valida: ");
        scanf("%d%c",&opcion[0],&opcion[1]);
    }
    switch(opcion[0])
    {
        case(1):printf("Ingrese la dimesion del tablero (Entre 5 y 30): ");
                partida->dim=pedirDim();
                abrirPartida(movimiento,partida);
                dosplayers(movimiento,partida);
                break;
        case(2):printf("Ingrese la dimesion del tablero (Entre 5 y 30): ");
                partida->dim=pedirDim();
                abrirPartida(movimiento,partida);
                dosplayers(movimiento,partida);


                break;
        case(3):
                printf("Ingrese nombre de juego que desea recuperar: ");
                scanf("%s",nombrearchivo);
                BORRA_BUFFER;
                hayarchivo=CargarPartida(nombrearchivo,partida);
                while(hayarchivo==0)
                {
                        printf("No existe el archivo,ingrese otro nombre: ");
                        scanf("%s",nombrearchivo);
                        BORRA_BUFFER;
                        hayarchivo=CargarPartida(nombrearchivo,partida);
                }
                partida->ptsjug1=0;
                partida->ptsjug2=0;
                if(partida->jugadores==0)
                {
                    dosplayers(movimiento,partida);
                }
                break;
        case(4):printf("\n\nSaliendo...Gracias por jugar.\n\n");
                exit(9);
                break;
    }
}

int pedirDim()
{
    int nivel[2]={0};
    scanf("%d%c",&nivel[0],&nivel[1]);
    
    while ( nivel[0]<5 || nivel[0]>30 || nivel[1]!='\n')
    {        
        printf("\nNivel incorrecto, ingrese un nivel valido: ");
        scanf("%d%c",&nivel[0],&nivel[1]);
        BORRA_BUFFER;
    }

    return nivel[0];
}

void quit(tPartida *partida)
{
    char*nombre_partida=malloc(sizeof(char));
    int rta,rta2,error=0,error2=0;
    printf("Esta seguro que quiere salir (Y/N)? ");
    rta=getchar();
    while(error==0)
    {
        if ('Y'==toupper(rta))
        {
            printf("Desea guardar la partida antes de salir (Y/N)? ");
            BORRA_BUFFER;
            error=1;
            rta2=getchar();
            while(error2==0)
            {
                if('Y'==toupper(rta2))
                {
                    printf("Ingrese el nombre del archivo: ");
                    BORRA_BUFFER;
                    error2=1;
                    scanf("%s",nombre_partida);
                    GuardarPartida(nombre_partida,partida);
                    printf("Su partida se guardo exitosmente....gracias por jugar.\n\n");
                    exit(9);

                }
                else if('N'==toupper(rta2))
                {
                    error2=1;
                    printf("Saliendo....gracias por jugar.\n\n");
                    exit(9);
                }
                else
                {
                    BORRA_BUFFER;
                    printf("Ingrese una opcion correcta: ");
                    rta2=getchar();
                }
            }

        }
        else if ('N'==toupper(rta))
        {
            error=1;
            BORRA_BUFFER;
            //ingrese_comando();
        }
        else
        {
            BORRA_BUFFER;
            printf("Ingrese una opcion correcta: ");
            rta=getchar();
        }
    }
}

int main(){
    tPartida partida;
    tMovimiento movimiento;

    /*char* nombrearchivo="matriz1";
    partida.turno=2;
    partida.dim=5;
    partida.tablero=crearMatriz(partida.dim);
    llenarFila(partida.tablero[0], "ABCDE");
    llenarFila(partida.tablero[1], "BA0ED");
    llenarFila(partida.tablero[2], "CAEDE");
    llenarFila(partida.tablero[3], "A0A0C");
    llenarFila(partida.tablero[4], "A0B0C");
    */

    menu();
    ingrese_comando(&movimiento,&partida);
    return 0;
}
