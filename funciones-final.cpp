#include <iostream>

using namespace std;

//Nodo para listas simples, pilas, colas, y circulares
struct Nodo{
    int info;
    Nodo* sig;
};

//Nodo especial para doblemente enlazadas
struct Nodo2{
    int info;
    Nodo2* sig;
    Nodo2* ant;
};

//Nodos para listas con sublistas
struct NodoSublista {
    int info;
    NodoSublista* sig;
};

struct NodoLista {
    int info;
    NodoLista* sig;
    NodoSublista* sublista;
};

//PILAS

void apilar(Nodo*& pila, int dato){
    Nodo* nuevo = new Nodo();
    nuevo->info = dato;
    nuevo->sig = pila;
    pila = nuevo;
}

int desapilar(Nodo*& pila){
    Nodo* aux = pila;
    int dato;
    dato = aux->info;
    pila = pila->sig;
    delete aux;
    return dato;
}

//COLAS

void encolar(Nodo*& frente, Nodo*& fin, int dato){
    Nodo* nuevo = new Nodo();
    nuevo->info = dato;
    nuevo->sig = NULL;
    if(fin){
        fin->sig = nuevo;
    }else{
        frente = nuevo;
    }
    fin = nuevo;
}

int desencolar(Nodo*& frente){
    Nodo* aux = frente;
    int dato = frente->info;
    frente = frente->sig;
    delete aux;
    return dato;
}

//LISTAS SIMPLEMENTE ENLAZADAS
void insertarOrdenado(Nodo*& lista, int dato){
    Nodo* nuevo = new Nodo();
    nuevo->info = dato;

    if(!lista || lista->info > dato){
        nuevo->sig = lista;
        lista = nuevo;
    }else{
        Nodo* aux = lista;
        while(aux->sig && aux->sig->info < dato){
            aux = aux->sig;
        }
        nuevo->sig = aux->sig;
        aux->sig = nuevo;
    }
}

void mostrarLista(Nodo* lista){
    Nodo* aux = lista;

    while(aux){
        cout<<aux->info<<endl;
        aux = aux->sig;
    }
}

Nodo* buscar(Nodo* lista, int dato){
    Nodo* aux = lista;

    while(aux && aux->info != dato){
        aux = aux->sig;
    }
    if(aux->info == dato){
        return aux;
    }else{
        return NULL;
    }
}

void eliminar(Nodo*& lista, int dato){
    Nodo *anterior, *aux;
    aux = lista;

    if(lista->info == dato){ // si el dato está al inicio de la lista
        lista = lista->sig;
        delete aux;
    }
    while(aux && aux->info != dato){
        anterior = aux;
        aux = aux->sig;
    }
    if(aux->info == dato){
        anterior->sig = aux->sig;
        delete aux;
    }
}

//LISTAS DOBLEMENTE ENLAZADAS
void insertarOrdenado(Nodo2*& lista, int dato) {
    Nodo2* nuevo = new Nodo2();
    nuevo->info = dato;
    nuevo->sig = nullptr;
    nuevo->ant = nullptr;

    if (!lista) {
        // Si la lista está vacía
        lista = nuevo;
    } else {
        Nodo2* aux = lista;

        if (aux->info > dato) {
            // Insertar al inicio
            nuevo->sig = lista;
            lista->ant = nuevo;
            lista = nuevo;
        } else {
            // Buscar la posición correcta para insertar
            while (aux->sig && aux->sig->info < dato) {
                aux = aux->sig;
            }
            nuevo->sig = aux->sig;
            nuevo->ant = aux;
            if (aux->sig) {
                aux->sig->ant = nuevo;
            }
            aux->sig = nuevo;
        }
    }
}

void mostrarLista(Nodo2* lista) {
    Nodo2* aux = lista;

    while(aux){
        cout << aux->info <<endl;
        aux = aux->sig;
    }
}

Nodo2* buscar(Nodo2* lista, int dato) {
    Nodo2* aux = lista;

    while (aux && aux->info != dato) {
        aux = aux->sig;
    }
    return aux;
}

void eliminar(Nodo2*& lista, int dato) {
    Nodo2* aux = lista;

    while (aux && aux->info != dato) {
        aux = aux->sig;
    }

    if (aux) {
        // Si se encontró el nodo a eliminar
        if (aux->ant) {
            aux->ant->sig = aux->sig;
        } else {
            // Si el nodo a eliminar es el primero de la lista
            lista = aux->sig;
        }
        if (aux->sig) {
            aux->sig->ant = aux->ant;
        }
        delete aux;
    }
}

//LISTAS CIRCULARES
void insertarOrdenado(Nodo*& lista, int dato){
    Nodo* nuevo = new Nodo();
    nuevo->info = dato;
    
    if(!lista){
        nuevo->sig = nuevo;
        lista = nuevo;
    }else{
        Nodo* aux = lista;

        if(aux->info > dato){
            while(aux->sig != lista){
                aux = aux->sig;
            }
            aux->sig = nuevo;
            nuevo->sig = lista;
            lista = nuevo;
        }else{
            while(aux->sig->info < dato){
                aux = aux->sig;
            }
            nuevo->sig = aux->sig;
            aux->sig = nuevo;
        }

    }
}

void mostrar(Nodo* lista){
    Nodo* aux = lista;

    do{
        cout<<aux->info<<endl;
        aux = aux->sig;
    }while(aux != lista);

}

void agregar(Nodo*& lista, int dato){ //para listas que no requieren un orden
    Nodo* nuevo = new Nodo();
    nuevo->info = dato;

    if(lista){
        nuevo->sig = lista->sig;
        lista->sig = nuevo;

    }else{
        nuevo->sig = nuevo;
        lista = nuevo;
    }
}

//LISTAS CON SUBLISTAS

//ARCHIVOS

struct Alumno{
    char nombre[30];
    int edad;
    int nota;
};

void cargarArchivo(const char* nombreArchivo, Alumno alumnos[], int cantAlumnos){
    FILE* archivo = fopen(nombreArchivo, "wb");

    if(archivo){
        for(int i = 0; i<cantAlumnos; i++){
            fwrite(&alumnos[i], sizeof(Alumno), 1, archivo);
        }   
        fclose(archivo);
    }else{
        cout<<"No se pudo abrir el archivo."<<endl;
    }

}

void leerArchivo(const char* nombreArchivo){
    FILE* archivo = fopen(nombreArchivo, "rb");

    if(archivo){
        Alumno alu;
        while(fread(&alu, sizeof(Alumno), 1, archivo)){
            cout<<"Nombre: "<<alu.nombre<<endl;
            cout<<"Edad: "<<alu.edad<<endl;
            cout<<"Nota: "<<alu.nota<<endl;
        }
        fclose(archivo);
    }else{
        cout<<"No se pudo abrir el archivo."<<endl;
    }

}

void agregarEnArchivo(const char* nombreArchivo){
    FILE* archivo = fopen(nombreArchivo, "ab");

    if(archivo){
        Alumno alu;
        cout<<"Ingrese nombre: "<<endl;
        cin>>alu.nombre;
        cout<<"Ingrese edad: "<<endl;
        cin>>alu.edad;
        cout<<"Ingrese nota: "<<endl;
        cin>>alu.nota;
        fwrite(&alu, sizeof(Alumno), 1, archivo);
        fclose(archivo);
    }else{
        cout<<"No se pudo abrir el archivo."<<endl;
    }

}