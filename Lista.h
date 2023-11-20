#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "Proceso.cpp"

using namespace std;

class Lista
{
public:
    Lista();

    // Setters
    void setInicio(Proceso *);
    void setFin(Proceso *);
    void setInicioRR(Proceso *);
    void setFinRR(Proceso *);

    // Getters
    Proceso *getInicio();
    Proceso *getFin();
    Proceso *getInicioRR();
    Proceso *getFinRR();

    // Metodos de la clase Lista
    void nuevoProceso(Proceso *);
    void particionar(Proceso *);
    Proceso *asignMemoria(Proceso *);
    Proceso hayEspacio(Proceso *);

    // Metodos para imprimir
    void imprimir();
    void imprimir_ListaListos();

private:
    Proceso *inicio;
    Proceso *fin;
    Proceso *inicioRR;
    Proceso *finRR;
};

#endif