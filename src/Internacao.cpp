#include <Internacao.h>
#include <Paciente.h>

Internacao::Internacao(Paciente *p, const std::string &ala, int leito, const DataHora &entrada)
    : paciente(p)
    , nomeAla(ala)
    , idLeito(leito)
    , dataEntrada(entrada)
{
}

DataHora Internacao::obterDataHora() const
{
    return dataEntrada;
}

bool Internacao::temConflito(const DataHora &outraData) const
{
    // Há conflito se a outra data está dentro do período da internação
    return outraData == dataEntrada;
}

std::string Internacao::obterDescricaoAgendamento() const
{
    return "Internacao na ala " + nomeAla + ", leito " + std::to_string(idLeito);
}

Paciente *Internacao::getPaciente() const
{
    return paciente;
}

std::string Internacao::getNomeAla() const
{
    return nomeAla;
}

int Internacao::getIdLeito() const
{
    return idLeito;
}

DataHora Internacao::getDataEntrada() const
{
    return dataEntrada;
}

DataHora Internacao::getDataSaida() const
{
    return dataSaida;
}

void Internacao::setDataSaida(const DataHora &saida)
{
    this->dataSaida = saida;
}

bool Internacao::estaAinda() const
{
    return dataSaida.ano == 0; // DataHora vazia tem ano 0
}

std::ostream &operator<<(std::ostream &os, const Internacao &i)
{
    os << "\n  Internacao:\n"
       << "    Ala:       " << i.nomeAla << "\n"
       << "    Leito:     " << i.idLeito << "\n"
       << "    Entrada:   " << i.dataEntrada;

    if (!i.estaAinda()) {
        os << "\n    Saida:     " << i.dataSaida;
    }

    os << "\n";

    return os;
}