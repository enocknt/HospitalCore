#pragma once

#include "DataHora.h"
#include "IAgendavel.h"

// Forward declarations
class Paciente;

class Internacao : public IAgendavel {
private:
    Paciente *paciente;
    std::string nomeAla;
    int idLeito;
    DataHora dataEntrada;
    DataHora dataSaida;

public:
    Internacao(Paciente *p, const std::string &ala, int leito, const DataHora &entrada);

    // Implementação da interface IAgendavel
    DataHora obterDataHora() const override;
    bool temConflito(const DataHora &outraData) const override;
    std::string obterDescricaoAgendamento() const override;

    // Getters
    Paciente *getPaciente() const;
    std::string getNomeAla() const;
    int getIdLeito() const;
    DataHora getDataEntrada() const;
    DataHora getDataSaida() const;

    // Setters
    void setDataSaida(const DataHora &saida);

    // Verificar se ainda está internado
    bool estaAinda() const;

    // Sobrecarga de operador
    friend std::ostream &operator<<(std::ostream &os, const Internacao &i);
};