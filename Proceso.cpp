#include "Proceso.h"

Proceso::Proceso()
{
    id = 0;
    tamanio = 0;
    cuanto = 0;
}

Proceso::Proceso(int _id, double _tamanio, int _cuanto)
{
    this->id = _id;
    this->tamanio = _tamanio;
    this->cuanto = _cuanto;
}
