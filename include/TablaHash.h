
#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "Paciente.h"
#include <memory>
#include <string>
#include <unordered_map>

class TablaHash {

private:

    std::unordered_map<std::string, std::shared_ptr<Paciente>> pacientes;

public:

    void insertar(std::shared_ptr<Paciente> paciente);

    std::shared_ptr<Paciente> buscar(std::string cedula) const;

    bool existe(std::string cedula) const;

    int getCantidad() const;

    void mostrarTodos() const;
};

#endif
