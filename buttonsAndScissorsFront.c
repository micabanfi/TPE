#include "buttonsAndScissorsBack.h"

void abrirPartida(tMovimiento *movimiento,tPartida *partida);
void dosplayers(tMovimiento *movimiento,tPartida* partida);
void errores(int a);
void ImprimirTablero(tPartida* partida);
int ingrese_comando(tMovimiento * movimiento, tPartida *partida);
int pedirDim();
void quit(tMovimiento *movimiento,tPartida *partida);
int menu();

void abrirPartida(tMovimiento *movimiento,tPartida *partida)
{
    int resp=2;
    resp=AbrirTablero(partida);
    while (resp==0){
        printf("Archivo no encontrado o corrupto. Intente nuevamente: ");
        partida->dim=pedirDim();
        resp=AbrirTablero(partida);
    }
    partida->ptsjug1=0;
    partida->ptsjug2=0;
}

void dosplayers(tMovimiento *movimiento,tPartida* partida)
{
    int hayplay,botones=0,invmov=0,com=0;

    ImprimirTablero(partida);
    hayplay=HayJugada(partida);
    while(hayplay==0)
    {
        if (partida->jugadores==1 && partida->turno==2)
        {
            MovPc(partida,movimiento);
            com=0;
            printf("\n\n\tLA COMPUTADORA ESTA REALIZANDO SU MOVIMIENTO\n\n");
        }
        else
        {
            com = ingrese_comando(movimiento,partida);
            invmov=InvalidMove(partida,movimiento);

            while (invmov!=0 && com==0)
            {
                errores(invmov);
                com = ingrese_comando(movimiento,partida);
                invmov=InvalidMove(partida,movimiento);
            }
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

        ImprimirTablero(partida);
        hayplay=HayJugada(partida);
        }
    }
    if(partida->turno==1)
        printf("\n\nFELICITACIONES JUGADOR 2! HAS GANADO!!\n\n");
    else
        printf("\n\nFELICITACIONES JUGADOR 1! HAS GANADO!!\n\n");
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
    printf("Botones J1: %d, J2: %d  \n\n\n\t\t",partida->ptsjug1,partida->ptsjug2);

//Graduacion de columnas
    for (int i = 0; i < partida->dim; ++i)
        printf("(%d)\t", i);

//Esquinas superiores
    printf("\n\n\n\n\t/");
    for (int k = 0; k < (partida->dim); ++k)
        printf("\t");
    printf("\t\\\n\n");

    for (int i = 0; i < partida->dim; ++i)
    {
        printf("(%d)\t", i);
        for (int j = 0; j < partida->dim; ++j)
        {
            if (partida->tablero[i][j] == '0')
                printf("\t %c", ' ');
            else
                printf("\t %c", partida->tablero[i][j]);
        }
        if (i < partida->dim-1)
            printf("\n\n\n");
        printf("\n");
    }

//Esquinas inferiores
    printf("\n\t\\");
    for (int k = 0; k < (partida->dim); ++k)
        printf("\t");
    printf("\t/\n\n");
    
    printf("Turno jugador %d \n",partida->turno);
}

int ingrese_comando(tMovimiento * movimiento, tPartida *partida)
{
    //ver por longitud cuando pongo el nombre
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

            if(strncmp(comando, "save ", 5)==0 && comando[5]!=0)
            {
                sscanf(comando,"save %s",nombre_partida);
                if (GuardarPartida(nombre_partida,partida))
                    printf("\nLa partida se guardo exitosamente!\n");
                else
                    printf("Por favor no utilize ese nombre. Intente con otro que no sea AxA.\n");
                return 1;
            }
            else if (strncmp(comando, "quit", 4)==0 && comando[4]==0)
            {
                quit(movimiento, partida);
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

int pedirDim()
{
    int nivel=0;
    char nivel2;
    scanf("%d%c",&nivel,&nivel2);
    while ( nivel< 5 || nivel>30 || isdigit(nivel)!=0 || isspace(nivel2)==0)
    {
      printf("Nivel inexistente, ingrese un nivel valido (Entre 5 y 30): ");
      scanf("%d%c",&nivel,&nivel2);
      BORRA_BUFFER;
    }

    return nivel;
}

void quit(tMovimiento *movimiento,tPartida *partida)
{
    char*nombre_partida=malloc(sizeof(char));
    int error=0,error2=0;
    char c,d;
    printf("Esta seguro que quiere salir? (Y/N): ");
    while(error==0)
    {

        c=getchar();
        d=getchar();

        if ('Y'==toupper(c) && '\n'==d)
        {
            printf("Desea guardar la partida antes de salir? (Y/N): ");
            error=1;
            while(error2==0)
            {

                c=getchar();
                d=getchar();
                if('Y'==toupper(c) && '\n'==d)
                {
                    printf("Ingrese el nombre del archivo: ");
                    error2=1;
                    scanf("%s",nombre_partida);
                    if (GuardarPartida(nombre_partida,partida))
                    {
                        printf("\nSu partida se guardo exitosamente.... Gracias por jugar!\n\n");
                        exit(9);
                    }
                    else
                        printf("Por favor no utilize ese nombre. Intente con otro que no sea AxA.\n");
                }
                else if('N'==toupper(c) && '\n'==d)
                {
                    error2=1;
                    printf("\nSaliendo.... Gracias por jugar!\n\n");
                    exit(9);
                }
                else
                {
                    BORRA_BUFFER;
                    printf("Ingrese una opcion correcta (Y/N): ");
                }
            }

        }
        else if ('N'==toupper(c) && '\n'==d)
        {
            error=1;
            ingrese_comando(movimiento,partida);
        }
        else
        {
            BORRA_BUFFER;
            printf("Ingrese una opcion correcta (Y/N): ");

        }
    }
}

int menu()
{
    int opcion[2]={0},hayarchivo=0;
    char *nombrearchivo=malloc(sizeof(char)*20);
    tPartida *partida=malloc(sizeof(tPartida));
    tMovimiento *movimiento=malloc((sizeof(tMovimiento)));
    printf("Menu Principal\n1.Juego de dos jugadores\n2.Juego contra computadora\n3.Recuperar un juego grabado\n4.Terminar\n\n");
    printf("Ingrese la opcion: ");
    scanf("%d%c", &opcion[0], &opcion[1]);
    while (opcion[0]<1 || opcion[0]>4 || opcion[1]!='\n')
    {
        BORRA_BUFFER;
        printf("\nOpcion incorrecta, ingrese opcion valida: ");
        scanf("%d%c", &opcion[0], &opcion[1]);
    }
    switch(opcion[0])
    {
        case(1):partida->jugadores=0;
                partida->turno=aleatorio(1, 2);
                printf("Ingrese la dimesion del tablero (Entre 5 y 30): ");
                partida->dim=pedirDim();
                abrirPartida(movimiento, partida);
                dosplayers(movimiento, partida);
                break;
        case(2):partida->jugadores=1;
                partida->turno=aleatorio(1,2);
                printf("Ingrese la dimesion del tablero (Entre 5 y 30): ");
                partida->dim=pedirDim();
                abrirPartida(movimiento,partida);
                dosplayers(movimiento, partida);


                break;
        case(3):
                printf("Ingrese el nombre del juego que desea cargar: ");
                scanf("%s",nombrearchivo);
                BORRA_BUFFER;
                hayarchivo=CargarPartida(nombrearchivo,partida);
                while(hayarchivo==0)
                {
                        printf("No existe el archivo! Ingrese otro nombre: ");
                        scanf("%s",nombrearchivo);
                        BORRA_BUFFER;
                        hayarchivo=CargarPartida(nombrearchivo,partida);
                }
                partida->ptsjug1=0;
                partida->ptsjug2=0;
                dosplayers(movimiento,partida);

                break;
        case(4):printf("\n\nSaliendo... Gracias por jugar!\n\n");
                exit(9);
                break;
    }
    return 0;
}
