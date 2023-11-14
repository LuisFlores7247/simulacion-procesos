#include <iostream>

using namespace std;

class Lista
{
public:
    class Proceso
    {
    public:
        int id;
        int tamanio;
        int cuanto;
        Proceso *liga;
        Proceso(int = 0, int = 0, int = 0);
    };
    Lista();
    int nuevoProceso(int, int, int);
    void restarMemoria(int);
    void imprimir();

private:
    Proceso *inicio;
    Proceso *fin;
};