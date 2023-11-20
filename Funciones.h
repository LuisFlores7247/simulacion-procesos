#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include "Lista.cpp"

enum TAM_MEMORIA
{
    TAM_1Mb = 1024,
    TAM_4Mb = 4096,
    TAM_8Mb = 8192
};

void iniciar();

void simulacion(Proceso *, Lista *, int, int);

int pedirTamMemoria();
int pedirTamMax(int);
int pedirCuanMax();

int crearMemoria(int, Lista *);

void iniciar()
{
    Lista *l = new Lista();

    Proceso *p = NULL;

    int opc = 0;

    int ram = crearMemoria(pedirTamMemoria(), l);
    int tamMax = pedirTamMax(ram);
    int cuanMax = pedirCuanMax();

    simulacion(p, l, tamMax, cuanMax);
}

void simulacion(Proceso *p, Lista *l, int tamMax, int cuanMax)
{
    /* Repite un ciclo desde 1 hasta el total de procesos. Llena el proceso con datos
   aleatorios, luego introduce el proceso a la lista de listos, como paso siguiente
   imprime el proceso generado y realiza la asignacion en memoria, la cual retorna un
  apuntador a un objeto del tipo proceso; si el proceso en su atributo status
  tiene almacenado un "ENMEMORIA", se procede a imprimir la lista actualizada con
  el nuevo proceso, sino, (el status del proceso es en espera) se indica que el
  proceso no pudo entrar a memoria y se continua la ejecucion de la simulacion,
  manteniendo el proceso en espera sin generar uno nuevo, hasta que hay algun
  lugar disonible*/
    for (int i = 1; i <= 5; i++)
    {

        p = llenarProceso(i, tamMax, cuanMax);

    proceso_en_espera:
        cout << endl
             << "Proceso " << i << ":   ";
        imprimirProceso(p);
        p = l->asignMemoria(p);
        if (p->status == ENMEMORIA)
        {
            cout << endl;
            l->nuevoProceso(p);
            l->imprimir();
        }
        else
        {
            cout << endl
                 << "En espera, espacio no disponible...";
            cout << endl;
            system("pause");

            /*Salta al instante despues de crear el proceso aleatorio para
            no crear uno nuevo y mantener el mismo hasta que se asigne a memoria*/
            goto proceso_en_espera;
        }
    }

    cout << endl
         << endl
         << "Lista de listos..." << endl;
    l->imprimir_ListaListos();
}

int pedirTamMemoria()
{
    int opc;
    cout << "Tamanios de memoria disponibles: " << endl;
    cout << "1. 1Mb\n2. 4Mb\n3. 8Mb\n";
    cout << endl
         << "TU opcion: ";
    cin >> opc;
    return opc;
}

int pedirTamMax(int ram)
{
    // Vuelve a pedir el dato mientras el tamaño maximo sea mas de la mitad de la memoria ram
    int tamMax;
    do
    {

        cout << endl
             << "Ingresa el tamanio maximo asignado a un proceso: ";
        cin >> tamMax;

        if (tamMax > ram / 2)
        {
            cout << "Opcio invalida. Introduce un valor menor";
        }

    } while (tamMax > ram / 2);
    return tamMax;
}
int pedirCuanMax()
{
    int cuanMax;
    cout << "Ingresa el maximo de cuantos de un proceso: ";
    cin >> cuanMax;
    return cuanMax;
}

int crearMemoria(int opc, Lista *l)
{
    TAM_MEMORIA ram;
    /* Crea un proceso inicial el cual tiene como tarea almacenar el valor de
la memoria RAM para luego en base a este generar las particiones de memoria*/
    if (opc == 1)
    {
        l->nuevoProceso(new Proceso(0, TAM_1Mb, 0));
        ram = TAM_1Mb;
    }

    else if (opc == 2)
    {
        l->nuevoProceso(new Proceso(0, TAM_4Mb, 0));
        ram = TAM_4Mb;
    }
    else if (opc == 3)
    {

        l->nuevoProceso(new Proceso(0, TAM_8Mb, 0));
        ram = TAM_8Mb;
    }
    return ram;
}

#endif