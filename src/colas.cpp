#include <iostream>

using namespace std;

// Estructura de un nodo
struct nodo {
    int nro;
    struct nodo *sgte;
};

// Estructura para la cola, con punteros al frente y al final
struct cola {
    nodo *delante;
    nodo *atras;
};

// Funcion para encolar (agregar un elemento al final)
void encolar(struct cola &q, int valor) {
    struct nodo *aux = new(struct nodo);
    aux->nro = valor;
    aux->sgte = NULL;
    if (q.delante == NULL)
        q.delante = aux; // Si la cola esta vacia, el nuevo nodo es el primero
    else
        (q.atras)->sgte = aux; // El ultimo nodo ahora apunta al nuevo
    q.atras = aux; // El nuevo nodo es el final de la cola
}

// Funcion para desencolar (eliminar el elemento del frente)
void desencolar(struct cola &q) {
    int num;
    struct nodo *aux;
    aux = q.delante;
    num = aux->nro;
    q.delante = (q.delante)->sgte; // El nuevo frente es el siguiente nodo
    cout << " << desencolado >> " << num << endl;
    delete(aux); // Libera la memoria del nodo que se desencolo
}

// Funcion para mostrar la cola
void muestraCola(struct cola q) {
    struct nodo *aux;
    aux = q.delante;
    while (aux != NULL) {
        cout << aux->nro << "\t";
        aux = aux->sgte;
    }
}

int main() {
    struct cola q;
    q.delante = NULL;
    q.atras = NULL;
    encolar(q, 1);
    encolar(q, 2);
    encolar(q, 3);

    cout << "Cola: ";
    muestraCola(q);
    cout << endl;

    desencolar(q);
    desencolar(q);

    cout << "Cola despues de desencolar: ";
    muestraCola(q);
    cout << endl;

    return 0;
}