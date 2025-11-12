#include "Consulta.h"
#include "Medico.h"
#include "Paciente.h"

Consulta::Consulta(Paciente *p, Medico *m, const DataHora &data)
    : dataHora(data)
    , paciente(p)
    , medico(m)
{
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
    os << "Consulta [Data: " << c.dataHora
       << " | Paciente: " << c.paciente->getNome()
       << " | Medico: Dr(a). " << c.medico->getNome() << "]";

    return os;
}