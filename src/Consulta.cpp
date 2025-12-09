#include <Consulta.h>
#include <Medico.h>
#include <Paciente.h>

Consulta::Consulta(Paciente *p, Medico *m, const DataHora &data)
    : dataHora(data)
    , paciente(p)
    , medico(m)
{
}

// Implementação da interface IAgendavel
DataHora Consulta::obterDataHora() const
{
    return dataHora;
}

bool Consulta::temConflito(const DataHora &outraData) const
{
    return dataHora == outraData;
}

std::string Consulta::obterDescricaoAgendamento() const
{
    return "Consulta agendada para " + std::to_string(dataHora.dia) + "/" + std::to_string(dataHora.mes) + "/" + std::to_string(dataHora.ano);
}

DataHora Consulta::getDataHora() const
{
    return dataHora;
}

Paciente *Consulta::getPaciente() const
{
    return paciente;
}

Medico *Consulta::getMedico() const
{
    return medico;
}

// Implementação da sobrecarga de operador
std::ostream &operator<<(std::ostream &os, const Consulta &c)
{
    os << "\n  Consulta:\n"
       << "    Data/Hora: " << c.dataHora << "\n"
       << "    Paciente:  " << c.paciente->getNome() << "\n"
       << "    Medico:    Dr(a). " << c.medico->getNome() << "\n";

    return os;
}