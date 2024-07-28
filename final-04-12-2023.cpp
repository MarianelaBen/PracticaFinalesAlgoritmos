#include <iostream>

using namespace std;

struct Pasajero{
    char apellidoYNombre[40];
    char destino[30];
    char vuelo[6];
    int asiento;
    int salida;
    int llegada;
};

struct Nodo{
    Pasajero datos;
    Nodo* sig;
};

void menu();
void ingresarPasajero(Nodo*&);
void insertarPasajero(Nodo*&, Pasajero);
void visualizarPasajero(char[], Nodo*);
void visualizarListaTotal(Nodo*);
void mostrarPasajero(Pasajero);
void visualizarListaDestino(char[], Nodo*);
void eliminarPasajero(char[], Nodo*);
void modificarDatosPas(Nodo*, char[]);

int main(){
    menu();
    
    return 0;
}

void menu(){
    int opcion;
    Nodo* lista;
    char d = 'y';

    while(d == 'y'){
    cout<<"Seleccione que accion desea realizar: "<<endl;
    cout<<"1. Ingresar pasajero"<<endl;
    cout<<"2. Visualizar pasajero"<<endl;
    cout<<"3. Visualizar lista de pasajeros"<<endl;
    cout<<"4. Visualizar lista de pasajeros por destino"<<endl;
    cout<<"5. Eliminar pasajero"<<endl;
    cout<<"6. Modificar pasajero"<<endl;
    cin>>opcion;

    switch(opcion){
        case 1:
            ingresarPasajero(lista);
            break;
        case 2:
            char nombreAVisualizar[40];
            cout<<"ingrese el nombre del pasajero a visualizar: "<<endl;
            cin>>nombreAVisualizar;
            visualizarPasajero(nombreAVisualizar, lista);
            break;
        case 3:
            visualizarListaTotal(lista);
            break;
        case 4:
            char destino[30];
            cout<<"ingrese el destino: "<<endl;
            cin>>destino;
            visualizarListaDestino(destino, lista);
            break;
        case 5:
            char nombreAEliminar[40];
            cout<<"ingrese el nombre del pasajero a eliminar: "<<endl;
            cin>>nombreAEliminar;
            eliminarPasajero(nombreAEliminar, lista);
            break;
        case 6: 
            char nombreAModificar[40];
            cout<<"ingrese el nombre del pasajero a modificar: "<<endl;
            cin>>nombreAModificar;
            modificarDatosPas(lista, nombreAModificar);
            break;
    }
    cout<<"desea continuar? (y/n)"<<endl;
    cin>>d;

    }
   
}

void ingresarPasajero(Nodo*& lista){
    Pasajero pasajero;
    cout<<"ingrese apellido y nombre: "<<endl;
    cin>>pasajero.apellidoYNombre;
    cout<<"ingrese el destino: "<<endl;
    cin>>pasajero.destino;
    cout<<"ingrese el vuelo: "<<endl;
    cin>>pasajero.vuelo;
    cout<<"ingrese el asiento: "<<endl;
    cin>>pasajero.asiento;
    cout<<"ingrese la salida: "<<endl;
    cin>>pasajero.salida;
    cout<<"ingrese la llegada: "<<endl;
    cin>>pasajero.llegada;

    insertarPasajero(lista, pasajero);
}

void insertarPasajero(Nodo*& lista, Pasajero pasajero){
    Nodo* nuevo = new Nodo;
    Nodo* aux;
    nuevo->datos = pasajero;
    
    if(!lista){
        nuevo->sig = lista; 
        lista = nuevo;
    }else{
        aux = lista;
        while(aux->sig != lista){
            aux = aux->sig;
        }
        aux->sig = nuevo;
        nuevo->sig = lista; // preguntar a nahuel si esto está bien para insertar en una lista circular.
    }

}

void visualizarPasajero(char nombre[], Nodo* lista){
    Nodo* aux = lista;
    while(aux->sig != lista){
        if(aux->datos.apellidoYNombre == nombre){
            mostrarPasajero(aux->datos);
        }else{
            aux = aux->sig;
        }
    }
    if(aux->datos.apellidoYNombre == nombre){
        mostrarPasajero(aux->datos);
    }

}

void visualizarListaTotal(Nodo* lista){
    Nodo* aux = lista;
    while(aux->sig != lista){
            mostrarPasajero(aux->datos);
            aux = aux->sig;
    }
    mostrarPasajero(aux->datos);
}

void mostrarPasajero(Pasajero aux){
    cout<<"nombre y apellido: "<<aux.apellidoYNombre<<endl;
    cout<<"destino: "<<aux.destino<<endl;
    cout<<"vuelo: "<<aux.vuelo<<endl;
    cout<<"asiento: "<<aux.asiento<<endl;
    cout<<"salida: "<<aux.salida<<endl;
    cout<<"llegada: "<<aux.llegada<<endl;

}

void visualizarListaDestino(char destino[], Nodo* lista){
    Nodo* aux = lista;
    while(aux->sig != lista){
        if(aux->datos.destino == destino){
            mostrarPasajero(aux->datos);
        }
        aux = aux->sig;
    }
    if(aux->datos.destino == destino){
        mostrarPasajero(aux->datos);
    }

}

void eliminarPasajero(char nombre[], Nodo* lista){
    Nodo* actual;
    Nodo* anterior = NULL;
    Nodo* nodoAEliminar;

    if(lista->datos.apellidoYNombre == nombre){ //si el nodo a eliminar está al principio de la lista
        nodoAEliminar = lista;
        actual = lista;
        
        while(actual->sig != lista){ //busca el ultimo nodo (el que apunta a lista) 
            anterior = actual;
            actual = actual->sig;
        }
        actual->sig = lista->sig;
        lista = lista->sig;
        delete nodoAEliminar;
    }else{//si el nodo a eliminar no está al principio de la lista
        actual = lista;
        while(actual->datos.apellidoYNombre != nombre){
            anterior = actual;
            actual = actual->sig;
        }
        if(actual->datos.apellidoYNombre == nombre){
            anterior->sig = actual->sig;
            delete actual;
        }
    }

}

void modificarDatosPas(Nodo* lista, char nombre[]){
    Nodo* aux = lista;
    while(aux){
        if(lista->datos.apellidoYNombre == nombre){
            cout<<"ingrese nuevo apellido y nombre: "<<endl;
            cin>>lista->datos.apellidoYNombre;
            cout<<"ingrese nuevo destino: "<<endl;
            cin>>lista->datos.destino;
            cout<<"ingrese nuevo vuelo: "<<endl;
            cin>>lista->datos.vuelo;
            cout<<"ingrese nuevo asiento: "<<endl;
            cin>>lista->datos.asiento;
            cout<<"ingrese nueva salida: "<<endl;
            cin>>lista->datos.salida;
            cout<<"ingrese nueva llegada: "<<endl;
            cin>>lista->datos.llegada;
            aux = NULL;
        }
        aux = aux->sig;
    }
}