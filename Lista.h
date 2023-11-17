#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "Proceso.cpp"

using namespace std;

enum TAM_MEMORIA
{
    TAM_1Mb = 1024,
    TAM_4Mb = 4096,
    TAM_8Mb = 8192
};

class Lista
{
public:
    Lista();
    int nuevoProceso(int, int, int);
    void particionar(Proceso *);
    void imprimir();

private:
    Proceso *inicio;
    Proceso *fin;
};

#endif