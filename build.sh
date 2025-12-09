#!/bin/bash

# Script de build para HospitalCore
# Uso: ./build.sh [clean|release|debug]

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"
TARGET_PATH="$BUILD_DIR/hospital_core"

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Função de ajuda
print_help() {
    echo "Uso: $0 [opção]"
    echo ""
    echo "Opções:"
    echo "  clean       - Limpa build anterior"
    echo "  release     - Build com otimizações (Release)"
    echo "  debug       - Build com símbolos de debug (Debug)"
    echo "  (padrão)    - Build normal"
    echo ""
}

# Verifica se CMake está instalado
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}Erro: CMake não encontrado. Instale CMake primeiro.${NC}"
    exit 1
fi

# Processa argumentos
BUILD_TYPE="Debug"
CLEAN_BUILD=false

case "${1:-}" in
    clean)
        echo -e "${YELLOW}Limpando build anterior...${NC}"
        rm -rf "$BUILD_DIR"
        mkdir -p "$BUILD_DIR"
        CLEAN_BUILD=true
        ;;
    release)
        BUILD_TYPE="Release"
        echo -e "${YELLOW}Build tipo: Release (otimizado)${NC}"
        ;;
    debug)
        BUILD_TYPE="Debug"
        echo -e "${YELLOW}Build tipo: Debug${NC}"
        ;;
    help|-h|--help)
        print_help
        exit 0
        ;;
    *)
        BUILD_TYPE="Debug"
        ;;
esac

# Cria diretório de build se não existir
if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
fi

# Executa CMake
echo -e "${YELLOW}Executando CMake...${NC}"
cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" "$SCRIPT_DIR"

# Compila
echo -e "${YELLOW}Compilando...${NC}"
make -j$(nproc)

# Verifica se compilation foi bem-sucedida
if [ -f "$TARGET_PATH" ]; then
    echo ""
    echo -e "${GREEN}✓ Build concluído com sucesso!${NC}"
    echo -e "${GREEN}✓ Executável: $TARGET_PATH${NC}"
    echo ""
    echo -e "${YELLOW}Para executar:${NC}"
    echo "  $TARGET_PATH"
    echo ""
else
    echo -e "${RED}✗ Erro: Executável não foi criado${NC}"
    exit 1
fi