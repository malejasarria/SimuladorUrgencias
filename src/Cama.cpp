
#include "../include/Cama.h"
#include <iostream>

Cama::Cama(int numero) {

    this->numero = numero;

    paciente = nullptr;

    anterior = nullptr;
    siguiente = nullptr;
}

int Cama::getNumero() const {
    return numero;
}

bool Cama::estaVacia() const {
    return paciente == nullptr;
}

std::shared_ptr<Paciente> Cama::getPaciente() const {
    return paciente;
}

void Cama::asignarPaciente(std::shared_ptr<Paciente> paciente) {
    this->paciente = paciente;
}

void Cama::liberar() {
    paciente = nullptr;
}

Cama* Cama::getAnterior() const {
    return anterior;
}

Cama* Cama::getSiguiente() const {
    return siguiente;
}

void Cama::setAnterior(Cama* anterior) {
    this->anterior = anterior;
}

void Cama::setSiguiente(Cama* siguiente) {
    this->siguiente = siguiente;
}

void Cama::mostrar() const {

    std::cout << "\nCama " << numero << ": ";

    if (estaVacia()) {
        std::cout << "Disponible";
    } else {
        std::cout << "Ocupada por "
                  << paciente->getNombre();
    }

    std::cout << std::endl;
}
