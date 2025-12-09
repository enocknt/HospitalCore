#pragma once

#include "PreferenciasUsuario.h"
#include "SistemaGestao.h"
#include "ValidadorDados.h"

#include <iostream>
#include <limits>
#include <string>

class Menu {
private:
    SistemaGestao sistema;
    PreferenciasUsuario preferences;
    bool executando;

    // Métodos utilitários
    void exibirMenuPrincipal();
    void processarEscolha(int escolha);
    int lerOpcao();
    std::string lerString(const std::string &prompt);
    std::string lerCPF(const std::string &prompt = "CPF (XXX.XXX.XXX-XX): ");
    std::string lerCRM(const std::string &prompt = "CRM: ");
    std::string lerNome(const std::string &prompt = "Nome: ");
    std::string lerEspecialidade(const std::string &prompt = "Especialidade: ");
    std::string lerHistorico(const std::string &prompt = "Historico: ");
    std::string lerNomeAla(const std::string &prompt = "Nome da Ala: ");
    int lerInt(const std::string &prompt);
    int lerIdLeito(const std::string &prompt = "ID do Leito: ");
    DataHora lerDataHora();
    void limparBuffer();
    void pausar();

    // Funções de CRUD
    void gerenciarPacientes();
    void gerenciarMedicos();
    void gerenciarAlasLeitos();
    void gerenciarConsultas();
    void gerenciarInternacoes();
    void demonstrarPolimorfismo();
    void gerenciarPreferences();

    // Salvar dados
    void salvarDados();

public:
    Menu();

    void executar();
};