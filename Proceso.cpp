#include "Proceso.h"
#include <ctime>
#include <cstdlib>

// Listas
Lista::Lista()
{
    inicio = fin = NULL;
}

Lista::Proceso::Proceso(int _id, int _tamanio, int _cuanto)
{
    id = _id;
    tamanio = _tamanio;
    cuanto = _cuanto;
}

int Lista::nuevoProceso(int _id, int _tamanio, int _cuanto)
{
    Proceso *aux = new Proceso(_id, _tamanio, _cuanto);
    if (inicio == NULL)
        inicio = aux;
    else
        fin->liga = aux;

    fin = aux;
    if (inicio->tamanio != _tamanio)
    {
        restarMemoria(_tamanio);
    }

    return aux->tamanio;
}
void Lista::restarMemoria(int _tamanio)
{
    cout << inicio->tamanio << " - " << _tamanio << endl;
    inicio->tamanio -= _tamanio;
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
        while (aux != nullptr)
        {
            cout << "[" << aux->id << "," << aux->tamanio << "," << aux->cuanto << "]";
            aux = aux->liga;
        }
    }
    cout << endl;
}

// Procesos
