#include <iostream>

using namespace std;

//PUNTO 1
struct Nodo{
    int dato;
    Nodo* sig;
};
//PUNTO 2
struct Reserva{
    int codigoHotel;
    int cantidadReservas;
    int diasDisponibles;
};

struct NodoListaReserva{
    int codigoHotel;
    int diasReservados;
    NodoListaReserva* sig;
};

Reserva reservas [50];

//PUNTO 3
struct Producto{
    int codigoProducto;
    int peso;
    char tipo;
    int cantidadEnStock;
};

struct NodoProducto{
    Producto producto;
    NodoProducto* sig;
};


Nodo* devolverListaOrdenada(Nodo* cola, Nodo* pila);
void insertarOrdenado(Nodo*& lista, int dato);
void insertarSinOrden(Nodo*& lista, int valor);

int main(){

    return 0;
}

void insertarOrdenado(Nodo*& lista, int valor){ 
    /* Crear un nodo nuevo */ 
    Nodo* nuevo = new Nodo();
    Nodo* anterior; 
    /*Le asigno el valor al nuevo nodo*/
    nuevo->dato = valor; 
    /* Si la lista está vacía o si el primer elemento es mayor a valor*/ 
    if(!lista || lista->dato > valor){ 
        /* Añadimos la lista a continuación del nuevo nodo */ 
        nuevo->sig = lista;   
        /* Ahora, el comienzo de nuestra lista es en nuevo nodo */ 
        lista = nuevo; 
    }else{ 
        /* Buscar el nodo de valor menor a valor */ 
        anterior = lista; 
        /* Avanzamos hasta el último elemento o hasta que el sig tenga   
        un valor mayor que v */ 
        while(anterior->sig && anterior->sig->dato <= valor){
            anterior = anterior->sig; 
        }   
        /* Insertamos el nuevo nodo después del nodo anterior */ 
        nuevo->sig = anterior->sig; 
        anterior->sig = nuevo; 
    } 
} 

Nodo* devolverListaOrdenada(Nodo* cola, Nodo* pila){
    Nodo* lista;

    while(pila){
        insertarOrdenado(lista, pila->dato);
        pila = pila->sig;
    }
    while(cola){
        insertarOrdenado(lista, pila->dato);
        cola = cola->sig;
    }

    return lista;
}

void insertarSinOrden(Nodo*& lista, int valor){
    Nodo* nuevo = new Nodo();
    Nodo* aux;
    nuevo->dato = valor;

    if(!lista){
        nuevo->sig = lista;
        lista = nuevo;
    }else{
        aux = lista;
        while(aux->sig){
            aux = aux->sig;
        }
        aux->sig = nuevo;
        nuevo->sig = NULL;
    }
}

Nodo* generarListaSinOrden(Nodo* pila, Nodo* cola){
    Nodo* lista;

    while(pila){
        while(cola){
            if(pila->dato == cola->dato){
                insertarSinOrden(lista, pila->dato);
                cola = NULL; 
            }
            cola = cola->sig;
        }
        pila = pila->sig;
    }

}


void actualizarVector(Reserva reservas[], NodoListaReserva* lista){
    NodoListaReserva* aux;
    for(int i=0; i<50; i++){
        aux = lista;
        while(aux && aux->codigoHotel != reservas[i].codigoHotel){
            aux = aux->sig;
        }
        if(aux->codigoHotel == reservas[i].codigoHotel){
            reservas[i].cantidadReservas ++;
            reservas[i].diasDisponibles -= aux->diasReservados;
        }

    }
}


NodoProducto* cargarLista(char nombreArchivo[]){
    FILE* archivo = fopen(nombreArchivo, "rb");
    Producto producto;
    NodoProducto* lista;

    if(!feof(archivo)){
        while(fread(&producto, sizeof(Producto), 1, archivo)){
            insertarProductoOrdenado(lista, producto);
        }
        fclose(archivo);
    }

    return lista;    
}

void cargarArchivo(char nombreArchivo[], NodoProducto* lista){
    FILE* archivo = fopen(nombreArchivo, "wb");
    Producto producto;
    while(lista){
        producto = lista->producto;
        fwrite(&producto, sizeof(Producto), 1, archivo);
        lista = lista->sig;
    }

    fclose(archivo);

}

void insertarProductoOrdenado(NodoProducto*& lista, Producto producto){ 
    NodoProducto* nuevo = new NodoProducto;
    NodoProducto* anterior; 

    nuevo->producto = producto; 

    if(!lista || lista->producto.codigoProducto > producto.codigoProducto){ 
        nuevo->sig = lista;   
        lista = nuevo; 
    }else{ 
        anterior = lista; 

        while(anterior->sig && anterior->sig->producto.codigoProducto <= producto.codigoProducto){
            anterior = anterior->sig; 
        }   

        nuevo->sig = anterior->sig; 
        anterior->sig = nuevo; 
    } 
} 

NodoProducto* listaProductosSinStock(char nombreArchivo[]){
    NodoProducto* lista;
    FILE* archivo = fopen(nombreArchivo, "rb");
    Producto producto;

    while(fread(&producto, sizeof(Producto), 1, archivo)){
        if(producto.cantidadEnStock == 0){
            insertarProductoOrdenado(lista, producto);
        }
    }
    fclose(archivo);

    return lista;
}

NodoProducto* listaProductosPesados(char nombreArchivo[]){
    NodoProducto* lista;
    FILE* archivo = fopen(nombreArchivo, "rb");
    Producto producto;

    while(fread(&producto, sizeof(Producto), 1, archivo)){
        if(producto.peso > 100 && producto.tipo == 'B'){
            insertarProductoOrdenado(lista, producto);
        }
    }
    fclose(archivo);

    return lista;
}