/*
 * Proyecto RPG main
 * Axel Daniel Ramírez Silva
 * A01704206
 * 11/06/2026
 *
 * Este es un proyecto que busca crear una simulación simple del genero de 
 * videjuegos Turn Based Role Playing Game (TBRPG) 1 contra 1. 
 * Cuenta con multiples niveles de dificultad que modifica las estadisticas 
 * de las acciones del enemigo, cada acción hecha por el enemigo 
 * tiene una probabilidad de ocurrir. El Jugador (tu), cuenta con 3 acciones diferentes, 
 * atacar, defender y curarse. Tanto el enemigo como el jugador ocupa una acción por turno.
 * El juego termina una vez que la vida de alguno de los dos miembros llegue a 0
 */

#include <iostream>

//Biblioteca con objetos de mi proyecto
#include "menu.h"
#include "pelea.h"

using namespace std;


int main(){

    Menu menu;

    cout << endl << "!!Bienvenido, oh gran guerrero!!" << endl << "Dime, Cual es tu nombre?" << endl << endl;
    menu.creaPeleadores();
    Pelea partida(0, menu.getJugador(), menu.getEnemigo());
    partida.ejecutarTurno();
    partida.verificaGanador();

    return 0;
}
