#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Participante{
    char nombre[10];
};

struct Nodo{
    Participante participante;
    Nodo* sig;
    Nodo* ant;
};

const int movimientos = 3;
int cantParticipantes = 4;
Participante equipo1[2];
Participante equipo2[2];
Nodo* lista;

void seleccion(Nodo*&, char*, Participante[], Participante[]);
void eliminar(Nodo*&, char*);


void seleccion(Nodo*& lista, char* nombre, Participante e1[], Participante e2[]){
    int pos = 0;
    Nodo* aux = lista;

    while(strcmp(aux->participante.nombre, nombre) != 0){
        aux = aux->sig;
    }

    while(lista){
        for(int i=0; i<movimientos; i++){
            aux = aux->sig;
        }
        strcpy(e1[pos].nombre, aux->participante.nombre);
        Nodo* aEliminar = aux;
        aux = aux->sig;
        eliminar(lista, aEliminar->participante.nombre);

        for(int i=0; i<movimientos; i++){
            aux = aux->ant;
        }
        strcpy(e2[pos].nombre, aux->participante.nombre);
        aEliminar = aux;
        aux = aux->ant;
        eliminar(lista, aEliminar->participante.nombre);
        pos++;
    }
}

void eliminar(Nodo*& lista, char nombre[]) {
    Nodo* aux = lista;

    // Encontrar el nodo con el nombre especificado
    while (strcmp(aux->participante.nombre, nombre) != 0) {
        aux = aux->sig;
    }

    if (strcmp(aux->participante.nombre, nombre) == 0) {
        // Si el nodo a eliminar es el único nodo en la lista
        if (aux->sig == aux) {
            lista = nullptr;
        } else {
            // Ajustar los punteros
            aux->ant->sig = aux->sig;
            aux->sig->ant = aux->ant;
            // Si el nodo a eliminar es el nodo al que apunta `lista`
            if (lista == aux) {
                lista = aux->sig;
            }
        }
        delete aux;
    }
}