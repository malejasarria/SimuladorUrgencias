
#include "../include/Simulador.h"
#include <iostream>
#include <memory>
#include <limits>
#include <vector>

// CONSTRUCTOR DEL SIMULADOR
Simulador::Simulador(std::string nombreMedico) {

    medicoActual = nullptr;

    camaActual = 1;
    turnoActual = 0;

    pacientesRecibidos = 0;
    pacientesDadosDeAlta = 0;
    pacientesPerdidos = 0;
    tiempoEsperaTotal = 0;

    arbolMedicos.insertar(Medico(nombreMedico));

    medicoActual = arbolMedicos.buscar(nombreMedico);

    if (medicoActual != nullptr) {
        medicoActual->iniciarJornada();
    }
}

// FINALIZAR TURNO Y ACTUALIZAR PACIENTES EN ESPERA
void Simulador::finalizarTurno() {

    turnoActual++;
    medicoActual->registrarTurno();

    std::vector<std::shared_ptr<Paciente>> perdidos =
        colaPrioridad.actualizarEsperaYRetirarPerdidos();

    for (const auto& paciente : perdidos) {

        paciente->asignarMedico(medicoActual->getNombre());

        pacientesPerdidos++;

        std::cout << "\n====================================\n";
        std::cout << " ALERTA: PACIENTE CRITICO PERDIDO\n";
        std::cout << "====================================\n";

        std::cout << "Paciente: "
                  << paciente->getNombre() << std::endl;

        std::cout << "Cedula: "
                  << paciente->getCedula() << std::endl;

        std::cout << "Medico responsable: "
                  << medicoActual->getNombre() << std::endl;

        std::cout << "Turnos esperando: "
                  << paciente->getTurnosEnCola() << std::endl;

        std::cout << "El paciente permanece en el historial.\n";
    }
}

// REGISTRAR PACIENTES EN TRIAGE
void Simulador::registrarPaciente() {

    std::string cedula;
    std::string nombre;
    std::string condicion;
    int gravedad;

    std::cout << "\n========== INGRESO DE PACIENTE ==========\n";

    std::cout << "Cedula: ";
    std::getline(std::cin >> std::ws, cedula);

    if (historial.existe(cedula)) {
        std::cout << "\nYa existe un paciente con esa cedula.\n";
        return;
    }

    std::cout << "Nombre completo: ";
    std::getline(std::cin, nombre);

    std::cout << "Condicion medica: ";
    std::getline(std::cin, condicion);

    std::cout << "\nNivel de gravedad:\n";
    std::cout << "1. Critico\n";
    std::cout << "2. Severo\n";
    std::cout << "3. Moderado\n";
    std::cout << "4. Leve\n";
    std::cout << "5. Consulta\n";

    std::cout << "Seleccione la gravedad: ";

    if (!(std::cin >> gravedad)) {
        std::cout << "\nEntrada no valida.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        return;
    }

    if (gravedad < 1 || gravedad > 5) {
        std::cout << "\nLa gravedad debe estar entre 1 y 5.\n";
        return;
    }

    std::shared_ptr<Paciente> nuevoPaciente =
        std::make_shared<Paciente>(
            cedula,
            nombre,
            gravedad,
            condicion,
            turnoActual
        );

    colaPrioridad.encolar(nuevoPaciente);
    historial.insertar(nuevoPaciente);

    std::cout << "\nPaciente registrado correctamente.\n";

    nuevoPaciente->mostrarInformacion();

    std::cout << "\nEl paciente fue agregado a la cola de prioridad.\n";
}

// RECIBIR PACIENTE EN LA CAMA ACTUAL
void Simulador::recibirPaciente() {

    std::cout << "\n========== RECEPCION DE PACIENTE ==========\n";

    if (medicoActual == nullptr) {
        std::cout << "\nNo hay un medico activo.\n";
        return;
    }

    Cama* cama = camas.buscarCama(camaActual);

    if (cama == nullptr || !cama->estaVacia()) {
        std::cout << "\nNo se puede recibir al paciente.";
        std::cout << "\nLa cama actual esta ocupada o no existe.\n";
        return;
    }

    if (colaPrioridad.estaVacia()) {
        std::cout << "\nNo hay pacientes en la cola de prioridad.\n";
        return;
    }

    std::shared_ptr<Paciente> paciente = colaPrioridad.desencolar();

    paciente->asignarMedico(medicoActual->getNombre());
    paciente->cambiarEstado("En tratamiento");

    camas.asignarPaciente(camaActual, paciente);

    pacientesRecibidos++;
    tiempoEsperaTotal += paciente->getTiempoEspera();

    finalizarTurno();

    std::cout << "\nPaciente recibido correctamente.\n";

    paciente->mostrarInformacion();

    std::cout << "\nAsignado a la cama #" << camaActual << ".\n";
}

// MOVER MEDICO A LA IZQUIERDA
void Simulador::moverIzquierda() {

    if (medicoActual == nullptr) {
        std::cout << "\nNo hay un medico activo.\n";
        return;
    }

    if (camaActual > 1) {
        camaActual--;

        std::cout << "\nEl medico se movio a la cama "
                  << camaActual << ".\n";
    } else {
        std::cout << "\nEl medico ya esta en la primera cama.\n";
    }

    finalizarTurno();
}

// MOVER MEDICO A LA DERECHA
void Simulador::moverDerecha() {

    if (medicoActual == nullptr) {
        std::cout << "\nNo hay un medico activo.\n";
        return;
    }

    if (camaActual < 10) {
        camaActual++;

        std::cout << "\nEl medico se movio a la cama "
                  << camaActual << ".\n";
    } else {
        std::cout << "\nEl medico ya esta en la ultima cama.\n";
    }

    finalizarTurno();
}

// TRATAR PACIENTE DE LA CAMA ACTUAL
void Simulador::tratarPaciente() {

    std::cout << "\n========== TRATAMIENTO DE PACIENTE ==========\n";

    if (medicoActual == nullptr) {
        std::cout << "\nNo hay un medico activo.\n";
        return;
    }

    Cama* cama = camas.buscarCama(camaActual);

    if (cama == nullptr || cama->estaVacia()) {
        std::cout << "\nNo hay ningun paciente en esta cama.\n";
        return;
    }

    std::shared_ptr<Paciente> paciente = cama->getPaciente();

    if (paciente->getTurnosTratamiento() <= 0) {
        std::cout << "\nEl paciente ya completo su tratamiento.\n";
        return;
    }

    paciente->reducirTratamiento();

    finalizarTurno();

    std::cout << "\nSe realizo un tratamiento correctamente.\n";

    std::cout << "\nPaciente: "
              << paciente->getNombre();

    std::cout << "\nTratamientos pendientes: "
              << paciente->getTurnosTratamiento() << std::endl;

    if (paciente->getTurnosTratamiento() == 0) {
        paciente->cambiarEstado("Tratamiento completado");

        std::cout << "\nEl paciente ha completado todos sus tratamientos.\n";
        std::cout << "Ya puede recibir el alta medica.\n";
    } else {
        std::cout << "\nEl paciente todavia necesita tratamiento.\n";
    }
}

// DAR ALTA A UN PACIENTE
void Simulador::darAltaPaciente() {

    std::cout << "\n========== ALTA MEDICA ==========\n";

    if (medicoActual == nullptr) {
        std::cout << "\nNo hay un medico activo.\n";
        return;
    }

    Cama* cama = camas.buscarCama(camaActual);

    if (cama == nullptr || cama->estaVacia()) {
        std::cout << "\nNo hay ningun paciente en esta cama.\n";
        return;
    }

    std::shared_ptr<Paciente> paciente = cama->getPaciente();

    if (paciente->getTurnosTratamiento() > 0) {
        std::cout << "\nEl paciente todavia no ha completado su tratamiento.\n";

        std::cout << "Tratamientos pendientes: "
                  << paciente->getTurnosTratamiento() << std::endl;

        return;
    }

    paciente->cambiarEstado("Dado de alta");

    pilaAtendidos.apilar(paciente);

    camas.liberarCama(camaActual);

    pacientesDadosDeAlta++;

    finalizarTurno();

    std::cout << "\nAlta medica realizada correctamente.\n";

    std::cout << "Paciente: "
              << paciente->getNombre() << std::endl;

    std::cout << "La cama "
              << camaActual << " quedo disponible.\n";
}

// BUSCAR PACIENTE POR CEDULA EN LA TABLA HASH
void Simulador::buscarPaciente() {

    std::string cedula;

    std::cout << "\n========== BUSQUEDA DE PACIENTE ==========\n";

    std::cout << "Ingrese la cedula del paciente: ";
    std::getline(std::cin >> std::ws, cedula);

    std::shared_ptr<Paciente> paciente = historial.buscar(cedula);

    if (paciente == nullptr) {
        std::cout << "\nNo se encontro ningun paciente con esa cedula.\n";
        return;
    }

    std::cout << "\nPaciente encontrado correctamente.\n";

    paciente->mostrarInformacion();
}

// MOSTRAR ESTADO DEL SIMULADOR
void Simulador::mostrarEstado() {

    std::cout << "\n====================================\n";
    std::cout << "       SIMULADOR DE URGENCIAS\n";
    std::cout << "====================================\n";

    std::cout << "\nMedico actual: ";

    if (medicoActual != nullptr) {
        std::cout << medicoActual->getNombre();
    }

    std::cout << "\nTurno actual: " << turnoActual;
    std::cout << "\nCama actual del medico: " << camaActual;

    std::cout << "\n\n--- ESTADO DE LAS CAMAS ---\n";
    camas.mostrarAdelante();

    std::cout << "\n--- COLA DE PRIORIDAD ---\n";
    colaPrioridad.mostrarCola();

    std::cout << "\n--- RESUMEN ---\n";

    std::cout << "Pacientes recibidos: "
              << pacientesRecibidos << std::endl;

    std::cout << "Pacientes dados de alta: "
              << pacientesDadosDeAlta << std::endl;

    std::cout << "Pacientes perdidos: "
              << pacientesPerdidos << std::endl;

    std::cout << "Camas disponibles: "
              << camas.contarDisponibles() << std::endl;

    std::cout << "\n====================================\n";
}

// MENU PRINCIPAL
void Simulador::iniciar() {

    int opcion;

    do {

        mostrarEstado();

        std::cout << "\n1. Registrar paciente en Triage";
        std::cout << "\n2. Actualizar estado";
        std::cout << "\n3. Recibir paciente (R)";
        std::cout << "\n4. Mover izquierda (A)";
        std::cout << "\n5. Mover derecha (D)";
        std::cout << "\n6. Tratar paciente (T)";
        std::cout << "\n7. Dar alta al paciente (X)";
        std::cout << "\n8. Mostrar pacientes dados de alta (U)";
        std::cout << "\n9. Buscar paciente por cedula (C)";
        std::cout << "\n0. Salir";

        std::cout << "\nSelecciona una opcion: ";

        if (!(std::cin >> opcion)) {

            std::cout << "\nEntrada no valida.\n";

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            continue;
        }

        switch (opcion) {

            case 1:
                registrarPaciente();
                break;

            case 2:
                std::cout << "\nEstado actualizado.\n";
                break;

            case 3:
                recibirPaciente();
                break;

            case 4:
                moverIzquierda();
                break;

            case 5:
                moverDerecha();
                break;

            case 6:
                tratarPaciente();
                break;

            case 7:
                darAltaPaciente();
                break;

            case 8:
                std::cout << "\n========== PILA DE PACIENTES DADOS DE ALTA ==========\n";
                pilaAtendidos.mostrarPila();
                break;

            case 9:
                buscarPaciente();
                break;

            case 0:
                std::cout << "\nSimulador cerrado.\n";
                break;

            default:
                std::cout << "\nOpcion no valida.\n";
        }

    } while (opcion != 0);
}
