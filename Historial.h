//
// Created by LucasMCgamer on 22/06/2026.
//

#ifndef PROYECTO_2_FINAL_HISTORIAL_H
#define PROYECTO_2_FINAL_HISTORIAL_H

#include "Partida.h"
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class Historial {
private:
    vector<Partida> partidas;

    Historial(bool) {}

public:
    Historial() {
        cargarArchivo();
    }

    void cargarArchivo() {
        ifstream archivo("../historial.txt");
        if (!archivo.is_open()) return;

        string linea;
        while (getline(archivo, linea)) {

            if (!linea.empty() && linea.back() == '\r')
                linea.pop_back();

            if (linea == "---" || linea.empty()) continue;

            string nombre = linea.substr(0, 20);
            int finNombre = nombre.find_last_not_of(' ');
            if (finNombre != string::npos)
                nombre = nombre.substr(0, finNombre + 1);

            bool gano = linea.find("Victoria") != string::npos;

            string fechaStr = linea.substr(20, 20);
            int finFecha = fechaStr.find_last_not_of(' ');
            if (finFecha != string::npos)
                fechaStr = fechaStr.substr(0, finFecha + 1);

            int dia = 1, mes = 1, ano = 2026, hora = 0, minuto = 0;
            int pos1 = fechaStr.find('/');
            int pos2 = fechaStr.find('/', pos1 == string::npos ? string::npos : pos1 + 1);
            int posEspacio = fechaStr.find(' ', pos2 == string::npos ? string::npos : pos2 + 1);
            int posDosPuntos = fechaStr.find(':', posEspacio == string::npos ? string::npos : posEspacio + 1);
            if (pos1 != string::npos && pos2 != string::npos &&
                posEspacio != string::npos && posDosPuntos != string::npos) {
                dia    = stoi(fechaStr.substr(0, pos1));
                mes    = stoi(fechaStr.substr(pos1 + 1, pos2 - pos1 - 1));
                ano    = stoi(fechaStr.substr(pos2 + 1, posEspacio - pos2 - 1));
                hora   = stoi(fechaStr.substr(posEspacio + 1, posDosPuntos - posEspacio - 1));
                minuto = stoi(fechaStr.substr(posDosPuntos + 1));
            }
            Fecha fecha(dia, mes, ano, hora, minuto);

            string durStr = linea.substr(40, 12);
            int minutos = 0, segundos = 0;
            int mPos = durStr.find('m');
            int sPos = durStr.find('s');
            if (mPos != string::npos)
                minutos = stoi(durStr.substr(0, mPos));
            if (sPos != string::npos)
                segundos = stoi(durStr.substr(mPos + 2, sPos - mPos - 2));

            int duracion = minutos * 60 + segundos;
            partidas.push_back(Partida(nombre, gano, duracion, fecha));
        }
        archivo.close();
    }

    void guardarPartida(Partida p) {
        partidas.push_back(p);
        guardarArchivo();
    }

    void guardarArchivo() {
        ofstream archivo("../historial.txt", ios::app);
        Partida& p = partidas.back();
        archivo << p << "\n---\n";
        archivo.close();
    }

    Historial operator+(Historial& otro) {
        Historial nuevo(false);
        for (int i = 0; i < partidas.size(); i++)
            nuevo.partidas.push_back(partidas[i]);
        for (int i = 0; i < otro.partidas.size(); i++)
            nuevo.partidas.push_back(otro.partidas[i]);
        return nuevo;
    }

    friend ostream& operator<<(ostream& os, const Historial& h) {
        if (h.partidas.empty()) {
            os << "\nNo hay partidas registradas.\n";
            return os;
        }
        os << "\n===== HISTORIAL =====\n";
        os << left << setw(20) << "Jugador" << setw(20) << "Fecha" << setw(12) << "Duracion" << "Resultado\n";
        os << string(60, '-') << "\n";
        for (const Partida& p : h.partidas)
            os << p << "\n";
        return os;
    }

    void mostrarPuntuacion() {
        if (partidas.empty()) {
            cout << "\nNo hay partidas registradas.\n";
            return;
        }

        vector<string> nombres;
        vector<int> victorias;
        vector<int> derrotas;

        for (const Partida& p : partidas) {
            string nombre = p.getJugador();
            bool gano = p.getGanada();

            int posicion = -1;
            for (int i = 0; i < nombres.size(); i++)
                if (nombres[i] == nombre) { posicion = i; break; }

            if (posicion == -1) {
                nombres.push_back(nombre);
                victorias.push_back(gano ? 1 : 0);
                derrotas.push_back(gano ? 0 : 1);
            } else {
                if (gano) victorias[posicion]++;
                else derrotas[posicion]++;
            }
        }

        cout << "\n===== PUNTUACION POR JUGADOR =====\n";
        cout << left
             << setw(20) << "Jugador"
             << setw(12) << "Victorias"
             << setw(12) << "Derrotas"
             << "Total\n";
        cout << string(50, '-') << "\n";

        for (int i = 0; i < nombres.size(); i++) {
            cout << left
                 << setw(20) << nombres[i]
                 << setw(12) << victorias[i]
                 << setw(12) << derrotas[i]
                 << victorias[i] + derrotas[i] << "\n";
        }
    }
};

#endif //PROYECTO_2_FINAL_HISTORIAL_H