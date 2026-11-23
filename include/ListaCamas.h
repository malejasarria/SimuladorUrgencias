
#ifndef LISTACAMAS_H
#define LISTACAMAS_H

#include "Cama.h"

class ListaCamas {

private:
    Cama* primero;
    Cama* ultimo;
    int cantidad;

public:

    ListaCamas();
    ~ListaCamas();

    void agregarCama(int numero);

    Cama* buscarCama(int numero);

    bool asignarPaciente(int numero, std::shared_ptr<Paciente> paciente);

    bool liberarCama(int numero);

    int contarDisponibles() const;

    void mostrarAdelante() const;

    void mostrarAtras() const;
};

#endif
