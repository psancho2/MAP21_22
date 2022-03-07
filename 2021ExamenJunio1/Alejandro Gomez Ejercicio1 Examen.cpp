#include <iostream>
#include <fstream>
#include <iomanip> 
using namespace std;

const int MAX_FILAS = 10;
const int MAX_COLUMNAS = 10;

typedef struct tMatriz{
    int matriz[MAX_FILAS][MAX_COLUMNAS];
    int nfila, ncolumna; // nº de filas y nº de columnas usadas
};

// subprogramas pedidos
void mostrar_diagonales(const tMatriz& m, int fila, int col);
int buscar_suma_par(const tMatriz& m);

// subprogramas ya implementados
void cargar_Matriz(tMatriz& m, ifstream& archivo); // para cargar la matriz desde archivo
void mostrar(const tMatriz& m); // para visualizar la matriz por pantalla


int main() {

    tMatriz m;
    ifstream archivo;

    archivo.open("matriz.txt");
    //archivo.open("matriz2.txt");  
    if (archivo.is_open()) {
        cargar_Matriz(m, archivo);
        archivo.close();
        mostrar(m);

        // solicitud de posición [fila, columna] desde la que se quieren mostrar las diagonales
        int fila, columna;
        cout << "Introduce la fila y la columna de un punto: " << endl;
        cout << "Fila ";
        cin >> fila;
        cout << "Columna ";
        cin >> columna;

        mostrar_diagonales(m, fila, columna);

        cout << endl;

        int columna_par;
        columna_par = buscar_suma_par(m);

        cout << "La primera columna con suma par >0 es la " << columna_par << endl;
        cin >> columna;

    }
    else
        cout << "Archivo inexistente\n";

    return 0;

}


void mostrar_diagonales(const tMatriz& m, int fila, int col) {

    cout << "Diagonal 1" << endl;
    int i = 1, j = 1;

    //mientras la fila dada mas i sea menor que el max de filas y la columna dada mas j sea menor que el max de columnas, se muestra
    while ((fila + i) < m.nfila && (col + j) < m.ncolumna) {

        cout << m.matriz[fila + i][col + j] << " ";

        i++;
        j++;
    }
    cout << endl;


    cout << "Diagonal 2" << endl;
    i = 1; 
    j = 1;

    //mientras la fila dada menos i sea mayor/igual que el 0 y la columna dada mas j sea menor que el max de columnas, se muestra
    while ((fila - i) >= 0 && (col + j) < m.ncolumna) {

        cout << m.matriz[fila - i][col + j] << " ";

        i++;
        j++;
    }
    cout << endl;


    cout << "Diagonal 3" << endl;
    i = 1;
    j = 1;

    //mientras la fila dada menos i sea mayor/igual que el 0 y la columna dada menos j sea mayor / igual que el 0, se muestra
    while ((fila - i) >= 0  && (col - j) >= 0) {

        cout << m.matriz[fila - i][col - j] << " ";

        i++;
        j++;
    }
    cout << endl;


    cout << "Diagonal 4" << endl;
    i = 1;
    j = 1;

    //mientras la fila dada mas i sea menor que el max de filas y la columna dada menos j sea mayor/igual que el 0, se muestra
    while ((fila + i) < m.nfila && (col - j) >= 0) {

        cout << m.matriz[fila + i][col - j] << " ";

        i++;
        j++;
    }
    cout << endl;
}


int buscar_suma_par(const tMatriz& m) {

    int i = 0, j = 0;
    int columna = -1;
    bool encontrado = false;

    //mientras los indices sean menores que los maximos y no se haya encontrado se sigue el while
    while (i < m.nfila && j < m.ncolumna && !encontrado) 
    {
        int suma = 0;
        i = 0;

        //este while suma las columnas y las guarda en suma
        while (i < m.ncolumna)
        {
            suma += m.matriz[i][j];

            i++;
        }

        //el if comprueba si es par y si si lo es devuelve la j que lo afirma y sale del bucle
        if ((suma % 2) == 0)
        {
            encontrado = true;
            columna = j;
        }

        //si no se cumple el if salta al else que vuelve al ciclo
        else
            j++;

    }

    return columna;
}

//
// subprogramas que se dan implementados
//

// carga la matriz desde el archivo dado
void cargar_Matriz(tMatriz& m, ifstream& archivo) {
    archivo >> m.nfila >> m.ncolumna;
    for (int i = 0; i < m.nfila; ++i) {
        for (int j = 0; j < m.ncolumna; ++j)
            archivo >> m.matriz[i][j];
    }
}

// muestra por pantalla la matriz
void mostrar(const tMatriz& m) {
    for (int i = 0; i < m.nfila; i++) {
        for (int j = 0; j < m.ncolumna; j++) {
            cout << setw(2) << m.matriz[i][j] << " ";
        }
        cout << endl;
    }
}



