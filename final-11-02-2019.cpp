#include <iostream>

using namespace std;

struct ArchivoCaja{
    int numeroCaja; //1 a 40
    int efectivoApertura=0;
};


struct Importe{
    int totalEfectivo=0;
    int cuponesTC=0;
    int importeTotalTC=0;
    int cuponesTD=0;
    int importeTotalTD=0;
    int valesPromo=0;
    int importeTotalVP=0;
};

struct Cliente{
    int numeroCarrito;
};

struct Nodo{
    Cliente cliente;
    Nodo* sig;
};

struct Cola{
    Nodo* frente;
    Nodo* fin;
};

struct Caja{
    int totalApertura=0;
    Importe importes;
    Cola clientes;
};

Caja cajas[40] = {NULL};
void queue(Cola&, Cliente);
Cliente unQueue(Cola&);
Importe calcularImporte(int);

void cajasHabilitadas(Caja cajas[], char* nombreArchivo){
    FILE* archivo = fopen(nombreArchivo, "rb");
    ArchivoCaja caja;

    if(archivo){
        while(fread(&caja, sizeof(ArchivoCaja), 1, archivo)){
            cajas[caja.numeroCaja-1].totalApertura += caja.efectivoApertura;
        }
        fclose(archivo);
    }else{
        cout<<"No se pudo abrir el archivo."<<endl;
    }
}

void nuevoCliente(Cola& cola, Cliente cliente){
    queue(cola, cliente);
}

void atenderCliente(Caja cajas[], int numCaja){
    Cliente aux;
    Importe importes;

    aux = unQueue(cajas[numCaja-1].clientes);
    importes = calcularImporte(aux.numeroCarrito);
    cajas[numCaja-1].importes.totalEfectivo = importes.totalEfectivo;
    cajas[numCaja-1].importes.importeTotalTC = importes.importeTotalTC;
    cajas[numCaja-1].importes.importeTotalTD = importes.importeTotalTD;
    cajas[numCaja-1].importes.importeTotalVP = importes.importeTotalVP;
    cajas[numCaja-1].importes.cuponesTC++;
    cajas[numCaja-1].importes.cuponesTD++;
    cajas[numCaja-1].importes.valesPromo++;
}

void reasignarCaja(int numCajaActual, int numCajaDestino, Caja cajas[]){
    Cliente aux;
    aux = unQueue(cajas[numCajaActual-1].clientes);
    queue(cajas[numCajaDestino-1].clientes, aux);
}