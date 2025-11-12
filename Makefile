# Compilador C++
CXX = g++

# Flags de compilação: C++17, todos os warnings, e símbolos de debug
CXXFLAGS = -std=c++17 -Wall -g

# Diretório dos fontes
SRCDIR = src

# Nome do executável
TARGET = hospital_core

# Encontra todos os arquivos .cpp no diretório src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Gera a lista de arquivos .o (objeto) a partir dos .cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Regra principal: compila o alvo (o executável)
all: $(TARGET)

# Regra de linkagem: junta todos os arquivos .o para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regra de compilação: transforma um .cpp em .o
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra "clean": remove os arquivos compilados e o executável
clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

# Regra "run": compila e executa o programa
run: all
	./$(TARGET)

.PHONY: all clean run