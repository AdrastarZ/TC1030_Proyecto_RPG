/*
 * Proyecto RPG main
 * Axel Daniel Ramírez Silva
 * A01704206
 * 11/06/2026
 *
 * La clase pelea se encarga de la interacción entre ambas clases hija ya una vez creadas 
 * a traves de la ejecución de turno, los turnos del jugador ejecutados mediante las acciones 
 * del usuario, las del enemigo ocurren de manera automatica. Cuando la vida de alguno de los 2
 * llega a 0 se termina la pelea y se anuncia al ganador
 */

#ifndef PELEA_H_
#define PELEA_H_

#include <iostream>

//Bibliotecas utilizadas para contar el tiempo
#include <chrono> 
#include <thread>

#include "personaje.h" //Biblioteca con objetos de mi proyecto

using namespace std;

//Declaración de la clase Pelea
class Pelea {

    // Declaración de atributos privados
    private:
    int turno;

    // Se declaran punteros de las clases hijas para guardar mismo espacio de memoria que las declaradas en menu
    Personaje *jugadorPrincipal;
    Personaje *enemigoPrincipal;    

    // Declaración de metodos públicos
    public:
    Pelea():turno(0), jugadorPrincipal(nullptr), enemigoPrincipal(nullptr){}
    Pelea(int _turno, Personaje *_jugadorPrincipal, Personaje* _enemigoPrincipal ):turno(_turno), jugadorPrincipal(_jugadorPrincipal), enemigoPrincipal(_enemigoPrincipal){}

    int getTurno(){return turno;}
    void setTurno(int turno){ this -> turno = turno;}

    void ejecutarTurno();
    void verificaGanador();

    int seleccionarAccion(int contador);

};


/**
 * ejecutarTurno
 *
 * Cada turno el Jugador y Enemigo hacen una acción de las 3 que tienen disponibles cada uno, 
 * la consola se encarga de mostrar lo que pasa en cada fase del turno (Turno del Jugador - Turno del Enemigo - Resumen de Turno), 
 * cada fin de turno muestra la vida actual de cada uno
 * 
 * Aqui se aplican los metodos de ataque, bloqueo, especial y recibirDano de Jugador y Enemigo
 * 
 * Entre cada fase de turno hay un temporizador para permitir leer al usuario los sucesos del turno de forma mas fluida
 * 
 * Si la vida de cualquiera de los 2 llega a 0 se termina la partida independientemente si paso el turno de los dos o no
 * 
 */

void Pelea::ejecutarTurno(){
    string nomJugador = jugadorPrincipal->getNombre();
    string nomEnemigo = enemigoPrincipal->getNombre();

    //Guarda las defensas originales del enemigo y jugador para restaurarlas en caso de hacer bloqueo
    //De no hacerlo la defensa aumenta constantemente cada vez que se seleccione la acción
    double tempDifJugador = jugadorPrincipal -> getDefensa();
    double tempDifEnemigo = enemigoPrincipal -> getDefensa();


    do
    { 
        int probabilidad = enemigoPrincipal ->elegirAccion();

        turno++;
        cout << endl << "------------------- Turno: " << turno << " ------------------- " << endl << endl;

        

        cout << "------------------- Turno de " << nomJugador << " -------------------" << endl;

        int accion = jugadorPrincipal -> elegirAccion();

        switch (accion)
        {
            case 1:
                enemigoPrincipal ->recibirDano(jugadorPrincipal->dano());
                cout << nomJugador << " ataco y " << nomEnemigo << " recibio dano" << endl << endl;
                break;
            
            case 2:
                jugadorPrincipal -> bloqueo();
                cout << endl << "La defensa de " << nomJugador << " incremento un 50%" << endl << "Defensa actual: " << jugadorPrincipal ->getDefensa() << endl << endl;
                break;
            case 3: 
                jugadorPrincipal -> accionEspecial();
                cout << nomJugador << " se a curado 30 puntos de salud" << endl << "Salud actual: "  << jugadorPrincipal -> getVida() << endl << endl;
                break;

            default:
                break;
        }

        this_thread::sleep_for(chrono::seconds(4));

        if(jugadorPrincipal -> getVida() == 0 || enemigoPrincipal ->getVida() == 0){
            break;
        }

        cout << "------------------- Turno de " << enemigoPrincipal -> getNombre() << " -------------------" << endl << endl;
        if(turno != 1){
            cout << "La defensa de " << nomEnemigo << " fue restaurada a: " << tempDifEnemigo << endl << endl;
            enemigoPrincipal -> setDefensa(tempDifEnemigo);
        }
        
        switch (probabilidad)
        {
        case 1:
            jugadorPrincipal ->recibirDano(enemigoPrincipal->dano());
            cout << nomEnemigo << " ataco y " << nomJugador << " recibio dano"<< endl << endl;
            break;

        case 2:
            cout << nomEnemigo << " decidio bloquear." << endl;
            enemigoPrincipal -> bloqueo();
            cout << endl << "La defensa de " << nomEnemigo << " incremento un 50%" << endl << "Defensa actual del enemigo: " << enemigoPrincipal ->getDefensa() << endl << endl;
            break;

        case 3: 
            jugadorPrincipal -> recibirDano(enemigoPrincipal -> accionEspecial());
            cout <<nomEnemigo << " activo su ataque especial 'Rayo Cosmico' y " << nomJugador << " recibio dano"<< endl << endl;
            break;

            default:
                break;
        } 
        
        cout << "La defensa de " << nomJugador << " fue restaurada a: " << tempDifJugador << endl;
        jugadorPrincipal -> setDefensa(tempDifJugador);
        
        
        this_thread::sleep_for(chrono::seconds(4));

        cout << endl << "------------------- Fin del turno: " << turno << " ------------------- " << endl << endl;
        cout << "PV restantes de " << nomJugador << ": " << jugadorPrincipal ->getVida() << endl;
        cout << "PV restantes de " << nomEnemigo << ": " << enemigoPrincipal ->getVida() << endl;

        this_thread::sleep_for(chrono::seconds(4));

        if(jugadorPrincipal -> getVida() == 0 || enemigoPrincipal ->getVida() == 0){
            break;
        }

    } while (jugadorPrincipal -> getVida() > 0 && enemigoPrincipal ->getVida() > 0);

    cout << endl << "------------------- Fin de la partida ------------------- " << endl << endl;
    cout << "PV restantes de " << nomJugador << ": " << jugadorPrincipal ->getVida() << endl;
    cout << "PV restantes de " << nomEnemigo << ": " << enemigoPrincipal ->getVida() << endl;
    
        
    }

/**
 * verificaGanador
 *
 * Una vez terminada la partida verifica quien de los dos fue el que termino con 0 puntos de vida y manda un mensaje dependiendo del resultado
 */

void Pelea::verificaGanador(){
    if(jugadorPrincipal -> getVida() == 0){
        cout << endl << "Parece que no has podido derrotar a " << enemigoPrincipal->getNombre() << " :(" << endl << "Suerte la proxima vez";
    }
    else if(enemigoPrincipal -> getVida() == 0){
        cout << endl << "Has conseguido derrotar a " << enemigoPrincipal->getNombre() << endl << "!! Felicidades " << jugadorPrincipal -> getNombre() << " !!";
    }
}
#endif
