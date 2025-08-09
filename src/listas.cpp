#include <iostream>

using namespace std;

// Define la estructura para un nodo de la lista
struct nodo {
    int nro;               // El dato que contiene el nodo
    struct nodo *sgte;     // Puntero al siguiente nodo en la lista
};

typedef struct nodo* Tlista; // Tlista es un alias para un puntero a un nodo

// Funcion para insertar un nodo al inicio de la lista
void insertarInicio(Tlista &lista, int valor) {
    Tlista aux;
    aux = new(struct nodo); // Crea un nuevo nodo
    aux->nro = valor;
    aux->sgte = lista;      // El nuevo nodo apunta al inicio actual
    lista = aux;            // El nuevo nodo se convierte en el inicio de la lista
}

// Funcion para insertar un nodo al final de la lista
void insertarFinal(Tlista &lista, int valor) {
    Tlista t, q = new(struct nodo);
    q->nro = valor;
    q->sgte = NULL;
    if (lista == NULL)
        lista = q; // Si la lista esta vacia, el nuevo nodo es el inicio
    else {
        t = lista;
        while (t->sgte != NULL) {
            t = t->sgte; // Recorre la lista hasta el ultimo nodo
        }
        t->sgte = q; // El ultimo nodo ahora apunta al nuevo nodo
    }
}

// Funcion para mostrar todos los elementos de la lista
void mostrarLista(Tlista lista) {
    Tlista aux = lista;
    while (aux != NULL) {
        cout << aux->nro << " -> ";
        aux = aux->sgte; // Avanza al siguiente nodo
    }
    cout << "NULL" << endl; // Indica el final de la lista
}

int main() {
    Tlista lista = NULL; // Inicializa la lista como vacia

    insertarInicio(lista, 1);
    insertarInicio(lista, 0);
    mostrarLista(lista); // Salida: 0 -> 1 -> NULL

    insertarFinal(lista, 2);
    mostrarLista(lista); // Salida: 0 -> 1 -> 2 -> NULL

    return 0;
}