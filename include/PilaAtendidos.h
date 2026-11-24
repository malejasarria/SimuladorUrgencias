
#ifndef PILAATENDIDOS_H
#define PILAATENDIDOS_H

#include "Paciente.h"
#include <memory>

class PilaAtendidos {

private:

    struct Nodo {
        std::shared_ptr<Paciente> paciente;
        Nodo* siguiente;

        Nodo(std::shared_ptr<Paciente> paciente);
    };

    Nodo* tope;
    int cantidad;

public:

    PilaAtendidos();
    ~PilaAtendidos();

    void apilar(std::shared_ptr<Paciente> paciente);

    std::shared_ptr<Paciente> desapilar();

    std::shared_ptr<Paciente> consultarTope() const;

    bool estaVacia() const;

    int getCantidad() const;

    void mostrarPila() const;
};

#endif
