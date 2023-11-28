#ifndef LISTA_H
#define LISTA_H

#include "Proceso.cpp"



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
    STATUS asignMemoria(Proceso *);
    Proceso hayEspacio(Proceso *);

    void agregarAlistaRR(Proceso*);


    // Metodos para imprimir
    void imprimir();
    void imprimir_ListaListos();

    //Round Robin
    void ejecucion(const int);
    void descargandoProceso();

private:
    Proceso *inicio;
    Proceso *fin;
    Proceso *inicioRR;
    Proceso *finRR;
};

#endif