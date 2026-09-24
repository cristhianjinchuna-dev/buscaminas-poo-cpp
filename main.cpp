#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Juego.h"
#include "Jugador.h"
#include "Historial.h"

using namespace std;

int main() {
    srand(time(NULL)); // semilla unica para todo el programa

    int op;

    do {
        cout << "\n==== BUSCAMINAS ====" << endl;
        cout << "1. Jugar"             << endl;
        cout << "2. Ver Historial"     << endl;
        cout << "3. Ver Puntuacion"    << endl;
        cout << "4. Borrar Historial"  << endl;
        cout << "5. Salir"             << endl;
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1: {
                Jugador* jugador = nullptr;
                int tipo;

                cout << "\n1. Jugador Humano\n";
                cout << "2. Jugador Maquina\n";
                cout << "Opcion: ";
                cin >> tipo;

                string nombre;
                switch (tipo) {
                    case 1:
                        cout << "Ingrese su nombre: ";
                        cin >> nombre;
                        jugador = new JugadorHumano(nombre);
                        break;
                    case 2:
                        jugador = new JugadorMaquina();
                        break;
                    default:
                        cout << "Opcion invalida.\n";
                        continue;
                }

                Juego juego(jugador);
                juego.iniciar();

                delete jugador;
                break;
            }
            case 2: {
                Historial h;
                cout << h;
                break;
            }
            case 3: {
                Historial h;
                h.mostrarPuntuacion();
                break;
            }
            case 4: {
                ofstream archivo("../historial.txt", ios::trunc);
                archivo.close();
                cout << "Historial borrado.\n";
                break;
            }
            case 5:
                cout << "Okey, nos vemos!!\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (op != 5);

    return 0;
}