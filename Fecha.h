//
// Created by LucasMCgamer on 22/06/2026.
//

#ifndef PROYECTO_2_FINAL_FECHA_H
#define PROYECTO_2_FINAL_FECHA_H

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Fecha {
private:
    int dia, mes, ano, hora, minuto;
public:
    Fecha() {
        time_t ahora = time(nullptr);
        tm* f = localtime(&ahora);
        dia    = f->tm_mday;
        mes    = f->tm_mon + 1;
        ano    = f->tm_year + 1900;
        hora   = f->tm_hour;
        minuto = f->tm_min;
    }


    Fecha(int d, int m, int a, int h, int min)
        : dia(d), mes(m), ano(a), hora(h), minuto(min) {}

    string formatear() const {
        string s = "";
        s += (dia < 10 ? "0" : "") + to_string(dia) + "/";
        s += (mes < 10 ? "0" : "") + to_string(mes) + "/";
        s += to_string(ano) + " ";
        s += (hora < 10 ? "0" : "") + to_string(hora) + ":";
        s += (minuto < 10 ? "0" : "") + to_string(minuto);
        return s;
    }

    friend ostream& operator<<(ostream& os, const Fecha& f) {
        os << f.formatear();
        return os;
    }
};

#endif //PROYECTO_2_FINAL_FECHA_H