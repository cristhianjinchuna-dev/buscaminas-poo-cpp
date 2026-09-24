//
// Created by LucasMCgamer on 22/06/2026.
//

#ifndef PROYECTO_2_FINAL_PARTIDA_H
#define PROYECTO_2_FINAL_PARTIDA_H

#include "Fecha.h"
#include <string>
#include <iomanip>
using namespace std;

class Partida {
private:
    string jugador;
    Fecha fecha;
    bool ganada;
    int duracion;
public:
    Partida(string nombre, bool gano, int seg)
        : jugador(nombre), ganada(gano), duracion(seg) {}


    Partida(string nombre, bool gano, int seg, Fecha f)
        : jugador(nombre), fecha(f), ganada(gano), duracion(seg) {}

    string getJugador() const { return jugador; }
    bool getGanada() const { return ganada; }
    int getDuracion() const { return duracion; }
    Fecha getFecha() const { return fecha; }

    bool operator==(const Partida& otro) const {
        return jugador == otro.jugador && ganada == otro.ganada && duracion == otro.duracion;
    }

    friend ostream& operator<<(ostream& os, const Partida& p) {
        string durStr = to_string(p.duracion / 60) + "m " + to_string(p.duracion % 60) + "s";
        os << left
           << setw(20) << p.jugador
           << setw(20) << p.fecha.formatear()
           << setw(12) << durStr
           << (p.ganada ? "Victoria" : "Derrota");
        return os;
    }
};

#endif //PROYECTO_2_FINAL_PARTIDA_H