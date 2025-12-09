#include <GerenciadorArquivos.h>
#include <PreferenciasUsuario.h>
#include <SistemaGestao.h>
#include <ValidadorDados.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace {

std::filesystem::path getDataDir()
{
    // Usa diretório do executável (build/) como base e cria subpasta dados/
    std::error_code ec;
    auto exePath = std::filesystem::canonical("/proc/self/exe", ec);
    std::filesystem::path base = ec ? std::filesystem::current_path() : exePath.parent_path();
    return base / "dados";
}

std::filesystem::path dataPath(const std::string &fileName)
{
    return getDataDir() / fileName;
}

std::vector<std::string> splitCSV(const std::string &linha, std::size_t expected)
{
    std::vector<std::string> colunas;
    std::stringstream ss(linha);
    std::string campo;

    while (std::getline(ss, campo, ',')) {
        colunas.push_back(campo);
    }

    // Se a linha termina com vírgula, getline não adiciona o último campo vazio automaticamente
    if (!linha.empty() && linha.back() == ',') {
        colunas.push_back("");
    }

    // Permite linhas com menos campos do que o esperado, mas sinaliza isso ao chamador
    if (expected != 0 && colunas.size() < expected) {
        return {};
    }

    return colunas;
}

bool parseData(const std::string &dataStr, int &dia, int &mes, int &ano)
{
    char sep1 = '/', sep2 = '/';
    std::stringstream ss(dataStr);
    return (ss >> dia >> sep1 >> mes >> sep2 >> ano) && sep1 == '/' && sep2 == '/';
}

bool parseHora(const std::string &horaStr, int &hora, int &minuto)
{
    char sep = ':';
    std::stringstream ss(horaStr);
    return (ss >> hora >> sep >> minuto) && sep == ':';
}

bool parseDataHora(const std::string &dataStr, const std::string &horaStr, DataHora &out)
{
    int d = 0, m = 0, a = 0, h = 0, min = 0;

    if (!parseData(dataStr, d, m, a) || !parseHora(horaStr, h, min)) {
        return false;
    }

    out = DataHora(d, m, a, h, min);
    return true;
}

std::string formatData(const DataHora &dt)
{
    std::ostringstream os;
    os << dt.dia << '/' << dt.mes << '/' << dt.ano;
    return os.str();
}

std::string formatHora(const DataHora &dt)
{
    std::ostringstream os;
    os << dt.hora << ':' << (dt.minuto < 10 ? "0" : "") << dt.minuto;
    return os.str();
}

} // namespace

// Definição dos nomes dos arquivos
const std::string GerenciadorArquivos::ARQUIVO_PACIENTES = "dados_pacientes.csv";
const std::string GerenciadorArquivos::ARQUIVO_MEDICOS = "dados_medicos.csv";
const std::string GerenciadorArquivos::ARQUIVO_ALAS = "dados_alas.csv";
const std::string GerenciadorArquivos::ARQUIVO_LEITOS = "dados_leitos.csv";
const std::string GerenciadorArquivos::ARQUIVO_CONSULTAS = "dados_consultas.csv";
const std::string GerenciadorArquivos::ARQUIVO_INTERNACOES = "dados_internacoes.csv";
const std::string GerenciadorArquivos::ARQUIVO_PREFERENCES = "preferencias.csv";

void GerenciadorArquivos::salvarPacientes(const SistemaGestao &sistema)
{
    std::filesystem::create_directories(getDataDir());

    std::ofstream arquivo(dataPath(ARQUIVO_PACIENTES));

    arquivo << "Nome,CPF,Historico\n";

    for (const auto &p : sistema.getPessoas()) {
        const auto *pac = dynamic_cast<const Paciente *>(p.get());
        if (!pac)
            continue;

        arquivo << '"' << pac->getNome() << '"' << ',' << pac->getCpf() << ',' << '"' << pac->getHistorico() << '"' << "\n";
    }

    arquivo.close();
}

void GerenciadorArquivos::salvarMedicos(const SistemaGestao &sistema)
{
    std::filesystem::create_directories(getDataDir());

    std::ofstream arquivo(dataPath(ARQUIVO_MEDICOS));
    arquivo << "Nome,CPF,Especialidade,CRM\n";
    for (const auto &p : sistema.getPessoas()) {
        const auto *m = dynamic_cast<const Medico *>(p.get());
        if (!m)
            continue;

        arquivo << '"' << m->getNome() << '"' << ',' << m->getCpf() << ',' << '"' << m->getEspecialidade() << '"' << ','
                << m->getCrm() << "\n";
    }
    arquivo.close();
}

void GerenciadorArquivos::salvarAlas(const SistemaGestao &sistema)
{
    std::filesystem::create_directories(getDataDir());

    std::ofstream arquivo(dataPath(ARQUIVO_ALAS));
    arquivo << "Nome\n";
    for (const auto &ala : sistema.getAlas()) {
        arquivo << '"' << ala->getNome() << '"' << "\n";
    }
    arquivo.close();
}

void GerenciadorArquivos::salvarLeitos(const SistemaGestao &sistema)
{
    std::filesystem::create_directories(getDataDir());

    std::ofstream arquivo(dataPath(ARQUIVO_LEITOS));
    arquivo << "NomeAla,IdLeito,Ocupado,CPFPaciente\n";

    for (const auto &ala : sistema.getAlas()) {
        for (const auto &leito : ala->getLeitos()) {
            arquivo << '"' << ala->getNome() << '"' << ',' << leito->getId() << ',' << (leito->estaOcupado() ? 1 : 0) << ',';
            if (leito->estaOcupado() && leito->getPaciente()) {
                arquivo << leito->getPaciente()->getCpf();
            }
            arquivo << "\n";
        }
    }

    arquivo.close();
}

void GerenciadorArquivos::salvarConsultas(const SistemaGestao &sistema)
{
    std::filesystem::create_directories(getDataDir());

    std::ofstream arquivo(dataPath(ARQUIVO_CONSULTAS));
    arquivo << "CPFPaciente,CRMMedico,Data,Hora\n";
    for (const auto &c : sistema.getConsultas()) {
        if (!c->getPaciente() || !c->getMedico())
            continue;

        arquivo << c->getPaciente()->getCpf() << ',' << c->getMedico()->getCrm() << ',' << formatData(c->getDataHora()) << ','
                << formatHora(c->getDataHora()) << "\n";
    }
    arquivo.close();
}

void GerenciadorArquivos::salvarInternacoes(const SistemaGestao &sistema)
{
    std::filesystem::create_directories(getDataDir());

    std::ofstream arquivo(dataPath(ARQUIVO_INTERNACOES));
    arquivo << "CPFPaciente,NomeAla,IdLeito,DataEntrada,DataSaida\n";
    for (const auto &i : sistema.getInternacoes()) {
        if (!i->getPaciente())
            continue;

        arquivo << i->getPaciente()->getCpf() << ',' << '"' << i->getNomeAla() << '"' << ',' << i->getIdLeito() << ','
                << formatData(i->getDataEntrada()) << ',';

        if (!i->estaAinda()) {
            arquivo << formatData(i->getDataSaida());
        }

        arquivo << "\n";
    }
    arquivo.close();
}

void GerenciadorArquivos::salvarPreferences(const PreferenciasUsuario &pref)
{
    std::filesystem::create_directories(getDataDir());

    std::ofstream arquivo(dataPath(ARQUIVO_PREFERENCES));

    arquivo << "Nome,Tema\n";
    arquivo << pref.getNomeExibicao() << "," << pref.getTema() << "\n";
    arquivo.close();

    std::cout << std::endl
              << "Preferencias salvas em " << dataPath(ARQUIVO_PREFERENCES) << std::endl;
}

void GerenciadorArquivos::carregarPacientes(SistemaGestao &sistema)
{
    std::ifstream arquivo(dataPath(ARQUIVO_PACIENTES));

    if (!arquivo.is_open())
        return;

    std::string linha;

    std::getline(arquivo, linha); // Pula cabeçalho

    while (std::getline(arquivo, linha)) {
        if (linha.empty())
            continue;

        auto colunas = splitCSV(linha, 3);
        if (colunas.size() < 3)
            continue;

        try {
            // Normaliza CPF removendo pontuação
            std::string cpf = ValidadorDados::limparCPF(colunas[1]);
            sistema.adicionarPaciente(colunas[0], cpf, colunas[2]);
        } catch (const std::exception &e) {
            std::cerr << "Erro ao carregar paciente: " << e.what() << std::endl;
        }
    }

    arquivo.close();
}

void GerenciadorArquivos::carregarMedicos(SistemaGestao &sistema)
{
    std::ifstream arquivo(dataPath(ARQUIVO_MEDICOS));
    if (!arquivo.is_open())
        return;

    std::string linha;
    std::getline(arquivo, linha); // Pula cabeçalho

    while (std::getline(arquivo, linha)) {
        if (linha.empty())
            continue;

        auto colunas = splitCSV(linha, 4);
        if (colunas.size() < 4)
            continue;

        try {
            std::string cpf = ValidadorDados::limparCPF(colunas[1]);
            sistema.adicionarMedico(colunas[0], cpf, colunas[2], colunas[3]);
        } catch (const std::exception &e) {
            std::cerr << "Erro ao carregar medico: " << e.what() << std::endl;
        }
    }

    arquivo.close();
}

void GerenciadorArquivos::carregarAlas(SistemaGestao &sistema)
{
    std::ifstream arquivo(dataPath(ARQUIVO_ALAS));

    if (!arquivo.is_open())
        return;

    std::string linha;
    std::getline(arquivo, linha); // Pula cabeçalho

    while (std::getline(arquivo, linha)) {
        if (!linha.empty()) {
            sistema.adicionarAla(linha);
        }
    }

    arquivo.close();
}

void GerenciadorArquivos::carregarConsultas(SistemaGestao &sistema)
{
    std::ifstream arquivo(dataPath(ARQUIVO_CONSULTAS));

    if (!arquivo.is_open())
        return;

    std::string linha;
    std::getline(arquivo, linha); // Pula cabeçalho

    while (std::getline(arquivo, linha)) {
        if (linha.empty())
            continue;

        auto colunas = splitCSV(linha, 4);
        if (colunas.size() < 4)
            continue;

        DataHora dataHora;
        if (!parseDataHora(colunas[2], colunas[3], dataHora))
            continue;

        try {
            std::string cpf = ValidadorDados::limparCPF(colunas[0]);
            sistema.agendarConsulta(cpf, colunas[1], dataHora);
        } catch (const std::exception &e) {
            std::cerr << "Erro ao carregar consulta: " << e.what() << std::endl;
        }
    }

    arquivo.close();
}

void GerenciadorArquivos::carregarInternacoes(SistemaGestao &sistema)
{
    std::ifstream arquivo(dataPath(ARQUIVO_INTERNACOES));

    if (!arquivo.is_open())
        return;

    std::string linha;
    std::getline(arquivo, linha); // Pula cabeçalho

    while (std::getline(arquivo, linha)) {
        if (linha.empty())
            continue;

        auto colunas = splitCSV(linha, 5);

        if (colunas.size() < 4)
            continue;

        const std::string cpf = ValidadorDados::limparCPF(colunas[0]);
        const std::string ala = colunas[1];
        const std::string idLeitoStr = colunas[2];
        const std::string dataEntradaStr = colunas[3];
        const std::string dataSaidaStr = colunas.size() >= 5 ? colunas[4] : "";

        int idLeito = 0;

        try {
            idLeito = std::stoi(idLeitoStr);
        } catch (...) {
            continue;
        }

        // Garante que a ala exista; se não existir, cria.
        try {
            sistema.buscarAla(ala);
        } catch (...) {
            try {
                sistema.adicionarAla(ala);
            } catch (...) {
                continue;
            }
        }

        // Garante que o leito exista
        try {
            sistema.adicionarLeitoNaAla(ala, idLeito);
        } catch (...) {
            // Ignora se já existir
        }

        // Interna o paciente (usa primeiro leito disponível da ala)
        try {
            sistema.internarPaciente(cpf, ala);

            // Se há data de saída, libera o paciente
            if (!dataSaidaStr.empty()) {
                sistema.darAltaPaciente(cpf);
            }
        } catch (const std::exception &e) {
            std::cerr << "Erro ao carregar internacao: " << e.what() << std::endl;
        }
    }

    arquivo.close();
}

PreferenciasUsuario GerenciadorArquivos::carregarPreferences()
{
    PreferenciasUsuario pref;

    std::ifstream arquivo(dataPath(ARQUIVO_PREFERENCES));

    if (!arquivo.is_open()) {
        std::cout << "Arquivo de preferencias nao encontrado. Usando padrao." << std::endl;
        return pref;
    }

    std::string linha;

    // Pula cabecalho
    std::getline(arquivo, linha);

    if (std::getline(arquivo, linha)) {
        auto colunas = splitCSV(linha, 2);

        if (colunas.size() >= 2) {
            pref.setNomeExibicao(colunas[0]);
            pref.setTema(colunas[1]);
        }
    }

    arquivo.close();

    return pref;
}

void GerenciadorArquivos::salvarTudo(const SistemaGestao &sistema, const PreferenciasUsuario &pref)
{
    salvarPacientes(sistema);
    salvarMedicos(sistema);
    salvarAlas(sistema);
    salvarLeitos(sistema);
    salvarConsultas(sistema);
    salvarInternacoes(sistema);
    salvarPreferences(pref);

    std::cout << std::endl
              << "Todos os dados foram salvos." << std::endl;
}

void GerenciadorArquivos::carregarTudo(SistemaGestao &sistema, PreferenciasUsuario &pref)
{
    std::cout << "Carregando dados..." << std::endl;

    carregarAlas(sistema);
    carregarPacientes(sistema);
    carregarMedicos(sistema);
    carregarConsultas(sistema);
    carregarInternacoes(sistema);

    pref = carregarPreferences();

    std::cout << std::endl
              << "Dados carregados com sucesso!" << std::endl;
}

bool GerenciadorArquivos::arquivoExiste(const std::string &nomeArquivo)
{
    std::ifstream arquivo(dataPath(nomeArquivo));

    return arquivo.good();
}