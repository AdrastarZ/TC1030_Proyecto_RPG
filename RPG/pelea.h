#ifndef PELEA_H_
#define PELEA_H_

#include <iostream>
#include "personaje.h"

using namespace std;

class Pelea {
    private:
    int turno;
    bool gameover;
    

    public:
    Pelea():turno(0),gameover(false){}
    Pelea(int _turno, bool death):turno(_turno), gameover(death){}

    int getTurno(){return turno;}
    void setTurno(int turno){ this -> turno = turno;}

    bool getGameOver(){ return gameover;}
    void setGameOver(bool death) { gameover = death;}

    int ejecutarTurno(){}
    int calcularDano(){}
    bool verificaGanador(){}

};

int Pelea::ejecutarTurno(){

}
#endif