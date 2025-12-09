#include <SistemaGestao.h>

// --- CRUD Paciente ---
void SistemaGestao::adicionarPaciente(const std::string &nome, const std::string &cpf, const std::string &historico)
{
    try {
        buscarPacientePorCpf(cpf);

        throw AgendamentoExcecao("CPF " + cpf + " ja esta cadastrado.");
    } catch (const EntidadeNaoEncontradaExcecao &e) {
        pessoas.push_back(std::make_unique<Paciente>(nome, cpf, historico));
    }
}

Paciente *SistemaGestao::buscarPacientePorCpf(const std::string &cpf)
{
    for (const auto &p : pessoas) {
        if (p->getCpf() == cpf) {
            // Usa dynamic_cast para verificar se é um Paciente
            Paciente *pac = dynamic_cast<Paciente *>(p.get());
            if (pac)
                return pac;
        }
    }

    // Lança exceção customizada
    throw EntidadeNaoEncontradaExcecao("Paciente com CPF " + cpf + " nao encontrado.");
}

void SistemaGestao::listarPacientes() const
{
    std::cout << "--- Lista de Pacientes ---" << std::endl;

    for (const auto &p : pessoas) {
        Paciente *pac = dynamic_cast<Paciente *>(p.get());

        if (pac) {
            std::cout << *pac << std::endl; // Usa operator<<
        }
    }
}

// --- CRUD Medico ---
void SistemaGestao::adicionarMedico(const std::string &nome, const std::string &cpf, const std::string &esp, const std::string &crm)
{
    try {
        buscarMedicoPorCrm(crm);

        throw AgendamentoExcecao("CRM " + crm + " ja esta cadastrado.");
    } catch (const EntidadeNaoEncontradaExcecao &e) {
        pessoas.push_back(std::make_unique<Medico>(nome, cpf, esp, crm));
    }
}

Medico *SistemaGestao::buscarMedicoPorCrm(const std::string &crm)
{
    for (const auto &p : pessoas) {
        Medico *med = dynamic_cast<Medico *>(p.get());

        if (med && med->getCrm() == crm) {
            return med;
        }
    }

    throw EntidadeNaoEncontradaExcecao("Medico com CRM " + crm + " nao encontrado.");
}

void SistemaGestao::listarMedicos() const
{
    std::cout << "--- Lista de Medicos ---" << std::endl;

    for (const auto &p : pessoas) {
        Medico *med = dynamic_cast<Medico *>(p.get());

        if (med) {
            std::cout << *med << std::endl; // Usa operator<<
        }
    }
}

// --- CRUD Pessoa Genérico ---
bool SistemaGestao::removerPessoa(const std::string &cpf)
{
    for (auto it = pessoas.begin(); it != pessoas.end(); ++it) {
        if ((*it)->getCpf() == cpf) {
            pessoas.erase(it);
            return true;
        }
    }

    return false;
}

// --- CRUD Ala ---
void SistemaGestao::adicionarAla(const std::string &nome)
{
    alas.push_back(std::make_unique<AlaHospitalar>(nome));
}

AlaHospitalar *SistemaGestao::buscarAla(const std::string &nome)
{
    for (const auto &ala : alas) {
        if (ala->getNome() == nome) {
            return ala.get();
        }
    }

    throw EntidadeNaoEncontradaExcecao("Ala '" + nome + "' nao encontrada.");
}

void SistemaGestao::listarAlas() const
{
    std::cout << "--- Alas do Hospital ---" << std::endl;

    for (const auto &ala : alas) {
        std::cout << "Ala: " << ala->getNome() << std::endl;
    }
}

// --- CRUD Leito (via Ala) ---
void SistemaGestao::adicionarLeitoNaAla(const std::string &nomeAla, int idLeito)
{
    AlaHospitalar *ala = buscarAla(nomeAla); // Pode lançar exceção

    ala->adicionarLeito(idLeito); // Pode lançar exceção
}

void SistemaGestao::listarLeitosDaAla(const std::string &nomeAla)
{
    AlaHospitalar *ala = buscarAla(nomeAla);

    ala->listarLeitos();
}

// --- CRUD Consulta ---
void SistemaGestao::agendarConsulta(const std::string &cpfPaciente, const std::string &crmMedico, const DataHora &data)
{
    // Validações
    Paciente *pac = buscarPacientePorCpf(cpfPaciente); // Lança se não achar

    Medico *med = buscarMedicoPorCrm(crmMedico); // Lança se não achar

    // Verifica conflito de agenda (simplificado)
    for (const auto &c : consultas) {
        if (c->getMedico() == med && c->getDataHora() == data) {
            throw AgendamentoExcecao("Medico ja tem consulta nesse horario.");
        }

        if (c->getPaciente() == pac && c->getDataHora() == data) {
            throw AgendamentoExcecao("Paciente ja tem consulta nesse horario.");
        }
    }

    // Cria
    consultas.push_back(std::make_unique<Consulta>(pac, med, data));
}

void SistemaGestao::listarConsultas() const
{
    std::cout << "--- Agenda de Consultas ---" << std::endl;

    if (consultas.empty()) {
        std::cout << "Nenhuma consulta agendada." << std::endl;
        return;
    }

    for (const auto &c : consultas) {
        std::cout << *c << std::endl; // Usa operator<<
    }
}

bool SistemaGestao::cancelarConsulta(const std::string &cpfPaciente, const DataHora &data)
{
    for (auto it = consultas.begin(); it != consultas.end(); ++it) {
        if ((*it)->getPaciente()->getCpf() == cpfPaciente && (*it)->getDataHora() == data) {
            consultas.erase(it);
            return true;
        }
    }

    return false;
}

// --- CRUD Internacao ---
void SistemaGestao::internarPaciente(const std::string &cpfPaciente, const std::string &nomeAla)
{
    Paciente *pac = buscarPacientePorCpf(cpfPaciente);

    AlaHospitalar *ala = buscarAla(nomeAla);

    Leito *leito = ala->buscarLeitoDisponivel(); // Lança LeitoExcecao se lotado

    leito->ocupar(pac);

    // Registra internacao no historico
    internacoes.push_back(std::make_unique<Internacao>(pac, nomeAla, leito->getId(), DataHora()));
}

void SistemaGestao::darAltaPaciente(const std::string &cpfPaciente)
{
    Paciente *pac = buscarPacientePorCpf(cpfPaciente);

    for (const auto &ala : alas) {
        for (const auto &leito : ala->getLeitos()) {
            if (leito->estaOcupado() && leito->getPaciente() == pac) {
                leito->desocupar();

                // Marca data de alta no historico (se existir registro aberto)
                for (auto &intn : internacoes) {
                    if (intn->getPaciente() == pac && intn->estaAinda()) {
                        intn->setDataSaida(DataHora());
                        break;
                    }
                }

                return;
            }
        }
    }

    throw EntidadeNaoEncontradaExcecao("Paciente nao esta internado.");
}

void SistemaGestao::listarInternados() const
{
    std::cout << "--- Pacientes Internados ---" << std::endl;

    for (const auto &ala : alas) {
        for (const auto &leito : ala->getLeitos()) {
            if (leito->estaOcupado()) {
                std::cout << "Ala: " << ala->getNome() << " | " << *leito << std::endl;
            }
        }
    }
}

void SistemaGestao::listarInternacoes() const
{
    std::cout << "--- Historico de Internacoes ---" << std::endl;

    if (internacoes.empty()) {
        std::cout << "Nenhuma internacao registrada." << std::endl;
        return;
    }

    for (const auto &i : internacoes) {
        std::cout << *i << std::endl;
    }
}

// --- Polimorfismo ---
void SistemaGestao::listarTodasPessoas() const
{
    std::cout << "--- Fichas de Todas as Pessoas (Pacientes e Medicos) ---" << std::endl;

    for (const auto &p : pessoas) {
        p->exibirFicha(); // Chama o método polimórfico
    }
}