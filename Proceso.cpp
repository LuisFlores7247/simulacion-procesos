#include "Proceso.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

// Listas
Lista::Lista()
{
    inicio = fin = nullptr; // Usar nullptr en lugar de NULL
}

// Constructor de la clase Proceso
Lista::Proceso::Proceso(int _id, int _tamanio, int _cuanto)
{
    id = _id;
    tamanio = _tamanio;
    cuanto = _cuanto;
    mem_asignada = 0; // Inicializar mem_asignada
}

int Lista::nuevoProceso(int _id, int _tamanio, int _cuanto)
{
    Proceso *aux = new Proceso(_id, _tamanio, _cuanto);
    if (inicio == nullptr)
    {
        inicio = aux;
    }
    else
    {
        fin->liga = aux;
    }

    fin = aux;
    if (inicio->tamanio != _tamanio)
    {
        aux->mem_asignada = asignarMemoria(_tamanio);
    }

    return aux->tamanio;
}

int Lista::asignarMemoria(int _tamanio)
{
    int tam_actual = inicio->tamanio, tam_asignar;
    while (inicio->tamanio > (_tamanio * 2))
    {
        inicio->tamanio /= 2;
    }
    tam_asignar = inicio->tamanio;
    inicio->tamanio = tam_actual - tam_asignar;
    return tam_asignar;
}

void Lista::imprimir()
{
    cout << endl;
    if (inicio == nullptr)
    {
        cout << "Lista Vacia..." << endl;
    }
    else
    {
        Proceso *aux = inicio;
        while (aux != NULL)
        {
            cout << "[" << aux->id << "," << aux->tamanio << "," << aux->cuanto << "," << aux->mem_asignada << "]";
            aux = aux->liga;
        }
    }
    cout << endl;
}

// Resto del código para los procesos
