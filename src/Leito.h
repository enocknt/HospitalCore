#pragma once

#include <iostream>

// Forward declaration para evitar inclusão circular
class Paciente;

class Leito {
private:
    int idLeito;
    bool ocupado;
    Paciente *pacienteAlocado; // Ponteiro bruto, pois o Leito não "possui" o Paciente

public:
    Leito(int id);

    bool estaOcupado() const;
    void ocupar(Paciente *p);
    void desocupar();
    int getId() const;
    Paciente *getPaciente() const;

    // Sobrecarga de operador (CRUD)
    friend std::ostream &operator<<(std::ostream &os, const Leito &l);
};