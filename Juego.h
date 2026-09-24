//
// Created by LucasMCgamer on 22/06/2026.
//

#ifndef PROYECTO_2_FINAL_JUEGO_H
#define PROYECTO_2_FINAL_JUEGO_H

#include "Tablero.h"
#include "Jugador.h"
#include "Historial.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

class Juego {
private:
    Jugador* jugador;
    Historial historial;
public:
    Juego(Jugador* j) : jugador(j) {}

    void iniciar() {
        int opcion, minas;

        cout << "\n===== BUSCAMINAS =====\n";
        cout << "1. Facil    (18 minas)\n";
        cout << "2. Medio    (40 minas)\n";
        cout << "3. Dificil  (60 minas)\n";
        cout << "4. Personalizado\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: minas = 18; break;
            case 2: minas = 40; break;
            case 3: minas = 60; break;
            default:
                cout << "Cantidad de minas (max 80): ";
                cin >> minas;
                if (minas < 1) minas = 1;
                if (minas > 80) minas = 80;
        }

        Tablero tablero(minas);
        time_t inicio = time(nullptr);
        bool fin = false;
        int turno = 1;

        if (jugador->necesitaJugadaInicial())
            tablero.revelar(tablero.getFilas() / 2, tablero.getColumnas() / 2);

        if (tablero.gano()) {
            tablero.mostrar(false);
            cout << "\nFELICIDADES! " << jugador->getNombre() << " gano.\n";
            int duracion = (int)(time(nullptr) - inicio);
            historial.guardarPartida(Partida(jugador->getNombre(), true, duracion));
            fin = true;
        } else if (tablero.getPerdio()) {
            tablero.mostrar(true);
            cout << "\nBOOM! " << jugador->getNombre() << " perdio.\n";
            int duracion = (int)(time(nullptr) - inicio);
            historial.guardarPartida(Partida(jugador->getNombre(), false, duracion));
            fin = true;
        }

        while (!fin) {
            tablero.mostrar(false);

            if (jugador->necesitaJugadaInicial())
                cout << "\n--- Turno " << turno++ << " ---\n";

            jugador->jugar(tablero);  // polimorfismo

            if (tablero.getPerdio()) {
                tablero.mostrar(true);
                cout << "\nBOOM! " << jugador->getNombre() << " perdio.\n";
                int duracion = (int)(time(nullptr) - inicio);
                historial.guardarPartida(Partida(jugador->getNombre(), false, duracion));
                fin = true;
                continue;
            }

            if (tablero.gano()) {
                tablero.mostrar(false);
                cout << "\nFELICIDADES! " << jugador->getNombre() << " gano.\n";
                int duracion = (int)(time(nullptr) - inicio);
                historial.guardarPartida(Partida(jugador->getNombre(), true, duracion));
                fin = true;
            }

            if (jugador->necesitaJugadaInicial() && !fin)
                this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }
};

#endif //PROYECTO_2_FINAL_JUEGO_H