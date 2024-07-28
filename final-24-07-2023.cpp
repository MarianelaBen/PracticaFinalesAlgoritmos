#include <iostream>

using namespace std;

struct Paciente{
    char nombre[40];
    int prioridad;
};

struct Nodo{
    Paciente paciente;
    Nodo* sig;
};

const int cantidadPrioridades = 5;
Nodo* colasPri[cantidadPrioridades], *colasFin[cantidadPrioridades];

void crearColaPrioridad(Nodo* cP[], Nodo* cF[], int cantPrioridades){
    for(int i=0; i<cantidadPrioridades; i++){
        cP[i] = NULL;
        cF[i] = NULL;
    }
}

void insertarPrioridad(Nodo* cP[], Nodo* cF[], Paciente p){
    int prioridad = p.prioridad;
    queue(cP[prioridad],cF[prioridad], p);
}

Paciente elementoMinimo(Nodo* cP[], Nodo* cF[]) {
    for (int i = 0; i < cantidadPrioridades; i++) {
        if (cP[i] != NULL) {
            return unQueue(cP[i], cF[i]);
        }
    }
    Paciente vacio = {"", -1}; // Si todas las colas están vacías, devolver un paciente vacío
    return vacio;
}

void queue(Nodo*& colaPri, Nodo*& colaFin, Paciente paciente) {
    Nodo* nuevo = new Nodo();
    nuevo->paciente = paciente;
    nuevo->sig = NULL;

    if (colaFin == NULL) {
        colaPri = nuevo;
        colaFin = nuevo;
    } else {
        colaFin->sig = nuevo;
        colaFin = nuevo;
    }
}

Paciente unQueue(Nodo*& colaPri, Nodo*& colaFin) {
    Nodo* temp = colaPri;
    Paciente paciente = temp->paciente;

    colaPri = colaPri->sig;
    if (colaPri == NULL) {
        colaFin = NULL; // Si la cola queda vacía
    }

    delete temp;
    return paciente;
}