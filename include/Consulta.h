#pragma once

#include "DataHora.h"
#include "IAgendavel.h"

// Forward declarations
class Paciente;
class Medico;

class Consulta : public IAgendavel {
private:
    DataHora dataHora;
    Paciente *paciente;
    Medico *medico;

public:
    Consulta(Paciente *p, Medico *m, const DataHora &data);

    // Implementação da interface IAgendavel
    DataHora obterDataHora() const override;
    bool temConflito(const DataHora &outraData) const override;
    std::string obterDescricaoAgendamento() const override;

    // Getters
    DataHora getDataHora() const;
    Paciente *getPaciente() const;
    Medico *getMedico() const;

    // Sobrecarga de operador (CRUD)
    friend std::ostream &operator<<(std::ostream &os, const Consulta &c);
};