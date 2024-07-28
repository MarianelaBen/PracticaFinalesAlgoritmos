#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct OtroLenguaje{
    char* nombre;
    int cantidadDeVotos=0;
    OtroLenguaje* sig;
};

struct Lenguaje{
    int py=0;
    int c=0;
    int java=0;
    int otros=0;
    OtroLenguaje* otroLenguaje;
};

Lenguaje votos[3][3];
int unaEncuesta(int&, int&, int&, char*&);
OtroLenguaje* insertarSinRepetir(OtroLenguaje*&, char*);


void cargarMatriz(Lenguaje votos[][3]){
    int actividad, institucion, lenguaje;
    char* otro;

    while(unaEncuesta(actividad, institucion, lenguaje, otro)){
        switch(lenguaje){
            case 1:
                votos[actividad-1][institucion-1].py++;
                break;
            case 2: 
                votos[actividad-1][institucion-1].c++;
                break;
            case 3:
                votos[actividad-1][institucion-1].java++;
                break;
            case 4:
                OtroLenguaje* aux;
                votos[actividad-1][institucion-1].otros++;
                aux = insertarSinRepetir(votos[actividad-1][institucion-1].otroLenguaje, otro);//asumo que esta funcion tambien insertar ordenado por cantidad de votos.
                aux->cantidadDeVotos++; 
                break;
        }
        
    }
}

void mostrarResultados(Lenguaje votos[][3], int actividad){
    const char* instituciones[] = {"universidad publica", "universidad privada", "terciario"};
    for(int i=0; i<3; i++){
        cout << "Votos " << instituciones[i] << ":" << endl;
        cout << "Python: " << votos[actividad-1][i].py << " C++: " << votos[actividad-1][i].c << " Java: " << votos[actividad-1][i].java << endl;
        cout << "Votos de otros lenguajes: " << endl;

        OtroLenguaje* aux = votos[actividad-1][i].otroLenguaje;
        while(aux){
            cout<<aux->nombre<<" cantidad de votos: "<<aux->cantidadDeVotos<<endl;
            aux = aux->sig;
        }
        
    }
}