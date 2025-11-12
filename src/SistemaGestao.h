#pragma once

#include "AlaHospitalar.h"
#include "Consulta.h"
#include "HospitalExcecao.h"
#include "Medico.h"
#include "Paciente.h"
#include "Pessoa.h"

#include <memory>
#include <vector>

class SistemaGestao {
private:
    // Polimorfismo: um único vetor para Pacientes e Médicos
    std::vector<std::unique_ptr<Pessoa> > pessoas;
    std::vector<std::unique_ptr<AlaHospitalar> > alas;
    std::vector<std::unique_ptr<Consulta> > consultas;

public:
    SistemaGestao() = default;

    // --- CRUD Paciente ---
    void adicionarPaciente(const std::string &nome, const std::string &cpf, const std::string &historico);
    Paciente *buscarPacientePorCpf(const std::string &cpf);
    void listarPacientes() const;
    bool removerPessoa(const std::string &cpf); // Remove Paciente ou Medico

    // --- CRUD Medico ---
    void adicionarMedico(const std::string &nome, const std::string &cpf, const std::string &esp, const std::string &crm);
    Medico *buscarMedicoPorCrm(const std::string &crm);
    void listarMedicos() const;

    // --- CRUD Ala ---
    void adicionarAla(const std::string &nome);
    AlaHospitalar *buscarAla(const std::string &nome);
    void listarAlas() const;

    // --- CRUD Leito (via Ala) ---
    void adicionarLeitoNaAla(const std::string &nomeAla, int idLeito);
    void listarLeitosDaAla(const std::string &nomeAla);

    // --- CRUD Consulta ---
    void agendarConsulta(const std::string &cpfPaciente, const std::string &crmMedico, const DataHora &data);
    void listarConsultas() const;
    bool cancelarConsulta(const std::string &cpfPaciente, const DataHora &data);

    // --- CRUD Internacao (Funções) ---
    void internarPaciente(const std::string &cpfPaciente, const std::string &nomeAla);
    void darAltaPaciente(const std::string &cpfPaciente);
    void listarInternados() const;

    // --- Polimorfismo ---
    void listarTodasPessoas() const;
};