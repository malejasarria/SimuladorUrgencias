
#include "../include/ColaPrioridad.h"
#include <iostream>
#include <vector>
#include <iomanip>

ColaPrioridad::Nodo::Nodo(std::shared_ptr<Paciente> paciente) {
    this->paciente = paciente;
    siguiente = nullptr;
}

ColaPrioridad::ColaPrioridad() {
    frente = nullptr;
    cantidad = 0;
}

ColaPrioridad::~ColaPrioridad() {
    while (frente != nullptr) {
        Nodo* temporal = frente;
        frente = frente->siguiente;
        delete temporal;
    }
}

void ColaPrioridad::encolar(std::shared_ptr<Paciente> paciente) {

    if (paciente == nullptr) {
        return;
    }

    Nodo* nuevo = new Nodo(paciente);

    if (frente == nullptr ||
        paciente->getGravedad() < frente->paciente->getGravedad()) {

        nuevo->siguiente = frente;
        frente = nuevo;

    } else {

        Nodo* actual = frente;

        while (actual->siguiente != nullptr &&
               actual->siguiente->paciente->getGravedad()
               <= paciente->getGravedad()) {

            actual = actual->siguiente;
        }

        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }

    cantidad++;
}

std::shared_ptr<Paciente> ColaPrioridad::desencolar() {

    if (estaVacia()) {
        return nullptr;
    }

    Nodo* temporal = frente;

    std::shared_ptr<Paciente> pacienteAtendido = temporal->paciente;

    frente = frente->siguiente;

    delete temporal;

    cantidad--;

    return pacienteAtendido;
}

std::shared_ptr<Paciente> ColaPrioridad::consultarPrimero() const {

    if (estaVacia()) {
        return nullptr;
    }

    return frente->paciente;
}

bool ColaPrioridad::estaVacia() const {
    return frente == nullptr;
}

int ColaPrioridad::getCantidad() const {
    return cantidad;
}

// MOSTRAR RESUMEN DE LA COLA POR GRAVEDAD
void ColaPrioridad::mostrarResumen() const {

    if (estaVacia()) {
        std::cout << "\nCola de prioridad: vacia.\n";
        return;
    }

    std::vector<int> cantidades(6, 0);
    std::vector<int> totalTurnos(6, 0);

    Nodo* actual = frente;

    while (actual != nullptr) {

        int gravedad = actual->paciente->getGravedad();

        if (gravedad >= 1 && gravedad <= 5) {
            cantidades[gravedad]++;
            totalTurnos[gravedad] +=
                actual->paciente->getTurnosEnCola();
        }

        actual = actual->siguiente;
    }

    std::string nombresGravedad[6] = {
        "",
        "Critico",
        "Severo",
        "Moderado",
        "Leve",
        "Consulta"
    };

    std::cout << "\n--- RESUMEN DE LA COLA DE PRIORIDAD ---\n";

    std::cout << "Total de pacientes esperando: "
              << cantidad << "\n";

    for (int gravedad = 1; gravedad <= 5; gravedad++) {

        if (cantidades[gravedad] > 0) {

            double promedioTurnos =
                static_cast<double>(totalTurnos[gravedad]) /
                cantidades[gravedad];

            std::cout << "\nGravedad " << gravedad
                      << " (" << nombresGravedad[gravedad] << "): "
                      << cantidades[gravedad] << " paciente(s)";

            std::cout << " | Espera promedio: "
                      << std::fixed << std::setprecision(1)
                      << promedioTurnos << " turnos";

            if (gravedad == 1) {
                std::cout << " [ATENCION]";
            }

            std::cout << "\n";
        }
    }

    std::cout << "\n--- ALERTAS DE PACIENTES CRITICOS ---\n";

    actual = frente;

    bool hayAlertas = false;

    while (actual != nullptr) {

        if (actual->paciente->getGravedad() == 1 &&
            actual->paciente->getTurnosEnCola() >= 5) {

            hayAlertas = true;

            std::cout << "ALERTA: "
                      << actual->paciente->getNombre()
                      << " | Cedula: "
                      << actual->paciente->getCedula()
                      << " | Turnos esperando: "
                      << actual->paciente->getTurnosEnCola()
                      << "\n";
        }

        actual = actual->siguiente;
    }

    if (!hayAlertas) {
        std::cout << "No hay pacientes criticos en riesgo.\n";
    }
}

// MOSTRAR LOS PACIENTES DE LA COLA
void ColaPrioridad::mostrarCola() const {

    if (estaVacia()) {
        std::cout << "\nNo hay pacientes en espera.\n";
        return;
    }

    std::cout << "\n--- PACIENTES EN COLA (ORDEN DE PRIORIDAD) ---\n";

    Nodo* actual = frente;

    while (actual != nullptr) {

        std::cout << "Paciente: "
                  << actual->paciente->getNombre()
                  << " | Cedula: "
                  << actual->paciente->getCedula()
                  << " | Gravedad: "
                  << actual->paciente->getGravedad()
                  << " | Espera: "
                  << actual->paciente->getTiempoEspera()
                  << " minutos\n";

        actual = actual->siguiente;
    }
}

// ACTUALIZAR ESPERA Y RETIRAR PACIENTES PERDIDOS
std::vector<std::shared_ptr<Paciente>>
ColaPrioridad::actualizarEsperaYRetirarPerdidos() {

    std::vector<std::shared_ptr<Paciente>> pacientesPerdidos;

    Nodo* actual = frente;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {

        actual->paciente->incrementarEspera();
        actual->paciente->incrementarTurnosEnCola();

        if (actual->paciente->getGravedad() == 1 &&
            actual->paciente->getTurnosEnCola() > 6) {

            std::shared_ptr<Paciente> perdido = actual->paciente;

            perdido->cambiarEstado("Perdido");

            Nodo* temporal = actual;

            if (anterior == nullptr) {
                frente = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            actual = actual->siguiente;

            delete temporal;

            cantidad--;

            pacientesPerdidos.push_back(perdido);

        } else {

            anterior = actual;
            actual = actual->siguiente;
        }
    }

    return pacientesPerdidos;
}
