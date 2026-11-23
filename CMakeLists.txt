
cmake_minimum_required(VERSION 3.20)

project(SimuladorUrgencias)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SimuladorUrgencias
        main.cpp
        src/Paciente.cpp
        src/Medico.cpp
        src/Cama.cpp
        src/ListaCamas.cpp
)

target_include_directories(SimuladorUrgencias PRIVATE
        include
)
