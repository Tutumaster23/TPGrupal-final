#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
using namespace std;

void mostrarMenu();
void jugarUnJugador(int &puntajeTotal, string &nombre);
void limpiarPantalla();
void mostrarCreditos();
void tirarDados(int dados[], int cantidad);
void mostrarDados(int dados[], int cantidad, int numLanzamiento);
void contarDados(int dados[], int conteo[]);
void combinaciones(int conteo[], int &puntajeRonda);
void cargarPuntaje (string nombre, int puntajeTotal);
void mostrarPuntaje();

#endif // FUNCIONES_H
