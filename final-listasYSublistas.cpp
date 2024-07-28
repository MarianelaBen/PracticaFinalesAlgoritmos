#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct ArchivoCamion{
    int idCamion;
    int cp;
};

struct ArchivoEnvio{
    char codigoPaquete[25];
    char direccion[50];
    int cp;
    int idCamion;
    int horaEntrega; 
};

struct Paquete{
    char codigoPaquete[25];
    char direccion[50];
    int horaEntrega; //HH:MM
};

struct NodoPaquete{
    Paquete paquete;
    NodoPaquete* sig;
};

struct ColaPaquetes{
    NodoPaquete* frente;
    NodoPaquete* fin;
};

struct Envio{
    int cp;
    ColaPaquetes* paquetes;
};

struct ListaEnvios{
    Envio envio;
    ListaEnvios* sig;
};

struct Camion{
    int cp;
    ListaEnvios* envios;
};

Camion camiones[100];

void leerVehiculos(Camion, const char*);
void queue(ColaPaquetes*&, Paquete);
Paquete unQueue(NodoPaquete*&, NodoPaquete*&);
ListaEnvios* insertarSinRepetir(ListaEnvios*&, Envio);
ListaEnvios* insertarOrdenado(ListaEnvios*&, Envio);
ListaEnvios* buscarEnLista(ListaEnvios*&, Envio);

int main(){

}

void leerVehiculos(Camion camiones[], const char* nombreArchivo){
    FILE* archivo = fopen(nombreArchivo, "rb");
    ArchivoCamion camion;
    if(archivo){
        while(fread(&camion, sizeof(ArchivoCamion), 1, archivo)){
            camiones[camion.idCamion-1].cp = camion.cp;
            camiones[camion.idCamion-1].envios = NULL;
        }
        fclose(archivo);
    }else{
        cout<<"No se pudo abrir el archivo"<<endl;
    }
}

void planificarEntregas(Camion camiones[], const char* nombreArchivo){
    FILE* archivo = fopen(nombreArchivo, "rb");
    ArchivoEnvio envioArchivo;

    if(archivo){
        Envio envio;
        Paquete paquete;

        while(fread(&envioArchivo, sizeof(ArchivoEnvio), 1, archivo)){
            ListaEnvios* aux;

            envio.cp = envioArchivo.cp;
            strcpy(paquete.codigoPaquete, envioArchivo.codigoPaquete);
            strcpy(paquete.direccion, envioArchivo.direccion);
            paquete.horaEntrega = envioArchivo.horaEntrega;

            aux = insertarSinRepetir(camiones[envioArchivo.idCamion-1].envios, envio); //agrego el envio a la lista de envios del camion correspondiente
            queue(aux->envio.paquetes, paquete); //agrego el paquete a la cola de envios correspondiente
            
        }
        fclose(archivo);
    }else{
        cout<<"No se pudo abrir el archivo"<<endl;
    }
}


void entregarPaquete(int idCamion, int cp, Camion camiones[]){ //esto no se si está bien porque en la consigna dice que recibe solo dos parametros
    ListaEnvios* listaEnvios = camiones[idCamion-1].envios;
    
    while(listaEnvios){
        if(listaEnvios->envio.cp == cp){
            unQueue(listaEnvios->envio.paquetes->frente, listaEnvios->envio.paquetes->fin);
            return;
        }
        listaEnvios = listaEnvios->sig;
    }
    cout<<"No se ha encontrado el envio"<<endl;
}

