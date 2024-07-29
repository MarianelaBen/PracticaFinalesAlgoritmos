#include <iostream>

using namespace std;

struct Empleado{
    int nLegajo;
    char nombres[50];
    char apellidos[50];
    long dni;
    int edad;
    int objetivos_logrados;
    bool recibeBono = false;
};

struct ExEmpleado{
    int nLegajo;
    int fechaBaja;
};

struct Nodo{
    ExEmpleado exEmpleado;
    Nodo* ant;
    Nodo* sig;
};

void pagarBono(char[], Nodo*);
Nodo* buscarBaja(Nodo*, int);
void agregarBajas(Nodo*&, int, int);

int main(){

}

void pagarBono(char arch_empleados[], Nodo* listaBajas){
    FILE* archivo = fopen(arch_empleados, "r+b");
    Empleado empleado;

    if(archivo){
        while(fread(&empleado, sizeof(Empleado), 1, archivo)){
            if(empleado.objetivos_logrados >= 5 && !buscarBaja(listaBajas, empleado.nLegajo)){
                empleado.recibeBono = true;
                fseek(archivo, -sizeof(Empleado), SEEK_CUR); // Mover el puntero atrás antes de escribir
                fwrite(&empleado, sizeof(Empleado), 1, archivo);
            }
        }
    }else{
        cout<<"No se ha podido abrir el archivo."<<endl;
    }
}

void agregarBaja(Nodo*& listaBajas, int nLegajo, int fechaBaja) {
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->exEmpleado.nLegajo = nLegajo;
    nuevoNodo->exEmpleado.fechaBaja = fechaBaja;
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;

    if(!listaBajas || listaBajas->exEmpleado.nLegajo > nLegajo){
        nuevoNodo->sig = listaBajas;
        if (listaBajas) {
            listaBajas->ant = nuevoNodo;
        }
        listaBajas = nuevoNodo;
    }else{
        Nodo* aux = listaBajas;
        while(aux->sig && aux->sig->exEmpleado.nLegajo < nuevoNodo->exEmpleado.nLegajo){
            aux = aux->sig;
        }
        nuevoNodo->sig = aux->sig;
        if(aux->sig){
            nuevoNodo->sig->ant = nuevoNodo;
        }
        aux->sig = nuevoNodo;
        nuevoNodo->ant = aux;
            
    }
}

// Punto 2

void func_ej_1(int *x, int pos, int valor){ //int* x es lo mismo que int x[]
    *(x+pos) = valor;//inserta un valor en la posicion x+pos del vector
    return;
}

int main(){
    int *p = NULL; //puntero p lo iguala a null
    int x[] = {21, 22, 23, 24, 25};
    p = x; //puntero p lo iguala al vector x
    func_ej_1(p, 2, 500); //inserta 500 en la posicion 2 del vector
    func_ej_1(p, 4, 500); // inserta 500 en la posicion 4 del vector
    for(int i = 0; i<5; i++){
        cout<<p[i]<<" ";
    }
    return 0;
}
/*
PUNTO 2
a) la salida del programa sera:
    21
    22
    500
    24
    500

b) si, es correcto que no haya una instrucción delete antes de finalizar, ya que no se reservó memoria
en este caso.
*/
//PUNTO 3
struct Nodo2{
    int info;
    Nodo2* sgte;
};

int main(){
    Nodo2 *p = NULL;
    Nodo2 *aux;
    p = new Nodo2();
    p->info = 15; //le asigna 15 al primer nodo p
    p->sgte = new Nodo2();
    p->sgte->info = 20; //le asigna 20 al segundo nodo de p
    p->sgte->sgte = NULL;
    aux = p->sgte; //aux es igual al segundo nodo de p (info = 20)
    p->sgte = new Nodo2();
    p->sgte->info = 90; //le asigna 90 al segundo nodo de p
    p->sgte->sgte = aux; //le asigna aux al tercer nodo de p (info = 20)
    aux = p; //aux apunta al primer nodo de p
    while(aux){
        cout<<aux->info<<";";
        aux = aux->sgte;
    }

    return 0;
}

/*
La salida por pantalla será:
    15;90;20;

PUNTO 4

FILE* f;
int y, z;
f = fopen("unarchivo", "wb");
int vec[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
fwrite(vec, sizeof(int), 10, f);
fclose(f);
f = fopen("unarchivo", "rb+");
fread(&y, sizeof(int), 1, f);
fread(&y, sizeof(int), 1, f);
fread(&y, sizeof(int), 1, f); 
y += 1000;
fseek(f, (-1)*sizeof(int), SEEK_CUR);
fwrite(&y, sizeof(int), 1, f);
fseek(f, 0, SEEK_SET);
while(fread(&z, sizeof(int), 1, f)){
    cout<<z<<";";
}
fclose(f);


la salida por pantalla sera:
    1003;2;3;4;5;6;7;8;9;10

*/
