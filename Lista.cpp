#include <iostream>
#include "Lista.h"

using namespace std;

// Constructor de la clase Lista
Lista::Lista()
{
    inicio = fin = NULL; // Inicializa los apuntadores
    inicioRR = finRR = NULL;
}

// Setters

void Lista::setInicio(Proceso *_inicio) { inicio->der = _inicio; }
void Lista::setFin(Proceso *_fin) { fin = _fin; }
void Lista::setInicioRR(Proceso *_inicioRR) { inicioRR = _inicioRR; }
void Lista::setFinRR(Proceso *_finRR) { finRR = _finRR; }

// Getters

Proceso *Lista::getInicio() { return inicio; }
Proceso *Lista::getFin() { return fin; }
Proceso *Lista::getInicioRR() { return inicioRR; }
Proceso *Lista::getFinRR() { return finRR; }

// Metodos de la clase Lista

void Lista::nuevoProceso(Proceso *aux)
{
    // Crea nodo con el valor de la memoria RAM seleccionado para partir de este

    if (inicio == NULL)
    {
        aux->status = HUECO;
        inicio = fin = aux;
    }
}

STATUS Lista::asignMemoria(Proceso *_proceso)
{
    Proceso *aux = inicio;
    // Recorremos la lista en busca de espacio
    while (aux != NULL)
    {
        if (aux->status == HUECO && _proceso->tamanio <= aux->tamanio)
        {

            if (aux->tamanio >= (_proceso->tamanio * 2) && aux->tamanio > 32) // muy grande
            {
                // Particiona
                Proceso *p = new Proceso(0, aux->tamanio / 2, 0), *q = aux->izq;
                aux->tamanio /= 2;
                p->izq = q;
                p->der = aux;

                if (q != NULL)
                    q->der = p;
                else
                    inicio = p;
                aux->izq = p;
                aux = p;
            }
            else
            {
                if (aux->tamanio >= _proceso->tamanio) // Corrobora que el espacio no es muy pequenio
                {
                    // asigna el proceso a memora
                    _proceso->mem_asignada = aux->tamanio;
                    *aux = *_proceso;
                    aux->status = ENMEMORIA;
                    // Como el proceso esta en memoria, se incluye en la lista de Round Robin
                    this->agregarAlistaRR(aux);

                    return ENMEMORIA;
                }
            }
        }
        else
            aux = aux->der;
    }
    return ENESPERA;
}

void Lista::agregarAlistaRR(Proceso *aux)
{
    // Parte de Round Robin
    aux->liga = NULL;
    if (aux->id != 0) // Si es cero quiere decir que se creo un hueco y no es relevante para el Round Robin
    {
        if (inicioRR == NULL)
        {
            // Si es el primer proceso a entrar, fija el inicio de la lista
            inicioRR = aux;
        }
        else
        {
            finRR->liga = aux;
        }
        finRR = aux;
    }
}

void Lista::imprimir()
{
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
}

// Metodos para el correcto funcionamiento de Round Robin

void Lista::ejecucion(const int cuanMax)
{
    // Funcion que ejecuta el proceso colocado en el inicio de la lista de RR, asi como acomodandola dependiendo de como quede el proceso despues de su ejecucion
    Proceso *q;
    if (inicioRR != NULL)
    {
        cout << endl
             << "El proceso " << imprimirProceso(inicioRR) << " esta siendo ejecutado en el procesador: ";
        if (inicioRR->cuanto - cuanMax <= 0)
        {
            inicioRR->cuanto = 0;
            cout << endl
                 << "El proceso termino su ejecucion, descargando de memoria...";
            q = inicioRR;
            inicioRR = inicioRR->liga;
            // Poner aqui funcion que descargue el proceso de memoria y condense la memoria si es posible
            // descargarProceso(q);
        }
        else
        {
            inicioRR->cuanto -= cuanMax;
            finRR->liga = inicioRR;
            inicioRR = inicioRR->liga;
            finRR = finRR->liga;
            finRR->liga = NULL;
        }
    }
    else
    {
        cout << endl
             << "El procesador no contiene ningun proceso, no hay procesos necesarios a ejecutar";
    }
}

void Lista::imprimir_ListaListos()
{
    if (inicioRR == NULL)
    {
        cout << "Lista Vacia..." << endl;
    }
    else
    {
        Proceso *aux = inicioRR;
        while (aux != NULL)
        {
            cout << imprimirProceso(aux);
            aux = aux->liga;
        }
    }
}

void Lista::juntarMemoria()
{
    // Funcion que recorre la lista de procesos y junta los huecos que se encuentren
    Proceso *aux = inicio;
    while (aux != NULL)
    {
        if (aux->der->tamanio < aux->tamanio)
        {
            aux = aux->der;
        }
        else
        {
            if (aux->status == HUECO && aux->der->status == HUECO && aux->tamanio == aux->der->tamanio)
            {

                aux->tamanio += aux->der->tamanio;
                aux->der = aux->der->der;
                aux->der->izq = aux;
                aux = aux->der;
            }
            else
            {
                aux = aux->der->der;
            }
        }
    }
    this->imprimir();
}