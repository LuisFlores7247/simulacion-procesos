#include <iostream>

using namespace std;

class Proceso
{
private:
    int id;
    double tamanio;
    int cuanto;

public:
    Proceso();
    Proceso(int, double, int);
    ~Proceso();
    void setId(int);
    void setTamanio(double);
    void setCuanto(int);
    int getId();
    double getTamanio();
    int getCuanto();
    void mostrar();
};