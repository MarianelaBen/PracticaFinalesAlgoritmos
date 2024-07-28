#include <iostream>
#include <cstring>

using namespace std;

struct Registro{
    int legajo;
    char apellidoYNombre[31];
    int nota;
    char fecha[9];
    char materia[7];
    char curso[6];
};

struct Nodo{
    Registro registro;
    Nodo* sig;
};

Nodo* generarLista(Nodo* l1, Nodo* l2){
    Nodo* lista = NULL;
    Nodo* aux;
    char materia[7];
    char fecha[9];
    char curso[6];

    while(l1){
        aux=l1;
        insertarOrdenado(lista, l1->registro);
        l1 = l1->sig;
        delete aux; 
    }
    while(l2){
        aux=l2;
        insertarOrdenado(lista, l2->registro);
        l2 = l2->sig;
        delete aux;
    }

    cout<<"Ingrese la materia (NNNNNN)"<<endl;
    cin>>materia;
    cout<<"Ingrese la fecha (AAAAMMDD)"<<endl;
    cin>>fecha;
    cout<<"Ingrese el curso (LNNNN)"<<endl;
    cin>>curso;

    aux=lista;
    while(aux){
        strcpy(aux->registro.materia, materia);
        strcpy(aux->registro.fecha, fecha);     
        strcpy(aux->registro.curso, curso);     
        aux = aux->sig;
    }

    return lista;
}

void grabarArchivo(Nodo* lista, const char nombreArchivo[]){
    FILE* archivo = fopen(nombreArchivo, "ab");
    Registro r;
    Nodo* aux = lista;
    
    while(aux){
        r = aux->registro;
        fwrite(&r, sizeof(Registro), 1, archivo);
        aux = aux->sig;
    }

    fclose(archivo);
}

void insertarOrdenado(Nodo* &lista, Registro reg) {
    Nodo* nuevo = new Nodo();
    nuevo->registro = reg;
    nuevo->sig = NULL;

    if (lista == NULL || strcmp(lista->registro.apellidoYNombre, reg.apellidoYNombre) > 0) {
        nuevo->sig = lista;
        lista = nuevo;
    } else {
        Nodo* actual = lista;
        while (actual->sig != NULL && strcmp(actual->sig->registro.apellidoYNombre, reg.apellidoYNombre) < 0) {
            actual = actual->sig;
        }
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
    }
}

