#include <iostream>
#include "funciones.h"
#include "funciones2.h"
#include <cstdlib>
using namespace std;
/// FUNCION PRINCIPAL DEL MODO DOS JUGADORES
void jugarDosJugadores(string &maxJugador, int &maxPuntaje) {
    int puntajeJ1 = 0, puntajeJ2 = 0; /// INICIALIZO LAS VARIABLES DE PUNTAJE EN CERO Y DE NOMBRE
    string nombreJ1, nombreJ2;

    /// PIDO LOS DOS NOMBRES
    cout << "Ingrese nombre del Jugador 1: ";
    cin >> nombreJ1;
    cout << "Ingrese nombre del Jugador 2: ";
    cin >> nombreJ2;

    /// FUNCION COPIADA DEL MODO UN JUGADOR
    jugarUnJugador2(puntajeJ1, nombreJ1, maxJugador, maxPuntaje);
    jugarUnJugador2(puntajeJ2, nombreJ2, maxJugador, maxPuntaje);

    /// COMPARACION PARA VER QUIEN GANO
    cout << "----------------------------------------------------------\n";
    cout << "RESULTADOS FINALES:\n";
    cout << nombreJ1 << ": " << puntajeJ1 << " PTS\n";
    cout << nombreJ2 << ": " << puntajeJ2 << " PTS\n";

    if (puntajeJ1 > puntajeJ2)
        cout << "GANADOR: " << nombreJ1;
    else if (puntajeJ2 > puntajeJ1)
        cout << "GANADOR: " << nombreJ2;
    else {
        cout << "EMPATE!! SE DEFINE POR SUERTE";

        bool empate = true;

        while(empate) {
            int dado1 = 1 + rand() % 6;
            int dado2 = 1 + rand() % 6;

            cout << nombreJ1 << " tira un " << dado1 << endl;
            cout << nombreJ2 << " tira un " << dado2 << endl;

            if (dado1 > dado2) {
                cout << "¡Gana " << nombreJ1 << "! La suerte es loca." << endl;

                empate = false;
            }
            else if (dado2 > dado1) {
                cout << "¡Gana " << nombreJ2 << "! La suerte es loca." << endl;

                empate = false;
            }
            else {
                cout << "¡Empate otra vez! Tiran de nuevo..." << endl;
            }
        }
    }
    cout << "----------------------------------------------------------\n";
    limpiarPantalla();
}

/// FUNCION DE MODO UN JUGADOR PARA DOS JUGADORES
void jugarUnJugador2(int &puntajeTotal, string &nombre, string &maxJugador, int &maxPuntaje){

    int cantDados = 5; /// VARIABLE PARA CANT. DE DADOS
    int dados[cantDados]; /// VEC CON EL TAMAÑO DE LOS DADOS QUE NECESITAMOS

    /// FOR PARA LA CANT. DE RONDAS
    for(int ronda = 1; ronda <=10; ronda++){

        /// INFO VISIBLE PARA EL USUARIO
        cout << "----------------------------------------------------------" <<endl;
        cout << "Turno de: " << nombre << " | Ronda : " << ronda << " | Puntaje total: " << puntajeTotal << " PTS." << endl;

        int numeroLanzamiento = 1; /// VARIABLE PARA GUARDAR QUE LANZAMIENTOS ES
        bool jugadorPlantado = false;
        char respuestaJugador, respuestaJugador2;

        /// MIENTRAS EL LANZAMIENTO SEA < 3 Y EL JUGADOR NO ESTE PLANTADO SIGUE
        while(numeroLanzamiento <= 3 && !jugadorPlantado){
        /// SI ES 1 SE TIRAM DADOS Y SE MUESTRAM
            if(numeroLanzamiento == 1){
                tirarDados(dados, cantDados);
                mostrarDados(dados, cantDados, 1);
            } else {
                cout << "CONTINUAR LANZANDO? (S/N)";
                cin >> respuestaJugador; /// PREGUNTO SI QUIERE SEGUIR TIRANDO ALGUN DADO

                 if (!(respuestaJugador == 'N' || respuestaJugador2 == 'n')) {
                cout << "DESEA TIRAR TODOS? ";
                cin >> respuestaJugador2;
                }

                if (respuestaJugador2 == 'S' || respuestaJugador2 == 's' ) {
                tirarDados(dados, cantDados);
                mostrarDados(dados, cantDados, 1);
                }

                if(respuestaJugador == 'S' || respuestaJugador == 's' && (!(respuestaJugador2 == 'S' || respuestaJugador2 == 's' ))){
                    int cantidadARelanzar;
                    cout << "CUANTOS DADOS VOLVES A TIRAR?: ";
                    cin >> cantidadARelanzar; /// PIDO CUANTOS QUIERE TIRAR

                    for (int i=0; i < cantidadARelanzar; i++){
                        int posicionDado;
                        cout << "CUAL DADO?: ";
                        cin >> posicionDado; /// PREGUNTO CUAL DE TODOS

                        int indice = posicionDado - 1; /// HAGO UN -1, PQ EL VEC VA DE 0 A 4

                        if(indice >= 0 && indice < cantDados){ /// SI LA POSICION ES IGUAL O MAYOR A CERO Y MENOR A CANTDADOS (QUE ES IGUAL A 5)
                            dados[indice] = 1+ (rand()% 6); /// SE GENERA UN DADO ALETORIO NUEVO
                        }
                    }

                    mostrarDados(dados, cantDados, numeroLanzamiento); /// MUESTRO LOS NUEVOS DADOS

                } else{
                    /// SI LA RESPUES ES N, CERRAMOS EL CICLO
                    jugadorPlantado = true;
                }
            }
            if(!jugadorPlantado) {
                numeroLanzamiento++; /// CONT++ PARA QUE NO SE PASE DE LOS 3 PERMITIDOS
            }
        }
        /// LOGICA DEL PUNTAJE
        int conteo[6];
        contarDados(dados, conteo); /// LLAMO LA FUNCION CONTAR DADOS, PARA CONTAR LOS DADOS RECIBIDOS

        int puntajeRonda = 0; /// INICIALIZO LA VARIBLE EN CERO
        combinaciones(conteo,puntajeRonda,numeroLanzamiento); /// MANDO EL CONTEO Y PUNTAJE COMO PARAMETROS, PARA QUE CUENTE Y HAGA LAS COMBINACIONES, PARA QUE TAMBIEN ME AÑADA LOS PUNTOS CORRESPONDIENTES

        cout << "----------------------------------------------------------" <<endl;
        cout << "FIN DE LOS LANZAMIENTOS" << endl;
        cout << "PUNTAJE DE LA RONDA: " << puntajeRonda << " PTS." << endl;
        puntajeTotal += puntajeRonda; /// GUARDO EL PUNTAJE TOTAL EN UNA VARIBLE, ASI LO DEVUELVO COMO REFERENCIA

        cout << "Presiona 'c' y luego enter para continuar" << endl;

        char pausa;
        cin >> pausa; /// INPUT PARA VOLVER A JUGAR, SIN TENER QUE CERRAR EL PROGRAMA
        system("cls");
    }

    /// FIN DEL JUEGO
    cout << "----------------------------------------------------------" <<endl;
    cout << "FIN DEL JUEGO"<< endl;
    cout << "Puntaje final de "<< nombre << ": " << puntajeTotal << " PTS" << endl;
    cargarPuntaje(nombre, puntajeTotal, maxJugador, maxPuntaje); /// CARGO EL PUNTAJE PARA VER SI ES EL MAS ALTO Y GAURDARLO JUNTO CON EL NOMBRE

    limpiarPantalla();
}
