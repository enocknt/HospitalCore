#pragma once

#include <iostream>
#include <string>

// Classe base abstrata
class Pessoa {
protected:
    std::string nome;
    std::string cpf;

public:
    Pessoa(const std::string &nome, const std::string &cpf);
    virtual ~Pessoa() = default; // Destrutor virtual

    // Polimorfismo: Método virtual puro
    virtual void exibirFicha() const = 0;

    // Getters
    std::string getNome() const;
    std::string getCpf() const;
};