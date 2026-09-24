//
// Created by LucasMCgamer on 22/06/2026.
//

#ifndef PROYECTO_2_FINAL_JUGADOR_H
#define PROYECTO_2_FINAL_JUGADOR_H

#include <iostream>
#include <string>
#include "Tablero.h"

using namespace std;

class Jugador {
protected:
    string nombre;
public:
    Jugador(string n) : nombre(n) {}

    string getNombre() { return nombre; }

    virtual void jugar(Tablero& tablero) = 0;

    virtual bool necesitaJugadaInicial() { return false; }

    virtual ~Jugador() {}
};

class JugadorHumano : public Jugador {
public:
    JugadorHumano(string n) : Jugador(n) {}

    void jugar(Tablero& tablero) override {
        int accion, fila, columna;
        cout << "\n1. Revelar casilla\n";
        cout << "2. Marcar/Desmarcar bandera\n";
        cout << "Opcion: ";
        cin >> accion;
        cout << "Fila (0-13): ";
        cin >> fila;
        cout << "Columna (0-17): ";
        cin >> columna;

        if (accion == 2)
            tablero.marcar(fila, columna);
        else {
            if (tablero.perdio(fila, columna))
                tablero.setPerdio(true);
            else
                tablero.revelar(fila, columna);
        }
    }

    ~JugadorHumano() {}
};

class JugadorMaquina : public Jugador {
public:
    JugadorMaquina() : Jugador("Maquina") {}

    void jugar(Tablero& tablero) override {
        tablero.jugadaMaquina();
    }

    bool necesitaJugadaInicial() override { return true; }

    ~JugadorMaquina() {}
};

#endif //PROYECTO_2_FINAL_JUGADOR_H