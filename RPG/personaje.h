/*
 * Proyecto RPG main
 * Axel Daniel Ramírez Silva
 * A01704206
 * 11/06/2026
 *
 * La clase personaje se encarga de definir los atributos y metodos principales que
 * heredan las clases jugador y enemigo, y ambos tiene sus propios metodos y atributos
 * para definir y diferenciar ambas clases
 */

#ifndef PERSONAJE_H_ 
#define PERSONAJE_H_ 

#include <string>
#include <random>
#include <cmath> //Ocupo ceil() para redondear variables hacia arriba

using namespace std;

// Declaración de clase abstracta Personaje
class Personaje {

    // Atributos que seran heredados por las hijas
    protected:
    string nombre;
    int ataque;
    double defensa;
    int especial;
    int vida;

    // Metodos que seran heredados
    public:
    Personaje(): nombre("Default"), ataque(0), defensa(0), especial(0) {}; //Constructor default
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

    // Declaracion de metodos virtuales
    virtual int elegirAccion() = 0; 
    virtual double dano() = 0;
    virtual double bloqueo() = 0;
    virtual int accionEspecial() = 0;
    virtual int recibirDano(int cantidad)=0;
    virtual int valorAleatorio()=0;
    
};

// Declaración de clase Jugador que hereda de Personaje
class Jugador:public Personaje{

    // Atributos privados a la clase
    private:
    int critico;
    int curacionesUsadas;

    // Declaración y sobreescritura de los metodos de la clase hija
    public:
    Jugador(): Personaje("Heroe", 0, 0.0, 0 ) {}; //Constructor default
    Jugador(string nombre, int ataque, double defensa, int special, int crit, int usos) : Personaje( nombre,  ataque,  defensa,  special), critico(crit), curacionesUsadas(usos){};

    int elegirAccion() override;
    int valorAleatorio() override;
    double dano() override;
    double bloqueo() override;
    int accionEspecial() override;
    int recibirDano(int cantidad) override;

};

/**
 * seleccionarAccion: Jugador
 * Se le permite seleccionar al jugador 1 de 3 acciones y devuelve un número acorde a esa acción seleccionada.
 * Si la opción que selecciono no es valida pide de nuevo una entrada de dato.
 *
 *  @return int Número de acción (1: Atacar, 2: Bloquear, 3: Curarse).
 */
int Jugador::elegirAccion(){
    string opcion = "";
    do
    { 
        cout << endl << "Que vas a hacer?" << endl << "1. Atacar: 10'%' de probabilidad de golpe critico" << endl << 
        "2. Bloquear: Aumenta en un 50'%' tu defense por 1 turno" << endl << 
        "3. Curarse: Cura 30 puntos de salud, no excede salud maxima de 100, limite de 3 curaciones " 
        << endl << "Presiona una tecla numerica del 1 al 3 para seleccionar tu accion: ";

        getline(cin, opcion);
        cout << endl;

        
        if(curacionesUsadas >= 3 && opcion == "3"){
            cout << "!! Te quedaste sin fuerzas para curarte !!" << endl << "Realiza otra accion" <<endl;
            opcion = "";
        }
        else{
            if(opcion == "1") {cout << "Haz decidido atacar: "; return 1;}
            else if(opcion == "2") {cout << "Haz decidido defenderte: "; return 2;}
            else if(opcion == "3") {curacionesUsadas++; cout << "Haz decidido curarte: "; return 3;}
            else{cout << endl << "La accion que seleccionaste no es valida. Intente de nuevo" << endl; opcion = "";}
        }
        
    } while (opcion != "1" && opcion != "2" && opcion != "3");

    return 0;
}


/**
 * valorAleatorio: Jugador
 *
 * Genera un numero aleatorio entre el 1 al 10 y lo devuelve.
 * Utiliza la libreria random y el motor mt19937.
 * Este valor es utilizado para definir una cualidad del
 * metodo dano del Jugador.
 * 
 * @return int Número aleatorio entre 1 y 10 usado para calcular golpes críticos.
 */
int Jugador::valorAleatorio(){
    int minimo = 1;
    int maximo = 10;
    random_device rd;
    mt19937 motor(rd());
    uniform_int_distribution<int> num_probabilidad(minimo,maximo); 
    int numAleatorio = num_probabilidad(motor); 

    return numAleatorio;
}


/**
 * dano: Jugador
 *
 * Devuelve el valor del ataque del Jugador.
 * Si el metodo de valor aleatorio es igual a 10 se triplica el daño, un golpe crítico.
 * 
 * @return double Cantidad de daño infligido final al oponente.
 */
double Jugador::dano(){
    int golpeCritico = valorAleatorio();
    if(golpeCritico == 10){
        cout << "!!Un golpe critico!! ";
        return ataque*critico;
    }
    else {
        return ataque;
    }
}


/**
 * bloqueo: Jugador
 *
 * Devuelve el valor de la defensa del Jugador multiplicado por 1.5.
 * Luego es redondeado al entero mas grande.
 * 
 * @return double Devuelve 0 tras haber modificado internamente la estadística de defensa.
 */
double Jugador::bloqueo(){
    double diff = defensa*1.5;
    defensa =  ceil(diff);
    return 0;
}


/**
 * accionEspecial: Jugador
 *
 * Suma la vida actual del Jugador con el valor designado de especial.
 * Si la suma de vida y especial llega a superar 100 el maximo valor que puede alcanzar la suma es 100.
 * 
 * @return int Devuelve 0 tras procesar la restauración de puntos de salud.
 */
int Jugador::accionEspecial(){
    if((vida+especial) > 100){
        vida = 100;
    }
    else{
        vida += especial;
    }
    return 0;
}


/**
 * recibirDano: Jugador
 *
 * Dependiendo de la cantidad de daño que reciba el parametro cantidad se le resta el parametro cantidad a la vida.
 * Si resulta el parametro ser menor que la defensa, para evitar valores negativos o 0 el daño minimo es 1. 
 * Si en algun punto la vida del Jugador llega a ser menor a 0, esta se restablece hasta 0 para evitar negativos.
 * 
 * @param cantidad El daño entrante crudo que genera el enemigo antes de la mitigación.
 * @return int Los puntos de vida actuales del jugador tras procesar el impacto.
 */
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


// Declaración de clase Enemigo que hereda de Personaje
class Enemigo:public Personaje{
    
    // Declaración y sobreescritura de los metodos de la clase hija
    public:
    Enemigo(): Personaje("Enemigo", 0, 0.0,0) {};
    Enemigo(string nombre, int ataque, double defensa, int special) : Personaje( nombre,  ataque,  defensa,  special) {};

    int valorAleatorio() override;
    int elegirAccion() override;
    double dano() override;
    double bloqueo() override;
    int accionEspecial() override;
    int recibirDano(int cantidad)override;

};


/**
 * valorAleatorio: Enemigo
 *
 * Genera un numero aleatorio entre el 1 al 100 y lo devuelve.
 * Utiliza la libreria random y el motor mt19937.
 * 
 * Este valor es utilizado para definir la probabilidad de que el enemigo realice una de las 3 acciones disponibles.
 * @return int Número aleatorio entre 1 y 100 utilizado para la toma de decisiones por probabilidad.
 */
int Enemigo::valorAleatorio(){
    int minimo = 1;
    int maximo = 100;
    random_device rd;
    mt19937 motor(rd());
    uniform_int_distribution<int> num_probabilidad(minimo,maximo); 
    int numAleatorio = num_probabilidad(motor); 

    return numAleatorio;
}


/**
 * dano: Enemigo
 *
 * Devuelve el valor del ataque del Enemigo.
 * 
 * @return double Daño base del enemigo.
 */
double Enemigo::dano() {return ataque;}


/**
 * bloqueo: Enemigo
 *
 * Devuelve el valor de la defensa del Enemigo multiplicado por 1.5.
 * Luego es redondeado al entero mas grande.
 * 
 * @return double Devuelve 0 tras haber modificado internamente la estadística de defensa del enemigo.
 */
double Enemigo::bloqueo(){
    double diff = defensa*1.5;
    defensa =  ceil(diff);
    return 0;
}


/**
 * accionEspecial: Enemigo
 *
 * Devuelve el valor del ataque especial.
 * 
 * @return int El daño plano asignado a la acción especial 'Rayo Cosmico'.
 */
int Enemigo::accionEspecial() {return especial;}


/**
 * elegirAccion: Enemigo
 *
 * Llama al metodo valorAleatorio, dependiendo de su resultado devuelve un valor entero, estos valores representan una de las 3 acciones posibles
 * 1. Atacar: 45% de probabilidad de ocurrir
 * 2. Bloquear: 45% de probabilidad de ocurrir
 * 3. Especial: 10% de probabilidad de ocurrir
 * 
 * @return int Código de acción determinado aleatoriamente (1: Ataque, 2: Bloqueo, 3: Especial).
 */
int Enemigo::elegirAccion(){ 
    int probabilidad = valorAleatorio();
    if(probabilidad >= 1 && probabilidad <= 45){
        return 1;
    }
    else if(probabilidad > 45 && probabilidad <= 90){
        return 2;
    }
    else{
        return 3;
    }

}


/**
 * recibirDano: Enemigo
 *
 * Dependiendo de la cantidad de daño que reciba el parametro cantidad se le resta el parametro cantidad a la vida.
 * Si resulta el parametro ser menor que la defensa, para evitar valores negativos o 0 el daño minimo es 1. 
 * 
 * Si en algun punto la vida del Enemigo llega a ser menor a 0, esta se restablece hasta 0 para evitar negativos.
 * @param cantidad El daño entrante crudo que genera el jugador antes de la mitigación.
 * @return int Los puntos de vida actuales del enemigo tras procesar el impacto.
 */
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
