#include <iostream>

using namespace std;

//punto 1

struct Nodo{
    int dato;
    Nodo* sig;
};

struct Alumno{
    int legajo;
    int nota1;
    int nota2;
};

struct NodoNotas{
    int legajo;
    int notaRecuperatorio;
    NodoNotas* sig;
};

Alumno alumnos[1500];



Nodo* retornarListaOrdenada(Nodo* cola, Nodo* pila){
    Nodo* auxCola;
    Nodo* auxPila;
    Nodo* lista;
    auxPila = pila;
    while(auxPila){
        auxCola = cola;
        while(auxCola){
            if(auxCola->dato == auxPila->dato){
                insertarOrdenado(lista, auxCola->dato);
            }
            auxCola = auxCola->sig;
        }
        auxPila = auxPila->sig;
    }

    return lista;
}

void insertarOrdenado(Nodo* lista, int dato){
    Nodo* nuevo = new Nodo();
    nuevo->dato = dato;
    if(!lista){ //si la lista está vacia
        lista = nuevo; //lista apunta al nuevo nodo
        nuevo->sig = NULL; //y el nuevo nodo apunta a null
    }else{ // si la lista NO está vacía
        Nodo* aux = lista; //creamos un nodo auxiliar para recorrer la lista y no perder el puntero principal (que seria lista)
        while(aux->sig != NULL && aux->sig->dato < dato){ //mientras que el siguiente al nodo en que estamos tenga algo y ese algo sea menor al dato
            aux = aux->sig; //pasamos al siguiente nodo
        }
        if(aux->sig != NULL){ //si el siguiente no es nulo, quiere decir que el siguiente es mayor al dato que queremos insertar
            nuevo->sig = aux->sig; //hacemos que el nuevo nodo apunte al siguiente
            aux->sig = nuevo; //y hacemos que el anterior apunte al nuevo nodo
        }else{
            aux->sig = nuevo;//si estaba vacía, hacemos que el ultimo nodo apunte al nuevo
            nuevo->sig = NULL;//y que el nuevo apunte a null.
        }
    }
}

//punto 2

void actualizarNotas(NodoNotas* lista, Alumno notas[]){
    NodoNotas* aux = lista;

    while(aux){
        for(int i=0; i<1500; i++){
            if(aux->legajo == notas[i].legajo){
                if(aux->notaRecuperatorio >= 6){
                    notas[i].nota2 = aux->notaRecuperatorio;
                }else{
                    i = 1500;
                }
            }
        }
        aux = aux->sig;
    }
}

//punto 4

/*Verdadero o falso
1. En el apareo, el conjunto resultante siempre contendrá todos lo elementos únicos presentes en ambos conjuntos originales, sin
ninguna pérdida de información.

2. El corte de control en archivos sólo puede aplicarse si el archivo está ordenado y no tiene clave repetida.

*/