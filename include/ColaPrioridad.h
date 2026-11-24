
#ifndef COLAPRIORIDAD_H
#define COLAPRIORIDAD_H

#include "Paciente.h"
#include <memory>

class ColaPrioridad {

private:

    struct Nodo {
        std::shared_ptr<Paciente> paciente;
        Nodo* siguiente;

        Nodo(std::shared_ptr<Paciente> paciente);
    };

    Nodo* frente;
    int cantidad;

public:

    ColaPrioridad();
    ~ColaPrioridad();

    void encolar(std::shared_ptr<Paciente> paciente);

    std::shared_ptr<Paciente> desencolar();

    std::shared_ptr<Paciente> consultarPrimero() const;

    bool estaVacia() const;

    int getCantidad() const;

    void mostrarCola() const;
};

#endif
