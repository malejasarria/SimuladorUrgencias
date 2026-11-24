
#include "../include/Simulador.h"
#include <iostream>

Simulador::Simulador(std::string nombreMedico) {

    medicoActual = nullptr;

    camaActual = 1;
    turnoActual = 0;

    pacientesRecibidos = 0;
    pacientesDadosDeAlta = 0;
    pacientesPerdidos = 0;
    tiempoEsperaTotal = 0;

    // Registrar al primer medico en el arbol.
    arbolMedicos.insertar(Medico(nombreMedico));

    // Obtener el medico registrado.
    medicoActual = arbolMedicos.buscar(nombreMedico);

    // Iniciar su primera jornada.
    if (medicoActual != nullptr) {
        medicoActual->iniciarJornada();
    }
}

void Simulador::mostrarEstado() {

    std::cout << "\n====================================\n";
    std::cout << "       SIMULADOR DE URGENCIAS\n";
    std::cout << "====================================\n";

    std::cout << "\nMedico actual: ";

    if (medicoActual != nullptr) {
        std::cout << medicoActual->getNombre();
    }

    std::cout << "\nTurno actual: " << turnoActual;
    std::cout << "\nCama actual del medico: " << camaActual;

    std::cout << "\n\n--- ESTADO DE LAS CAMAS ---\n";
    camas.mostrarAdelante();

    std::cout << "\n--- COLA DE PRIORIDAD ---\n";
    colaPrioridad.mostrarCola();

    std::cout << "\n--- RESUMEN ---\n";
    std::cout << "Pacientes recibidos: "
              << pacientesRecibidos << std::endl;

    std::cout << "Pacientes dados de alta: "
              << pacientesDadosDeAlta << std::endl;

    std::cout << "Pacientes perdidos: "
              << pacientesPerdidos << std::endl;

    std::cout << "Camas disponibles: "
              << camas.contarDisponibles() << std::endl;

    std::cout << "\n====================================\n";
}

void Simulador::iniciar() {

    int opcion;

    do {
        mostrarEstado();

        std::cout << "\n1. Actualizar estado";
        std::cout << "\n0. Salir";
        std::cout << "\nSelecciona una opcion: ";

        std::cin >> opcion;

        if (opcion == 1) {
            std::cout << "\nEstado actualizado.\n";
        } else if (opcion != 0) {
            std::cout << "\nOpcion no valida.\n";
        }

    } while (opcion != 0);

    std::cout << "\nSimulador cerrado.\n";
}
