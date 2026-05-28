#ifndef PELEA_H_
#define PELEA_H_

#include <iostream>
#include "personaje.h"
#include "menu.h"

using namespace std;

class Pelea {
    private:
    int turno;
    bool gameover;
    Personaje *jugadorPrincipal;
    Personaje *enemigoPrincipal;    

    public:
    Pelea():turno(0),gameover(false){}
    Pelea(int _turno, bool death, Personaje *_jugadorPrincipal, Personaje* _enemigoPrincipal ):turno(_turno), gameover(death), jugadorPrincipal(_jugadorPrincipal), enemigoPrincipal(_enemigoPrincipal){}

    int getTurno(){return turno;}
    void setTurno(int turno){ this -> turno = turno;}

    bool getGameOver(){ return gameover;}
    void setGameOver(bool death) { gameover = death;}

    void ejecutarTurno();
    void verificaGanador();

};

void Pelea::ejecutarTurno(){

    while (gameover == false)
    {
        //Guarda las defensas originales del enemigo y jugador para restaurarlas en caso hacer bloqueo
        double tempDifJugador = jugadorPrincipal -> getDefensa();
        double tempDifEnemigo = enemigoPrincipal -> getDefensa();
        int probabilidad = enemigoPrincipal ->probAtaque();

        turno++;
        cout << endl << "Turno: " << turno  << endl << endl;

        Menu menu;
        int accion =  menu.seleccionarAccion();

        switch (accion)
        {
            case 1:
                enemigoPrincipal ->recibirDano(jugadorPrincipal->dano());
                cout << jugadorPrincipal->getNombre() << " ataco y " << enemigoPrincipal->getNombre() << " recibio daño" << endl;
                break;
            
            case 2:
                jugadorPrincipal -> bloqueo();
                cout << "La defensa de " << jugadorPrincipal->getNombre() << " incremento un 50%" << endl << "Defensa actual: " << jugadorPrincipal ->getDefensa() << endl;
                break;
            case 3: 
                jugadorPrincipal -> accionEspecial();
                cout << jugadorPrincipal->getNombre() << " se a curado 30 puntos de salud" << endl << "Salud actual: "  << jugadorPrincipal -> getVida() << endl;
                break;
            default:
                break;
        }

        if(jugadorPrincipal -> getVida() == 0 || enemigoPrincipal ->getVida() == 0){
            gameover = true;
            cout << "Fin de la partida";
        }

        switch (probabilidad)
        {
        case 1:
            jugadorPrincipal ->recibirDano(enemigoPrincipal->dano());
            cout << enemigoPrincipal->getNombre() << " ataco y " << jugadorPrincipal->getNombre() << " recibio daño" << endl;
            break;

        case 2:
            cout << enemigoPrincipal -> getNombre() << " decidio bloquear." << endl;
            enemigoPrincipal -> bloqueo();
            cout << "La defensa de " << enemigoPrincipal->getNombre() << " incremento un 50%" << endl << "Defensa actual del enemigo: " << enemigoPrincipal ->getDefensa() << endl;
            break;

        case 3: 
            jugadorPrincipal -> recibirDano(enemigoPrincipal -> accionEspecial());
            cout <<enemigoPrincipal->getNombre() << " activo su ataque especial 'Rayo Cosmico' " << endl << "Puntos de vida restantes: "  << jugadorPrincipal -> getVida() << endl;
            break;

            default:
                break;
        } 

        jugadorPrincipal -> setDefensa(tempDifJugador);
        enemigoPrincipal -> setDefensa(tempDifEnemigo);

        cout << "Resumen del  turno " << turno << endl; 
        cout << "PV restantes de " << jugadorPrincipal->getNombre() << ": " << jugadorPrincipal ->getVida() << endl;
        cout << "PV restantes de " << enemigoPrincipal->getNombre() << ": " << enemigoPrincipal ->getVida() << endl;

        if(jugadorPrincipal -> getVida() == 0 || enemigoPrincipal ->getVida() == 0){
            gameover = true;
            cout << "Fin de la partida";
        }
    }
}

void Pelea::verificaGanador(){
    if(jugadorPrincipal -> getVida() == 0){
        cout << "Parece que no has podido derrotar a " << enemigoPrincipal->getNombre() << " :(" << endl << "Suerte la proxima vez";
    }
    else if(enemigoPrincipal -> getVida() == 0){
        cout << "Has conseguido derrotar a " << enemigoPrincipal->getNombre() << endl << "!! Felicidades " << jugadorPrincipal -> getNombre() << " !!";
    }
}
#endif
