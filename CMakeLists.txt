cmake_minimum_required(VERSION 3.27)
project(patient-records-manager C)

set(CMAKE_C_STANDARD 17)

add_executable(patient-records main.c
        Doente.c
        Doente.h
        Registo.c
        Registo.h
        ListaDoentes.c
        ListaDoentes.h
        Data.c
        Data.h
        ListaRegistos.h
        ListaRegistos.c
)
