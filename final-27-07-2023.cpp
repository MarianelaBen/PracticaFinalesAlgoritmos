#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Paciente{
    char nombre[40];
};

struct Nodo{
    Paciente p;
    Nodo* sig;
};

struct Cola{
    Nodo* frente;
    Nodo* fin;
};

Cola pacientes[5] = {NULL};
void queue(Cola, char[]);
Nodo* unQueue(Cola);

void crearCola(Cola p[]){
    for(int i = 0; i<5; i++){
        p[i].frente = NULL;
        p[i].fin = NULL;
    }
}

void insertarEnPrioridad(Cola p[], int prioridad, char nombre[]){
    queue(p[prioridad], nombre);
}   

Nodo* elementoMinimo(Cola p[]) {
    for(int i = 0; i < 5; i++) {
        if(p[i].frente) {
            return p[i].frente;
        }
    }
    return NULL;
}

void quitarMinimo(Cola p[]) {
    for(int i = 0; i < 5; i++) {
        if(p[i].frente) {
            Nodo* aux = unQueue(p[i]);
            return;
        }
    }
}

bool colaVacia(Cola p[], int pri) {
    return p[pri].frente == NULL;
}

bool prioridadVacia(Cola p[]){
    for(int i = 0; i<5; i++){
        if(!colaVacia(p, i)){
            return false;
        }
    }
    return true;
}



