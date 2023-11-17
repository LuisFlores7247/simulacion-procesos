#include <iostream>
#include "Lista.h"

// Constructor de la clase Lista
Lista::Lista()
{
    inicio = fin = NULL; // Inicializa los apuntadores
    inicioRR = finRR = NULL;
}

// Setters

void Lista::setInicio(Proceso *_inicio)
{
    inicio->der = _inicio;
}

void Lista::setFin(Proceso *_fin)
{
    fin = _fin;
}

void Lista::setInicioRR(Proceso *_inicioRR)
{
    inicioRR = _inicioRR;
}
void Lista::setFinRR(Proceso *_finRR)
{
    finRR = _finRR;
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

Proceso *Lista::getInicioRR()
{
    return inicioRR;
}
Proceso *Lista::getFinRR()
{
    return finRR;
}

// Metodos de la clase Lista
int Lista::nuevoProceso(int _id, int _tamanio, int _cuanto)
{
    Proceso *aux = new Proceso(_id, _tamanio, _cuanto); // Crea un nuevo nodo
    if (inicio == NULL)
    {
        fin = aux;
    }
    else
    {
        aux->der = inicio;
        aux->izq = NULL;
        inicio->izq = aux;
    }

    inicio = aux;
    //Parte de Round Robin
    if (aux->id != 0)   //Si es cero quiere decir que se creo un hueco y no es relevante para el Round Robin
    {
        if (inicioRR == NULL)   //Si es el primer proceso a entrar, fija el inicio de la lista
            inicioRR = aux;
        finRR->liga = aux;
        finRR = aux;        
    }
    
    return aux->tamanio;
}

void Lista::particionar(Proceso *_proceso)
{
    Proceso *aux = inicio, *pos;

    while (aux != NULL)
    {
        if (aux->status == HUECO && aux->tamanio >= (_proceso->tamanio * 2) && aux->tamanio > 32)
        {
            this->nuevoProceso(0, aux->tamanio / 2, 0);
            aux->tamanio /= 2;
        }
        aux = aux->izq;
    }
}

Proceso Lista::hayEspacio(Proceso *_proceso)
{
    Proceso *aux = inicio;
    Proceso p;
    while (aux != NULL)
    {
        if (aux->status == HUECO && (aux->tamanio / 2))
        {
            p = *aux;
            return p;
        }
        aux = aux->der;
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
            aux->status == HUECO ? cout << "[" << aux->id << "," << aux->tamanio << "," << aux->cuanto << "]"
                                 : cout << "[" << aux->id << "," << aux->tamanio << "(" << aux->mem_asignada << ")," << aux->cuanto << "]";

            aux = aux->der;
        }
    }
    cout << endl;
}