#include <iostream>
#include "funciones.h"
#include <cstdlib>
using namespace std;

/// FUNCION PARA MOSTRAR EL MENU
void mostrarMenu(){
    cout << "----------------------------------------------------------" <<endl;
    cout << "*****************BIENVENIDO A GENERALA*****************"<< endl;
    cout << "----------------------------------------------------------" <<endl;
    cout << "1. Nueva partida (1 jugador)" << endl;
    cout << "2. Nueva partida (2 jugadores)" << endl;
    cout << "3. Ver puntuacion mas alta" << endl;
    cout << "4. Ver creditos" << endl;
    cout << "5. Salir" << endl;
    cout << "----------------------------------------------------------" <<endl;
}
/// FUNCION PARA HACER UNA PAUSA Y LIMPIAR PANTALLA
void limpiarPantalla(){
    system ("pause");
    system ("cls");
}

/// FUNCION PRINCIPAL PARA MODO UN JUGADOR
void jugarUnJugador(int &puntajeTotal, string &nombre, string &maxJugador, int &maxPuntaje){
    cout << "Ingrese su nombre: ";
    cin >> nombre; /// LE PEDIMOS EL NOMBRE Y LO MANDAMOS COMO REFERENCIA

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

                cout << "DESEA TIRAR TODOS? ";
                cin >> respuestaJugador2;

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
        combinaciones(conteo,puntajeRonda); /// MANDO EL CONTEO Y PUNTAJE COMO PARAMETROS, PARA QUE CUENTE Y HAGA LAS COMBINACIONES, PARA QUE TAMBIEN ME AÑADA LOS PUNTOS CORRESPONDIENTES

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

/// FUNCION PARA TIRAR DADOS
void tirarDados(int dados[], int cantidad){
    for (int i=0; i< cantidad; i++){
        dados[i] = (rand()% 6) + 1; /// FOR PARA GENERAR DADOS ALEATORIOS
    }
}
/// FUNCION PARA CONTAR DADOS
void contarDados(int dados[], int conteo[]){
    for ( int i = 0; i < 6; i++){
        conteo [i]=0; /// inicializo el conteo en 0
    }

    for(int i = 0; i<5; i++){
        int valorDado = dados[i];
                                 ///CUENTO LAS VECES QUE SE REPITE UN NUMERO
        conteo[valorDado -1]++;
    }
}

/// FUNCION PARA MOSTRAR DADOS EN PANTALLA
void mostrarDados(int dados[], int cantidad, int numLanzamiento){
    cout << "Lanzamiento " << numLanzamiento << endl;
    cout << "Tus dados: ";

    for(int i = 0; i<cantidad; i++){
        cout << dados[i] << " "; /// FOR PARA RECORRER EL VEC Y MOSTRAR LOS DADOS
    }
    cout << endl;

}

/// FUNCION PARA CALCULAR LAS COMBINACIONES Y DETERMINAR EL PUNTAJE
void combinaciones(int conteo[], int &puntajeRonda){
    bool hayGenerala = false;
    bool hayPoker = false;
    bool hayDos = false;
    bool hayTres = false;
    bool hayEscalera1 = (conteo[0] == 1 && conteo[1] == 1 && conteo[2] == 1 && conteo[3] == 1 && conteo[4] == 1);
    bool hayEscalera2 = (conteo[1] == 1 && conteo[2] == 1 && conteo[3] == 1 && conteo[4] == 1 && conteo[5] == 1);
    /// BOOL PARA DETERMINAR QUE COMBINACION DA TRUE
    for(int i = 0; i<6; i++){
        if (conteo[i]== 5) hayGenerala = true;
        if (conteo[i]== 4) hayPoker = true;
        if (conteo[i]== 2) hayDos = true;
        if (conteo[i]== 3) hayTres = true;
       }
    /// SI DA TRUE ALGUNA COMBINACION SE AÑADE AL PUNTAJE
    if(hayGenerala){
        puntajeRonda += 50;
    } else if(hayPoker){
        puntajeRonda += 40;
    } else if (hayDos && hayTres){
        puntajeRonda += 30;
    } else if (hayEscalera1 || hayEscalera2){
        puntajeRonda += 25;
    } else { /// SI NO HAY COMBINACION POSIBLE, SE UTILIZA LOS JUEGOS DE DADOS
    for(int i = 0; i<6; i++){
        puntajeRonda += conteo[i]*(i+1);
    }
    }
}

/// FUNCION PARA SABER EL PUNTAJE MAS ALTO DE TODAS LAS PARTIDAS JUGADAS
void cargarPuntaje(string nombre, int puntajeTotal, string &maxJugador, int &maxPuntaje){
    if (puntajeTotal > maxPuntaje){
        maxPuntaje = puntajeTotal;
        maxJugador = nombre;
    }
}

/// FUNCION QUE MUESTRA LOS PUNTAJES
void mostrarPuntaje(string maxJugador, int maxPuntaje) {
    cout << "************************* Puntaje ************************" << endl;
    cout << "----------------------------------------------------------" <<endl;
    cout << endl;
    if (maxPuntaje == 0){
        cout << "No hay puntajes actualmente." << endl;
    } else
    cout << "Mejor jugador: " << maxJugador << " con " << maxPuntaje << " Puntos."<<endl;
    cout << endl;
    limpiarPantalla();
}

/// FUNCION QUE MUESTRA LOS CREDITOS
void mostrarCreditos(){
    cout << "************************* CREDITOS ************************" << endl;
    cout << "----------------------------------------------------------" <<endl;
    cout << "PROGRAMACION I - UNIVERSIDAD TECNOLOGICA NACIONAL (FRGP)" << endl;
    cout << "----------------------------------------------------------"<<endl;
    cout << "GRUPO 9" << endl;
    cout << "----------------------------------------------------------"<<endl;
    cout << "INTEGRANTES DEL GRUPO: " << endl;
    cout << "- FRANCISCO CRISTIANI - LEGAJO: " << endl;
    cout << "- FRANCISCO SACKMANN - LEGAJO: " << endl;
    cout << "- FRANCO PACHECO - LEGAJO: " << endl;
    cout << "- RODRIGO GODOY- LEGAJO: " << endl;
}
