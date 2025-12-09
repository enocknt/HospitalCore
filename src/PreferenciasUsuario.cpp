#include <PreferenciasUsuario.h>

PreferenciasUsuario::PreferenciasUsuario()
    : nomeExibicao("Usuario Padrão")
    , tema("claro")
{
}

PreferenciasUsuario::PreferenciasUsuario(const std::string &nome, const std::string &t)
    : nomeExibicao(nome)
    , tema(t)
{
}

std::string PreferenciasUsuario::getNomeExibicao() const
{
    return nomeExibicao;
}

std::string PreferenciasUsuario::getTema() const
{
    return tema;
}

void PreferenciasUsuario::setNomeExibicao(const std::string &nome)
{
    this->nomeExibicao = nome;
}

void PreferenciasUsuario::setTema(const std::string &t)
{
    if (t == "claro" || t == "escuro") {
        this->tema = t;
    }
}

bool PreferenciasUsuario::ehTemaDarkModeAtivo() const
{
    return tema == "escuro";
}

std::string PreferenciasUsuario::obterIdentificador() const
{
    return "preferencias_" + nomeExibicao;
}

std::string PreferenciasUsuario::obterDescricao() const
{
    return "Preferencias [Nome: " + nomeExibicao + ", Tema: " + tema + "]";
}