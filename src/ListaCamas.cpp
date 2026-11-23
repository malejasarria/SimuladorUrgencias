
#include "../include/ListaCamas.h"
#include <iostream>

ListaCamas::ListaCamas() {

    primero = nullptr;
    ultimo = nullptr;
    cantidad = 0;

    for (int i = 1; i <= 10; i++) {
        agregarCama(i);
    }
}

ListaCamas::~ListaCamas() {

    Cama* actual = primero;

    while (actual != nullptr) {

        Cama* siguiente = actual->getSiguiente();

        delete actual;

        actual = siguiente;
    }
}

void ListaCamas::agregarCama(int numero) {

    Cama* nueva = new Cama(numero);

    if (primero == nullptr) {

        primero = nueva;
        ultimo = nueva;

    } else {

        ultimo->setSiguiente(nueva);
        nueva->setAnterior(ultimo);

        ultimo = nueva;
    }

    cantidad++;
}

Cama* ListaCamas::buscarCama(int numero) {

    Cama* actual = primero;

    while (actual != nullptr) {

        if (actual->getNumero() == numero) {
            return actual;
        }

        actual = actual->getSiguiente();
    }

    return nullptr;
}

bool ListaCamas::asignarPaciente(
    int numero,
    std::shared_ptr<Paciente> paciente
) {

    Cama* cama = buscarCama(numero);

    if (cama == nullptr || !cama->estaVacia() || paciente == nullptr) {
        return false;
    }

    cama->asignarPaciente(paciente);

    return true;
}

bool ListaCamas::liberarCama(int numero) {

    Cama* cama = buscarCama(numero);

    if (cama == nullptr || cama->estaVacia()) {
        return false;
    }

    cama->liberar();

    return true;
}

int ListaCamas::contarDisponibles() const {

    int disponibles = 0;

    Cama* actual = primero;

    while (actual != nullptr) {

        if (actual->estaVacia()) {
            disponibles++;
        }

        actual = actual->getSiguiente();
    }

    return disponibles;
}

void ListaCamas::mostrarAdelante() const {

    std::cout << "\n--- CAMAS DEL HOSPITAL ---\n";

    Cama* actual = primero;

    while (actual != nullptr) {

        actual->mostrar();

        actual = actual->getSiguiente();
    }
}

void ListaCamas::mostrarAtras() const {

    std::cout << "\n--- RECORRIDO INVERSO ---\n";

    Cama* actual = ultimo;

    while (actual != nullptr) {

        actual->mostrar();

        actual = actual->getAnterior();
    }
}
//
// Created by Asus on 23/11/2026.
//
