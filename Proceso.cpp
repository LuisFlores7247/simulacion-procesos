#include "Proceso.h"

// Constructor de la clase Proceso
Proceso::Proceso(int _id, int _tamanio, int _cuanto)
    : id(_id), tamanio(_tamanio), cuanto(_cuanto), mem_asignada(0), status(HUECO), liga(NULL) {}

// Setters

void Proceso::setId(int _id)
{
    id = _id;
}

void Proceso::setTamanio(int _tamanio)
{
    tamanio = _tamanio;
}

void Proceso::setCuanto(int _cuanto)
{
    cuanto = _cuanto;
}

void Proceso::setMem_asignada(int _mem_asignada)
{
    mem_asignada = _mem_asignada;
}

// Getters

int Proceso::getId()
{
    return id;
}

int Proceso::getTamanio()
{
    return tamanio;
}

int Proceso::getCuanto()
{
    return cuanto;
}

int Proceso::getMem_asignada()
{
    return mem_asignada;
}

// Sobrecarga de operadores
Proceso &Proceso::operator=(const Proceso &_proceso)
{
    if (this != &_proceso)
    {
        this->id = _proceso.id;
        this->tamanio = _proceso.tamanio;
        this->cuanto = _proceso.cuanto;
        this->mem_asignada = _proceso.mem_asignada;
        this->liga = _proceso.liga;
    }
    return *this;
}

// Resto del código para los procesos
