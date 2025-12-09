#pragma once

#include "Pessoa.h"

class Paciente : public Pessoa {
private:
    std::string historicoMedico;

public:
    Paciente(const std::string &nome, const std::string &cpf, const std::string &historico);

    // Polimorfismo: Implementação do método
    virtual void exibirFicha() const override;

    // Getters/Setters
    std::string getHistorico() const;
    void setHistorico(const std::string &novoHistorico);

    // Sobrecarga de operador (CRUD)
    friend std::ostream &operator<<(std::ostream &os, const Paciente &p);
};