#include <iostream>
#include <cstdlib>      // Para rand()
#include <vector>       // Para almacenar recorridos
using namespace std;

// Estructura de un nodo del árbol binario
struct nodo {
    int nro;               // Valor del nodo
    struct nodo *izq, *der; // Punteros a hijos izquierdo y derecho
};

// Definimos ABB como puntero a nodo
typedef struct nodo *ABB;

// Función para crear un nuevo nodo con valor x
ABB crearNodo(int x) {
    ABB nuevoNodo = new(struct nodo);  // Reservar memoria
    nuevoNodo->nro = x;                // Asignar valor
    nuevoNodo->izq = NULL;             // Inicializar hijo izquierdo
    nuevoNodo->der = NULL;             // Inicializar hijo derecho
    return nuevoNodo;
}

// Función para insertar un valor en el árbol binario
void insertar(ABB &arbol, int x) {
    if (arbol == NULL)
        arbol = crearNodo(x);          // Si el árbol está vacío, crear raíz
    else if (x < arbol->nro)
        insertar(arbol->izq, x);       // Insertar en subárbol izquierdo
    else if (x > arbol->nro)
        insertar(arbol->der, x);       // Insertar en subárbol derecho
}

// Recorrido en orden: izquierda → raíz → derecha
void enOrden(ABB arbol, vector<int> &v) {
    if (arbol != NULL) {
        enOrden(arbol->izq, v);
        v.push_back(arbol->nro);       // Guardar valor en vector
        enOrden(arbol->der, v);
    }
}

// Recorrido en preorden: raíz → izquierda → derecha
void preOrden(ABB arbol, vector<int> &v) {
    if (arbol != NULL) {
        v.push_back(arbol->nro);
        preOrden(arbol->izq, v);
        preOrden(arbol->der, v);
    }
}

// Recorrido en postorden: izquierda → derecha → raíz
void postOrden(ABB arbol, vector<int> &v) {
    if (arbol != NULL) {
        postOrden(arbol->izq, v);
        postOrden(arbol->der, v);
        v.push_back(arbol->nro);
    }
}

// Función para mostrar un recorrido con etiqueta de grupo
void mostrarGrupo(const string &nombre, const vector<int> &v, int grupo) {
    cout << "\n " << nombre << " (Grupo " << grupo << "): ";
    for (int i = 0; i < v.size(); ++i)
        cout << "[" << v[i] << "] ";   // Mostrar cada valor entre corchetes
    cout << endl;
}

// Función principal
int main() {
    ABB arbol = NULL;  // Inicializar árbol vacío
    int n, x;          // n = cantidad de nodos, x = valor de cada nodo

    cout << "\n\t\t[ DEBER - RECORRIDOS EN ABB ]\n\n";

    // Validar que se ingresen al menos 6 nodos
    do {
        cout << " Ingrese cantidad de nodos (mínimo 6): ";
        cin >> n;
    } while (n < 6);

    cout << "\n Insertando nodos aleatorios...\n";

    // Insertar n nodos con valores aleatorios
    for (int i = 0; i < n; i++) {
        x = rand() % 100;              // Generar número aleatorio entre 0 y 99
        cout << " Nodo " << i + 1 << ": " << x << endl;
        insertar(arbol, x);            // Insertar en el árbol
    }

    // Vectores para almacenar los recorridos
    vector<int> orden, pre, post;

    // Realizar los tres recorridos
    enOrden(arbol, orden);
    preOrden(arbol, pre);
    postOrden(arbol, post);

    // Mostrar cada recorrido con su grupo asignado
    mostrarGrupo("En Orden", orden, 2);
    mostrarGrupo("Pre Orden", pre, 3);
    mostrarGrupo("Post Orden", post, 4);

    return 0;
}
