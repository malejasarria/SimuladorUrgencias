
#include "include/Simulador.h"
#include <iostream>
#include <string>

int main() {

    std::string nombreMedico;

    std::cout << "====================================\n";
    std::cout << "       SIMULADOR DE URGENCIAS\n";
    std::cout << "====================================\n";

    std::cout << "\nIngresa el nombre del medico: ";
    std::getline(std::cin, nombreMedico);

    Simulador simulador(nombreMedico);

    simulador.iniciar();

    return 0;
}
