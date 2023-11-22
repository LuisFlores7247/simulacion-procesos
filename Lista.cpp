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
void Lista::nuevoProceso(Proceso *aux)
{
    // Crea nodo con el valor de la memoria RAM seleccionado para partir de este

    if (inicio == NULL)
    {
        aux->status=HUECO;
        inicio=fin=aux;
    
    }


}

void Lista::particionar(Proceso *_proceso)
{
    Proceso *aux = inicio;

    while (aux != NULL)
    {
        if (aux->status == HUECO && aux->tamanio >= (_proceso->tamanio * 2) && aux->tamanio > 32)
        {
            //this->nuevoProceso(0, aux->tamanio / 2, 0);
            aux->tamanio /= 2;
        }
        aux = aux->izq;
    }    
}

STATUS Lista::asignMemoria(Proceso *_proceso)
{
    Proceso *aux = inicio;
    //Recorremos la lista en busca de espacio
    while (aux != NULL)
    {
        if (aux->status == HUECO && _proceso->tamanio<=aux->tamanio)
        {
            
            if (aux->tamanio >= (_proceso->tamanio * 2) && aux->tamanio > 32)    // muy grande
            {   
                //Particiona
                Proceso *p = new Proceso(0,aux->tamanio/2,0), *q = aux->izq;
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
                if (aux->tamanio >= _proceso->tamanio)   // Corrobora que el espacio no es muy pequenio
                {
                    //asigna el proceso a memora
                    _proceso->mem_asignada = aux->tamanio;
                    *aux = *_proceso;
                    aux->status = ENMEMORIA;
                    //Como el proceso esta en memoria, se incluye en la lista de Round Robin
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

void Lista::agregarAlistaRR(Proceso* aux)
{
    //Parte de Round Robin
    aux->liga = nullptr;
    if (aux->id != 0)   //Si es cero quiere decir que se creo un hueco y no es relevante para el Round Robin
    {
        if (inicioRR == NULL){
        //Si es el primer proceso a entrar, fija el inicio de la lista
            inicioRR= aux;
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

//Metodos para el correcto funcionamiento de Round Robin


void Lista::ejecucion(const NUM_CPUS aux, const int cuanMax)
{
    //Funcion que, dependiendo de la cantidad de procesadores que se establecieron, se ejecutan x cantidad de procesos restando los cuantos del sistema a los 
    //cuantos necesarios para su ejecucion
    Proceso *q = inicioRR;
    int n;
    for (int i = 0; i < aux; i++)
    {
        if (q != NULL)
        {
            (q->cuanto - cuanMax < 0) ? n = 0 : n = q->cuanto - cuanMax;
            
        }
        else
        {
            cout << endl << "El procesador " << i+1 << "No contiene ningun proceso, no hay procesos necesarios a ejecutar";
        }
    }
    
}

void Lista::imprimir_ListaListos()
{
    cout << endl;
    if (inicioRR == NULL)
    {
        cout << "Lista Vacia..." << endl;
    }
    else
    {
        Proceso *aux = inicioRR;
        while (aux != NULL)
        {
            imprimirProceso(aux);
            aux=aux->liga;
    
        }
    }
    cout << endl;
}
