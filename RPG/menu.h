#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <random>
#include <cctype>
#include "personaje.h"



using namespace std;

class Menu{
    private:
    int dificultad;
    Personaje *jugador;
    Personaje *enemigo;

    public:

    Menu(){}
    ~Menu(){ delete jugador; delete enemigo;}

    void setDificultad(int diff){ dificultad = diff;}
    int getDificultad(){ return dificultad;}

    Personaje *getJugador(){return jugador;}
    Personaje *getEnemigo(){return enemigo;}

    string darNombres();
    int seleccionarDiff();
    void creaPeleadores();
    int seleccionarAccion();

};

string Menu::darNombres(){
    string nombre = "";
    char respuesta;
    do
    {
        cout << "El nombre no puede contener numeros, espacios o caracteres especiales" << endl;
        cout << "El nombre no puede tener mas de 10 caracteres" << endl;
        do
        {
            getline(cin, nombre);
            cout << endl;

            if(nombre.length() > 10){
                cout << "!!! El nombre no puede contener mas de 10 caracteres !!!" << endl << "Intenta de nuevo" << endl;
                nombre = "";
            }

            else if(nombre.length() == 0){
                cout << "!!! El nombre debe contener por lo menos 1 caracter !!!" << endl << "Intenta de nuevo" << endl;
                nombre = "";
            }

            else if (nombre.length()<10) {
                for(int i = 0; i <nombre.length(); i++){
                    if(!isalpha(nombre[i])){
                        cout << "El nombre no puede contener numeros, espacios o caracteres especiales" << endl << "Intenta de nuevo" << endl;
                        nombre = "";
                        break;
                    }
                }
                
            }
        } while (nombre == "" );
        
        do
        {
            cout << "El nombre que escribiste es: " << nombre << "." << endl ;
            cout << "Estas seguro de que ese es el nombre que deseas?" << endl << "No podras cambiar tu eleccion despues" << endl;
            cout << "Si, ese es el nombre / Mmm Prefiero volver atras. (S/N) " ;
            cin.get(respuesta);
            cin.ignore(256, '\n');
            respuesta = toupper(respuesta);

            if(respuesta == 'N'){
            nombre = "";
            cout << endl;
            }
            else if(respuesta != 'N' && respuesta != 'S'){
               cout << endl << "Opcion no reconocida. Intente de nuevo" << endl << endl;
            }
        } while (respuesta != 'N' && respuesta != 'S');
        
    } while ( nombre == "");

    return nombre;
}

int Menu::seleccionarDiff(){
    string diff = "";
    do
    {
        cout << endl << "Presiona una tecla numerica del 1 al 4 para seleccionar el nivel de dificultad : " << endl;
        cout << "1. Facil\t2. Normal\t3. Dificil\t4. Imposible"<< endl;
        getline(cin,diff);
        cout << endl;

        if(diff != "1" && diff != "2" && diff != "3" && diff != "4"){
            cout << endl << "La dificultad que seleccionaste no es valida. Intente de nuevo" << endl;          
            diff = "";
        }
        else if(diff == "1") {dificultad = 1; diff = "Facil"; cout << "Has seleccionado la dificultad: " << diff; return dificultad;}
        else if(diff == "2") {dificultad = 2; diff = "Normal"; cout << "Has seleccionado la dificultad: " << diff; return dificultad;}
        else if(diff == "3") {dificultad = 3; diff = "Dificil"; cout << "Has seleccionado la dificultad: " << diff; return dificultad;}
        else{dificultad = 4; diff = "Imposible"; cout << "Has seleccionado la dificultad: " << diff << endl << "!!Buena suerte!!"; return dificultad;}
        

    } while (diff != "Facil" && diff != "Normal" && diff != "Dificil" && diff != "Imposible");

    return 0;
}

void Menu::creaPeleadores(){
    string nombreJug = darNombres();
    cout << endl << "Cual es el nombre de tu enemigo?" << endl; 
    string nombreEn = darNombres();
    int dificultad = seleccionarDiff();

    jugador = new Jugador(nombreJug, 30, 20.0, 30, 3);

    enemigo = new Enemigo();

    enemigo -> setNombre(nombreEn);

    switch (dificultad)
    {
    case 1:
        enemigo->setAtaque(20);
        enemigo -> setDefensa(5);
        enemigo ->setEspecial(30);
        break;

    case 2:
        enemigo->setAtaque(25);
        enemigo -> setDefensa(10);
        enemigo ->setEspecial(35);
        break;
    case 3:
        enemigo->setAtaque(30);
        enemigo -> setDefensa(15);
        enemigo ->setEspecial(40);
        break;
    case 4:
        enemigo->setAtaque(40);
        enemigo -> setDefensa(25);
        enemigo ->setEspecial(50);
        break;
    default:
    cout << "Ocpion no valida";
        break;
    }
    
   
};

int Menu::seleccionarAccion(){
    string opcion = "";
    do
    { 
        cout << "Que vas a hacer?" << endl << "1. Atacar\t2. Bloquear\t3.Curarse" << endl << "Presiona una tecla numerica del 1 al 3 para seleccionar tu accion: ";
        getline(cin, opcion);
        cout << endl;

        if(opcion == "1") {cout << "Haz decidido atacar: "; return 1;}
        else if(opcion == "2") {cout << "Haz decidido defenderte: "; return 2;}
        else if(opcion == "3") {cout << "Haz decidido curarte: "; return 3;}
        else{cout << endl << "La accion que seleccionaste no es valida. Intente de nuevo" << endl; opcion = "";}

    } while (opcion != "1" && opcion != "2" && opcion != "3");
    return 0;

}
#endif  
