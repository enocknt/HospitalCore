#include <ValidadorDados.h>
#include <algorithm>
#include <cctype>

bool ValidadorDados::somenteDigitos(const std::string &str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

bool ValidadorDados::somenteLetras(const std::string &str)
{
    if (str.empty())
        return false;

    for (char c : str) {
        if (!isalpha(c) && c != ' ')
            return false;
    }

    return true;
}

bool ValidadorDados::validarCPF(const std::string &cpf)
{
    std::string cpfLimpo = limparCPF(cpf);

    // CPF deve ter exatamente 11 dígitos
    if (cpfLimpo.length() != 11 || !somenteDigitos(cpfLimpo))
        return false;

    // Verificar se todos os dígitos são iguais (CPFs inválidos)
    if (cpfLimpo[0] == cpfLimpo[1] && cpfLimpo[1] == cpfLimpo[2] && cpfLimpo[2] == cpfLimpo[3])
        return false; // Todos os dígitos são iguais

    // Calcular e verificar primeiro dígito verificador
    int digito1 = calcularDigitoCPF(cpfLimpo, 10);

    if (cpfLimpo[9] - '0' != digito1)
        return false;

    // Calcular e verificar segundo dígito verificador
    int digito2 = calcularDigitoCPF(cpfLimpo, 11);

    if (cpfLimpo[10] - '0' != digito2)
        return false;

    return true;
}

int ValidadorDados::calcularDigitoCPF(const std::string &cpf, int posicao)
{
    int soma = 0;

    int multiplicador = posicao;

    for (int i = 0; i < posicao - 1; i++) {
        soma += (cpf[i] - '0') * multiplicador;
        multiplicador--;
    }

    int resto = soma % 11;

    return resto < 2 ? 0 : 11 - resto;
}

std::string ValidadorDados::limparCPF(const std::string &cpf)
{
    std::string cpfLimpo;

    for (char c : cpf) {
        if (isdigit(c)) {
            cpfLimpo += c;
        }
    }

    return cpfLimpo;
}

std::string ValidadorDados::formatarCPF(const std::string &cpf)
{
    std::string cpfLimpo = limparCPF(cpf);

    if (cpfLimpo.length() != 11)
        return cpf; // Retorna original se inválido

    return cpfLimpo.substr(0, 3) + "." + cpfLimpo.substr(3, 3) + "." + cpfLimpo.substr(6, 3) + "-" + cpfLimpo.substr(9, 2);
}

bool ValidadorDados::validarNome(const std::string &nome)
{
    if (nome.length() < 3)
        return false;

    return somenteLetras(nome);
}

bool ValidadorDados::validarCRM(const std::string &crm)
{
    // CRM deve ter entre 4 e 10 dígitos
    std::string crmLimpo;

    for (char c : crm) {
        if (isdigit(c)) {
            crmLimpo += c;
        }
    }

    return crmLimpo.length() >= 4 && crmLimpo.length() <= 10;
}

bool ValidadorDados::validarEmail(const std::string &email)
{
    // Usa string padrão para evitar problemas com raw string e formatação
    std::regex emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

    return std::regex_match(email, emailRegex);
}

bool ValidadorDados::validarData(int dia, int mes, int ano)
{
    // Validar ano (deve ser razoável)
    if (ano < 1900 || ano > 2100)
        return false;

    // Validar mês
    if (mes < 1 || mes > 12)
        return false;

    // Validar dia conforme o mês
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Verificar ano bissexto
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasPorMes[1] = 29;
    }

    return dia >= 1 && dia <= diasPorMes[mes - 1];
}

bool ValidadorDados::validarHora(int hora)
{
    return hora >= 0 && hora <= 23;
}

bool ValidadorDados::validarMinuto(int minuto)
{
    return minuto >= 0 && minuto <= 59;
}

bool ValidadorDados::validarEspecialidade(const std::string &especialidade)
{
    if (especialidade.length() < 3)
        return false;

    // Permitir letras, espaços e alguns caracteres especiais comuns
    for (char c : especialidade) {
        if (!isalnum(c) && c != ' ' && c != '-' && c != '/')
            return false;
    }

    return true;
}

bool ValidadorDados::validarHistorico(const std::string &historico)
{
    return !historico.empty() && historico.length() <= 500;
}

bool ValidadorDados::validarNomeAla(const std::string &nomeAla)
{
    if (nomeAla.empty() || nomeAla.length() > 50)
        return false;

    for (char c : nomeAla) {
        if (!isalnum(c) && c != ' ' && c != '-')
            return false;
    }

    return true;
}

bool ValidadorDados::validarIdLeito(int idLeito)
{
    return idLeito > 0 && idLeito < 10000; // Leito com ID entre 1 e 9999
}