#pragma once

#include <exception>
#include <string>

// Classe base para todas as exceções customizadas do sistema
// Herda de std::exception para polimorfismo
class HospitalExcecao : public std::exception {
protected:
    std::string mensagem;

public:
    HospitalExcecao(const std::string &msg)
        : mensagem(msg)
    {
    }

    // Polimorfismo: Sobrescreve o método what()
    virtual const char *what() const noexcept override
    {
        return mensagem.c_str();
    }
};

// Exceção para erros de agendamento
class AgendamentoExcecao : public HospitalExcecao {
public:
    AgendamentoExcecao(const std::string &msg)
        : HospitalExcecao("[Erro de Agendamento] " + msg)
    {
    }
};

// Exceção para erros de alocação de leitos
class LeitoExcecao : public HospitalExcecao {
public:
    LeitoExcecao(const std::string &msg)
        : HospitalExcecao("[Erro de Alocacao] " + msg)
    {
    }
};

// Exceção para buscas (CRUD)
class EntidadeNaoEncontradaExcecao : public HospitalExcecao {
public:
    EntidadeNaoEncontradaExcecao(const std::string &msg)
        : HospitalExcecao("[Erro de Busca] " + msg)
    {
    }
};