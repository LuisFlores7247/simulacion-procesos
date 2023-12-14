#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include "colores.h"
#include "Lista.cpp"
#include "conio.h"
#include <sys/time.h>

void presentacion(int);

void iniciarSimulacion(int);
void limpiarMemoria(Lista *);

void simulacion(Proceso *, Lista *, int, int, int, int, int);

int pedirTamMemoria(int);
int pedirTamMax(int, int);
int pedirCuanMax(int);
int pedirCuanSistema(int, int);
int crearMemoria(int, Lista *);
void borrarParteConsola(int x, int y, int ancho, int alto);

long obtenerTiempo();

void presentacion(int consoleWidth)
{
    string divisor = "------------------------------------------------------";
    // Datos de la portada
    string titulo = "Proyecto Sistemas Operativos";
    string institucion = "Universidad Autonoma de Aguascalientes";
    string carr = "Ing. Sistemas Computacionales";
    string centro = "Centro de Ciencias Basicas";
    string prof = "Javier Santiago Lopez Cortez";
    string fecha = "11 de diciembre de 2023";
    string integrantes[] = {"Daan Jostin Carabez Garcia", "Sergio Eder Cervantes Rincon", "Angel Esteban Esparza Munoz", "Luis David Flores Martinez"};

    // Imprimir la portada
    int leftPadding = (consoleWidth - divisor.length()) / 2;
    gotoxy(leftPadding, 1);
    cout << divisor << endl;

    leftPadding = (consoleWidth - titulo.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << titulo << endl;

    leftPadding = (consoleWidth - divisor.length()) / 2;
    gotoxy(leftPadding, 5);
    cout << divisor << endl;

    leftPadding = (consoleWidth - institucion.length()) / 2;
    gotoxy(leftPadding, 7);
    cout << institucion << endl;

    leftPadding = (consoleWidth - carr.length()) / 2;
    gotoxy(leftPadding, 8);
    cout << carr << endl;

    leftPadding = (consoleWidth - centro.length()) / 2;
    gotoxy(leftPadding, 9);
    cout << centro << endl;

    leftPadding = (consoleWidth - (prof.length() + 10)) / 2;
    gotoxy(leftPadding, 10);
    cout << "Profesor: " << prof << endl;

    leftPadding = (consoleWidth - (fecha.length() + 7)) / 2;
    gotoxy(leftPadding, 11);
    cout << "Fecha: " << fecha << endl;

    leftPadding = (consoleWidth - divisor.length()) / 2;
    gotoxy(leftPadding, 13);
    cout << divisor << endl;

    // Imprimir la lista de integrantes
    leftPadding = (consoleWidth - 12) / 2;
    gotoxy(leftPadding, 15);
    cout << "Integrantes:" << endl;
    int i = 16;
    for (const auto &integrante : integrantes)
    {
        leftPadding = (consoleWidth - integrante.length()) / 2;
        gotoxy(leftPadding, i);

        cout << integrante << endl;
        i++;
    }
}
void iniciarSimulacion(int consoleWidth)
{
    srand(time(NULL));
    Lista *l = new Lista();

    Proceso *p = NULL;

    presentacion(consoleWidth);
    int leftPadding = (consoleWidth - 40) / 2;
    gotoxy(leftPadding, 22);
    system("pause");
    int ram = crearMemoria(pedirTamMemoria(consoleWidth), l);
    int tamMax = pedirTamMax(ram, consoleWidth);
    int cuanMax = pedirCuanMax(consoleWidth);
    int cuanSistema = pedirCuanSistema(cuanMax, consoleWidth);

    cout << "Iniciando simulacion..." << endl;
    Sleep(1.5);

    simulacion(p, l, tamMax, cuanMax, cuanSistema, ram, consoleWidth);
}

void simulacion(Proceso *p, Lista *l, int tamMax, int cuanMax, int cuanSistema, int ram, int consoleWidth)
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

    l->cont = 0;
    l->TrTs = 0;
    int i = 1;
    long inicio = obtenerTiempo();
    while (true)
    {
        if (_kbhit())
        {
            char tecla = _getch();
            if (tecla == '\r')
            {
                break;
            }
            switch (tecla)
            {
            case ' ':
                // Pausa de la simulacion
                system("pause");
                break;
            case '1':
                // Cambio a Velocidad 1
                l->setVelocidad(VELOCIDAD_1);
                break;
            case '2':
                // Cambio a Velocidad 2
                l->setVelocidad(VELOCIDAD_2);
                break;
            case '3':
                // Cambio a Velocidad 3
                l->setVelocidad(VELOCIDAD_3);
                break;
            }
        }
        system("cls");
        int leftPadding = (consoleWidth - 42) / 2;
        gotoxy(leftPadding, 2);
        cout << ROJO << "Para Terminar la simulacion presiona ENTER";
        leftPadding = (consoleWidth - 60) / 2;
        gotoxy(leftPadding, 3);
        cout << "Si quiere pausar la simulacion presiona la barra espaciadora";
        leftPadding = (consoleWidth - 70) / 2;
        gotoxy(leftPadding, 4);
        cout << "Para cambiar la velocidad usa las teclas 1 , 2 y 3 para cada velocidad";
        leftPadding = (consoleWidth - 21) / 2;
        gotoxy(leftPadding, 5);
        cout << "Velocidad actual: ";
        cout << NEGRITA;
        (l->getVelocidad() == VELOCIDAD_1) ? cout << " [1] " : (l->getVelocidad() == VELOCIDAD_2) ? cout << " [2] "
                                                                                                  : cout << " [3] ";
        cout << endl;

        if (band == ENMEMORIA)
        {
            p = new Proceso(i, rand() % tamMax + 1, rand() % cuanMax + 1);
            p->tiempo_Servicio = p->cuanto;
        }

        leftPadding = ((consoleWidth - (18 + (contarDigitos(i) * 2) + contarDigitos(p->getTamanio()) + contarDigitos(p->getMem_asignada()) + contarDigitos(p->getCuanto()))) / 2);
        gotoxy(leftPadding, 7);
        cout << AMARILLO << "Proceso " << i << ":   " << imprimirProceso(p) << RESET;
        cout << endl;

        band = p->status = l->asignMemoria(p);
        if (p->status == ENESPERA)
        {
            cout << endl
                 << "En espera, espacio no disponible...";
            cout << endl;
        }
        if (l->getVelocidad() != VELOCIDAD_3)
        {
            cout << endl;
            l->imprimir(consoleWidth);
            cout << endl
                 << endl
                 << CYAN << "El porcentaje de RAM es: " << setprecision(2) << fixed << (l->porcentajeMem(ram) * 100) << "%";
            // Parte de la ejecucion (Round Robin)
            cout << endl
                 << endl
                 << AZUL << "Lista RR: ";
            l->imprimir_ListaListos();
            cout << endl
                 << RESET;
        }

        l->ejecucion(cuanSistema, consoleWidth);

        if (l->getVelocidad() != VELOCIDAD_3)
        {

            cout << endl
                 << RESET;
            l->imprimir(consoleWidth);
            cout << endl
                 << endl
                 << CYAN << "El porcentaje de RAM es: " << setprecision(2) << fixed << (l->porcentajeMem(ram) * 100) << "%";
            cout << endl
                 << endl
                 << AZUL << "Lista RR: ";
            l->imprimir_ListaListos();
            cout << RESET;

            cout << endl
                 << endl;
        }

        if (band != ENESPERA)
        {
            i++;
        }

        Sleep(l->getVelocidad());
    }
    long fin = obtenerTiempo();
    system("cls");

    long tiempoEjecucion = ((fin - inicio) / 1000);
    int leftPadding = (consoleWidth - 40) / 2;
    gotoxy(leftPadding, 2);
    cout << NEGRITA << MAGENTA << "Promedio de Tr/Ts x proceso: " << BLANCO << l->TrTs / l->cont << " cuantos" << endl;
    leftPadding = (consoleWidth - 35) / 2;
    gotoxy(leftPadding, 4);
    cout << MAGENTA << "Tiempo de ejecucion: " << BLANCO << tiempoEjecucion << " segundos" << endl;
}

int pedirTamMemoria(int consoleWidth)
{
    int opc;
    bool check = false;
    do
    { // Repite el ciclo mientras la opcion sea invalida
        system("cls");
        int leftPadding = (consoleWidth - 33) / 2;
        gotoxy(leftPadding, 2);
        cout << "Tamanios de memoria disponibles: " << endl;
        leftPadding = (consoleWidth - 6) / 2;
        gotoxy(leftPadding, 4);
        cout << "1. 1Mb";
        leftPadding = (consoleWidth - 6) / 2;
        gotoxy(leftPadding, 5);
        cout << "2. 4Mb";
        leftPadding = (consoleWidth - 6) / 2;
        gotoxy(leftPadding, 6);
        cout << "3. 8Mb\n";
        leftPadding = (consoleWidth - 21) / 2;
        gotoxy(leftPadding, 8);
        cout << "Selecciona del 1-3...";
        leftPadding = (consoleWidth - 11) / 2;
        gotoxy(leftPadding, 10);
        cout << "Tu opcion: ";
        leftPadding = (consoleWidth) / 2;
        gotoxy(leftPadding, 11);
        cin >> opc;

        if (opc < 1 || opc > 3)
        {
            leftPadding = (consoleWidth - 23) / 2;
            gotoxy(leftPadding, 13);
            cout << "Opcion no disponible..." << endl;
            check = true;
            leftPadding = (consoleWidth - 40) / 2;
            gotoxy(leftPadding, 15);
            system("pause");
        }
        else
        {
            check = false;
        }

    } while (check == true);

    return opc;
}

int pedirTamMax(int ram, int consoleWidth)
{
    // Vuelve a pedir el dato mientras el tamaño maximo sea mas de la mitad de la memoria ram
    int tamMax;
    do
    {
        system("cls");
        int leftPadding = (consoleWidth - 49) / 2;
        gotoxy(leftPadding, 2);
        cout << "Ingresa el tamanio maximo asignado a un proceso: ";
        leftPadding = (consoleWidth) / 2;
        gotoxy(leftPadding, 3);
        cin >> tamMax;

        if (tamMax > ram / 2)
        {
            leftPadding = (consoleWidth - 41) / 2;
            gotoxy(leftPadding, 5);
            cout << "Opcion invalida. Introduce un valor menor" << endl;
            leftPadding = (consoleWidth - 40) / 2;
            gotoxy(leftPadding, 17);
            system("pause");
        }

    } while (tamMax > ram / 2);
    return tamMax;
}
int pedirCuanMax(int consoleWidth)
{
    int cuanMax = 0;
    do
    {
        borrarParteConsola((consoleWidth - 5) / 2, 6, 5, 1);

        int leftPadding = (consoleWidth - 44) / 2;
        gotoxy(leftPadding, 5);
        cout << "Ingresa el maximo de cuantos de un proceso: ";

        leftPadding = (consoleWidth / 2);
        gotoxy(leftPadding, 6);
        cin >> cuanMax;
        if (cuanMax < 1)
        {
            leftPadding = (consoleWidth - 20) / 2;
            gotoxy(leftPadding, 8);
            cout << "Cuantos invalidos..." << endl;
            leftPadding = (consoleWidth - 40) / 2;
            gotoxy(leftPadding, 10);
            system("pause");
            borrarParteConsola(((consoleWidth - 20) / 2), 8, 20, 1);
            borrarParteConsola(leftPadding, 10, 40, 1);
        }

    } while (cuanMax < 1);

    return cuanMax;
}

int pedirCuanSistema(int cuanMax, int consoleWidth)
{
    int cuanSistema;
    do
    {
        int leftPadding = (consoleWidth - 33) / 2;
        gotoxy(leftPadding, 8);
        cout << "Ingresa los cuantos del sistema: ";
        leftPadding = (consoleWidth) / 2;
        gotoxy(leftPadding, 9);
        cin >> cuanSistema;
        if (cuanSistema >= cuanMax || cuanSistema < 1)
        {
            leftPadding = (consoleWidth - 32) / 2;
            gotoxy(leftPadding, 11);
            cout << "Cuantos del sistema invalidos..." << endl;
            leftPadding = (consoleWidth - 40) / 2;
            gotoxy(leftPadding, 13);
            system("pause");
            borrarParteConsola(((consoleWidth - 5) / 2), 9, 6, 1);
            borrarParteConsola(((consoleWidth - 32) / 2), 11, 32, 1);
            borrarParteConsola(leftPadding, 13, 40, 1);
        }

    } while (cuanSistema >= cuanMax || cuanSistema < 1);

    return cuanSistema;
}

int crearMemoria(int opc, Lista *l)
{
    TAM_MEMORIA ram;
    /* Crea un proceso inicial el cual tiene como tarea almacenar el valor de
    la memoria RAM para luego en base a este generar las particiones de memoria*/
    do
    {
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
        else
        {
            cout << endl
                 << "Opcion invalida....";
        }
    } while (opc < 1 || opc > 3);
    return ram;
}

long obtenerTiempo()
{
    struct timeval inicio;
    gettimeofday(&inicio, NULL);
    return inicio.tv_sec * 1000 + inicio.tv_usec / 1000;
}

void borrarParteConsola(int x, int y, int ancho, int alto)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error al obtener el identificador de la consola." << std::endl;
        return;
    }

    // Rellenar la región con espacios en blanco
    CHAR_INFO buffer[ancho * alto];
    COORD bufferSize = {static_cast<SHORT>(ancho), static_cast<SHORT>(alto)};
    COORD bufferCoord = {0, 0};
    SMALL_RECT writeRegion = {
        static_cast<SHORT>(x),
        static_cast<SHORT>(y),
        static_cast<SHORT>(x + ancho - 1),
        static_cast<SHORT>(y + alto - 1)};

    for (int i = 0; i < ancho * alto; ++i)
    {
        buffer[i].Char.UnicodeChar = L' ';
        buffer[i].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    }

    WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &writeRegion);
}

#endif