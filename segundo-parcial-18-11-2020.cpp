#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Tipo1 {
  char dato1[3];
};

struct Tipo2 {
  char dato2[3];
  char dato1[3];
};

struct NodoListaTipo2 { // nodos lista secundaria
  Tipo2 info;
  NodoListaTipo2 *sig;
  NodoListaTipo2 *ant;
};

struct NodoListaTipo1 { // nodos lista principal
  Tipo1 info;
  NodoListaTipo1 *sig;
  NodoListaTipo2 *sublista;
};

int main() {

  NodoListaTipo1 *lista;

  NodoListaTipo1 *paux1 = lista;
  NodoListaTipo2 *paux2;

  while (paux1 && strcmp(paux1->info.dato1, "N4") != 0) {
    paux1 = paux1->sig;
  }
  if (paux1) {
    paux2 = paux1->sublista;
    while (paux2 && strcmp(paux2->info.dato2, "S6") != 0) {
      paux2 = paux2->sig;
    }
    if (paux2) {
      paux2->ant->sig = paux2->sig;
      paux2->sig->ant = paux2->ant;
      delete (paux2);
    }
  }

  paux1 = lista;
  while (paux1 && strcmp(paux1->info.dato1, "N2") != 0) {
    paux1 = paux1->sig;
  }
  if (paux1) {
    NodoListaTipo1 *nuevo = new NodoListaTipo1;
    strcpy(nuevo->info.dato1, "N5");
    nuevo->sublista = NULL;
    nuevo->sig = paux1->sig;
    paux1->sig = nuevo;
  }
}

void leerArchivo(char *nombreArchivo, NodoListaTipo1 *lista) {
  FILE *archivo = fopen(nombreArchivo, "rb");
  Tipo2 registro;
  

  while (fread(&registro, sizeof(Tipo2), 1, archivo)) {
    NodoListaTipo1 *aux = lista;
    while(strcmp(aux->info.dato1, registro.dato1)) {
      aux = aux->sig;
      }
      NodoListaTipo2 *nuevo = new NodoListaTipo2;
      strcpy(nuevo->info.dato1, registro.dato1);
      strcpy(nuevo->info.dato2, registro.dato2);
      NodoListaTipo2 *aux2 = aux->sublista;

      if(!aux2){
        nuevo->sig = aux2;
        nuevo->ant = NULL;
        aux2 = nuevo;
      }else{
        while(aux2->sig != NULL){
          aux2 = aux2->sig;
        }
        aux2->sig = nuevo;
        nuevo->ant = aux2;
        nuevo->sig = NULL;
      }
      

  }
}

void eliminarNodo(NodoListaTipo1*& lista, char valor[]){
  NodoListaTipo1* aux = lista;
  NodoListaTipo1* anterior;

  while(aux && strcmp(aux->info.dato1, valor)){
    anterior = aux;
    aux = aux->sig;
  }
  if(!strcmp(aux->info.dato1, valor)){
    anterior->sig = aux->sig;
    while(aux->sublista){
      if(aux->sublista->sig){
        aux->sublista = aux->sublista->sig;
        delete(aux->sublista->ant);
      }else{
        delete(aux->sublista);
        aux->sublista = NULL;
      }
    }
    delete(aux);
  }
}

NodoListaTipo1* listasQ[100] = {NULL};

struct Tipo1{
  int lista;
  char dato1[3];
};

void leerArchivo(char nombreArchivo[], NodoListaTipo1* listasQ[]){
    FILE* archivo = fopen(nombreArchivo, "rb");
    Tipo1 dato;

  while(fread(&dato, sizeof(Tipo1), 1, archivo)){    
    insertar(listasQ[dato.lista-1], dato);
  }
}