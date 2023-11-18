#ifndef PROCESO_H
#define PROCESO_H


enum STATUS
{
    HUECO = 0,
    EJECUCION,
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
    Proceso *llenarProceso(int, int, int);

    //Imprimir datos de un proceso
    friend void imprimirProceso(Proceso *p);

};

#endif