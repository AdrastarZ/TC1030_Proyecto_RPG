# TC1030_Proyecto_RPG
Este proyecto busca crear una simulación simple de un juego de rol por turnos (TBRPG) entre 2 entidades o clases. Las estructuras principales son el Menu y la Pelea, estas dos sirven para: seleccionar dificultad, organizar el orden de turnos, e informar y seleccionar de acciones que realizan los Personajes, respectivamente. Los Personajes se dividen en 2, el Jugador y el Enemigo. Ambos cuentan con puntos de vida, pueden atacar y defender. El Jugador puede utilizar una función extra para curarse vida, mientras que el Enemigo puede realizar un super ataque para infligir más daño. La vida, ataque y defensa del Jugador y la vida del Enemigo son constantes, mientras que el daño, defensa y super ataque del Enemigo varian dependiendo del nivel de dificultad que sea seleccionado al inicio en el Menu. Cuando los puntos de vida del Jugador o el Enemigo llega a 0 se termina la Pelea.

## Funcionalidad
El programa permite unicamente al usuario hacer una serie de selecciones mediante el uso de las teclas numéricas, esto para configurar la dificultad y seleccionar las acciones del Jugador

## Casos a tomar en cuenta (Desactualizado)
Hay que tomar en cuenta principalmente el input del usuario. Sabiendo que la forma en como se pondra en marcha el programa es mediante los numeros que provee el usuario, habra que añadir una función para que en caso de que se inserte algun número o caracter que no esta previsto, se le pida al usuario que lo intente de nuevo con un número válido

Otro caso a tomar en cuenta es la implementación erronea de la habilidad de curación del Jugador, si no se llega a poner un limite a la salud maxima de este, al aplicar la curación se podria exceder la vida limite que estaba planeado.


