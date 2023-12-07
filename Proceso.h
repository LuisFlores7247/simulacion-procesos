#ifndef PROCESO_H
#define PROCESO_H
#include <string>
#include <cctype>
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
    double tiempo_Servicio;
    double tiempo_Estancia;
    STATUS status;
    Proceso *izq;
    Proceso *der;
    Proceso *liga;
    Proceso(int = 0, int = 0, int = 0, double=0);

    // setters
    void setId(int);
    void setTamanio(int);
    void setCuanto(int);
    void setMem_asignada(int);
    void setServicio(double);
    void setEstancia(double);

    // getters
    int getId();
    int getTamanio();
    int getCuanto();
    int getMem_asignada();
    double getServicio();
    double getEstancia();
    // Sobrecarga de operadores
    Proceso &operator=(const Proceso &);

    // Imprimir datos de un proceso
    friend string imprimirProceso(Proceso *);
    friend string imprimirProceso(Proceso *, int);

    //Descargar proceso 
    friend void descargarProceso(Proceso *); 

    // Round Robin
};

#endif