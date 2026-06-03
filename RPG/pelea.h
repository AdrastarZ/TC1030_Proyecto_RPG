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
    Jugador *jugadorPrincipal;
    Enemigo *enemigoPrincipal;    

    // Declaración de metodos públicos
    public:
    Pelea():turno(0){}
    Pelea(int _turno, Jugador *_jugadorPrincipal, Enemigo* _enemigoPrincipal ):turno(_turno), jugadorPrincipal(_jugadorPrincipal), enemigoPrincipal(_enemigoPrincipal){}

    int getTurno(){return turno;}
    void setTurno(int turno){ this -> turno = turno;}

    void ejecutarTurno();
    void verificaGanador();

    int seleccionarAccion(int contador);

};

/**
 * seleccionarAccion
 * 
 * Durante el turno del jugador se le permite seleccionar 1 de 3 acciones y devuelve un número acordea a esa acción seleccionada
 * 
 * Si la opción que selecciono no es valida pide de nuevo una entrada de dato
 */

int Pelea::seleccionarAccion(int contador){
    string opcion = "";
    do
    { 
        cout << endl << "Que vas a hacer?" << endl << "1. Atacar: 10'%' de probabilidad de golpe critico" << endl << 
        "2. Bloquear: Aumenta en un 50'%' tu defensa por 1 turno" << endl << 
        "3. Curarse: Cura 30 puntos de salud, no excede salud maxima de 100, limite de 3 curaciones " 
        << endl << "Presiona una tecla numerica del 1 al 3 para seleccionar tu accion: ";

        getline(cin, opcion);
        cout << endl;

        if(opcion == "1") {cout << "Haz decidido atacar: "; return 1;}
        else if(opcion == "2") {cout << "Haz decidido defenderte: "; return 2;}
        else if(opcion == "3") {cout << "Haz decidido curarte: "; return 3;}
        else{cout << endl << "La accion que seleccionaste no es valida. Intente de nuevo" << endl; opcion = "";}

    } while (opcion != "1" && opcion != "2" && opcion != "3");
    return 0;
}

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

    int contador = 1; //Se utiliza para contar el numero de usos que lleva la acción curación
    bool confirmarSanacion;

    do
    {
        int accion;
        confirmarSanacion = false;
        Pelea partida;

        
        int probabilidad = enemigoPrincipal ->probAtaque();

        turno++;
        cout << endl << "------------------- Turno: " << turno << " ------------------- " << endl << endl;

        

        cout << "------------------- Turno de " << nomJugador << " -------------------" << endl;

        // Se implemento esta sección para evitar que el Jugador utilice constantemente la acción de curación
        // Obligandolo a ser mas estrategico
        do
        {
            accion = partida.seleccionarAccion(contador);
            if(accion == 3 && contador > 3){
                cout << "!! Te quedaste sin fuerzas para curarte !!" << endl << "\t\t\t Realiza otra accion" <<endl;
            }
            else if(accion == 3 && contador <= 3 ) { contador ++; confirmarSanacion = true;}
            else{
                confirmarSanacion = true;
            }
        } while (!confirmarSanacion);
        
        

        switch (accion)
        {
            case 1:
                enemigoPrincipal ->recibirDano(jugadorPrincipal->dano());
                cout << nomJugador << " ataco y " << nomEnemigo << " recibio dano" << endl << endl;
                break;
            
            case 2:
                jugadorPrincipal -> bloqueo();
                cout << "La defensa de " << nomJugador << " incremento un 50%" << endl << "Defensa actual: " << jugadorPrincipal ->getDefensa() << endl << endl;
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
            cout << "La defensa de " << nomEnemigo << " incremento un 50%" << endl << "Defensa actual del enemigo: " << enemigoPrincipal ->getDefensa() << endl << endl;
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
