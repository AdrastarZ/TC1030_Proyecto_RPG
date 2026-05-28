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
    int especial;
    int vida;

    public:
    Personaje(): nombre("Default"), ataque(0), defensa(0), especial(0) {};
    Personaje(string nom, int atk, double def, int special) : nombre(nom), ataque(atk), defensa(def), especial(special), vida(100){};
    virtual ~Personaje(){}

    void setNombre(string nombre) {this -> nombre = nombre;}
    string getNombre() {return nombre;}

    void setAtaque(int ataque) {this -> ataque = ataque;}
    int getAtaque() {return ataque;}

    void setDefensa(int defensa) {this -> defensa = defensa;}
    double getDefensa() {return defensa;}

    void setVida(int salud) {vida = salud;}
    double getVida() {return vida;}

    void setEspecial(int special)  {especial = special;}
    int getEspecial()  {return especial;}


    virtual double dano() = 0;
    virtual double bloqueo() = 0;
    virtual int accionEspecial() = 0;
    virtual int recibirDano(int cantidad)=0;
    virtual int valorAleatorio()=0;
    int probAtaque(){return 0;};
    
};


class Jugador:public Personaje{
// El heroe recibe un boost de ataque
    private:
    int critico;

    public:
    Jugador(): Personaje("Heroe", 0, 0.0, 0 ) {};
    Jugador(string nombre, int ataque, double defensa, int special, int crit) : Personaje( nombre,  ataque,  defensa,  special), critico(crit){};

    void setCritico(int crit)  {critico = crit;}
    int getCritico() {return critico;}

    int valorAleatorio() override;

    double dano() override;
    double bloqueo() override;
    int accionEspecial() override;
    
    int recibirDano(int cantidad) override;

};

int Jugador::valorAleatorio(){
    int minimo = 1;
    int maximo = 10;
    random_device rd;
    mt19937 motor(rd());
    uniform_int_distribution<int> num_probabilidad(minimo,maximo); // Declara un maximo y un minimo que el motor mt19937 tiene que seguir
    int numAleatorio = num_probabilidad(motor); //Devuelve el valor que da el motor con los limites impuestos

    return numAleatorio;
}



double Jugador::dano(){
    int golpeCritico = valorAleatorio();
    if(golpeCritico == 10){
        cout << "!!Un golpe critico!!";
        return ataque*critico;
    }
    else {
        return ataque;
    }
}

double Jugador::bloqueo(){
    double diff = defensa*1.5;
    defensa =  ceil(diff);
    return 0;
}

int Jugador::accionEspecial(){
    if((vida+especial) > 100){
        vida = 100;
    }
    else{
        vida += especial;
    }
    return 0;
}


int Jugador::recibirDano(int cantidad){

    if(cantidad <= defensa){
        cantidad = 1;
        vida -= cantidad;
    }
    else{
        vida = vida - (cantidad - defensa);
    }

    
    if(vida <= 0){
        vida = 0;
    }
    
    return vida;
}

class Enemigo:public Personaje{
// El enemigo cambia las estadisticas segun su dificultad
    
    public:
    Enemigo(): Personaje("Enemigo", 0, 0.0,0) {};
    Enemigo(string nombre, int ataque, double defensa, int special) : Personaje( nombre,  ataque,  defensa,  special) {};


    int valorAleatorio() override;
    int probAtaque();
    double dano() override;
    double bloqueo() override;
    int accionEspecial() override;
    int recibirDano(int cantidad)override;

};

int Enemigo::valorAleatorio(){
    int minimo = 1;
    int maximo = 100;
    random_device rd;
    mt19937 motor(rd());
    uniform_int_distribution<int> num_probabilidad(minimo,maximo); // Declara un maximo y un minimo que el motor mt19937 tiene que seguir
    int numAleatorio = num_probabilidad(motor); //Devuelve el valor que da el motor con los limites impuestos

    return numAleatorio;
}

double Enemigo::dano() {return ataque;}

double Enemigo::bloqueo(){
    double diff = defensa*1.5;
    defensa =  ceil(diff);
    return 0;
}
int Enemigo::accionEspecial() {return especial;}

int Enemigo::probAtaque(){ 
    int probabilidad = valorAleatorio();
    if(probabilidad >= 1 && probabilidad <= 45){
        return 1;
    }
    else if(probabilidad >= 45 && probabilidad <= 90){
        return 2;
    }
    else{
        return 3;
    }

}
int Enemigo::recibirDano(int cantidad){

    if(cantidad <= defensa){
        cantidad = 1;
        vida -= cantidad;
    }
    else{
        vida = vida - (cantidad - defensa);
    }

    
    if(vida <= 0){
        vida = 0;
    }
    
    return vida;
}

#endif 
