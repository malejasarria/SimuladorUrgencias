
#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

class Paciente {

private:
    std::string cedula;
    std::string nombre;
    std::string condicion;
    std::string estado;
    std::string medicoAsignado;

    int gravedad;
    int turnoLlegada;
    int tiempoEspera;
    int turnosTratamiento;

public:

    Paciente(std::string cedula, std::string nombre,
             int gravedad, std::string condicion,
             int turnoLlegada);

    std::string getCedula() const;
    std::string getNombre() const;
    std::string getEstado() const;
    int getGravedad() const;
    int getTiempoEspera() const;
    int getTurnosTratamiento() const;

    void incrementarEspera();
    void reducirTratamiento();

    void asignarMedico(std::string medico);
    void cambiarEstado(std::string nuevoEstado);

    void mostrarInformacion() const;
};

#endif
