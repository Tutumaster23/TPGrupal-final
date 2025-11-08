#include <iostream>
#include "funciones.h"
#include <cstdlib>
using namespace std;

/// Puntaje maximo y nombre en 0
string maxJugador = "";
int maxPuntaje = 0;

///funcion que muestra el menu
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

void limpiarPantalla(){
    system ("pause");
    system ("cls");
}

///jugar un jugador
void jugarUnJugador(int &puntajeTotal,string &nombre){
    cout << "Ingrese su nombre: ";
    cin >> nombre;

    int cantDados = 5;
    int dados[cantDados];

    //bucle rondas
    for(int ronda = 1; ronda <=1; ronda++){

        //mostramos info
        cout << "----------------------------------------------------------" <<endl;
        cout << "Turno de: " << nombre << " | Ronda : " << ronda << " | Puntaje total: " << puntajeTotal << " PTS." << endl;

        int numeroLanzamiento = 1;
        bool jugadorPlantado = false;
        char respuestaJugador;

        //mientras el lanzamiento < 3 y el jugador no este plantado
        while(numeroLanzamiento <= 3 && !jugadorPlantado){

            if(numeroLanzamiento == 1){
                tirarDados(dados, cantDados);
                mostrarDados(dados, cantDados, 1);
            } else {
                cout << "CONTINUAR LANZANDO? (S/N)";
                cin >> respuestaJugador;

                if(respuestaJugador == 'S' || respuestaJugador == 's'){
                    int cantidadARelanzar;
                    cout << "CUANTOS DADOS VOLVES A TIRAR?: ";
                    cin >> cantidadARelanzar;

                    for (int i=0; i< cantidadARelanzar; i++){
                        int posicionDado;
                        cout << "CUAL DADO?: ";
                        cin >> posicionDado;

                        int indice = posicionDado - 1;

                        if(indice >= 0 && indice < cantDados){
                            dados[indice] = 1+ (rand()% 6);
                        }
                    }

                    mostrarDados(dados, cantDados, numeroLanzamiento);

                } else{
                    //si la respuesta es N
                    jugadorPlantado = true;
                }
            }
            if(!jugadorPlantado) {
                numeroLanzamiento++;
            }
        }
        ///logica del puntaje
        int conteo[6];
        contarDados(dados, conteo);

        int puntajeRonda = 0;
        combinaciones(conteo,puntajeRonda);

        cout << "----------------------------------------------------------" <<endl;
        cout << "FIN DE LOS LANZAMIENTOS" << endl;
        cout << "PUNTAJE DE LA RONDA: " << puntajeRonda << " PTS." << endl;
        puntajeTotal += puntajeRonda;

        cout << "Presiona 'c' y luego enter para continuar" << endl;

        char pausa;
        cin >> pausa; // para frenar el programa espera un input
        system("cls");
    }

    //fin de juego
    cout << "----------------------------------------------------------" <<endl;
    cout << "FIN DEL JUEGO"<< endl;
    cout << "Puntaje final de "<< nombre << ": " << puntajeTotal << " PTS" << endl;
    cargarPuntaje(nombre, puntajeTotal);

    limpiarPantalla();
}

///funcion para tirar dados
void tirarDados(int dados[], int cantidad){
    for (int i=0; i< cantidad; i++){
        dados[i] = 1+ (rand()% 6); //con modulo el resultado siempre es entre 0 y 5, se suma uno para q quiede entre 0 y 6
    }
}

void contarDados(int dados[], int conteo[]){
    for ( int i = 0; i < 6; i++){
        conteo [i]=0;
    }

    //recorrer los 5 dados
    for(int i = 0; i<5; i++){
        int valorDado = dados[i];

        conteo[valorDado -1]++;
    }
}

///funcion para mostrar los 5 dados
void mostrarDados(int dados[], int cantidad, int numLanzamiento){
    cout << "Lanzamiento " << numLanzamiento << endl;
    cout << "Tus dados: ";

    for(int i = 0; i<cantidad; i++){
        cout << dados[i] << " ";
    }
    cout << endl;

}

/// funcion para calcular las combinaciones y determinar puntaje de ronda
void combinaciones(int conteo[], int &puntajeRonda){
    bool hayGenerala = false;
    bool hayPoker = false;
    bool hayDos = false;
    bool hayTres = false;
    bool hayEscalera1 = (conteo[0] == 1 && conteo[1] == 1 && conteo[2] == 1 && conteo[3] == 1 && conteo[4] == 1);
    bool hayEscalera2 = (conteo[1] == 1 && conteo[2] == 1 && conteo[3] == 1 && conteo[4] == 1 && conteo[5] == 1);
    // Se utilizan booleanos para determinar que combinacion se alcanzo
    for(int i = 0; i<6; i++){
        if (conteo[i]== 5) hayGenerala = true;
        if (conteo[i]== 4) hayPoker = true;
        if (conteo[i]== 2) hayDos = true;
        if (conteo[i]== 3) hayTres = true;
       }
    // Si se alcanza una de las combinaciones se añade al puntaje
    if(hayGenerala){
        puntajeRonda += 50;
    } else if(hayPoker){
        puntajeRonda += 40;
    } else if (hayDos && hayTres){
        puntajeRonda += 30;
    } else if (hayEscalera1 || hayEscalera2){
        puntajeRonda += 25;
    } else { // Si no se da ninguna combinacion se utiliza los juegos de dados
    for(int i = 0; i<6; i++){
        puntajeRonda += conteo[i]*(i+1);
    }
    }
}

/// funcion para determinar cual es el puntaje mas alto de todas las partidas jugadas al momento
void cargarPuntaje(string nombre, int puntajeTotal){
    if (puntajeTotal > maxPuntaje){
        maxPuntaje = puntajeTotal;
        maxJugador = nombre;
    }

}

/// funcion que muestra los puntajes y si no hay informa
void mostrarPuntaje() {
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

///funcion que muestra los creditos, nombre apellido y legajo
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


