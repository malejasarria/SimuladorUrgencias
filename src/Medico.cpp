
#include "../include/Medico.h"
#include <iostream>

Medico::Medico(std::string nombre) {

    this->nombre = nombre;

    jornadasTrabajadas = 0;
    turnosJornada = 0;
    totalTurnos = 0;
}

std::string Medico::getNombre() const {
    return nombre;
}

int Medico::getJornadasTrabajadas() const {
    return jornadasTrabajadas;
}

int Medico::getTurnosJornada() const {
    return turnosJornada;
}

int Medico::getTotalTurnos() const {
    return totalTurnos;
}

void Medico::iniciarJornada() {

    if (jornadasTrabajadas > 0) {
        historialTurnos.push_back(turnosJornada);
    }

    jornadasTrabajadas++;
    turnosJornada = 0;
}

void Medico::registrarTurno() {

    if (turnosJornada < 50) {
        turnosJornada++;
        totalTurnos++;
    }
}

void Medico::mostrarInformacion() const {

    std::cout << "\n--- INFORMACION DEL MEDICO ---\n";

    std::cout << "Nombre: " << nombre << std::endl;

    std::cout << "Jornadas trabajadas: "
              << jornadasTrabajadas << std::endl;

    std::cout << "Turnos de esta jornada: "
              << turnosJornada << std::endl;

    std::cout << "Total de turnos: "
              << totalTurnos << std::endl;

    std::cout << "\n--- HISTORIAL DE JORNADAS ---\n";

    for (int i = 0; i < static_cast<int>(historialTurnos.size()); i++) {

        std::cout << "Jornada " << i + 1 << ": "
                  << historialTurnos[i] << " turnos\n";
    }

    if (jornadasTrabajadas > 0) {

        std::cout << "Jornada " << jornadasTrabajadas << ": "
                  << turnosJornada << " turnos (actual)\n";
    }
}
