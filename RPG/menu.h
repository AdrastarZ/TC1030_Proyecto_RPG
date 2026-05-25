#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <random>
#include <cctype>
#include "pelea.h"
#include "personaje.h"


using namespace std;

class Menu{
    private:
    int dificultad;
    Personaje *jugador;
    Personaje *enemigo;

    public:

    Menu():dificultad(0){}
    Menu(int diff):dificultad(diff){}


    void setDificultad(int diff){ dificultad = diff;}
    int getDificultad(){ return dificultad;}


    string darNombres(){}
    int seleccionarDiff(){}
    void creaPeleadores(){}
    int seleccionarAccion(){}
    void mostrarAccion(){}

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
               cout << "Opcion no reconocida. Intente de nuevo" << endl << endl;
            }
        } while (respuesta != 'N' && respuesta != 'S');
        
    } while ( nombre == "");

    return nombre;
}


void Menu::creaPeleadores(){
    
};

#endif
