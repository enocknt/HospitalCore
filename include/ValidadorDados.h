#pragma once

#include <regex>
#include <string>

// Classe responsável pela validação de dados de entrada
class ValidadorDados {
public:
    // Validar CPF (formato: XXX.XXX.XXX-XX ou XXXXXXXXXXX)
    static bool validarCPF(const std::string &cpf);

    // Validar email (formato básico)
    static bool validarEmail(const std::string &email);

    // Validar nome (apenas letras e espaços, min 3 caracteres)
    static bool validarNome(const std::string &nome);

    // Validar CRM (formato: números com ou sem pontos/hífen)
    static bool validarCRM(const std::string &crm);

    // Validar data (dia, mês, ano)
    static bool validarData(int dia, int mes, int ano);

    // Validar hora (0-23)
    static bool validarHora(int hora);

    // Validar minuto (0-59)
    static bool validarMinuto(int minuto);

    // Validar especialidade (não vazia, min 3 caracteres)
    static bool validarEspecialidade(const std::string &especialidade);

    // Validar histórico médico (não vazio)
    static bool validarHistorico(const std::string &historico);

    // Validar nome de ala (não vazio, sem caracteres especiais)
    static bool validarNomeAla(const std::string &nomeAla);

    // Validar ID de leito (positivo)
    static bool validarIdLeito(int idLeito);

    // Remover formatação de CPF (. e -)
    static std::string limparCPF(const std::string &cpf);

    // Formatar CPF para exibição (XXX.XXX.XXX-XX)
    static std::string formatarCPF(const std::string &cpf);

private:
    // Calcular dígito verificador do CPF
    static int calcularDigitoCPF(const std::string &cpf, int posicao);

    // Verificar se string contém apenas dígitos
    static bool somenteDigitos(const std::string &str);

    // Verificar se string contém apenas letras e espaços
    static bool somenteLetras(const std::string &str);
};