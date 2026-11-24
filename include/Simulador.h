
#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "ListaCamas.h"
#include "ColaPrioridad.h"
#include "PilaAtendidos.h"
#include "TablaHash.h"
#include "ArbolMedicos.h"
#include "Medico.h"

#include <string>

class Simulador {
private:
    ListaCamas camas;
    ColaPrioridad colaPrioridad;
    PilaAtendidos pilaAtendidos;
    TablaHash historial;
    ArbolMedicos arbolMedicos;

    Medico* medicoActual;

    int camaActual;
    int turnoActual;

    int pacientesRecibidos;
    int pacientesDadosDeAlta;
    int pacientesPerdidos;
    int tiempoEsperaTotal;

    void mostrarEstado();

public:
    Simulador(std::string nombreMedico);

    void iniciar();
    void registrarPaciente();
    void recibirPaciente();
    void moverIzquierda();
    void moverDerecha();
    void tratarPaciente();
    void darAltaPaciente();
};

#endif
