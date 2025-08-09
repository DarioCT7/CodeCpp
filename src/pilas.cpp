#include <iostream>

using namespace std;

// Estructura de un nodo para la pila
struct nodo {
    int nro;
    struct nodo *sgte;
};

typedef nodo* ptrPila; // Alias para un puntero a nodo

// Funcion para apilar (push), inserta un elemento al inicio de la lista enlazada
void push(ptrPila &p, int valor) {
    ptrPila aux = new(struct nodo);
    aux->nro = valor;
    aux->sgte = p;
    p = aux;
    cout << " << apilado >> " << valor << endl;
}

// Funcion para desapilar (pop), elimina el elemento del inicio
void pop(ptrPila &p) {
    if (p == NULL) { // Si la pila esta vacia
        cout << "La pila esta vacia." << endl;
        return;
    }
    ptrPila aux;
    aux = p;
    cout << " << desapilado >> " << aux->nro << endl;
    p = aux->sgte; // La pila ahora apunta al siguiente nodo
    delete(aux); // Libera la memoria del nodo que se desapilo
}

int main() {
    ptrPila p = NULL; // Pila inicializada como vacia
    push(p, 3);
    push(p, 5);
    push(p, 8);

    pop(p); // Salida: << desapilado >> 8
    pop(p); // Salida: << desapilado >> 5
    pop(p); // Salida: << desapilado >> 3
    pop(p); // Intentar desapilar de una pila vacia
    return 0;
}