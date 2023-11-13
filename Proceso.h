#include <iostream>

using namespace std;

class Lista
{
public:
    class Proceso
    {
    public:
        int id;
        double tamanio;
        int cuanto;
        Proceso *liga;
        Proceso(int = 0);
    };
    Lista();
    void insertaFinal(int);
    void imprimir();

private:
    Proceso *inicio;
    Proceso *fin;
};