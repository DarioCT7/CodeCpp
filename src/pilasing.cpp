#include <iostream>
using namespace std;

// Estructura de un nodo de la pila
struct nodo {
    int nro;             // Valor que guarda el nodo
    struct nodo *sgte;   // Puntero al siguiente nodo
};

// Definimos un tipo de dato puntero a nodo, llamado ptrPila
typedef nodo *ptrPila;

// Función para apilar (push): insertar un elemento al inicio
void push(ptrPila &p, int valor) {
    ptrPila aux = new(struct nodo);  // Crear nuevo nodo
    aux->nro = valor;                // Asignar valor
    aux->sgte = p;                   // Enlazar al nodo anterior (top actual)
    p = aux;                         // Actualizar el tope de la pila
    cout << " << apilado >> " << endl;
}

// Función para desapilar (pop): eliminar el elemento del tope
void pop(ptrPila &p) {
    ptrPila aux;
    aux = p;                         // Apuntar al tope
    cout << " << desapilado >> " << aux->nro << endl;
    p = aux->sgte;                   // Mover el tope al siguiente nodo
    delete(aux);                     // Liberar memoria del nodo eliminado
}

// Función para mostrar todos los elementos de la pila
void mostrar_pila(ptrPila p) {
    ptrPila aux;
    aux = p;                         // Apuntar al tope

    while (aux != NULL) {           // Mientras haya nodos
        cout << "\t" << aux->nro << endl;  // Mostrar valor
        aux = aux->sgte;            // Avanzar al siguiente nodo
    }
}

// Función para destruir toda la pila
void destruir_pila(ptrPila &p) {
    ptrPila aux;

    while (p != NULL) {             // Mientras haya nodos
        aux = p;                    // Apuntar al tope
        p = aux->sgte;              // Mover el tope
        cout << "despachando: " << aux->nro << "\t";
        delete(aux);                // Eliminar nodo
    }

    cout << "\n\n\t\t Pila despachada...\n\n";
}

// Función que muestra el menú y devuelve la opción elegida
int menu() {
    int op;
    cout << endl;
    cout << " 1. APILAR                                " << endl;
    cout << " 2. DESAPILAR                             " << endl;
    cout << " 3. ELIMINAR PILA                         " << endl;
    cout << " 4. SALIR                                 " << endl;
    cout << "\n INGRESE OPCION: ";
    cin >> op;

    if (op == 4) exit(0);           // Salir si se elige opción 4
    return op;
}

// Función principal
int main() {
    ptrPila p = NULL;               // Crear pila vacía
    int valor;

    do {
        cout << "\n\n    FUNCIONALIDAD PILA : \n";
        if (p == NULL)
            cout << "\t << vacia >> ";     // Mensaje si la pila está vacía
        else
            mostrar_pila(p);               // Mostrar pila si tiene elementos

        switch (menu()) {                  // Ejecutar según opción del menú
            case 1:
                cout << "\n NUMERO A APILAR: ";
                cin >> valor;              // Leer valor
                push(p, valor);            // Apilar
                break;

            case 2:
                pop(p);                    // Desapilar
                break;

            case 3:
                destruir_pila(p);          // Eliminar toda la pila
                break;
        }
    } while (true);                        // Repetir indefinidamente

    return 0;
}
