#include "Leito.h"
#include "Paciente.h"

Leito::Leito(int id)
    : idLeito(id)
    , ocupado(false)
    , pacienteAlocado(nullptr)
{
}

bool Leito::estaOcupado() const
{
    return ocupado;
}

void Leito::ocupar(Paciente *p)
{
    this->pacienteAlocado = p;
    this->ocupado = true;
}

void Leito::desocupar()
{
    this->pacienteAlocado = nullptr;
    this->ocupado = false;
}

int Leito::getId() const
{
    return idLeito;
}

Paciente *Leito::getPaciente() const
{
    return pacienteAlocado;
}

// Implementação da sobrecarga de operador
std::ostream &operator<<(std::ostream &os, const Leito &l)
{
    os << "Leito [ID: " << l.idLeito << ", Status: " << (l.ocupado ? "Ocupado" : "Livre");

    if (l.ocupado) {
        os << ", Paciente: " << l.pacienteAlocado->getNome();
    }

    os << "]";

    return os;
}