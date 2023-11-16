#include "Lista.h"

// Constructor de la clase Lista
Lista::Lista()
{
    inicio = fin = NULL; // Inicializa los apuntadores
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
        buddySystem(aux); // Si no, se aplica el algoritmo de Buddy System
        fin->liga = aux;  // Si no, el nuevo nodo se liga al final de la lista
        fin = aux;        // El nuevo nodo es el fin de la lista
    }

    return aux->tamanio;
}

void Lista::buddySystem(Proceso *_proceso)
{
    Proceso *aux = inicio;

    while (aux != NULL && aux->tamanio >= 64)
    {
        if (aux->tamanio >= (_proceso->tamanio * 2))
        {
            this->nuevoProceso(0, aux->tamanio / 2, 0);
            aux->tamanio /= 2;
        }
        aux = aux->liga;
    }
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