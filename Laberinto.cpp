#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 100;



char laberinto[MAX][MAX];
int filas = 0, columnas = 0;
int inicioX, inicioY;
int finX, finY;

int leerLaberinto(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo\n";
        return 0;
    }

    string linea;
    while (getline(archivo, linea)) {
        for (int j = 0; j < linea.length(); j++) {
            laberinto[filas][j] = linea[j];
            if (linea[j] == 'I') {
                inicioX = filas;
                inicioY = j;
            }
            if (linea[j] == 'S') {
                finX = filas;
                finY = j;
            }
        }
        columnas = linea.length();
        filas++;
    }
    archivo.close();
    return 1;
}

int resolver(int x, int y) {
    if (x < 0 || y < 0 || x >= filas || y >= columnas)
        return 0;

    if (laberinto[x][y] == '#' || laberinto[x][y] == '*')
        return 0;

    if (x == finX && y == finY)
        return 1;

    char temp = laberinto[x][y];
    laberinto[x][y] = '*';

    if (resolver(x + 1, y)) return 1;
    if (resolver(x - 1, y)) return 1;
    if (resolver(x, y + 1)) return 1;
    if (resolver(x, y - 1)) return 1;

    laberinto[x][y] = temp;
    return 0;
}

int main() {
    char nombre[100];

    cout << "Ingrese nombre del archivo: ";
    cin >> nombre;

    if (!leerLaberinto(nombre)) return 1;

    if (resolver(inicioX, inicioY)) {
        laberinto[inicioX][inicioY] = 'I';
        laberinto[finX][finY] = 'S';

        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << laberinto[i][j];
            }
            cout << endl;
        }

        cout << "Ruta encontrada en: " << nombre << endl;
    } else {
        cout << "No se pudo encontrar salida en " << nombre << endl;
    }

    return 0;
}

