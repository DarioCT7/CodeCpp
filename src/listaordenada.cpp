#include <iostream>
#include <stdlib.h>     // Para rand() y system()
using namespace std;

// Estructura de un nodo de la lista
struct nodo {
    int nro;             // Valor numérico del nodo
    struct nodo *sgte;   // Puntero al siguiente nodo
};

// Definimos un tipo de dato puntero a nodo
typedef struct nodo *Tlista;

// Punteros globales al inicio y fin de la lista
Tlista inicio, fin;

// Función para generar una lista con n números aleatorios
void generarLista(Tlista &inicio, Tlista &fin, int n) {
    Tlista q;

    for (int i = 0; i < n; i++) {
        q = new(struct nodo);           // Crear nuevo nodo
        q->nro = rand() % 50;           // Asignar número aleatorio entre 0 y 49

        if (inicio == NULL) {           // Si la lista está vacía
            q->sgte = inicio;
            inicio = q;
            fin = q;
        } else {                        // Insertar al final
            q->sgte = fin->sgte;        // q->sgte = NULL
            fin->sgte = q;              // Enlazar nuevo nodo al final
            fin = q;                    // Actualizar puntero al último nodo
        }
    }

    cout << "\n\n\tLista de numeros generados... " << endl;
}

// Función para mostrar todos los elementos de la lista
void mostrarLista(Tlista inicio) {
    while (inicio != NULL) {
        cout << "  " << inicio->nro;    // Mostrar valor
        inicio = inicio->sgte;          // Avanzar al siguiente nodo
    }
}

// Función para ordenar la lista usando el algoritmo de burbuja
void ordenarLista(Tlista lista) {
    Tlista actual, siguiente;
    int t;

    actual = lista;

    while (actual->sgte != NULL) {      // Recorrer la lista
        siguiente = actual->sgte;

        while (siguiente != NULL) {     // Comparar con los siguientes nodos
            if (actual->nro > siguiente->nro) {
                // Intercambiar valores si están en orden incorrecto
                t = siguiente->nro;
                siguiente->nro = actual->nro;
                actual->nro = t;
            }
            siguiente = siguiente->sgte;
        }

        actual = actual->sgte;
        siguiente = actual->sgte;       // Reiniciar siguiente para próxima pasada
    }

    cout << "\n\n\tLista ordenada..." << endl;
}

// Función para mostrar el menú
void menu() {
    cout << "\n\t\tORDENAMIENTO BURBUJA EN LISTA ENLAZADA SIMPLE\n\n";
    cout << " 1. GENERAR NUMEROS                  " << endl;
    cout << " 2. MOSTRAR NUMEROS                  " << endl;
    cout << " 3. ORDENAR NUMEROS                  " << endl;
    cout << " 4. SALIR                            " << endl;
    cout << "\n INGRESE OPCION: ";
}

// Función principal
int main() {
    inicio = NULL;   // Inicializar lista vacía
    fin = NULL;

    int op;          // Opción del menú
    int num;         // Cantidad de números a generar

    do {
        menu();      // Mostrar menú
        cin >> op;   // Leer opción

        switch (op) {
            case 1:
                cout << "\n Cantidad de numeros: ";
                cin >> num;
                generarLista(inicio, fin, num);  // Generar lista
                break;

            case 2:
                cout << "\n\n LISTA:\n\n";
                mostrarLista(inicio);            // Mostrar lista
                break;

            case 3:
                ordenarLista(inicio);            // Ordenar lista
                break;
        }

        cout << endl << endl;
    } while (op != 4);  // Repetir hasta que el usuario elija salir

    return 0;
}
