#include "Menu.h"

#include <iostream>

int main()
{
    // Bloco try-catch principal para capturar exceções não tratadas
    try {
        Menu menu;

        menu.executar();
    } catch (const std::exception &e) {
        std::cerr << "Uma falha critica ocorreu: " << e.what() << std::endl;

        return 1;
    }

    return 0;
}