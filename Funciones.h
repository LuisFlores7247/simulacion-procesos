#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <ctime>
#include "Lista.cpp"
#include "cstdlib"
#include "windows.h"


void iniciarSimulacion();

void simulacion(Proceso *, Lista *, int, int,int);

int pedirTamMemoria();
int pedirTamMax(int);
int pedirCuanMax();
int pedirCuanSistema(int);
int crearMemoria(int, Lista *);

void iniciarSimulacion()
{
    srand(time(NULL));
    Lista *l = new Lista();

    Proceso *p = NULL;

    int ram = crearMemoria(pedirTamMemoria(), l);
    int tamMax = pedirTamMax(ram);
    int cuanMax = pedirCuanMax();
    int cuanSistema = pedirCuanSistema(cuanMax);

    cout << "Iniciando simulacion..." << endl;
    Sleep(1.5);

    simulacion(p, l, tamMax, cuanMax,cuanSistema);
}

void simulacion(Proceso *p, Lista *l, int tamMax, int cuanMax, int cuanSistema)
{

    /* Repite un ciclo desde 1 hasta el total de procesos. Llena el proceso con datos
    aleatoriosl, como paso siguiente imprime el proceso generado y realiza la asignacion en memoria,
    la cual retorna un apuntador a un objeto del tipo proceso; si el proceso en su atributo status
    tiene almacenado un "ENMEMORIA", se procede a imprimir la lista actualizada con
    el nuevo proceso, sino, (el status del proceso es en espera) se indica que el
    proceso no pudo entrar a memoria y se continua la ejecucion de la simulacion,
    manteniendo el proceso en espera sin generar uno nuevo, hasta que hay algun
    lugar disonible*/
    STATUS band = ENMEMORIA; // Esta bandera es la que dictara la creacion de procesos o no, si tiene un valor de
                             // ENMEMORIA, significa que puede seguir creando procesos ya que todos estan en memoria
                             // en caso de que este ENESPERA, significa que existe un proceso en espera por lo cual no se debe generar procesos

    for (int i = 1; i <= 5; i++)
    {
        if (band == ENMEMORIA)
        {
            p = llenarProceso(i, tamMax, cuanMax);
        }
        
        cout << endl;
        cout<<endl<<"Proceso "<<i<<":   " << imprimirProceso(p); 
        
        band = p->status = l->asignMemoria(p);
        if(p->status==ENMEMORIA){  
            cout << endl << "RAM: ";    
            l->imprimir();
        }
        else
        {
            cout << endl
                 << "En espera, espacio no disponible...";
            cout << endl;
            system("pause");
        }
        //Parte de la ejecucion (Round Robin)
        cout << endl << "Lista RR: ";
        l->imprimir_ListaListos();
        l->ejecucion(cuanSistema);
        cout << endl << "Lista RR: ";
        l->imprimir_ListaListos();

    }

    cout << endl
         << endl
         << "Lista de listos..." << endl;
    l->imprimir_ListaListos();
}

int pedirTamMemoria()
{
    int opc;
    bool check = false;
    do
    { // Repite el ciclo mientras la opcion sea invalida
        system("cls");
        cout << "Tamanios de memoria disponibles : " << endl;
        cout << "1. 1Mb\n2. 4Mb\n3. 8Mb\n";
        cout << endl
             << "Selecciona del 1-3...";
        cout << endl
             << "Tu opcion: ";
        cin >> opc;

        if (opc < 1 || opc > 3)
        {
            cout << endl
                 << "Opcion no disponible..." << endl;
            check = true;
            system("pause");
        }
        else
        {
            check = false;
        }

    } while (check == true);

    return opc;
}

int pedirTamMax(int ram)
{
    // Vuelve a pedir el dato mientras el tamaño maximo sea mas de la mitad de la memoria ram
    int tamMax;
    do
    {

        system("cls");
        cout << endl
             << "Ingresa el tamanio maximo asignado a un proceso: ";
        cin >> tamMax;

        if (tamMax > ram / 2)
        {
            cout << "Opcio invalida. Introduce un valor menor" << endl;
            system("pause");
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

int pedirCuanSistema(int cuanMax)
{
    int cuanSistema;
    bool check = false;
    do
    {
        system("cls");
        cout << endl
             << "Ingresa los cuantos del sistema: ";
        cin >> cuanSistema;

        if (cuanSistema > cuanMax || cuanSistema <= 0)
        {
            cout << endl
                 << "Cantidad de cuantos de procesamiento invalida!!!" <<endl;
            system("pause");
            check = true;
        }
        else
        {
            check = false;
        }

    } while (check == true);
    return cuanSistema;
    // validar que no sea mayor a cuanMax
}

int crearMemoria(int opc, Lista *l)
{
    TAM_MEMORIA ram;
    /* Crea un proceso inicial el cual tiene como tarea almacenar el valor de
    la memoria RAM para luego en base a este generar las particiones de memoria*/
    do{
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
        else{
            cout << endl << "Opcion invalida....";
        }
    }while(opc<1 || opc>3);
    return ram;
}

#endif