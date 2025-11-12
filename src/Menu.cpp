#include "Menu.h"

Menu::Menu()
    : executando(true)
{
}

void Menu::executar()
{
    while (executando) {
        exibirMenuPrincipal();

        int escolha = lerOpcao();

        // Trata exceções globais (validação, etc)
        try {
            processarEscolha(escolha);
        } catch (const HospitalExcecao &e) {
            std::cerr << "\n!!! Erro: " << e.what() << " !!!" << std::endl;
            pausar();
        } catch (const std::exception &e) {
            std::cerr << "\n!!! Erro Inesperado: " << e.what() << " !!!" << std::endl;
            pausar();
        }
    }
}

void Menu::exibirMenuPrincipal()
{
    std::cout << std::endl
              << "--- Sistema de Gestao Hospitalar 'HospitalCore' ---" << std::endl
              << std::endl;

    std::cout << "1. Gerenciar Pacientes" << std::endl;
    std::cout << "2. Gerenciar Medicos" << std::endl;
    std::cout << "3. Gerenciar Alas e Leitos" << std::endl;
    std::cout << "4. Gerenciar Consultas" << std::endl;
    std::cout << "5. Gerenciar Internacoes" << std::endl;
    std::cout << "6. Listar Ficha de Todas as Pessoas" << std::endl;
    std::cout << "0. Sair" << std::endl
              << std::endl;

    std::cout << "Escolha uma opcao: ";
}

void Menu::processarEscolha(int escolha)
{
    switch (escolha) {
        case 1:
            gerenciarPacientes();
            break;
        case 2:
            gerenciarMedicos();
            break;
        case 3:
            gerenciarAlasLeitos();
            break;
        case 4:
            gerenciarConsultas();
            break;
        case 5:
            gerenciarInternacoes();
            break;
        case 6:
            demonstrarPolimorfismo();
            break;
        case 0:
            executando = false;
            break;
        default:
            std::cout << "Opcao invalida." << std::endl;
            pausar();
    }
}

// --- Funções de CRUD (Exemplos) ---

void Menu::gerenciarPacientes()
{
    std::cout << std::endl
              << "--- Gestao de Pacientes ---" << std::endl
              << std::endl;
    std::cout << "1. Adicionar Paciente" << std::endl;
    std::cout << "2. Listar Pacientes" << std::endl;
    std::cout << "3. Buscar Paciente (por CPF)" << std::endl;
    std::cout << "4. Atualizar Historico" << std::endl;
    std::cout << "5. Remover Paciente" << std::endl;
    std::cout << "0. Voltar" << std::endl
              << std::endl;

    int escolha = lerOpcao();

    if (escolha == 1) {
        std::string n = lerString("Nome: ");
        std::string c = lerString("CPF: ");
        std::string h = lerString("Historico: ");

        sistema.adicionarPaciente(n, c, h);

        std::cout << "Paciente adicionado com sucesso!" << std::endl;
    } else if (escolha == 2) {
        sistema.listarPacientes();
    } else if (escolha == 3) {
        std::string c = lerString("CPF: ");

        Paciente *p = sistema.buscarPacientePorCpf(c);

        p->exibirFicha();
    } else if (escolha == 4) {
        std::string c = lerString("CPF: ");

        Paciente *p = sistema.buscarPacientePorCpf(c);

        std::string h = lerString("Novo Historico: ");

        p->setHistorico(h);

        std::cout << "Historico atualizado." << std::endl;
    } else if (escolha == 5) {
        std::string c = lerString("CPF: ");

        if (sistema.removerPessoa(c))
            std::cout << "Paciente removido." << std::endl;
        else
            std::cout << "Paciente nao encontrado." << std::endl;
    }

    if (escolha != 0)
        pausar();
}

void Menu::gerenciarMedicos()
{
    std::cout << std::endl
              << "--- Gestao de Medicos ---" << std::endl
              << std::endl;
    std::cout << "1. Adicionar Medico" << std::endl;
    std::cout << "2. Listar Medicos" << std::endl;
    std::cout << "3. Buscar Medico (por CRM)" << std::endl;
    std::cout << "0. Voltar" << std::endl
              << std::endl;

    int escolha = lerOpcao();

    if (escolha == 1) {
        std::string n = lerString("Nome: ");
        std::string c = lerString("CPF: ");
        std::string e = lerString("Especialidade: ");
        std::string crm = lerString("CRM: ");

        sistema.adicionarMedico(n, c, e, crm);

        std::cout << "Medico adicionado com sucesso!" << std::endl;
    } else if (escolha == 2) {
        sistema.listarMedicos();
    } else if (escolha == 3) {
        std::string crm = lerString("CRM: ");

        Medico *m = sistema.buscarMedicoPorCrm(crm);

        m->exibirFicha();
    }

    if (escolha != 0)
        pausar();
}

void Menu::gerenciarAlasLeitos()
{
    std::cout << std::endl
              << "--- Gestao de Alas e Leitos ---" << std::endl
              << std::endl;
    std::cout << "1. Adicionar Ala" << std::endl;
    std::cout << "2. Listar Alas" << std::endl;
    std::cout << "3. Adicionar Leito a uma Ala" << std::endl;
    std::cout << "4. Listar Leitos de uma Ala" << std::endl;
    std::cout << "0. Voltar" << std::endl
              << std::endl;

    int escolha = lerOpcao();

    if (escolha == 1) {
        std::string n = lerString("Nome da Ala (ex: Cardiologia): ");

        sistema.adicionarAla(n);

        std::cout << "Ala adicionada!" << std::endl;
    } else if (escolha == 2) {
        sistema.listarAlas();
    } else if (escolha == 3) {
        std::string n = lerString("Nome da Ala: ");

        int id = lerInt("ID do novo Leito (ex: 101): ");

        sistema.adicionarLeitoNaAla(n, id);

        std::cout << "Leito adicionado!" << std::endl;
    } else if (escolha == 4) {
        std::string n = lerString("Nome da Ala: ");

        sistema.listarLeitosDaAla(n);
    }

    if (escolha != 0)
        pausar();
}

void Menu::gerenciarConsultas()
{
    std::cout << std::endl
              << "--- Gestao de Consultas ---" << std::endl
              << std::endl;
    std::cout << "1. Agendar Consulta" << std::endl;
    std::cout << "2. Listar Consultas" << std::endl;
    std::cout << "3. Cancelar Consulta" << std::endl;
    std::cout << "0. Voltar" << std::endl
              << std::endl;

    int escolha = lerOpcao();

    if (escolha == 1) {
        std::string c = lerString("CPF do Paciente: ");
        std::string crm = lerString("CRM do Medico: ");

        DataHora d = lerDataHora();

        sistema.agendarConsulta(c, crm, d);

        std::cout << "Consulta agendada!" << std::endl;
    } else if (escolha == 2) {
        sistema.listarConsultas();
    } else if (escolha == 3) {
        std::string c = lerString("CPF do Paciente: ");

        DataHora d = lerDataHora();

        if (sistema.cancelarConsulta(c, d))
            std::cout << "Consulta cancelada." << std::endl;
        else
            std::cout << "Consulta nao encontrada." << std::endl;
    }

    if (escolha != 0)
        pausar();
}

void Menu::gerenciarInternacoes()
{
    std::cout << std::endl
              << "--- Gestao de Internacoes ---" << std::endl
              << std::endl;
    std::cout << "1. Internar Paciente" << std::endl;
    std::cout << "2. Dar Alta a Paciente" << std::endl;
    std::cout << "3. Listar Pacientes Internados" << std::endl;
    std::cout << "0. Voltar" << std::endl
              << std::endl;

    int escolha = lerOpcao();

    if (escolha == 1) {
        std::string c = lerString("CPF do Paciente: ");
        std::string a = lerString("Nome da Ala: ");
        sistema.internarPaciente(c, a);
        std::cout << "Paciente internado com sucesso!" << std::endl;
    } else if (escolha == 2) {
        std::string c = lerString("CPF do Paciente: ");
        sistema.darAltaPaciente(c);
        std::cout << "Paciente recebeu alta." << std::endl;
    } else if (escolha == 3) {
        sistema.listarInternados();
    }
    if (escolha != 0)
        pausar();
}

void Menu::demonstrarPolimorfismo()
{
    // Chama o método que usa o virtual 'exibirFicha()'
    sistema.listarTodasPessoas();

    pausar();
}

// --- Funções Utilitárias ---
int Menu::lerOpcao()
{
    int escolha;

    while (!(std::cin >> escolha)) {
        std::cout << "Entrada invalida. Digite um numero: ";

        limparBuffer();
    }

    limparBuffer(); // Limpa o '\n'

    return escolha;
}

std::string Menu::lerString(const std::string &prompt)
{
    std::string input;

    std::cout << prompt;

    std::getline(std::cin, input);

    return input;
}

int Menu::lerInt(const std::string &prompt)
{
    int input;

    std::cout << prompt;

    while (!(std::cin >> input)) {
        std::cout << "Entrada invalida. Digite um numero: ";

        limparBuffer();
    }

    limparBuffer(); // Limpa o '\n'

    return input;
}

DataHora Menu::lerDataHora()
{
    int d = lerInt("Dia (DD): ");
    int m = lerInt("Mes (MM): ");
    int a = lerInt("Ano (AAAA): ");
    int h = lerInt("Hora (HH): ");

    return DataHora(d, m, a, h, 0);
}

void Menu::limparBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::pausar()
{
    std::cout << "\nPressione ENTER para continuar...";

    limparBuffer();
}