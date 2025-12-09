#pragma once

#include <string>

// Forward declarations
class SistemaGestao;
class PreferenciasUsuario;

// Classe responsável pela persistência de dados em arquivos
class GerenciadorArquivos {
private:
    static const std::string ARQUIVO_PACIENTES;
    static const std::string ARQUIVO_MEDICOS;
    static const std::string ARQUIVO_ALAS;
    static const std::string ARQUIVO_LEITOS;
    static const std::string ARQUIVO_CONSULTAS;
    static const std::string ARQUIVO_INTERNACOES;
    static const std::string ARQUIVO_PREFERENCES;

public:
    // Salvar dados
    static void salvarPacientes(const SistemaGestao &sistema);
    static void salvarMedicos(const SistemaGestao &sistema);
    static void salvarAlas(const SistemaGestao &sistema);
    static void salvarLeitos(const SistemaGestao &sistema);
    static void salvarConsultas(const SistemaGestao &sistema);
    static void salvarInternacoes(const SistemaGestao &sistema);
    static void salvarPreferences(const PreferenciasUsuario &pref);

    // Carregar dados
    static void carregarPacientes(SistemaGestao &sistema);
    static void carregarMedicos(SistemaGestao &sistema);
    static void carregarAlas(SistemaGestao &sistema);
    static void carregarConsultas(SistemaGestao &sistema);
    static void carregarInternacoes(SistemaGestao &sistema);
    static PreferenciasUsuario carregarPreferences();

    // Salvar e carregar tudo
    static void salvarTudo(const SistemaGestao &sistema, const PreferenciasUsuario &pref);
    static void carregarTudo(SistemaGestao &sistema, PreferenciasUsuario &pref);

    // Verificar se arquivo existe
    static bool arquivoExiste(const std::string &nomeArquivo);
};