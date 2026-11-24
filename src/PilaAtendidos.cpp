
#include "../include/PilaAtendidos.h"
#include <iostream>

PilaAtendidos::Nodo::Nodo(std::shared_ptr<Paciente> paciente) {

    this->paciente = paciente;
    siguiente = nullptr;
}

PilaAtendidos::PilaAtendidos() {

    tope = nullptr;
    cantidad = 0;
}

PilaAtendidos::~PilaAtendidos() {

    vaciar();
}

void PilaAtendidos::apilar(std::shared_ptr<Paciente> paciente) {

    if (paciente == nullptr) {
        return;
    }

    Nodo* nuevo = new Nodo(paciente);

    nuevo->siguiente = tope;
    tope = nuevo;

    cantidad++;
}

std::shared_ptr<Paciente> PilaAtendidos::desapilar() {

    if (estaVacia()) {
        return nullptr;
    }

    Nodo* temporal = tope;

    std::shared_ptr<Paciente> paciente = temporal->paciente;

    tope = tope->siguiente;

    delete temporal;

    cantidad--;

    return paciente;
}

std::shared_ptr<Paciente> PilaAtendidos::consultarTope() const {

    if (estaVacia()) {
        return nullptr;
    }

    return tope->paciente;
}

bool PilaAtendidos::estaVacia() const {

    return tope == nullptr;
}

int PilaAtendidos::getCantidad() const {

    return cantidad;
}

void PilaAtendidos::mostrarPila() const {

    if (estaVacia()) {

        std::cout << "\nNo hay pacientes atendidos.\n";
        return;
    }

    std::cout << "\n--- HISTORIAL DE PACIENTES ATENDIDOS ---\n";

    Nodo* actual = tope;

    while (actual != nullptr) {

        std::cout << "Paciente: "
                  << actual->paciente->getNombre()
                  << " | Gravedad: "
                  << actual->paciente->getGravedad()
                  << std::endl;

        actual = actual->siguiente;
    }
}

void PilaAtendidos::vaciar() {

    while (tope != nullptr) {

        Nodo* temporal = tope;

        tope = tope->siguiente;

        delete temporal;
    }

    cantidad = 0;
}
