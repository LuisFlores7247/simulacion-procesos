#include <iostream>
#include "Proceso.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Lista *l = new Lista();
    for (int i = 1; i <= 10; i++)
    {
        l->insertaFinal(i);
    }
    l->imprimir();

    delete l;
    return 0;
}
