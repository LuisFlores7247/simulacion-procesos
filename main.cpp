#include "Funciones.h"
#include "Lista.cpp"


using namespace std;

int main()
{
    srand(time(NULL));

    Lista *l = new Lista();

    Proceso *p=NULL;

    int opc=0, tamMax=0, cuanMax=0, numProces=0;

    TAM_MEMORIA ram;

    cout << "Tamanios de memoria disponibles: " << endl;
    cout << "1. 1Mb\n2. 4Mb\n3. 8Mb\n";
    cout<<endl<<"TU opcion: ";
    cin >> opc;

    /* Crea un proceso inicial el cual tiene como tarea almacenar el valor de 
    la memoria RAM para luego en base a este generar las particiones de memoria*/
    if (opc == 1){
        l->nuevoProceso(new Proceso(0,TAM_1Mb,0));
        ram=TAM_1Mb;
    }
        
    else if (opc == 2){
        l->nuevoProceso(new Proceso(0,TAM_4Mb,0));
        ram=TAM_4Mb;
    }
    else if (opc == 3){

        l->nuevoProceso(new Proceso(0,TAM_8Mb,0));
        ram=TAM_8Mb;
    }
    //Vuelve a pedir el dato mientras el tamaño maximo sea mas de la mitad de la memoria ram
    do{

        cout<<endl<<"Ingresa el tamanio maximo asignado a un proceso: ";
        cin>>tamMax;

        if(tamMax>ram/2){
            cout<<"Opcio invalida. Introduce un valor menor";
        }

    }while(tamMax>ram/2);

    cout<<"Ingresa el maximo de cuantos de un proceso: ";
    cin>>cuanMax;
    int cuanSistema;
    cout << "Ingresa los cuantos del sistema: ";
    cin >>cuanSistema;
    cout<<endl<<"Numero de procesos a ejecutar: ";
    cin>>numProces;
    
    cout << endl << "Por ultimo, dame la cantidad de procesadores que ejecutaran la simulacion: \n1 / 2 / 4 / 8" << endl;
    NUM_CPUS cpus;
    cin >> opc;
    (opc == 1)  ? cpus = CPU_1 : (opc == 2) ? cpus = CPU_2 : (opc == 4) ? cpus = CPU_4 : (opc == 8) ? cpus = CPU_8 : cpus = CPU_1;
    //VALIDACION QUE EL USUARIO INGRESE EL NUMERO CORRECTO NECESARIO
    system("cls");

    // iniciarSimulacion();

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

// int main(void)
// {
//     srand(time(NULL));
//     cout << endl << "Hola!!, bienvenido a la simulacion de gestion de memoria y procesos del equipo 4!!!";
//     cout << endl << "Esperamos que este nuestro proyecto final de sistemas operativos te sea de tu agrado";

// }