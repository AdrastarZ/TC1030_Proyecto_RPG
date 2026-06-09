/*
 * Proyecto RPG main
 * Axel Daniel Ramírez Silva
 * A01704206
 * 11/06/2026
 *
 * La clase menu es con lo que el usuario principalmente interactua cuando el programa corre,
 * siendo la salida de consola, esperando una entrada de dato.
 * 
 * Esta clase se encarga de definir nombres, dificultad, y preparar las clases hijas de Jugador y
 * Enemigo con los dos parametros pasados para ponerlos en la memoria dinámica
 */

#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <cctype> //Biblioteca usada para comprobar uso de caracteres alfa numéricos

#include "personaje.h" //Biblioteca con objetos de mi proyecto

using namespace std;

//Declaración de la clase menu
class Menu{

    // Declaración de atributos privados
    private:
    int dificultad;

    // Se declaran punteros de las clases hijas
    Personaje *jugador;
    Personaje *enemigo;

    // Declaración de metodos públicos
    public:

    Menu(){}
    ~Menu(){ delete jugador; delete enemigo;} // Destruimos los atributos jugador y enemigo para evitar fallos en memoria

    Personaje *getJugador(){return jugador;}
    Personaje *getEnemigo(){return enemigo;}

    string darNombres();
    int seleccionarDiff();
    void creaPeleadores();

};

/**
 * darNombres
 *
 * Pide al usuario que inserte un nombre.
 * Para evitar problemas de compilación, lógica o con loops, se pusieron parametros para limitar lo que el usuario puede poner.
 * Tiene un maximo de 10 caracteres, debe tener un minimo de un caracter, no puede tener numeros, espacios, ni caracteres especiales.
 * Al final se le pregunta al usuario si esta satisfecho con su selección de ser así el programa continua, sino vuelve a preguntar por el nombre.
 *  
 * @return string El nombre validado e ingresado por el usuario de forma correcta.
 */
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


/**
 * seleccionarDiff
 *
 * Pide al usuario una entrada numérica del 1 al 5, dependiendo de la entrada es la dificultad que se selecciona para jugar.
 * Si se inserta un valor que no es el indicado, se reiniciara el ciclo hasta que la entrada sea una de las solicitadas.
 * 
 * @return int El número entero que representa la dificultad elegida (del 1 al 5).
 */
int Menu::seleccionarDiff(){
    string diff = "";
    do
    {
        cout << endl << "Presiona una tecla numerica del 1 al 4 para seleccionar el nivel de dificultad : " << endl;
        cout << "1. Facil\t2. Normal\t3. Dificil\t4. Muy dificil\t\t5. Heartless"<< endl;
        getline(cin,diff);
        cout << endl;

        if(diff != "1" && diff != "2" && diff != "3" && diff != "4" && diff != "5"){
            cout << endl << "La dificultad que seleccionaste no es valida. Intente de nuevo" << endl;          
            diff = "";
        }
        else if(diff == "1") {dificultad = 1; diff = "Facil"; cout << "Has seleccionado la dificultad: " << diff; return dificultad;}
        else if(diff == "2") {dificultad = 2; diff = "Normal"; cout << "Has seleccionado la dificultad: " << diff; return dificultad;}
        else if(diff == "3") {dificultad = 3; diff = "Dificil"; cout << "Has seleccionado la dificultad: " << diff; return dificultad;}
        else if(diff == "4") {dificultad = 4; diff = "Muy dificil"; cout << "Has seleccionado la dificultad: " << diff; return dificultad;}
        else{dificultad = 5; diff = "Heartless"; cout << "Has seleccionado la dificultad: " << diff << endl << "!!Buena suerte!!"; return dificultad;}
        

    } while (diff != "Facil" && diff != "Normal" && diff != "Dificil" && diff != "Muy dificil" && diff != "Heartless"); // Corregido "Muy dificil" para evitar bucle infinito

    return 0;
}


/**
 * creaPeleadores
 *
 * Llama al metodo darNombres 2 veces, unos para darle un nombre al Jugador, otro al Enemigo
 * Llama al metodo seleccionarDiff para modificar las estadisticas de las acciones del jugador dependiendo de lo que se escogio anteriormente
 * Crea los objetos de las clases, el Jugador con estadisticas que predefinidas, las del Enemigo varian segun la dificultad 
 * */
void Menu::creaPeleadores(){
    string nombreJug = darNombres();
    cout << endl << "Cual es el nombre de tu enemigo?" << endl; 
    string nombreEn = darNombres();
    int dificultad = seleccionarDiff();

    jugador = new Jugador(nombreJug, 30, 20.0, 30, 3, 0); // Nombre, ataque, defensa, curación, critico, curaciones usadas

    enemigo = new Enemigo(nombreEn, 0, 0.0, 0);

    switch (dificultad)
    {
    case 1:
        enemigo -> setAtaque(20);
        enemigo -> setDefensa(5);
        enemigo -> setEspecial(30);
        break;
    case 2:
        enemigo -> setAtaque(25);
        enemigo -> setDefensa(10);
        enemigo -> setEspecial(35);
        break;
    case 3:
        enemigo -> setAtaque(30);
        enemigo -> setDefensa(15);
        enemigo -> setEspecial(40);
        break;
    case 4:
        enemigo -> setAtaque(40);
        enemigo -> setDefensa(25);
        enemigo -> setEspecial(50);
        break;
    case 5:
        enemigo -> setAtaque(50);
        enemigo -> setDefensa(25);
        enemigo -> setEspecial(70);
        break;

    default:
    cout << "Ocpion no valida";
        break;
    } 
};

#endif
