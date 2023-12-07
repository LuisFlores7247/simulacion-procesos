#ifndef LISTA_H
#define LISTA_H

#include "Proceso.cpp"

enum TAM_MEMORIA
{
    TAM_1Mb = 1024,
    TAM_4Mb = 4096,
    TAM_8Mb = 8192
};
// Enum CPUS no necesario por el momento

class Lista
{
public:
    int TrTs;
    int cont;
    Lista(int=0, int=0);

    // Setters
    void setInicio(Proceso *);
    void setFin(Proceso *);
    void setInicioRR(Proceso *);
    void setFinRR(Proceso *);
    void setTrTs(int);
    void setCont(int);
    
    // Getters
    Proceso *getInicio();
    Proceso *getFin();
    Proceso *getInicioRR();
    Proceso *getFinRR();
    int getTsTr();
    int getCont();

    // Metodos de la clase Lista
    void nuevoProceso(Proceso *);
    STATUS asignMemoria(Proceso *);
    void juntarMemoria();
    void agregarAlistaRR(Proceso *);
    //Metodos para estadisticas
    double porcentajeMem(const int);

    // Metodos para imprimir
    void imprimir();
    void imprimir_ListaListos();

    // Round Robin
    void ejecucion(const int);
    // void descargandoProceso(); que esta funcion mandes el proceso a descargar como parametro de preferencia

private:
    Proceso *inicio;
    Proceso *fin;
    Proceso *inicioRR;
    Proceso *finRR;
};

#endif