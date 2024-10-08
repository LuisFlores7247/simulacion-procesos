#include <iostream>
#include "Lista.h"
#include "colores.h"
#include <iomanip>
#include <cstdlib>
#include <math.h>

using namespace std;

// Constructor de la clase Lista
Lista::Lista(int _TrTs, int _cont)
{
    this->TrTs = _TrTs;
    this->cont = _cont;
    inicio = fin = NULL; // Inicializa los apuntadores
    inicioRR = finRR = NULL;
    vel = VELOCIDAD_1; // Inicializa la velocidad de la simulacion como 1, es decir la mas lenta
}

// Setters

void Lista::setInicio(Proceso *_inicio) { inicio->der = _inicio; }
void Lista::setFin(Proceso *_fin) { fin = _fin; }
void Lista::setInicioRR(Proceso *_inicioRR) { inicioRR = _inicioRR; }
void Lista::setFinRR(Proceso *_finRR) { finRR = _finRR; }
void Lista::setTrTs(int _TrTs) { TrTs = _TrTs; }
void Lista::setCont(int _cont) { cont = _cont; }
void Lista::setVelocidad(VELOCIDAD _vel) { vel = _vel; }

// Getters

Proceso *Lista::getInicio() { return inicio; }
Proceso *Lista::getFin() { return fin; }
Proceso *Lista::getInicioRR() { return inicioRR; }
Proceso *Lista::getFinRR() { return finRR; }
int Lista::getTsTr() { return TrTs; }
int Lista::getCont() { return cont; }
VELOCIDAD Lista::getVelocidad() { return vel; }

// Metodos de la clase Lista

void gotoxy(int x, int y);
int contarDigitos(int);

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
double Lista::porcentajeMem(const int tamRam)
{
    double suma = 0;
    if (inicio != NULL)
    {
        Proceso *aux = inicio;
        while (aux != NULL)
        {
            if (aux->status == ENMEMORIA)
                suma += aux->mem_asignada;
            aux = aux->der;
        }
    }
    return suma / tamRam;
}

void Lista::imprimir(int consoleWidth)
{
    int leftPadding;
    if (inicio == NULL)
    {
        leftPadding = (consoleWidth - 14) / 2;
        gotoxy(leftPadding, 10);
        cout << "Lista Vacia..." << endl;
    }
    else
    {
        Proceso *aux = inicio;
        string line = "";
        int i = 0;

        while (aux != NULL)
        {
            aux->status == HUECO ? cout << "[" << aux->id << "," << aux->tamanio << "," << aux->cuanto << "]"
                                 : cout << "[" << aux->id << "," << aux->tamanio << "(" << (aux->mem_asignada) << ")," << (aux->cuanto) << "]";
            aux = aux->der;
        }
    }
}

// Metodos para el correcto funcionamiento de Round Robin

void Lista::ejecucion(const int cuanMax, int consoleWidth)
{
    // Funcion que ejecuta el proceso colocado en el inicio de la lista de RR, asi como acomodandola dependiendo de como quede el proceso despues de su ejecucion
    Proceso *q, *t = inicioRR;

    if (inicioRR != NULL)
    {
        if (vel != VELOCIDAD_3)
        {
            cout << endl;
            cout << NEGRITA << VERDE << "El proceso " << imprimirProceso(inicioRR) << " esta siendo ejecutado en el procesador... " << endl;

            cout << "El proceso " << imprimirProceso(inicioRR, cuanMax) << " ha salido del procesador" << endl;
        }
        if (t->cuanto < cuanMax)
        {
            t->tiempo_Estancia = t->tiempo_Estancia + t->cuanto;
            t = t->liga;
        }
        while (t != NULL)
        {

            t->tiempo_Estancia = t->tiempo_Estancia + cuanMax;
            t = t->liga;
        }

        if (inicioRR->cuanto - cuanMax <= 0)
        {
            TrTs = TrTs + (inicioRR->tiempo_Estancia / inicioRR->tiempo_Servicio);
            inicioRR->cuanto = 0;
            if (vel != VELOCIDAD_3)
            {
                cout << endl;

                cout << MAGENTA << "El proceso termino su ejecucion !!!, descargando de memoria..." << endl;

                cout << MAGENTA << "Tiempo de Estancia/Servicio: " << setprecision(2) << fixed << inicioRR->tiempo_Estancia / inicioRR->tiempo_Servicio << " cuantos.." << RESET << RESET << endl
                     << endl;
            }

            q = inicioRR;
            inicioRR = inicioRR->liga;
            cont++;
            descargarProceso(q);
            this->juntarMemoria(consoleWidth);
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
        int i = 0;
        while (aux != NULL)
        {
            cout << imprimirProceso(aux);
            if (i == 10)
            {
                cout << endl;
                i = 0;
            }

            aux = aux->liga;
        }
    }
}

void Lista::juntarMemoria(int consoleWidth)
{
    // Funcion que recorre la lista de procesos y junta los huecos que se encuentren
    Proceso *aux = inicio;
    Proceso *q = NULL;

    int tamAux;
    int tamAuxDer;

    while (aux->der != NULL)
    {

        if (aux->status != HUECO)
        {
            tamAux = aux->mem_asignada;
        }
        else
        {
            tamAux = aux->tamanio;
        }

        if (aux->der->status != HUECO)
        {
            tamAuxDer = aux->der->mem_asignada;
        }
        else
        {
            tamAuxDer = aux->der->tamanio;
        }

        if (tamAuxDer < tamAux)
        {
            aux = aux->der;
        }
        else
        {
            if (aux->status == HUECO && aux->der->status == HUECO && tamAux == tamAuxDer)
            {
                aux->tamanio += aux->der->tamanio;
                q = aux->der;

                if (aux->der->der == NULL)
                {
                    aux->der = NULL;
                    fin = aux;

                    return;
                }
                else
                {
                    aux->der->der->izq = aux;
                    aux->der = aux->der->der;
                }

                delete (q);
                if (vel != VELOCIDAD_3)
                {
                    cout << endl
                         << endl;
                    cout << ROJO << "Uniendo buddys" << endl;
                    this->imprimir(consoleWidth);
                    cout << endl;
                }
            }

            else
            {
                if (aux->der->der == NULL)
                {
                    return;
                }
                else
                {
                    aux = aux->der->der;
                }
            }
        }
    }
}

void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
Lista::~Lista()
{
    Proceso *p = inicio, *q = inicio;
    while (p != NULL)
    {
        p = q->der;
        delete q;
        q = p;
    }
}

int contarDigitos(int numero)
{
    if (numero == 0)
    {
        return 1;
    }

    int digitos = static_cast<int>(std::log10(std::abs(numero))) + 1;

    return digitos;
}