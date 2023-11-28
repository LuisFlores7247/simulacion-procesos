#include "Funciones.h"

using namespace std;

int main()
{
    srand(time(NULL));

    system("cls");

    iniciarSimulacion();

    return 0;
}

// Estructura aproximada del main como tal
/*
int main(int argc, char const *argv[])
{
    //Bienvenida

    //Preguntar cuando se este listo para iniciar la simulacion
    //Setear las variables Parametrizables
    //Empezar el ciclo principal, seria un while true o algo parecido para que salga en cuanto el usuario de esq
    //Ver si hay un proceso en espera y si hay lugar en la memoria principal para alojarla, en caso de que si, acomodar el proceso en memoria
    //Generar un nuevo proceso a menos que exista otro proceso en espera
    //Si se crea un nuevo proceso, verificar si puede entrar a memoria principal, en caso de que si, hacer las particiones de Buddy system
    //Meter el proceso en memoria principal
    //El planificador selecciona el proceso a ejecutar
    //Se le da su tiempo a ejecucion, se restan los cuantos de procesamiento que se le dan
    //Si en este turno de ejecucion, se le acaba el tiempo de procesamiento al proceso, se baja de memoria, quedando un hueco
    //Si no acabo de ejecutarse, Round Robin lo manda hasta el ultimo lugar de la cola
    //Si se libero la memoria, el buddy sistem evalua si hay huecos adyacentes y los une
    //Se actualiza el modulo de estadisticas
    //Dependiendo de la velocidad de la simulacion, se imprimen los valores que se deben de imprimir
    //La simulacion evalua si se presiono esq o se cambio la velocidad de impresion de datos, en ese caso, se hacen las acciones correspondientes
    return 0;
}
*/