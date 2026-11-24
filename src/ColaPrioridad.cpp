
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
                  << std::endl;

        actual = actual->siguiente;
    }
}
