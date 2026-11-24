
#ifndef ARBOLMEDICOS_H
#define ARBOLMEDICOS_H

#include "Medico.h"
#include <string>

class ArbolMedicos {
private:
    struct Nodo {
        Medico medico;
        Nodo* izquierda;
        Nodo* derecha;

        Nodo(Medico medico);
    };

    Nodo* raiz;

    Nodo* insertar(Nodo* nodo, Medico medico);
    Nodo* buscar(Nodo* nodo, std::string nombre) const;
    void mostrarInorden(Nodo* nodo) const;
    void liberar(Nodo* nodo);

public:
    ArbolMedicos();
    ~ArbolMedicos();

    void insertar(Medico medico);
    Medico* buscar(std::string nombre) const;
    void mostrarMedicos() const;
};

#endif
