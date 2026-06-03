# TC1030_Proyecto_RPG
Este proyecto busca crear una simulación simple de un juego de rol por turnos (TBRPG) entre 2 entidades o clases. Las estructuras principales son el Menu y la Pelea, estas dos sirven para: seleccionar dificultad, organizar el orden de turnos, e informar y seleccionar de acciones que realizan los Personajes, respectivamente. Los Personajes se dividen en 2, el Jugador y el Enemigo. Ambos cuentan con puntos de vida, pueden atacar y defender. El Jugador puede utilizar una función extra para curarse vida, mientras que el Enemigo puede realizar un super ataque para infligir más daño. La vida, ataque y defensa del Jugador y la vida del Enemigo son constantes, mientras que el daño, defensa y super ataque del Enemigo varian dependiendo del nivel de dificultad que sea seleccionado al inicio en el Menu. Cuando los puntos de vida del Jugador o el Enemigo llega a 0 se termina la Pelea.

---

## Instalación y ejecución del programa

1. Abre una terminal (PowerShell o CMD) y navega a la carpeta:
   ```
   cd ruta\a\la\carpeta
   ```
2. Compila:
   ```
   g++ main.cpp -o RPG
   ```
3. Ejecuta:
   ```
   ./RPG.exe
   ```

---

## Funcionalidad
El programa permite unicamente al usuario hacer una serie de selecciones mediante el uso del teclado, esto para crear un nombre, configurar la dificultad y seleccionar las acciones del Jugador

--- 

## Casos que hacen que el programa deje de funcionar(Solucionados)
| Situación | Efecto | Solución |
|---|---|---|
| Escribir una numero una cadena de texto | Al entrar un valor numérico en darNombres el bucle do while entra en ciclo infinito | Para solucionarlo se añadio la función isalpha para verificar que el valor sea alfa numérico e igualar el valor dado a un string vacio |
| Insertar un valor numérico que no este en el rango | El metodo seleccionarAccion espera un valor entre 1 a 5, de no ser insertado uno de estos valores, el bucle do while se convierte en un ciclo infinito | Para solucionarlo se implementaron multiples if para recibir de manera adecuada los casos correctos, igual que los incorrectos |



