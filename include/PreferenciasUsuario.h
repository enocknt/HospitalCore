#pragma once

#include <string>
#include "IGerenciavel.h"

// Classe para armazenar preferências do usuário
// Implementa IGerenciavel para ser gerenciada como uma entidade
class PreferenciasUsuario : public IGerenciavel {
private:
    std::string nomeExibicao;
    std::string tema; // "claro" ou "escuro"

public:
    PreferenciasUsuario();
    PreferenciasUsuario(const std::string &nome, const std::string &t);

    // Getters
    std::string getNomeExibicao() const;
    std::string getTema() const;

    // Setters
    void setNomeExibicao(const std::string &nome);
    void setTema(const std::string &t);

    // Verificar tema
    bool ehTemaDarkModeAtivo() const;

    // Implementação da interface IGerenciavel
    virtual std::string obterIdentificador() const override;
    virtual std::string obterDescricao() const override;
};