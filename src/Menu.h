#pragma once

#include "SistemaGestao.h"

#include <iostream>
#include <limits>
#include <string>

class Menu {
private:
    SistemaGestao sistema;
    bool executando;

    // Métodos utilitários
    void exibirMenuPrincipal();
    void processarEscolha(int escolha);
    int lerOpcao();
    std::string lerString(const std::string &prompt);
    int lerInt(const std::string &prompt);
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

public:
    Menu();

    void executar();
};