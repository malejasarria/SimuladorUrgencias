
#include "../include/TablaHash.h"
#include <iostream>

void TablaHash::insertar(std::shared_ptr<Paciente> paciente) {

    if (paciente == nullptr) {
        return;
    }

    pacientes[paciente->getCedula()] = paciente;
}

std::shared_ptr<Paciente> TablaHash::buscar(std::string cedula) const {

    auto resultado = pacientes.find(cedula);

    if (resultado != pacientes.end()) {
        return resultado->second;
    }

    return nullptr;
}

bool TablaHash::existe(std::string cedula) const {

    return pacientes.find(cedula) != pacientes.end();
}

int TablaHash::getCantidad() const {

    return static_cast<int>(pacientes.size());
}

void TablaHash::mostrarTodos() const {

    if (pacientes.empty()) {
        std::cout << "\nNo hay pacientes registrados.\n";
        return;
    }

    std::cout << "\n--- HISTORIAL DE PACIENTES ---\n";

    for (const auto& elemento : pacientes) {

        std::cout << "Cedula: " << elemento.first
                  << " | Nombre: " << elemento.second->getNombre()
                  << " | Estado: " << elemento.second->getEstado()
                  << std::endl;
    }
}
