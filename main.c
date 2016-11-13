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
}tMovimiento;






int main()
{
    tPartida partida;
    tMovimiento movimiento;
    menu();
    ingrese_comando(&movimiento,&partida);
    return 0;
}
