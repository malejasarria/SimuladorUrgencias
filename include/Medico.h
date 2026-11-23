
#ifndef MEDICO_H
#define MEDICO_H

#include <string>

class Medico {

private:
    std::string nombre;
    int jornadasTrabajadas;
    int turnosJornada;
    int totalTurnos;

public:

    Medico(std::string nombre);

    std::string getNombre() const;
    int getJornadasTrabajadas() const;
    int getTurnosJornada() const;
    int getTotalTurnos() const;

    void iniciarJornada();
    void registrarTurno();
    void mostrarInformacion() const;
};

#endif
