#include <iostream>

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
    class Proceso
    {
    public:
        int id;
        int tamanio;
        int cuanto;
        int mem_asignada;
        Proceso *liga;
        Proceso(int = 0, int = 0, int = 0);
    };
    Lista();
    int nuevoProceso(int, int, int);
    int asignarMemoria(int);
    void imprimir();

private:
    Proceso *inicio;
    Proceso *fin;
};