cmake_minimum_required(VERSION 3.10)
project(HospitalCore)

# Configurar C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

# Incluir o diretório de headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Fonte dos arquivos
set(SOURCES
    src/main.cpp
    src/AlaHospitalar.cpp
    src/Consulta.cpp
    src/GerenciadorArquivos.cpp
    src/Internacao.cpp
    src/Leito.cpp
    src/Medico.cpp
    src/Menu.cpp
    src/Paciente.cpp
    src/Pessoa.cpp
    src/PreferenciasUsuario.cpp
    src/SistemaGestao.cpp
    src/ValidadorDados.cpp
)

# Criar executável
add_executable(hospital_core ${SOURCES})

# Mensagens de build
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Include directory: ${CMAKE_SOURCE_DIR}/include")