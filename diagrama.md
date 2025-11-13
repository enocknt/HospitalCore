# Diagrama de Classes UML - HospitalCore

```mermaid
classDiagram
    direction LR

    %% --- Definição das Classes ---

    class Pessoa {
        <<Abstract>>
        # string nome
        # string cpf
        + Pessoa(string n, string c)
        + virtual ~Pessoa()
        + virtual void exibirFicha() const = 0
        + string getNome() const
    }

    class Paciente {
        - string historicoMedico
        + Paciente(string n, string c, string hist)
        + void exibirFicha() const override
    }

    class Medico {
        - string especialidade
        - string crm
        + Medico(string n, string c, string esp, string crm)
        + void exibirFicha() const override
    }

    class Consulta {
        - DataHora dataHora
        - Paciente* paciente
        - Medico* medico
        + Consulta(Paciente* p, Medico* m, DataHora d)
    }

    class AlaHospitalar {
        - string nomeAla
        - vector~unique_ptr~Leito~~ leitos
        + AlaHospitalar(string nome)
        + void adicionarLeito(int id)
        + Leito* buscarLeitoDisponivel()
    }

    class Leito {
        - int idLeito
        - bool ocupado
        - Paciente* pacienteAlocado
        + Leito(int id)
        + bool estaOcupado() const
        + void ocupar(Paciente* p)
        + void desocupar()
    }

    class SistemaGestao {
        - vector~unique_ptr~Pessoa~~ pessoas
        - vector~unique_ptr~AlaHospitalar~~ alas
        - vector~unique_ptr~Consulta~~ consultas
        + void adicionarPaciente(...)
        + void adicionarMedico(...)
        + void agendarConsulta(...)
        + void internarPaciente(...)
    }

    class HospitalExcecao {
        <<Abstract>>
        # string mensagem
        + virtual const char* what() const noexcept
    }
    class AgendamentoExcecao { }
    class LeitoExcecao { }
    class EntidadeNaoEncontradaExcecao { }

    %% --- Herança de Pessoas (Polimorfismo 1) ---
    Pessoa <|-- Paciente
    Pessoa <|-- Medico

    %% --- Herança de Exceções (Polimorfismo 2) ---
    std.exception <|-- HospitalExcecao
    HospitalExcecao <|-- AgendamentoExcecao
    HospitalExcecao <|-- LeitoExcecao
    HospitalExcecao <|-- EntidadeNaoEncontradaExcecao

    %% --- Relações de Agregação e Associação ---
    
    %% O SistemaGestao "gerencia" as entidades principais
    SistemaGestao o-- "1..*" Pessoa : "gerencia"
    SistemaGestao o-- "1..*" AlaHospitalar : "gerencia"
    SistemaGestao o-- "0..*" Consulta : "gerencia"

    %% Uma Consulta "refere-se a" um Paciente e um Medico
    Consulta "1" ..> "1" Paciente : "paciente"
    Consulta "1" ..> "1" Medico : "medico"

    %% Uma AlaHospitalar "contém" Leitos
    AlaHospitalar "1" o-- "1..*" Leito : "contem"
    
    %% Um Leito "aloca" um Paciente (ou nenhum)
    Leito "1" o-- "0..1" Paciente : "aloca"
