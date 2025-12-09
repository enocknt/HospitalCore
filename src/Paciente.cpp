#include <Paciente.h>
#include <ValidadorDados.h>

Paciente::Paciente(const std::string &nome, const std::string &cpf, const std::string &historico)
    : Pessoa(nome, cpf)
    , historicoMedico(historico)
{
}

void Paciente::exibirFicha() const
{
    std::cout << "\n--- Ficha do Paciente ---\n"
              << std::endl;
    std::cout << "Nome:      " << nome << std::endl;
    std::cout << "CPF:       " << ValidadorDados::formatarCPF(cpf) << std::endl;
    std::cout << "Historico: " << historicoMedico << std::endl;
    std::cout << "---------------------------\n"
              << std::endl;
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
    os << "Paciente [Nome: " << p.nome << ", CPF: " << ValidadorDados::formatarCPF(p.cpf) << "]";

    return os;
}