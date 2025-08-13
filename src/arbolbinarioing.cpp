#include <iostream>
#include <cstdlib>  // Para rand()
using namespace std;

// Estructura de un nodo del árbol binario
struct nodo {
    int nro;               // Valor del nodo
    struct nodo *izq, *der; // Punteros a los hijos izquierdo y derecho
};

// Definimos un tipo ABB como puntero a nodo
typedef struct nodo *ABB;

// Función para crear un nuevo nodo con valor x
ABB crearNodo(int x) {
    ABB nuevoNodo = new(struct nodo);  // Reservar memoria
    nuevoNodo->nro = x;                // Asignar valor
    nuevoNodo->izq = NULL;             // Inicializar hijo izquierdo
    nuevoNodo->der = NULL;             // Inicializar hijo derecho
    return nuevoNodo;
}

// Función para insertar un valor en el árbol
void insertar(ABB &arbol, int x) {
    if (arbol == NULL)
        arbol = crearNodo(x);          // Si el árbol está vacío, crear raíz
    else if (x < arbol->nro)
        insertar(arbol->izq, x);       // Insertar en subárbol izquierdo
    else if (x > arbol->nro)
        insertar(arbol->der, x);       // Insertar en subárbol derecho
}

// Recorrido en preorden: raíz → izquierda → derecha
void preOrden(ABB arbol) {
    if (arbol != NULL) {
        cout << arbol->nro << " ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

// Recorrido en orden: izquierda → raíz → derecha
void enOrden(ABB arbol) {
    if (arbol != NULL) {
        enOrden(arbol->izq);
        cout << arbol->nro << " ";
        enOrden(arbol->der);
    }
}

// Recorrido en postorden: izquierda → derecha → raíz
void postOrden(ABB arbol) {
    if (arbol != NULL) {
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout << arbol->nro << " ";
    }
}

// Visualiza el árbol en forma jerárquica (rotado 90°)
void verArbol(ABB arbol, int n) {
    if (arbol == NULL)
        return;

    verArbol(arbol->der, n + 1);  // Mostrar subárbol derecho

    for (int i = 0; i < n; i++)   // Espaciado según nivel
        cout << "   ";

    cout << arbol->nro << endl;   // Mostrar nodo actual

    verArbol(arbol->izq, n + 1);  // Mostrar subárbol izquierdo
}

// Función principal
int main() {
    ABB arbol = NULL;  // Inicializar árbol vacío

    int n;  // Número de nodos a insertar
    int x;  // Valor de cada nodo

    cout << "\n\t\t  ..[ ARBOL BINARIO DE BUSQUEDA ]..  \n\n";
    cout << " Numero de nodos del arbol:  ";
    cin >> n;
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << " Numero del nodo " << i + 1 << ": ";
        cin >> x;
        x = rand() % 100;         // Generar número aleatorio entre 0 y 99
        insertar(arbol, x);       // Insertar en el árbol
    }

    // Mostrar árbol visualmente
    cout << "\n Mostrando ABB \n\n";
    verArbol(arbol, 0);

    // Mostrar recorridos del árbol
    cout << "\n Recorridos del ABB";
    cout << "\n\n En orden   :  ";   enOrden(arbol);
    cout << "\n\n Pre Orden  :  ";   preOrden(arbol);
    cout << "\n\n Post Orden :  ";   postOrden(arbol);
    cout << endl << endl;

    return 0;
}

// DEBER : cantidad de números a ingresar debe ser mayor a 6...
//     Task                           group
//     verArbol( arbol, 0);             1    5    9
//     enOrden(arbol);                  2    6    ...
//     preOrden(arbol);                 3    7
//     postOrden(arbol);                4    8
