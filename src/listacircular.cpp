#include <iostream>
#include <stdlib.h>
using namespace std;

// Estructura de un nodo de la lista circular
struct nodo {
    int nro;             // Valor numérico del nodo
    struct nodo *sgte;   // Puntero al siguiente nodo
};

// Definimos un tipo de dato puntero a nodo circular
typedef struct nodo *TlistaC;

// Punteros globales para las listas y sus finales
TlistaC lista1, lista2, fin1, fin2;

// Muestra ambas listas circulares por separado
void mostrarListas() {
    TlistaC aux;

    // Mostrar lista 1
    aux = lista1;
    if (lista1 != NULL) {
        cout << "\n\n Lista 1 :\n\n";
        do {
            cout << "  " << aux->nro;
            aux = aux->sgte;
        } while (aux != lista1);  // Recorrer hasta volver al inicio
    } else {
        cout << "\n\n\tLista vacia...!" << endl;
    }

    // Mostrar lista 2
    aux = lista2;
    if (lista2 != NULL) {
        cout << "\n\n Lista 2 :\n\n";
        do {
            cout << "  " << aux->nro;
            aux = aux->sgte;
        } while (aux != lista2);
    } else {
        cout << "\n\n\tLista vacia...!" << endl;
    }
}

// Inserta un nodo al final de una lista circular
void insertar(TlistaC &lista, TlistaC &fin, int valor) {
    TlistaC q = new(struct nodo);  // Crear nuevo nodo
    q->nro = valor;

    if (lista == NULL) {           // Si la lista está vacía
        lista = q;
        lista->sgte = lista;       // Apunta a sí misma
        fin = q;
    } else {
        fin->sgte = q;             // Enlazar nuevo nodo al final
        q->sgte = lista;           // Cerrar el ciclo
        fin = q;                   // Actualizar puntero al último nodo
    }
}

// Permite ingresar elementos a ambas listas circulares
void ingresarListas() {
    int tam1, tam2, dato;

    cout << "\n Tamanio de lista 1 : "; cin >> tam1;
    cout << endl;

    for (int i = 0; i < tam1; i++) {
        cout << "\tElemento " << i + 1 << ": ";
        cin >> dato;
        insertar(lista1, fin1, dato);
    }

    cout << "\n Tamanio de lista 2 : "; cin >> tam2;
    cout << endl;

    for (int i = 0; i < tam2; i++) {
        cout << "\tElemento " << i + 1 << ": ";
        cin >> dato;
        insertar(lista2, fin2, dato);
    }
}

// Une las dos listas circulares en una sola estructura
void unirListas() {
    fin1->sgte = lista2;  // El último de L1 apunta al inicio de L2
    fin2->sgte = lista1;  // El último de L2 apunta al inicio de L1
    cout << "\n\n\tListas circulares L1 y L2 unidas..." << endl;
}

// Muestra la lista 1 (ahora unida con la 2 si se ejecutó unirListas)
void mostrarLista1() {
    TlistaC aux = lista1;

    if (lista1 != NULL) {
        cout << "\n\n Lista 1 :\n\n";
        do {
            cout << "  " << aux->nro;
            aux = aux->sgte;
        } while (aux != lista1);  // Recorrer hasta volver al inicio
    } else {
        cout << "\n\n\tLista vacia...!" << endl;
    }
}

// Muestra el menú de opciones
void menu() {
    cout << "\n\t\tUNIR LISTAS CIRCULARES\n\n";
    cout << " 1. INGRESAR LISTAS                  " << endl;
    cout << " 2. MOSTRAR LISTAS                   " << endl;
    cout << " 3. UNIR LISTAS                      " << endl;
    cout << " 4. MOSTRAR LISTA 1                  " << endl;
    cout << " 5. SALIR                            " << endl;
    cout << "\n INGRESE OPCION: ";
}

// Función principal
int main() {
    int op;  // Opción del menú

    do {
        menu(); cin >> op;

        switch (op) {
            case 1: ingresarListas();  break;     // Cargar listas
            case 2: mostrarListas();   break;     // Mostrar ambas listas
            case 3: unirListas();      break;     // Unir listas
            case 4: mostrarLista1();   break;     // Mostrar lista 1 (unida)
        }

        cout << endl << endl;
    } while (op != 5);  // Repetir hasta que el usuario elija salir

    return 0;
}
