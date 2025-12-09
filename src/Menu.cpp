#include <GerenciadorArquivos.h>
#include <Menu.h>

Menu::Menu()
    : executando(true)
{
    // Carrega preferências salvas anteriormente
    GerenciadorArquivos::carregarTudo(sistema, preferences);
}

void Menu::executar()
{
    // Exibe saudação personalizada
    std::cout << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "  Bem-vindo ao HospitalCore!" << std::endl;
    std::cout << "  Usuario: " << preferences.getNomeExibicao() << std::endl;
    std::cout << "  Tema: " << (preferences.ehTemaDarkModeAtivo() ? "Escuro" : "Claro") << std::endl;
    std::cout << "==================================================" << std::endl;

    pausar();

    while (executando) {
        exibirMenuPrincipal();

        int escolha = lerOpcao();

        // Trata exceções globais (validação, etc)
        try {
            processarEscolha(escolha);
        } catch (const HospitalExcecao &e) {
            std::cerr << "\n! Erro: " << e.what() << " ." << std::endl;
            pausar();
        } catch (const std::exception &e) {
            std::cerr << "\n! Erro Inesperado: " << e.what() << " ." << std::endl;
            pausar();
        }
    }

    // Salva dados ao encerrar
    salvarDados();
}

void Menu::exibirMenuPrincipal()
{
    std::cout << std::endl
              << "--- Sistema de Gestao Hospitalar 'HospitalCore' ---" << std::endl
              << std::endl;

    std::cout << "Usuario: " << preferences.getNomeExibicao() << std::endl
              << std::endl;

    std::cout << "1. Gerenciar Pacientes" << std::endl;
    std::cout << "2. Gerenciar Medicos" << std::endl;
    std::cout << "3. Gerenciar Alas e Leitos" << std::endl;
    std::cout << "4. Gerenciar Consultas" << std::endl;
    std::cout << "5. Gerenciar Internacoes" << std::endl;
    std::cout << "6. Listar Ficha de Todas as Pessoas" << std::endl;
    std::cout << "7. Gerenciar Preferencias" << std::endl;
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
        case 7:
            gerenciarPreferences();
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
        std::string n = lerNome("Nome: ");
        std::string c = lerCPF("CPF: ");
        std::string h = lerHistorico("Historico: ");

        sistema.adicionarPaciente(n, c, h);

        std::cout << "Paciente adicionado com sucesso!" << std::endl;
    } else if (escolha == 2) {
        sistema.listarPacientes();
    } else if (escolha == 3) {
        std::string c = lerCPF("CPF: ");

        Paciente *p = sistema.buscarPacientePorCpf(c);

        p->exibirFicha();
    } else if (escolha == 4) {
        std::string c = lerCPF("CPF: ");

        Paciente *p = sistema.buscarPacientePorCpf(c);

        std::string h = lerHistorico("Novo Historico: ");

        p->setHistorico(h);

        std::cout << "Historico atualizado." << std::endl;
    } else if (escolha == 5) {
        std::string c = lerCPF("CPF: ");

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
        std::string n = lerNome("Nome: ");
        std::string c = lerCPF("CPF: ");
        std::string e = lerEspecialidade("Especialidade: ");
        std::string crm = lerCRM("CRM: ");

        sistema.adicionarMedico(n, c, e, crm);

        std::cout << "Medico adicionado com sucesso!" << std::endl;
    } else if (escolha == 2) {
        sistema.listarMedicos();
    } else if (escolha == 3) {
        std::string crm = lerCRM("CRM: ");

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
              << std::endl
              << std::endl;

    int escolha = lerOpcao();

    if (escolha == 1) {
        std::string n = lerNomeAla("Nome da Ala (ex: Cardiologia): ");

        sistema.adicionarAla(n);

        std::cout << "Ala adicionada!" << std::endl;
    } else if (escolha == 2) {
        sistema.listarAlas();
    } else if (escolha == 3) {
        std::string n = lerNomeAla("Nome da Ala: ");

        int id = lerIdLeito("ID do novo Leito (ex: 101): ");

        sistema.adicionarLeitoNaAla(n, id);

        std::cout << "Leito adicionado!" << std::endl;
    } else if (escolha == 4) {
        std::string n = lerNomeAla("Nome da Ala: ");

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
        std::string c = lerCPF("CPF do Paciente: ");
        std::string crm = lerCRM("CRM do Medico: ");

        DataHora d = lerDataHora();

        sistema.agendarConsulta(c, crm, d);

        std::cout << "Consulta agendada!" << std::endl;
    } else if (escolha == 2) {
        sistema.listarConsultas();
    } else if (escolha == 3) {
        std::string c = lerCPF("CPF do Paciente: ");

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
        std::string c = lerCPF("CPF do Paciente: ");
        std::string a = lerNomeAla("Nome da Ala: ");
        sistema.internarPaciente(c, a);
        std::cout << "Paciente internado com sucesso!" << std::endl;
    } else if (escolha == 2) {
        std::string c = lerCPF("CPF do Paciente: ");
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

void Menu::gerenciarPreferences()
{
    std::cout << std::endl
              << "--- Preferencias do Usuario ---" << std::endl
              << std::endl;
    std::cout << "Nome Atual: " << preferences.getNomeExibicao() << std::endl;
    std::cout << "Tema Atual: " << (preferences.ehTemaDarkModeAtivo() ? "Escuro" : "Claro") << std::endl
              << std::endl;

    std::cout << "1. Alterar Nome" << std::endl;
    std::cout << "2. Alterar Tema" << std::endl;
    std::cout << "3. Salvar Preferencias" << std::endl;
    std::cout << "0. Voltar" << std::endl
              << std::endl;

    int escolha = lerOpcao();

    if (escolha == 1) {
        std::cout << "Nome atual: " << preferences.getNomeExibicao() << std::endl;
        std::string novoNome = lerString("Novo nome: ");

        if (novoNome.empty()) {
            std::cout << "Erro: Nome nao pode ser vazio." << std::endl;
        } else if (!ValidadorDados::validarNome(novoNome)) {
            std::cout << "Erro: Nome invalido. Deve ter minimo 3 caracteres e conter apenas letras e espacos."
                      << std::endl;
        } else {
            preferences.setNomeExibicao(novoNome);
            std::cout << "Nome alterado com sucesso!" << std::endl;
        }
    } else if (escolha == 2) {
        std::cout << "1. Claro" << std::endl;
        std::cout << "2. Escuro" << std::endl;
        int temaCod = lerOpcao();

        if (temaCod == 1) {
            preferences.setTema("claro");
            std::cout << "Tema alterado para CLARO." << std::endl;
        } else if (temaCod == 2) {
            preferences.setTema("escuro");
            std::cout << "Tema alterado para ESCURO." << std::endl;
        } else {
            std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }
    } else if (escolha == 3) {
        GerenciadorArquivos::salvarPreferences(preferences);
        std::cout << "Preferencias salvas!" << std::endl;
    }

    if (escolha != 0)
        pausar();
}

void Menu::salvarDados()
{
    GerenciadorArquivos::salvarTudo(sistema, preferences);
    std::cout << "\nDados salvos ao encerrar a aplicacao." << std::endl;
}

// --- Funções Utilitárias ---
int Menu::lerOpcao()
{
    int escolha;

    while (!(std::cin >> escolha)) {
        std::cin.clear();
        limparBuffer();
        std::cout << "Entrada invalida. Digite um numero: ";
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

    while (true) {
        std::cout << prompt;
        if (std::cin >> input) {
            limparBuffer(); // Limpa o '\n'
            return input;
        }
        std::cin.clear();
        limparBuffer();
        std::cout << "Entrada invalida. Digite um numero: ";
    }
}

DataHora Menu::lerDataHora()
{
    int d, m, a, h, min;
    bool valido = false;

    while (!valido) {
        try {
            d = lerInt("Dia (DD): ");
            m = lerInt("Mes (MM): ");
            a = lerInt("Ano (AAAA): ");
            h = lerInt("Hora (HH): ");
            min = lerInt("Minuto (MM): ");

            if (!ValidadorDados::validarData(d, m, a)) {
                throw DataInvalidaExcecao(d, m, a);
            }

            if (!ValidadorDados::validarHora(h)) {
                throw HoraInvalidaExcecao(h);
            }

            if (!ValidadorDados::validarMinuto(min)) {
                throw MinutoInvalidoExcecao(min);
            }

            valido = true;
        } catch (const ValidacaoExcecao &e) {
            std::cerr << "\n! " << e.what() << " ." << std::endl;
            std::cout << "Tente novamente." << std::endl;
        }
    }

    return DataHora(d, m, a, h, min);
}

std::string Menu::lerCPF(const std::string &prompt)
{
    std::string cpf;
    bool valido = false;

    while (!valido) {
        try {
            cpf = lerString(prompt);

            if (!ValidadorDados::validarCPF(cpf)) {
                throw CPFInvalidoExcecao(cpf);
            }

            valido = true;
        } catch (const CPFInvalidoExcecao &e) {
            std::cerr << "\n! " << e.what() << " ." << std::endl;
        }
    }

    return ValidadorDados::limparCPF(cpf);
}

std::string Menu::lerNome(const std::string &prompt)
{
    std::string nome;

    bool valido = false;

    while (!valido) {
        try {
            nome = lerString(prompt);

            if (!ValidadorDados::validarNome(nome)) {
                throw NomeInvalidoExcecao(nome);
            }

            valido = true;
        } catch (const NomeInvalidoExcecao &e) {
            std::cerr << "\n! " << e.what() << " ." << std::endl;
        }
    }

    return nome;
}

std::string Menu::lerCRM(const std::string &prompt)
{
    std::string crm;

    bool valido = false;

    while (!valido) {
        try {
            crm = lerString(prompt);

            if (!ValidadorDados::validarCRM(crm)) {
                throw CRMInvalidoExcecao(crm);
            }

            valido = true;
        } catch (const CRMInvalidoExcecao &e) {
            std::cerr << "\n! " << e.what() << " ." << std::endl;
        }
    }

    return crm;
}

std::string Menu::lerEspecialidade(const std::string &prompt)
{
    std::string especialidade;

    bool valido = false;

    while (!valido) {
        try {
            especialidade = lerString(prompt);

            if (!ValidadorDados::validarEspecialidade(especialidade)) {
                throw ValidacaoExcecao("Especialidade invalida. Deve conter min. 3 caracteres.");
            }

            valido = true;
        } catch (const ValidacaoExcecao &e) {
            std::cerr << "\n! " << e.what() << " ." << std::endl;
        }
    }

    return especialidade;
}

std::string Menu::lerHistorico(const std::string &prompt)
{
    std::string historico;

    bool valido = false;

    while (!valido) {
        try {
            historico = lerString(prompt);

            if (!ValidadorDados::validarHistorico(historico)) {
                throw ValidacaoExcecao("Historico invalido. Nao pode estar vazio ou exceder 500 caracteres.");
            }

            valido = true;
        } catch (const ValidacaoExcecao &e) {
            std::cerr << "\n! " << e.what() << " ." << std::endl;
        }
    }

    return historico;
}

std::string Menu::lerNomeAla(const std::string &prompt)
{
    std::string nomeAla;

    bool valido = false;

    while (!valido) {
        try {
            nomeAla = lerString(prompt);

            if (!ValidadorDados::validarNomeAla(nomeAla)) {
                throw ValidacaoExcecao("Nome da ala invalido. Maximo 50 caracteres, sem caracteres especiais.");
            }

            valido = true;
        } catch (const ValidacaoExcecao &e) {
            std::cerr << "\n! " << e.what() << " ." << std::endl;
        }
    }

    return nomeAla;
}

int Menu::lerIdLeito(const std::string &prompt)
{
    int id;
    bool valido = false;

    while (!valido) {
        try {
            std::cout << prompt;
            if (!(std::cin >> id)) {
                std::cin.clear();
                limparBuffer();
                throw ValidacaoExcecao("Entrada invalida. Digite um numero inteiro entre 1 e 9999.");
            }

            limparBuffer();

            if (!ValidadorDados::validarIdLeito(id)) {
                throw ValidacaoExcecao("ID do leito invalido. Deve estar entre 1 e 9999.");
            }

            valido = true;
        } catch (const ValidacaoExcecao &e) {
            std::cerr << "\n! " << e.what() << " ." << std::endl;
        }
    }

    return id;
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