//
// Created by LucasMCgamer on 22/06/2026.
//

#ifndef PROYECTO_2_FINAL_TABLERO_H
#define PROYECTO_2_FINAL_TABLERO_H

#include <cstdlib>
#include "Celda.h"
#include <vector>
#include <ctime>


class Tablero {
private:
    int minas;
    int filas = 14;
    int columnas = 18;
    bool perdioMaquina = false;
    vector<vector<Celda>> matriz;
public:
    int getFilas() { return filas; }
    int getColumnas() { return columnas; }
    bool getPerdio() { return perdioMaquina; }

    Tablero(int m) {

        int maxMinas = filas * columnas - 1;
        if (m < 0) m = 0;
        if (m > maxMinas) m = maxMinas;

        minas = m;
        int minas_puestas = 0;
        matriz.resize(filas, vector<Celda>(columnas));

        while (minas_puestas < m) {
            int i = rand() % filas;
            int j = rand() % columnas;
            if (!matriz[i][j].getEsMina()) {
                matriz[i][j].setEsMina(true);
                minas_puestas++;
            }
        }

        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if (matriz[i][j].getEsMina()) continue;
                int contador = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas)
                            if (matriz[ni][nj].getEsMina())
                                contador++;
                    }
                matriz[i][j].setMinas_vecinas(contador);
            }
        }
    }

    void mostrar(bool MinasReveladas) {
        cout << "   ";
        for (int j = 0; j < columnas; j++)
            cout << (j < 10 ? " " : "") << j << " ";
        cout << endl;

        cout << "   ";
        for (int j = 0; j < columnas; j++)
            cout << "---";
        cout << endl;

        for (int i = 0; i < filas; i++) {
            cout << (i < 10 ? " " : "") << i << " |";
            for (int j = 0; j < columnas; j++) {
                Celda& c = matriz[i][j];
                if (MinasReveladas && c.getEsMina())
                    cout << " * ";
                else if (c.getEsMarcada())
                    cout << " F ";
                else if (!c.getEsRevelado())
                    cout << " # ";
                else {
                    int n = c.getMinas_vecinas();
                    cout << (n == 0 ? " . " : " " + to_string(n) + " ");
                }
            }
            cout << endl;
        }
    }

    void revelar(int f, int c) {
        if (!SePuedeRevelar(f, c)) return;
        matriz[f][c].setEsRevelado(true);
        if (matriz[f][c].getMinas_vecinas() == 0) {
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                    if (di != 0 || dj != 0)
                        revelar(f + di, c + dj);
        }
    }

    bool SePuedeRevelar(int f, int c) {
        if (f < 0 || f >= filas || c < 0 || c >= columnas) return false;
        if (matriz[f][c].getEsMina()) return false;
        if (matriz[f][c].getEsRevelado()) return false;
        if (matriz[f][c].getEsMarcada()) return false; // una celda marcada no se revela (ni por expansion recursiva)
        return true;
    }

    bool perdio(int f, int c) {
        if (f < 0 || f >= filas || c < 0 || c >= columnas) return false;
        return matriz[f][c].getEsMina();
    }

    bool gano() {
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                if (!matriz[i][j].getEsMina() && !matriz[i][j].getEsRevelado())
                    return false;
        return true;
    }

    void marcar(int f, int c) {
        if (f < 0 || f >= filas || c < 0 || c >= columnas) return;
        if (matriz[f][c].getEsRevelado()) return;
        matriz[f][c].setEsMarcada(!matriz[f][c].getEsMarcada());
    }

    void jugadaMaquina() {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if (!matriz[i][j].getEsRevelado()) continue;
                int n = matriz[i][j].getMinas_vecinas();
                if (n == 0) continue;

                int sinRevelar = 0, marcadas = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i+di, nj = j+dj;
                        if (ni < 0 || ni >= filas || nj < 0 || nj >= columnas) continue;
                        if (!matriz[ni][nj].getEsRevelado()) sinRevelar++;
                        if (matriz[ni][nj].getEsMarcada()) marcadas++;
                    }


                if (sinRevelar > 0 && sinRevelar == n && marcadas < n) {
                    for (int di = -1; di <= 1; di++)
                        for (int dj = -1; dj <= 1; dj++) {
                            if (di == 0 && dj == 0) continue;
                            int ni = i+di, nj = j+dj;
                            if (ni < 0 || ni >= filas || nj < 0 || nj >= columnas) continue;
                            if (!matriz[ni][nj].getEsRevelado() && !matriz[ni][nj].getEsMarcada())
                                matriz[ni][nj].setEsMarcada(true);
                        }
                    return;
                }

                if (marcadas == n && sinRevelar > marcadas) {
                    for (int di = -1; di <= 1; di++)
                        for (int dj = -1; dj <= 1; dj++) {
                            if (di == 0 && dj == 0) continue;
                            int ni = i+di, nj = j+dj;
                            if (ni < 0 || ni >= filas || nj < 0 || nj >= columnas) continue;
                            if (!matriz[ni][nj].getEsRevelado() && !matriz[ni][nj].getEsMarcada()) {
                                if (matriz[ni][nj].getEsMina()) {
                                    perdioMaquina = true;
                                    return;
                                }
                                revelar(ni, nj);
                                return;
                            }
                        }
                }
            }
        }

        vector<int> filasC, columnasC;
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                if (!matriz[i][j].getEsRevelado() && !matriz[i][j].getEsMarcada()) {
                    filasC.push_back(i);
                    columnasC.push_back(j);
                }

        if (filasC.empty()) {
            perdioMaquina = true;
            return;
        }

        int idx = rand() % filasC.size();
        int f = filasC[idx];
        int c = columnasC[idx];

        if (matriz[f][c].getEsMina()) {
            perdioMaquina = true;
            return;
        }
        revelar(f, c);
    }

    void setPerdio(bool val) {
        perdioMaquina = val;
    }

};




#endif //PROYECTO_2_FINAL_TABLERO_H