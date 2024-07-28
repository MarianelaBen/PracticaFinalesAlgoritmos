#include <iostream>

using namespace std;

struct Nodo{
    int dato;
    Nodo* sig;
};

struct Saldo{
    int numeroCuenta;
    int cantidadTransacciones;
    int saldo;
};

struct NodoTransaccion{
    int numeroCuenta;
    int monto;
    NodoTransaccion* sig;
};

Saldo saldos[150];

Nodo* retornaListaOrdenada(Nodo* pila, Nodo* cola){
    Nodo* lista;
    Nodo* aux;
    while(pila){
        aux = cola; 
        while(aux){
            if(pila->dato == cola->dato){
                insertarOrdenado(lista, pila->dato);
                aux = NULL;
            }else{
                aux = aux->sig;
            }
        }
        pila = pila->sig;
    }
    return lista;
}

void insertarOrdenado(Nodo*& lista, int valor){
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    Nodo* aux;

    if(!lista || lista->dato > valor){
        nuevo->sig = lista;
        lista = nuevo;
    }else{
        aux = lista;
        while(aux->sig && aux->sig->dato < valor){
            aux = aux->sig;
        }
            nuevo->sig = aux->sig;
            aux->sig = nuevo;
    }
}

void actualizarSaldos(Saldo saldos[], NodoTransaccion* lista){
    NodoTransaccion* aux;
    aux = lista; 
    while(aux){
        for(int i=0; i<150;i++){
            if(saldos[i].numeroCuenta == aux->numeroCuenta){
                saldos[i].saldo -= aux->monto;
                saldos[i].cantidadTransacciones++;
                i = 150;
            }
        }
        aux = aux->sig;
    }
}

// PUNTO 3

void proc(int v[], int len) {
    *v = 10; // Esto asigna el valor 10 al primer elemento del array.
}

int main() {
    int *p = NULL;
    int x = 30;
    p = new int[3]; // Reserva memoria para un array de 3 enteros.
    p[1] = x; // Asigna el valor 30 al segundo elemento del array.
    proc(p, 3); // Llama a la función proc, que asigna 10 al primer elemento del array.
    p[2] = *(p + 1) + x; // Asigna a p[2] el valor de p[1] + x, es decir, 30 + 30 = 60.
    for (int i = 0; i < 3; i++) {
        cout << *(p + i) << " " << endl; // Imprime los elementos del array.
    }
    delete[] p; // Libera la memoria asignada.
    return 0;
}
/*Entonces la salida del programa será: 10 30 60*/

int main() {
    int *p;              // Declara un puntero a entero.
    int x = 10;          // Declara una variable entera x y la inicializa a 10.
    p = new int[10];     // Reserva memoria para un array de 10 enteros y asigna su dirección a p.
    p[0] = 20;           // Asigna el valor 20 al primer elemento del array.
    p[1] = 21;           // Asigna el valor 21 al segundo elemento del array.
    p[2] = *p;           // Asigna al tercer elemento del array el valor del primer elemento (20).
    p[3] = *(p+1);       // Asigna al cuarto elemento del array el valor del segundo elemento (21).
    p[4] = *p + *(p+1);  // Asigna al quinto elemento del array la suma del primer y segundo elemento (20 + 21).
    cout << *(p+4) << endl;  // Imprime el valor del quinto elemento del array.
    delete[] p;          // Libera la memoria asignada al array.
    return 0;
}
/*Entonces la salida del programa será: 41*/

//PUNTO 4

/* Indique con V o F 

a. "La manera correcta de enviar como parametro por referencia un vector es: "int* vec[]".
Falso.
La manera correcta de enviar un vector (array) como parámetro por referencia en C/C++ es usando un puntero, 
pero la declaración debe ser int* vec o int vec[]. Ambas formas son equivalentes y se usan para indicar que 
se está pasando un puntero al primer elemento del array. Aquí hay una breve explicación de cada una:

1. int* vec: Se usa un puntero para señalar el inicio del array.
2. int vec[]: Se usa una sintaxis que también indica un puntero al primer elemento del array, pero hace más 
evidente que se trata de un array.

b. "La estrategia de resolución de apareo, sólo puede aplicarse en Archivos." 
Falso.
La estrategia de resolución de apareo no se aplica exclusivamente a archivos. Esta técnica se utiliza en diversos
contextos, incluyendo algoritmos de ordenamiento y manipulación de datos

*/