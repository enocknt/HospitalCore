# 🏥 HospitalCore - Sistema de Gestão Hospitalar

![Status](https://img.shields.io/badge/status-concluído-green)
![Linguagem](https://img.shields.io/badge/linguagem-C%2B%2B17-blue.svg)
![Plataforma](https://img.shields.io/badge/plataforma-Linux%2FmacOS%2FWindows-lightgrey)

Projeto acadêmico de um sistema de gestão hospitalar em C++ para a disciplina de **IMD0030 - Linguagem de Programação I**. O sistema implementa conceitos de **Encapsulamento**, **Herança**, **Polimorfismo** e **Tratamento de Exceções**.

---

## ✨ Funcionalidades

O sistema permite o gerenciamento completo (CRUD) das principais entidades de um hospital:

* **🧑‍⚕️ Gestão de Médicos:** Cadastrar, listar e buscar por CRM.
* **🤕 Gestão de Pacientes:** Cadastrar, listar, buscar por CPF e atualizar prontuário.
* **🏥 Gestão de Alas:** Cadastrar novas alas (ex: "Cardiologia").
* **🛏️ Gestão de Leitos:** Adicionar leitos a uma ala e listar ocupação.
* **📅 Agendamento de Consultas:** Criar, listar e cancelar consultas, com verificação de conflitos.
* **🛌 Controle de Internações:** Internar pacientes em leitos disponíveis e dar alta.
* **🚫 Tratamento de Exceções:** O sistema usa exceções customizadas para validar dados e gerenciar erros (ex: `LeitoExcecao` para ala lotada).
* **🔍 Demonstração de Polimorfismo:** Uma função especial exibe a "ficha" de todas as `Pessoas` (Médicos e Pacientes) usando um método virtual.

---

## 🛠️ Tecnologias Utilizadas

* **C++ 17:** Linguagem principal do projeto.
* **Makefile:** Para automação da compilação.
* **Mermaid:** Para geração do diagrama de classes UML.

---

## 🚀 Como Compilar e Rodar

O projeto utiliza `make` para compilação.

### 1. Pré-requisitos

* Um compilador C++ (g++)
* `make`

### 2. Compilando o Projeto

No terminal, na raiz do projeto, execute:

```sh
make
```

Isso irá compilar todos os fontes da pasta src/ e criar um executável chamado `hospital_core`.

### 3. Rodando a Aplicação

Para executar o sistema, rode:

```sh
./hospital_core
```

## 📄 License

Este projeto está licenciado sob a Licença MIT.