#include "Lista.h"

// Constructor de la clase Lista
Lista::Lista()
{
    inicio = fin = NULL; // Inicializa los apuntadores
}

// Setters

void Lista::setInicio(Proceso *_inicio)
{
    inicio = _inicio;
}

void Lista::setFin(Proceso *_fin)
{
    fin = _fin;
}

// Getters

Proceso *Lista::getInicio()
{
    return inicio;
}

Proceso *Lista::getFin()
{
    return fin;
}

// Metodos de la clase Lista
int Lista::nuevoProceso(int _id, int _tamanio, int _cuanto)
{
    Proceso *aux = new Proceso(_id, _tamanio, _cuanto); // Crea un nuevo nodo
    if (inicio == NULL)
    {
        inicio = fin = aux; // Si la lista está vacía, el nuevo nodo es el inicio y el fin
    }
    else
    {
        fin->liga = aux; // Si no, el nuevo nodo se liga al final de la lista
        fin = aux;       // El nuevo nodo es el fin de la lista
    }

    return aux->tamanio;
}

void Lista::particionar(Proceso *_proceso)
{
    Proceso *aux = inicio, *pos;

    while (aux != NULL)
    {
        if (aux->status == HUECO && aux->tamanio >= (_proceso->tamanio * 2))
        {
            this->nuevoProceso(0, aux->tamanio / 2, 0);
            aux->tamanio /= 2;
        }
        aux = aux->liga;
    }
}

bool Lista::hayEspacio(Proceso *_proceso, Proceso *_pos)
{
    Proceso *aux = inicio;
    while (aux != NULL)
    {
        if (aux->status == HUECO && (aux->liga->tamanio <= _proceso->tamanio && aux->liga->status == HUECO))
        {
            _pos = aux;
            return true;
        }
        if ((aux->status == HUECO && aux->tamanio >= _proceso->tamanio) && (aux->tamanio < _pos->tamanio))
        {
            _pos = aux;
        }
        aux = aux->liga;
    }
    return false;
}

void Lista::imprimir()
{
    cout << endl;
    if (inicio == NULL)
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