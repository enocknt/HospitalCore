#include "Pessoa.h"

Pessoa::Pessoa(const std::string &nome, const std::string &cpf)
    : nome(nome)
    , cpf(cpf)
{
}

std::string Pessoa::getNome() const
{
    return nome;
}

std::string Pessoa::getCpf() const
{
    return cpf;
}