#ifndef PROCESO_H
#define PROCESO_H
#include <string>
using namespace std;

enum STATUS
{
    HUECO = 0,
    ENMEMORIA,
    EJECUCION,
    ENESPERA,
};

class Proceso
{
public:
    int id;
    int tamanio;
    int cuanto;
    int mem_asignada;
    STATUS status;
    Proceso *izq;
    Proceso *der;
    Proceso *liga;
    Proceso(int = 0, int = 0, int = 0);

    // setters
    void setId(int);
    void setTamanio(int);
    void setCuanto(int);
    void setMem_asignada(int);

    // getters
    int getId();
    int getTamanio();
    int getCuanto();
    int getMem_asignada();

    // Sobrecarga de operadores
    Proceso &operator=(const Proceso &);

    //Llenar proceso aleatoriamente
    friend Proceso *llenarProceso(int, int, int);

    //Imprimir datos de un proceso
    friend string imprimirProceso(Proceso *p);

    //Round Robin

    
};

#endif