#include <Medico.h>
#include <ValidadorDados.h>

Medico::Medico(const std::string &nome, const std::string &cpf, const std::string &especialidade, const std::string &crm)
    : Pessoa(nome, cpf)
    , especialidade(especialidade)
    , crm(crm)
{
}

void Medico::exibirFicha() const
{
    std::cout << "\n--- Ficha do Medico ---\n"
              << std::endl;
    std::cout << "Nome:           Dr(a). " << nome << std::endl;
    std::cout << "CPF:            " << ValidadorDados::formatarCPF(cpf) << std::endl;
    std::cout << "CRM:            " << crm << std::endl;
    std::cout << "Especialidade:  " << especialidade << std::endl;
    std::cout << "------------------------\n"
              << std::endl;
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
    os << "Medico [Nome: Dr(a). " << m.nome << ", CRM: " << m.crm << ", CPF: " << ValidadorDados::formatarCPF(m.cpf) << ", Esp: " << m.especialidade << "]";

    return os;
}