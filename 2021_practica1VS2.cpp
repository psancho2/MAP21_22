// 2021_practica1VS2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

typedef enum {NADIE, TENISTA1, TENISTA2} tTenista;
typedef enum {NADA, QUINCE, TREINTA, CUARENTA, VENTAJA} tPuntosJuego;

const int MIN_HABILIDAD = 1, MAX_HABILIDAD = 3, MIN_VELOCIDAD = 1, MAX_VELOCIDAD = 3;
const int ANCHO_PISTA = 7, LARGO_PISTA = 2;
const bool JUEGO_ALEATORIO = false, MODO_DEBUG = true;

const int PUNTOS_GANAR = 4;
const int JUEGOS_SET = 3;

const int DIM_ARRAY_GOLPES = 2 + ANCHO_PISTA;
typedef int tConteoGolpes[DIM_ARRAY_GOLPES];


// Funcion que realiza una secuencia de golpear y correr hacia la bola por parte de los tenistas
void lance(tTenista tenista_golpea, string nombre_golpea, int habil_golpea, tConteoGolpes golpes, int& golpes_ganadores1, int vel_recibe, int& pos_recibe, int& pos_bola, tTenista& ganador_punto);

//Funcion que devuelve la posicion de la bola (el campo contrario) tras el golpeo del jugador
//Se calcula en funcion de la posicion del tenista, su habilidad y el destino deseado para la bola
//Si el tiro excede su habilidad, puede no llegar a su destino
int golpeoBola(int posicion_tenista, int habilidad);

// Función que devuelve la posicion final del tenista que corre hacia la bola
// La posición final se calcula en función de posicion_tenista, su velocidad y posicion_bola
// Si su velocidad es inferior a la distancia entre posicion_tenista y posicion_tenista, no llega a la bola
int correTenista(int posicion_tenista, int habilidad);
int main()
{
   
}

///////////////////////////////////
//FUNCIONES DE LA LÓGICA DEL JUEGO
// ///////////////////////////////
// 

// Funcion que realiza un lance: secuencia de golpeo de un tenista y correr hacia la bola del otro
void lance(tTenista tenista_golpea, string nombre_golpea, int habil_golpea, tConteoGolpes golpes, int& golpes_ganadores, int vel_recibe, int& pos_recibe, int& pos_bola, tTenista& ganador_punto) {
    tTenista tenista_recibe = (tenista_golpea == TENISTA1) ? TENISTA2 : TENISTA1;
    cout << "Golpea " << nombre_golpea << endl << endl;
    pos_bola = golpeoBola(pos_bola, habil_golpea);
    golpes[pos_bola]++;

    //si la bola entra en la pista
    if (pos_bola > 0 && pos_bola <= ANCHO_PISTA) {
        pos_recibe = correTenista(pos_recibe, vel_recibe, pos_bola);
        if (pos_bola != pos_recibe) {
            ganador_punto = tenista_golpea;
            golpes_ganadores++;
        }
    }
    //si la bola no entra gana el que recibe
    else {
        ganador_punto = tenista_recibe;
    }
}

//Funcion que devuelve la posicion de la bola (el campo contrario) tras el golpeo del jugador
int golpeoBola(int posicion_tenista, int habilidad) {
	int destino_deseado, distancia_a_destino, destino_alcanzado, dificultad_max, resultado, probab_exito;
    if (JUEGO_ALEATORIO) {
        destino_deseado = rand() % ANCHO_PISTA + 1;
        if (MODO_DEBUG)
            cout << " El jugador dispara hacia la calle " << destino_deseado << endl;
    }
    else {
        do {
            cout << "  Indique a que zona de la pista desea mandar la bola (1-" << ANCHO_PISTA << "): ";
            cin >> destino_deseado;
            if (destino_deseado < 1 && destino_deseado > ANCHO_PISTA)
                cout << "   Error introduzca un valor válido" << endl;
        } while (destino_deseado < 1 && destino_deseado > ANCHO_PISTA);
    }

    distancia_a_destino = abs(posicion_tenista - destino_deseado);
    if (distancia_a_destino <= habilidad) {
        destino_alcanzado = destino_deseado;
        if (MODO_DEBUG)
            cout << " Ese ha sido un tiro sencillo" << endl;
    }
    else {// Si no se da ese caso, aún puede llegar (calculamos las probabilidades)

        if (MODO_DEBUG)
            cout << " Tiro complicado que... ";

        dificultad_max = (ANCHO_PISTA - 1) - MIN_HABILIDAD;
        // La dificultad depende de la distancia y de la habilidad del jugador
        // Se expresa en tanto por 1 sobre la dificultad máxima
        probab_exito = 100 - (distancia_a_destino - habilidad) * 100 / dificultad_max;

        resultado = rand() % 100;
        if (MODO_DEBUG)
            cout << "(probab_exito=" << probab_exito << "  y resultado=" << resultado << ") ";

        // Si el resultado es inferior a la probabilidad, entonces llega
        if (resultado < probab_exito) {
            destino_alcanzado = destino_deseado;
            if (MODO_DEBUG)
                cout << " Llega a su destino!" << endl;
        }
        else { // Si el resultado no es inferior, entonces falla

            // Puede irse (aleatoriamente) a la izquierda o a la derecha del destino
            if (rand() % 2 == 0)
                destino_alcanzado = destino_deseado - 1;
            else
                destino_alcanzado = destino_deseado + 1;

            if (MODO_DEBUG)
                cout << " No ha sido preciso!" << endl;
        }
    }

    return destino_alcanzado;
}
// Función que calcula la posicion final del que corre hacia la bola
int correTenista(int posicion_tenista, int velocidad, int posicion_bola) {

    int distancia_bola;

    distancia_bola = abs(posicion_tenista - posicion_bola);

    if (distancia_bola <= velocidad) {
        posicion_tenista = posicion_bola;
        if (MODO_DEBUG) cout << " Su rival llega a la bola." << endl;
    }
    else {
        if (MODO_DEBUG) cout << " Su rival no llega a la bola." << endl;

        // Calculamos la posicion final del tenista, ya que al menos lo intentó
        if (posicion_bola > posicion_tenista) {

            posicion_tenista = posicion_tenista + velocidad;
        }
        else
            posicion_tenista = posicion_tenista - velocidad;
    }

    return posicion_tenista;
}