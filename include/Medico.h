#pragma once

#include "Pessoa.h"

class Medico : public Pessoa {
private:
    std::string especialidade;
    std::string crm;

public:
    Medico(const std::string &nome, const std::string &cpf, const std::string &especialidade, const std::string &crm);

    // Polimorfismo: Implementação do método
    virtual void exibirFicha() const override;

    // Getters
    std::string getEspecialidade() const;
    std::string getCrm() const;

    // Sobrecarga de operador (CRUD)
    friend std::ostream &operator<<(std::ostream &os, const Medico &m);
};