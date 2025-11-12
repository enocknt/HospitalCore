#pragma once

#include "DataHora.h"

// Forward declarations
class Paciente;
class Medico;

class Consulta {
private:
    DataHora dataHora;
    Paciente *paciente; // Não possui
    Medico *medico; // Não possui

public:
    Consulta(Paciente *p, Medico *m, const DataHora &data);

    // Getters
    DataHora getDataHora() const;
    Paciente *getPaciente() const;
    Medico *getMedico() const;

    // Sobrecarga de operador (CRUD)
    friend std::ostream &operator<<(std::ostream &os, const Consulta &c);
};