#include <iostream>
#include "menu.h"
#include "pelea.h"

using namespace std;

int main(){
    Menu menu;

    cout << "!!Bienvenido, oh gran guerrero!!" << endl << "Dime, Cual es tu nombre?" << endl << endl;
    menu.creaPeleadores();
    Pelea partida(0 ,false, menu.getJugador(), menu.getEnemigo());
    partida.ejecutarTurno();
    partida.verificaGanador();

    return 0;
}