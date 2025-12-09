#pragma once

#include "DataHora.h"

// Interface para entidades que podem ser agendadas (Consultas, Internações, etc)
class IAgendavel {
public:
    virtual ~IAgendavel() = default;

    // Retorna a data/hora do agendamento
    virtual DataHora obterDataHora() const = 0;

    // Verifica se há conflito com outra data/hora
    virtual bool temConflito(const DataHora &outraData) const = 0;

    // Retorna uma descrição do agendamento
    virtual std::string obterDescricaoAgendamento() const = 0;
};