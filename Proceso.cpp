#include "Proceso.h"
#include <ctime>
#include <cstdlib>

Lista::Lista()
{
    inicio = fin = NULL;
}

Lista::Proceso::Proceso(int indice)
{
    id = indice;
    tamanio = rand() % 100 + 1;
    cuanto = rand() % 10 + 1;
}

void Lista::insertaFinal(int indice)
{
    Proceso *aux = new Proceso(indice);
    if (inicio == NULL)
        inicio = aux;
    else
        fin->liga = aux;

    fin = aux;
}

void Lista::imprimir()
{
    cout << endl;
    if (inicio == NULL)
        cout << endl
             << "Lista Vacia...";
    else
    {
        Proceso *aux = inicio;
        while (aux->liga != NULL)
        {
            cout << "[" << aux->id << "," << aux->tamanio << "," << aux->cuanto << "]";
            aux = aux->liga;
            cout << endl;
        }
    }
    cout << endl;
}