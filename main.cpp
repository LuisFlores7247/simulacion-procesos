#include <iostream>
#include "Proceso.cpp"
#include "ctime"
#include "cstdlib"

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int TAM_1Mb = 1024, TAM_4Mb = 4096, TAM_8Mb = 8192;
    int tamanio = 0, cuanto = 0, opc;
    Lista *l = new Lista();
    cout << "Ingrese el tamanio de la memoria: " << endl;
    cout << "1. 1Mb\n2. 4Mb\n3. 8Mb\n";
    cin >> opc;
    if (opc == 1)
        l->nuevoProceso(0, TAM_1Mb, 0);
    else if (opc == 2)
        l->nuevoProceso(0, TAM_4Mb, 0);
    else if (opc == 3)
        l->nuevoProceso(0, TAM_8Mb, 0);

    for (int i = 1; i <= 5; i++)
    {
        tamanio = rand() % 10 + 1;
        cuanto = rand() % 10 + 1;
        l->nuevoProceso(i, tamanio, cuanto);
    }
    l->imprimir();

    delete l;
    return 0;
}
