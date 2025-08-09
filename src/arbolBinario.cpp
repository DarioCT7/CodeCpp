#include <iostream>
#include <conio.h> // Para la funcion getch() en Windows

using namespace std;

// Define la estructura de un nodo para el arbol
struct Nodo {
    int dato;      // El valor del nodo
    Nodo *izq;     // Puntero al subarbol izquierdo
    Nodo *der;     // Puntero al subarbol derecho
};

// Declaracion de funciones
Nodo *crearNodo(int);
void insertar(Nodo *&, int);
void mostrarArbol(Nodo *, int);
bool buscar(Nodo *, int);
int minimo(Nodo *);
int maximo(Nodo *);
void preOrden(Nodo *);
void inOrden(Nodo *);
void postOrden(Nodo *);

int main() {
    Nodo *arbol = NULL; // Puntero a la raiz del arbol, inicialmente nulo
    int dato;

    cout << "Ingrese 5 numeros para el arbol binario:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "Numero " << i + 1 << ": ";
        cin >> dato;
        insertar(arbol, dato); // Inserta el dato en el arbol
    }
    cout << endl;

    cout << "Mostrando la estructura del arbol:" << endl;
    mostrarArbol(arbol, 0); // Muestra el arbol
    cout << endl;

    int valor_buscar;
    cout << "Ingrese un valor a buscar: ";
    cin >> valor_buscar;
    if (buscar(arbol, valor_buscar)) {
        cout << "El valor " << valor_buscar << " se encuentra en el arbol." << endl;
    } else {
        cout << "El valor " << valor_buscar << " NO se encuentra en el arbol." << endl;
    }
    cout << endl;

    cout << "El valor minimo en el arbol es: " << minimo(arbol) << endl;
    cout << "El valor maximo en el arbol es: " << maximo(arbol) << endl;
    cout << endl;

    // Diferentes recorridos del arbol
    cout << "Recorrido Pre-Orden: ";
    preOrden(arbol); // Raiz, Izquierda, Derecha
    cout << endl;

    cout << "Recorrido In-Orden: ";
    inOrden(arbol);  // Izquierda, Raiz, Derecha (Ordenado)
    cout << endl;

    cout << "Recorrido Post-Orden: ";
    postOrden(arbol); // Izquierda, Derecha, Raiz
    cout << endl;

    return 0;
}

// Implementación de funciones
Nodo *crearNodo(int n) {
    Nodo *nuevo_nodo = new Nodo(); // Reserva memoria para un nuevo nodo
    nuevo_nodo->dato = n;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->der = NULL;
    return nuevo_nodo;
}

void insertar(Nodo *&arbol, int n) {
    if (arbol == NULL) { // Si el arbol esta vacio, el nuevo nodo es la raiz
        Nodo *nuevo_nodo = crearNodo(n);
        arbol = nuevo_nodo;
    } else {
        if (n < arbol->dato) { // Si el dato es menor, se inserta en el subarbol izquierdo
            insertar(arbol->izq, n);
        } else { // Si es mayor o igual, se inserta en el subarbol derecho
            insertar(arbol->der, n);
        }
    }
}

void mostrarArbol(Nodo *arbol, int cont) {
    if (arbol == NULL) {
        return;
    } else {
        mostrarArbol(arbol->der, cont + 1); // Recorre el subarbol derecho
        for (int i = 0; i < cont; i++) {
            cout << "   ";
        }
        cout << arbol->dato << endl; // Muestra el dato de la raiz
        mostrarArbol(arbol->izq, cont + 1); // Recorre el subarbol izquierdo
    }
}

bool buscar(Nodo *arbol, int n) {
    if (arbol == NULL) { // No se encontro el valor
        return false;
    } else if (arbol->dato == n) { // Se encontro el valor
        return true;
    } else if (n < arbol->dato) { // Busca en el subarbol izquierdo
        return buscar(arbol->izq, n);
    } else { // Busca en el subarbol derecho
        return buscar(arbol->der, n);
    }
}

int minimo(Nodo *arbol) {
    if (arbol == NULL) {
        cout << "El arbol esta vacio" << endl;
        return -1;
    }
    // El valor minimo esta en el nodo mas a la izquierda
    while (arbol->izq != NULL) {
        arbol = arbol->izq;
    }
    return arbol->dato;
}

int maximo(Nodo *arbol) {
    if (arbol == NULL) {
        cout << "El arbol esta vacio" << endl;
        return -1;
    }
    // El valor maximo esta en el nodo mas a la derecha
    while (arbol->der != NULL) {
        arbol = arbol->der;
    }
    return arbol->dato;
}

void preOrden(Nodo *arbol) {
    if (arbol == NULL) {
        return;
    } else {
        cout << arbol->dato << " "; // Raiz
        preOrden(arbol->izq); // Izquierda
        preOrden(arbol->der); // Derecha
    }
}

void inOrden(Nodo *arbol) {
    if (arbol == NULL) {
        return;
    } else {
        inOrden(arbol->izq);  // Izquierda
        cout << arbol->dato << " "; // Raiz
        inOrden(arbol->der);  // Derecha
    }
}

void postOrden(Nodo *arbol) {
    if (arbol == NULL) {
        return;
    } else {
        postOrden(arbol->izq);  // Izquierda
        postOrden(arbol->der);  // Derecha
        cout << arbol->dato << " "; // Raiz
    }
}