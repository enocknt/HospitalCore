#pragma once

#include "HospitalExcecao.h"
#include "Leito.h"

#include <memory>
#include <string>
#include <vector>

class AlaHospitalar {
private:
    std::string nomeAla;
    std::vector<std::unique_ptr<Leito> > leitos; // Ala "possui" os leitos

public:
    AlaHospitalar(const std::string &nome);

    void adicionarLeito(int idLeito);
    Leito *buscarLeitoDisponivel();
    void listarLeitos() const;
    std::string getNome() const;

    // CRUD
    Leito *buscarLeito(int idLeito);
    bool removerLeito(int idLeito);

    // Getter público para permitir iteração (leitura)
    const std::vector<std::unique_ptr<Leito> > &getLeitos() const;
};