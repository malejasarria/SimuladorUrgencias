
#include "../include/ColaPrioridad.h"
#include <iostream>

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

void ColaPrioridad::mostrarCola() const {

    if (estaVacia()) {

        std::cout << "\nNo hay pacientes en espera.\n";
        return;
    }

    std::cout << "\n--- COLA DE PRIORIDAD ---\n";

    Nodo* actual = frente;

    while (actual != nullptr) {

        std::cout << "Paciente: "
                  << actual->paciente->getNombre()
                  << " | Gravedad: "
                  << actual->paciente->getGravedad()
                  << " | Espera: "
                  << actual->paciente->getTiempoEspera()
                  << " minutos"
                  << " | Turnos: "
                  << actual->paciente->getTurnosEnCola()
                  << std::endl;

        actual = actual->siguiente;
    }
}

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
