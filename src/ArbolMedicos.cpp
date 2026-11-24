
#include "../include/ArbolMedicos.h"
#include <iostream>

ArbolMedicos::Nodo::Nodo(Medico medico)
    : medico(medico), izquierda(nullptr), derecha(nullptr) {
}

ArbolMedicos::ArbolMedicos() {
    raiz = nullptr;
}

ArbolMedicos::~ArbolMedicos() {
    liberar(raiz);
}

ArbolMedicos::Nodo* ArbolMedicos::insertar(Nodo* nodo, Medico medico) {

    if (nodo == nullptr) {
        return new Nodo(medico);
    }

    if (medico.getNombre() < nodo->medico.getNombre()) {
        nodo->izquierda = insertar(nodo->izquierda, medico);
    } else if (medico.getNombre() > nodo->medico.getNombre()) {
        nodo->derecha = insertar(nodo->derecha, medico);
    }

    return nodo;
}

void ArbolMedicos::insertar(Medico medico) {
    raiz = insertar(raiz, medico);
}

ArbolMedicos::Nodo* ArbolMedicos::buscar(
    Nodo* nodo, std::string nombre) const {

    if (nodo == nullptr || nodo->medico.getNombre() == nombre) {
        return nodo;
    }

    if (nombre < nodo->medico.getNombre()) {
        return buscar(nodo->izquierda, nombre);
    }

    return buscar(nodo->derecha, nombre);
}

Medico* ArbolMedicos::buscar(std::string nombre) const {
    Nodo* resultado = buscar(raiz, nombre);

    if (resultado == nullptr) {
        return nullptr;
    }

    return &(resultado->medico);
}

void ArbolMedicos::mostrarInorden(Nodo* nodo) const {

    if (nodo == nullptr) {
        return;
    }

    mostrarInorden(nodo->izquierda);
    nodo->medico.mostrarInformacion();
    mostrarInorden(nodo->derecha);
}

void ArbolMedicos::mostrarMedicos() const {

    if (raiz == nullptr) {
        std::cout << "\nNo hay medicos registrados.\n";
        return;
    }

    std::cout << "\n--- MEDICOS REGISTRADOS ---\n";
    mostrarInorden(raiz);
}

void ArbolMedicos::liberar(Nodo* nodo) {

    if (nodo == nullptr) {
        return;
    }

    liberar(nodo->izquierda);
    liberar(nodo->derecha);

    delete nodo;
}
