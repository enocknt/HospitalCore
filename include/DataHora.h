#pragma once

#include <iostream>
#include <string>

// Simples struct para armazenar data e hora
struct DataHora {
    int dia, mes, ano, hora, minuto;

    DataHora(int d = 1, int m = 1, int a = 2025, int h = 0, int min = 0)
        : dia(d)
        , mes(m)
        , ano(a)
        , hora(h)
        , minuto(min)
    {
    }

    // Sobrecarga de operador << para facilitar a exibição
    friend std::ostream &operator<<(std::ostream &os, const DataHora &dt)
    {
        os << dt.dia << "/" << dt.mes << "/" << dt.ano << " " << dt.hora << ":" << dt.minuto;

        return os;
    }

    // Sobrecarga de operador == para verificar conflitos
    bool operator==(const DataHora &other) const
    {
        return dia == other.dia && mes == other.mes && ano == other.ano && hora == other.hora; // Simplificado para conflito de hora cheia
    }
};