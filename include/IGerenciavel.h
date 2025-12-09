#pragma once

#include <string>

// Interface para entidades que podem ser gerenciadas (CRUD)
// Garante que todas as entidades gerenciáveis implementem métodos de identificação
class IGerenciavel {
public:
    virtual ~IGerenciavel() = default;

    // Retorna um identificador único para a entidade
    virtual std::string obterIdentificador() const = 0;

    // Retorna uma descrição textual da entidade
    virtual std::string obterDescricao() const = 0;
};