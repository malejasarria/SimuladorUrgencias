
#include "../include/Paciente.h"
#include <iostream>

Paciente::Paciente(std::string cedula, std::string nombre,
                   int gravedad, std::string condicion,
                   int turnoLlegada) {

    this->cedula = cedula;
    this->nombre = nombre;
    this->gravedad = gravedad;
    this->condicion = condicion;
    this->turnoLlegada = turnoLlegada;

    tiempoEspera = 0;
    turnosTratamiento = 6 - gravedad;
    estado = "En cola";
    medicoAsignado = "Sin asignar";
}

std::string Paciente::getCedula() const {
    return cedula;
}

std::string Paciente::getNombre() const {
    return nombre;
}

int Paciente::getGravedad() const {
    return gravedad;
}

int Paciente::getTiempoEspera() const {
    return tiempoEspera;
}

int Paciente::getTurnosTratamiento() const {
    return turnosTratamiento;
}

void Paciente::incrementarEspera() {
    tiempoEspera++;
}

void Paciente::reducirTratamiento() {
    if (turnosTratamiento > 0) {
        turnosTratamiento--;
    }
}

void Paciente::asignarMedico(std::string medico) {
    medicoAsignado = medico;
}

void Paciente::cambiarEstado(std::string nuevoEstado) {
    estado = nuevoEstado;
}

void Paciente::mostrarInformacion() const {

    std::cout << "\n--- PACIENTE ---\n";

    std::cout << "Cedula: " << cedula << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Gravedad: " << gravedad << std::endl;
    std::cout << "Condicion: " << condicion << std::endl;
    std::cout << "Tiempo de espera: " << tiempoEspera << std::endl;

    std::cout << "Tratamientos pendientes: "
              << turnosTratamiento << std::endl;

    std::cout << "Estado: " << estado << std::endl;
    std::cout << "Medico: " << medicoAsignado << std::endl;
}
