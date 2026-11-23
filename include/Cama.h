
#ifndef CAMA_H
#define CAMA_H

#include "Paciente.h"
#include <memory>

class Cama {

private:
    int numero;
    std::shared_ptr<Paciente> paciente;

    Cama* anterior;
    Cama* siguiente;

public:

    Cama(int numero);

    int getNumero() const;

    bool estaVacia() const;

    std::shared_ptr<Paciente> getPaciente() const;

    void asignarPaciente(std::shared_ptr<Paciente> paciente);

    void liberar();

    Cama* getAnterior() const;
    Cama* getSiguiente() const;

    void setAnterior(Cama* anterior);
    void setSiguiente(Cama* siguiente);

    void mostrar() const;
};

#endif
