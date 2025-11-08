#include <iostream>
#include "funciones.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(NULL)); ///PARA QUE RAND GENERE NUMEROS ALEATORIOS TODAS LAS PARTIDAS

    int opcion;

    ///MOSTRAR MENU
    do{
        mostrarMenu();
        cout << "SELECCIONE UNA OPCION: " << endl;
        cin >> opcion;
        system ("cls");
        switch(opcion){
    case 1: {
        //NUEVA PARTIDA(1 JUGADOR)
        system ("cls");
        // se declara el puntaje total y nombre en 0 para resetear la ronda
        int puntajeTotal = 0;
        string nombre = "";
        jugarUnJugador(puntajeTotal, nombre);
        break;
    }
    case 2:
        //NUEVA PARTIDA(2 JUGADORES)
        break;
    case 3:
        //VER PUNTUACION MAS ALTA
        mostrarPuntaje();
        break;
    case 4:
        //VER CREDITOS
        mostrarCreditos();
        break;
    case 5:
        //SALIR
        cout << "Saliendo del juego..." << endl;
        break;
    default:
        //OPCION NO VALIDA
        cout << "Opcion no valida, intentalo de nuevo" << endl;

        break;
        }
    }while(opcion!=5);






    return 0;
}
