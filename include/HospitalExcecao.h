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

// Exceção para validação de dados
class ValidacaoExcecao : public HospitalExcecao {
public:
    ValidacaoExcecao(const std::string &msg)
        : HospitalExcecao("[Erro de Validacao] " + msg)
    {
    }
};

// Exceção para CPF inválido
class CPFInvalidoExcecao : public ValidacaoExcecao {
public:
    CPFInvalidoExcecao(const std::string &cpf)
        : ValidacaoExcecao("CPF invalido: " + cpf + ". Use formato XXX.XXX.XXX-XX ou XXXXXXXXXXX")
    {
    }
};

// Exceção para CRM inválido
class CRMInvalidoExcecao : public ValidacaoExcecao {
public:
    CRMInvalidoExcecao(const std::string &crm)
        : ValidacaoExcecao("CRM invalido: " + crm + ". CRM deve conter 4-10 digitos")
    {
    }
};

// Exceção para nome inválido
class NomeInvalidoExcecao : public ValidacaoExcecao {
public:
    NomeInvalidoExcecao(const std::string &nome)
        : ValidacaoExcecao("Nome invalido: " + nome + ". Deve conter apenas letras e ter min. 3 caracteres")
    {
    }
};

// Exceção para data inválida
class DataInvalidaExcecao : public ValidacaoExcecao {
public:
    DataInvalidaExcecao(int dia, int mes, int ano)
        : ValidacaoExcecao("Data invalida: " + std::to_string(dia) + "/" + std::to_string(mes) + "/"
              + std::to_string(ano))
    {
    }
};

// Exceção para hora inválida
class HoraInvalidaExcecao : public ValidacaoExcecao {
public:
    HoraInvalidaExcecao(int hora)
        : ValidacaoExcecao("Hora invalida: " + std::to_string(hora) + ". Deve estar entre 0 e 23")
    {
    }
};

// Exceção para minuto inválido
class MinutoInvalidoExcecao : public ValidacaoExcecao {
public:
    MinutoInvalidoExcecao(int minuto)
        : ValidacaoExcecao("Minuto invalido: " + std::to_string(minuto) + ". Deve estar entre 0 e 59")
    {
    }
};