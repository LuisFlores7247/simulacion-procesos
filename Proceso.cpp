#include "Proceso.h"
#include <iostream>

using namespace std;

// Constructor de la clase Proceso
Proceso::Proceso(int _id, int _tamanio, int _cuanto, double _tServicio)
    : id(_id), tamanio(_tamanio), cuanto(_cuanto), mem_asignada(0), tiempo_Servicio(_tServicio), tiempo_Estancia(0),  izq(NULL), der(NULL), liga(NULL)
{   
    
    (_id == 0 && _cuanto == 0) ? status = HUECO : status = ENESPERA;
}

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

void  Proceso::setEstancia(double _estancia){
    tiempo_Estancia = _estancia;
}


void Proceso::setServicio(double _servicio){
    tiempo_Servicio = _servicio;
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
double Proceso::getServicio(){
    return tiempo_Servicio;
}
double Proceso::getEstancia(){
    return tiempo_Estancia;
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
        this->status = _proceso.status;
        this->tiempo_Estancia= _proceso.tiempo_Estancia;
        this->tiempo_Servicio=_proceso.tiempo_Servicio;
    }
    return *this;
}

// Resto del código para los procesos

string imprimirProceso(Proceso *p)
{
    string aux = "[" + to_string(p->id) + "," + to_string(p->tamanio) + "," + to_string(p->cuanto) + "]";
    return aux;
}

string imprimirProceso(Proceso *p, int minus)
{
    int n = p->cuanto;
    (n - minus < 0) ? n = 0 : n -=minus;
    string aux = "[" + to_string(p->id) + "," + to_string(p->tamanio) + "," + to_string(n) + "]";
    return aux;

}
void descargarProceso(Proceso *p)
{
    p->id=0;
    p->tamanio=p->mem_asignada;
    p->cuanto=0;
    p->status=HUECO;
}