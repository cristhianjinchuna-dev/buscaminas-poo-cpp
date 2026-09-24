//
// Created by LucasMCgamer on 22/06/2026.
//

#ifndef PROYECTO_2_FINAL_CELDA_H
#define PROYECTO_2_FINAL_CELDA_H

#include <iostream>

using namespace std;

class Celda {
private:
    bool EsMina;
    bool EsMarcada;
    bool EsRevelado;
    int Minas_vecinas;
public:
    Celda() {
        EsMina = false;
        EsMarcada = false;
        EsRevelado = false;
        Minas_vecinas = 0;
    }

    bool getEsMina() {
        return EsMina;
    }

    bool getEsMarcada() {
        return EsMarcada;
    }

    bool getEsRevelado() {
        return EsRevelado;
    }

    int getMinas_vecinas() {
        return Minas_vecinas;
    }

    void setEsMina(bool val) {
        EsMina = val;
    }
    void setEsMarcada(bool val) {
        EsMarcada = val;
    }
    void setEsRevelado(bool val) {
        EsRevelado = val;
    }
    void setMinas_vecinas(int val) {
        Minas_vecinas = val;
    }

};


#endif //PROYECTO_2_FINAL_CELDA_H