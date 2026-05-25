#ifndef PERSONAJE_H_ 
#define PERSONAJE_H_ 

#include <string>
#include <random>
#include <cmath>

using namespace std;

class Personaje {

    protected:
    string nombre;
    int ataque;
    double defensa;
    int vida;

    public:
    Personaje(): nombre("Default"), ataque(0), defensa(0) {};
    Personaje(string nom, int atk, double def) : nombre(nom), ataque(atk), defensa(def), vida(100){};

    void setNombre(int nombre) {this -> nombre = nombre;}
    string getNombre() {return nombre;}

    void setAataque(int ataque) {this -> nombre = ataque;}
    int getAtaque() {return ataque;}

    void setDefensa(int defensa) {this -> nombre = defensa;}
    double getDefensa() {return defensa;}

    virtual double dano() = 0;
    virtual double bloqueo() = 0;

};


class Jugador:public Personaje{
// El heroe recibe un boost de ataque
    private:
    int sanacion;
    int critico;


    public:
    Jugador(): Personaje("Heroe", 0, 0.0) {};
    Jugador(string nombre, int ataque, double defensa, int cura, int crit) : Personaje(nombre, ataque, defensa), sanacion(cura), critico(crit){};

    
    void setSanacion(int cura) {sanacion = cura;}
    int getSanacion(){return sanacion;}

    void setCritico(int crit) {critico = crit;}
    int getCritico() {return critico;}

    int valorAleatorio(){}

    double dano() override{}
    double bloqueo() override{}

};


int Jugador::valorAleatorio(){
    int minimo = 0;
    int maximo = 10;
    random_device rd;
    mt19937 motor(rd());
    uniform_int_distribution<int> num_probabilidad(minimo,maximo); // Declara un maximo y un minimo que el motor mt19937 tiene que seguir
    int numAleatorio = num_probabilidad(motor); //Devuelve el valor que da el motor con los limites impuestos

    return numAleatorio;
}

double Jugador::dano(){
    if(valorAleatorio() == 10){
        return ataque*3;
    }
    else if (valorAleatorio()!=10){
        return ataque;
    }
}

double Jugador::bloqueo(){
    double dano_bloqueado = defensa*1.5;
    return ceil(dano_bloqueado);
}

class Enemigo:public Personaje{
// El enemigo cambia las estadisticas segun su dificultad
    private:
    int superAtk;
    
    public:
    Enemigo(): Personaje("Enemigo", 0, 0.0) {};
    Enemigo(string nombre, int ataque, double defensa, int atkEspecial) : Personaje(nombre, ataque, defensa), superAtk(atkEspecial) {};

    void setSuper(int atkEspecial) {superAtk = atkEspecial;}
    int getSuper() {return superAtk;}


    double dano() override{}
    double bloqueo() override{}
    int super(){}

};

double Enemigo::dano() {return ataque;}

double Enemigo::bloqueo(){
    double dano_bloqueado = defensa*1.5;
    return ceil(dano_bloqueado);
}

int Enemigo::super() {return superAtk;}

#endif 