#include "AlaHospitalar.h"

AlaHospitalar::AlaHospitalar(const std::string &nome)
    : nomeAla(nome)
{
}

void AlaHospitalar::adicionarLeito(int idLeito)
{
    // Verifica se já existe
    for (const auto &leito : leitos) {
        if (leito->getId() == idLeito) {
            throw LeitoExcecao("Leito com ID " + std::to_string(idLeito) + " ja existe nesta ala.");
        }
    }

    leitos.push_back(std::make_unique<Leito>(idLeito));
}

Leito *AlaHospitalar::buscarLeitoDisponivel()
{
    for (const auto &leito : leitos) {
        if (!leito->estaOcupado()) {
            return leito.get(); // Retorna ponteiro bruto
        }
    }

    // Lança exceção customizada
    throw LeitoExcecao("Nenhum leito disponivel na ala " + nomeAla);
}

void AlaHospitalar::listarLeitos() const
{
    std::cout << "--- Leitos da Ala: " << nomeAla << " ---" << std::endl;

    if (leitos.empty()) {
        std::cout << "Nenhum leito cadastrado." << std::endl;
        return;
    }

    for (const auto &leito : leitos) {
        std::cout << *leito << std::endl; // Usa o operator<<
    }
}

std::string AlaHospitalar::getNome() const
{
    return nomeAla;
}

Leito *AlaHospitalar::buscarLeito(int idLeito)
{
    for (const auto &leito : leitos) {
        if (leito->getId() == idLeito) {
            return leito.get();
        }
    }

    throw EntidadeNaoEncontradaExcecao("Leito " + std::to_string(idLeito) + " nao encontrado.");
}

bool AlaHospitalar::removerLeito(int idLeito)
{
    for (auto it = leitos.begin(); it != leitos.end(); ++it) {
        if ((*it)->getId() == idLeito) {
            if ((*it)->estaOcupado()) {
                throw LeitoExcecao("Nao pode remover leito ocupado.");
            }

            leitos.erase(it);

            return true;
        }
    }

    return false;
}

const std::vector<std::unique_ptr<Leito> > &AlaHospitalar::getLeitos() const
{
    return this->leitos;
}