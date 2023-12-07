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
enum VELOCIDAD
{
    VELOCIDAD_1 = 5000,
    VELOCIDAD_2 = 1000,
    VELOCIDAD_3 = 0
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
    void setVelocidad(VELOCIDAD);

    // Getters
    Proceso *getInicio();
    Proceso *getFin();
    Proceso *getInicioRR();
    Proceso *getFinRR();
    VELOCIDAD getVelocidad();

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

    //Destructor de la clase lista
    ~Lista();

private:
    Proceso *inicio;
    Proceso *fin;
    Proceso *inicioRR;
    Proceso *finRR;
    VELOCIDAD vel;
};

#endif