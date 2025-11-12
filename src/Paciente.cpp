#include "Paciente.h"

Paciente::Paciente(const std::string &nome, const std::string &cpf, const std::string &historico)
    : Pessoa(nome, cpf)
    , historicoMedico(historico)
{
}

void Paciente::exibirFicha() const
{
    std::cout << "--- Ficha do Paciente ---" << std::endl;
    std::cout << "Nome: " << nome << std::endl;
    std::cout << "CPF: " << cpf << std::endl;
    std::cout << "Historico: " << historicoMedico << std::endl;
    std::cout << "-------------------------" << std::endl;
}

std::string Paciente::getHistorico() const
{
    return historicoMedico;
}

void Paciente::setHistorico(const std::string &novoHistorico)
{
    this->historicoMedico = novoHistorico;
}

// Implementação da sobrecarga de operador
std::ostream &operator<<(std::ostream &os, const Paciente &p)
{
    os << "Paciente [Nome: " << p.nome << ", CPF: " << p.cpf << "]";

    return os;
}