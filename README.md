# HospitalCore - Sistema de Gestao Hospitalar

![Status](https://img.shields.io/badge/status-ativo-green)
![Linguagem](https://img.shields.io/badge/linguagem-C%2B%2B17-blue.svg)
![Build](https://img.shields.io/badge/build-CMake-brightgreen)
![Plataforma](https://img.shields.io/badge/plataforma-Linux%2FmacOS%2FWindows-lightgrey)

Projeto academico de um sistema completo de gestao hospitalar em C++ para a disciplina de **IMD0030 - Linguagem de Programacao I**. O sistema implementa conceitos avancados de **Encapsulamento**, **Heranca**, **Polimorfismo**, **Interfaces**, **Tratamento de Excecoes** e **Validacao de Dados**.

---

## Funcionalidades Principais

O sistema oferece gerenciamento completo (CRUD) das principais entidades hospitalares com validacao robusta:

### Gestao de Pessoas
- **Medicos:** Cadastrar, listar e buscar por CRM (validado)
- **Pacientes:** Cadastrar, listar, buscar por CPF (com digitos verificadores) e atualizar prontuario
- **Historico:** Manutencao de historico medico com validacao de comprimento

### Infraestrutura Hospitalar
- **Alas:** Cadastrar e gerenciar alas (ex: "Cardiologia", "Ortopedia")
- **Leitos:** Adicionar leitos as alas, listar por ala, controle de ocupacao
- **Internacoes:** Admissao e alta de pacientes com controle de disponibilidade

### Agendamentos e Consultas
- **Consultas:** Agendar, listar e cancelar com verificacao de conflitos de horarios
- **Validacao de Datas:** Suporte a anos bissextos, validacao de meses e dias
- **Interface IAgendavel:** Polimorfismo para agendamentos (Consultas e Internacoes)

### Validacao de Dados
- **CPF:** Verificacao de digitos verificadores (modulo 11)
- **CRM:** Validacao de formato (4-10 digitos)
- **Nomes:** Minimo 3 caracteres, apenas letras e espacos
- **Datas:** Validacao completa com suporte a anos bissextos
- **Horarios:** Validacao de hora (0-23) e minuto (0-59)
- **Historicos:** Comprimento maximo de 500 caracteres
- **Nomes de Alas:** Alfanumericos e hifen, maximo 50 caracteres

### Persistencia de Dados
- **Arquivo CSV:** Armazenamento de preferencias do usuario
- **Carregamento Automatico:** Preferences carregadas ao iniciar
- **Salvamento:** Opcao de persistir preferencias

### Preferencias do Usuario
- **Nome de Exibicao:** Customizar nome mostrado no menu
- **Tema:** Modo escuro/claro (armazenado em arquivo)

---

## Estrutura do Projeto

```
HospitalCore/
├── include/              # Headers (.h) - Interfaces e declaracoes
│   ├── Pessoa.h          # Classe abstrata base
│   ├── Paciente.h        # Heranca de Pessoa
│   ├── Medico.h          # Heranca de Pessoa
│   ├── AlaHospitalar.h   # Gerenciamento de alas
│   ├── Leito.h           # Representacao de leitos
│   ├── Consulta.h        # Implementa IAgendavel
│   ├── Internacao.h      # Implementa IAgendavel
│   ├── SistemaGestao.h   # Sistema principal (coordena CRUD)
│   ├── Menu.h            # Interface de usuario
│   ├── IGerenciavel.h    # Interface para gerenciamento
│   ├── IAgendavel.h      # Interface para agendamentos
│   ├── ValidadorDados.h  # Validacao de entrada
│   ├── HospitalExcecao.h # Hierarquia de excecoes
│   ├── DataHora.h        # Estrutura de data/hora
│   ├── GerenciadorArquivos.h  # Persistencia de dados
│   └── PreferenciasUsuario.h   # Preferencias armazenadas
├── src/                  # Implementacoes (.cpp)
│   ├── main.cpp
│   ├── Pessoa.cpp
│   ├── Paciente.cpp
│   ├── Medico.cpp
│   ├── AlaHospitalar.cpp
│   ├── Leito.cpp
│   ├── Consulta.cpp
│   ├── Internacao.cpp
│   ├── SistemaGestao.cpp
│   ├── Menu.cpp
│   ├── ValidadorDados.cpp
│   ├── GerenciadorArquivos.cpp
│   └── PreferenciasUsuario.cpp
├── build/                # Diretorio de build (CMake), executavel (hospital_core) e dados gerados em build/dados/
├── CMakeLists.txt        # Configuracao CMake
├── build.sh              # Script de automacao de build
└── README.md             # Este arquivo
```

---

## Tecnologias Utilizadas

- **C++ 17:** Linguagem principal com recursos modernos (unique_ptr, regex, etc.)
- **CMake 3.10+:** Build system cross-platform (Linux, macOS, Windows)
- **STL:** Containers (vector, map), algoritmos, regex para validacao
- **Excecoes Customizadas:** Hierarquia completa de excecoes do dominio
- **Memoria Dinamica:** Uso de unique_ptr para RAII

---

## Requisitos Atendidos

- ✓ Minimo 11 classes: 13 classes implementadas
- ✓ Minimo 2 interfaces: IGerenciavel e IAgendavel
- ✓ Minimo 2 classes abstratas: Pessoa (abstrata base), HospitalExcecao (heranca)
- ✓ CRUD para 8+ entidades: Pacientes, Medicos, Alas, Leitos, Consultas, Internacoes
- ✓ Tratamento de excecoes: Hierarquia com 12+ tipos customizados
- ✓ Validacao de entrada: ValidadorDados com 11 metodos de validacao
- ✓ Persistencia de dados: GerenciadorArquivos (CSV), PreferenciasUsuario
- ✓ Polimorfismo: Virtual methods, interfaces, heranca multipla

---

## Como Compilar e Executar

### Prerequisitos

- CMake >= 3.10
- Compilador C++ com suporte a C++17 (g++, clang)
- Make

### Compilacao - Metodo 1: Script Automatico (Recomendado)

```bash
cd HospitalCore
./build.sh
```

Opcoes do script:
```bash
./build.sh clean        # Clean build (limpa anterior)
./build.sh release      # Build otimizado
./build.sh debug        # Build com simbolos de debug
```

### Compilacao - Metodo 2: CMake Manual

```bash
cd HospitalCore
mkdir -p build
cd build
cmake ..
make
```

### Compilacao - Metodo 3: Build Release Otimizado

```bash
cd HospitalCore
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Executando

```bash
./build/hospital_core   # a partir da raiz do projeto, apos compilar
# Saida dos arquivos CSV: pasta build/dados/ (junto do executavel)
```

### Limpeza

```bash
cd HospitalCore
rm -rf build/*
```

---

## Uso do Sistema

1. Ao iniciar, o sistema carrega as preferencias do usuario (se existirem)
2. Menu principal oferece acesso a:
   - Gestao de Pacientes (CRUD completo)
   - Gestao de Medicos (CRUD completo)
   - Gestao de Alas e Leitos
   - Agendamento de Consultas
   - Controle de Internacoes
   - Preferencias do Usuario
   - Demonstracao de Polimorfismo

3. Todos os inputs sao validados:
   - CPF com verificacao de digitos
   - CRM validado
   - Datas com suporte a anos bissextos
   - Horarios (0-23h, 0-59min)

4. Dados persistidos em arquivo CSV (preferencias.csv)

---

## Hierarquia de Excecoes

```
HospitalExcecao (base)
├── PacienteExcecao
├── MedicoExcecao
├── AlaExcecao
├── LeitoExcecao
├── ConsultaExcecao
├── InternacaoExcecao
├── ValidacaoExcecao
│   ├── CPFInvalidoExcecao
│   ├── CRMInvalidoExcecao
│   ├── NomeInvalidoExcecao
│   ├── DataInvalidaExcecao
│   ├── HoraInvalidaExcecao
│   └── MinutoInvalidoExcecao
└── ArquivoExcecao
```

---

## Validadores Implementados

A classe `ValidadorDados` oferece metodos estaticos para:
- `validarCPF()` - Verificacao de digitos (modulo 11)
- `validarCRM()` - Formato e comprimento
- `validarNome()` - Minimo 3 caracteres, letras+espacos
- `validarData()` - Validacao completa com anos bissextos
- `validarHora()` - 0-23
- `validarMinuto()` - 0-59
- `validarEspecialidade()` - Formato alfanumerico
- `validarHistorico()` - Comprimento maximo
- `validarNomeAla()` - Caracteres permitidos
- `validarIdLeito()` - Intervalo 1-9999
- Metodos auxiliares para limpeza e formatacao

---

## Arquivos de Dados

- **preferencias.csv:** Armazena preferencias do usuario (nome de exibicao, tema) em `build/dados/` junto ao executavel

---

## Estatisticas do Projeto

- **Classes:** 13 (Pessoa, Paciente, Medico, AlaHospitalar, Leito, Consulta, Internacao, SistemaGestao, Menu, ValidadorDados, GerenciadorArquivos, PreferenciasUsuario, HospitalExcecao)
- **Interfaces:** 2 (IGerenciavel, IAgendavel)
- **Excecoes Customizadas:** 12+ tipos
- **Metodos de Validacao:** 11

---

## Notas de Implementacao

1. **Memoria:** Uso de `unique_ptr` em `SistemaGestao` para containers
2. **Validacao:** Todas as entradas validadas antes de processamento
3. **Persistencia:** Dados de preferencias salvos em CSV simples
4. **Polimorfismo:** Uso de virtual methods para `exibirFicha()`
5. **Excecoes:** Try-catch com mensagens descritivas ao usuario
6. **Regex:** Validacao de formatos usando `<regex>`
7. **STL:** Uso extensivo de containers (vector, map) e algoritmos

---

## Licenca

MIT License - Veja LICENSE.txt para detalhes