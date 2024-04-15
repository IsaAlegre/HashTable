#include <stdio.h>
#include <stdlib.h> //Es la biblioteca que permite la utilización de funciones como malloc.


// Estructura para almacenar los datos de una persona. 
typedef struct {
    char nombre_apellido[100];
    int dni;
    char sexo; //Sólo se define en ´F´ o ´M´.
    float estatura;
    float peso;
} Persona;


// Estructura para un nodo de la lista enlazada.
typedef struct {
    Persona persona;
    struct Nodo* siguiente;
} Nodo;


// Función para insertar un nuevo nodo al inicio de la lista.


Nodo* insertar(Nodo* cabeza, Persona persona) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo)); //malloc se utiliza para reservar el espacio de memoria en que se guarda el próximo nodo.
    nuevoNodo->persona = persona; //Se copia la información de la nueva persona al nodo.
    nuevoNodo->siguiente = cabeza; //Se le está diciendo al nuevo nodo que a lo apunta es al nodo cabeza. El nuevo nodo ahora se coloca al principio de la lista, y su siguiente apunta al antiguo primer nodo.
    return nuevoNodo;
}


// Función para buscar una persona por su DNI en la tabla hash.
void buscarPorDNI(Nodo* tablaHash[], int clave_hash, int dniBusqueda) {
    // Buscar en la lista enlazada correspondiente, ejemplo la 2.
    Nodo* actual = tablaHash[clave_hash]; //Se utiliza el nodo actual para posicionarse al comienzo de la lista de dicha posición de la tabla.
    while (actual != NULL) { //Se recorre todos los registros de la lista siempre y cuando estos no estén vacíos.
        if (actual->persona.dni == dniBusqueda) {
            //Si encuentra una coincidencia realiza lo sig.
            printf("Registro encontrado:\n");
            printf("Nombre y apellido: %s\n", actual->persona.nombre_apellido);
            printf("DNI: %d\n", actual->persona.dni);
            printf("Sexo: %c\n", actual->persona.sexo);
            printf("Estatura: %f\n cm", actual->persona.estatura);
            printf("Peso: %f\n kg", actual->persona.peso);
            return 0;
        }
        actual = actual->siguiente; //  Si en el registro que revisó no estaba el DNI, el nodo actual se convertiría en el nodo al que estaba apuntando anteriormente y se van a buscar en la información de las sig. personas.
    }


    // Si llega aquí, la persona no fue encontrada y se devuelve la información.
    printf("Registro no encontrado para el DNI %d\n", dniBusqueda);
}


// Función para imprimir todos los registros en la tabla hash. 
void imprimirRegistros(Nodo* tablaHash[], int tamanoTabla) {
    int i = 0;
    while (i < tamanoTabla) { //Se recorre cada posición de la tabla, del 0 al 14.
        Nodo* actual = tablaHash[i]; //Se comienza en el nodo cabeza de la lista de la posición inicial, que se denomina nodo actual.
        while (actual != NULL) {
            printf("Nombre: %s, DNI: %d, Sexo: %c, Estatura: %f, Peso: %f\n",  actual->persona.nombre_apellido, actual->persona.dni, actual->persona.sexo,   actual->persona.estatura, actual->persona.peso); //Se van a imprimir los datos de la persona del nodo en la que se mantiene posicionado en cada ciclo del bucle. Con cada repetición del bucle, los datos de las personas cambian a los del nodo siguiente.
            actual = actual->siguiente;
        }
        ++i; //Una vez se llega al final de la lista de la posición en la que se estaba, se agrega un valor a la posición y se comienza a recorrer la lista de la siguiente.
    }
}


int main() {
    int i = 0;
    const int tamanoTabla = 15; //se define el tamaño de la tabla como variable global
    int clave_hash;
    int dniBusqueda;


    // Arreglo de punteros a nodos (tabla hash)
    Nodo* tablaHash[tamanoTabla];


    while (i <= 1000) {
        Persona nuevaPersona;
        //Se generan datos ficticios a base de un bucle, los cuales van a ser valores cualquiera para poder realizar la simulación de los registros reales y únicos de personas.
        sprintf(nuevaPersona.nombre_apellido, "Persona%d", i);
        nuevaPersona.dni = 10000000 + i;  // DNI único para cada registro que se le va a asignar a cada persona nueva creada.
        nuevaPersona.sexo = 'F';
        nuevaPersona.estatura = 170.0 + 0.01 * i;
        nuevaPersona.peso = 55.0 + i * 0.02; //Cálculos para que en cada persona varíe en datos.


        // Calcular la clave hash a base de la utilización del cálculo de módulo. 
        int claveHash = nuevaPersona.dni % tamanoTabla;


        // Dependiendo de la clave hash que  se obtenga con cada persona, la posición de la tabla hash y la lista a la que va a estar enlazada va a cambiar.
        tablaHash[claveHash] = insertar(tablaHash[claveHash], nuevaPersona); //se calcula en dónde va a guardarse con la función de insertar.


        ++i;
    }


    // Imprimir todos los registros antes de buscar como muestra solamente, para así tener una muestra.
    printf("Todos los registros:\n");
    imprimirRegistros(tablaHash, tamanoTabla);


    // Pedir al usuario que ingrese un DNI para buscar
    printf("Ingrese el DNI a buscar: ");
    scanf("%d", &dniBusqueda);//lee el DNI ingresado y lo almacena en ´dniBusqueda´


    clave_hash = dniBusqueda % tamanoTabla; //calcula la clave hash para el DNI ingresado


    // Buscar la persona por DNI al utilizar la función.
    buscarPorDNI(tablaHash, clave_hash, dniBusqueda);


    return 0;
}
