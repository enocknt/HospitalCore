#include "Medico.h"

Medico::Medico(const std::string &nome, const std::string &cpf, const std::string &especialidade, const std::string &crm)
    : Pessoa(nome, cpf)
    , especialidade(especialidade)
    , crm(crm)
{
}

void Medico::exibirFicha() const
{
    std::cout << "--- Ficha do Medico ---" << std::endl;
    std::cout << "Nome: Dr(a). " << nome << std::endl;
    std::cout << "CPF: " << cpf << std::endl;
    std::cout << "CRM: " << crm << std::endl;
    std::cout << "Especialidade: " << especialidade << std::endl;
    std::cout << "-----------------------" << std::endl;
}

std::string Medico::getEspecialidade() const
{
    return especialidade;
}

std::string Medico::getCrm() const
{
    return crm;
}

// Implementação da sobrecarga de operador
std::ostream &operator<<(std::ostream &os, const Medico &m)
{
    os << "Medico [Nome: Dr(a). " << m.nome << ", CRM: " << m.crm << ", Esp: " << m.especialidade << "]";

    return os;
}