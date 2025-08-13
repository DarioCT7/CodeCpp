#include <iostream>
using namespace std;

// Estructura de un nodo de la cola
struct nodo {
    int nro;             // Valor que guarda el nodo
    struct nodo *sgte;   // Puntero al siguiente nodo
};

// Estructura de la cola
struct cola {
    nodo *delante;       // Puntero al primer nodo (frente de la cola)
    nodo *atras;         // Puntero al último nodo (final de la cola)
};

// Función para encolar (agregar) un elemento al final de la cola
void encolar(struct cola &q, int valor) {
    struct nodo *aux = new(struct nodo); // Crear nuevo nodo
    aux->nro = valor;                     // Asignar valor
    aux->sgte = NULL;                     // El nuevo nodo no apunta a nadie

    if (q.delante == NULL)                // Si la cola está vacía
        q.delante = aux;                  // El nuevo nodo es el primero
    else
        (q.atras)->sgte = aux;            // Enlazar el nuevo nodo al final

    q.atras = aux;                        // Actualizar el puntero al último nodo
}

// Función para desencolar (quitar) el primer elemento de la cola
int desencolar(struct cola &q) {
    int num;
    struct nodo *aux;

    aux = q.delante;                      // Apuntar al primer nodo
    num = aux->nro;                       // Guardar el valor a retornar
    q.delante = (q.delante)->sgte;        // Mover el frente al siguiente nodo
    delete(aux);                          // Liberar memoria del nodo eliminado
    return num;                           // Retornar el valor eliminado
}

// Función para mostrar todos los elementos de la cola
void muestraCola(struct cola q) {
    struct nodo *aux;
    aux = q.delante;

    while (aux != NULL) {                 // Mientras haya nodos
        cout << "   " << aux->nro;        // Mostrar el valor
        aux = aux->sgte;                  // Avanzar al siguiente nodo
    }
}

// Función para vaciar completamente la cola
void vaciaCola(struct cola &q) {
    struct nodo *aux;

    while (q.delante != NULL) {           // Mientras haya nodos
        aux = q.delante;                  // Apuntar al frente
        q.delante = aux->sgte;            // Mover el frente
        delete(aux);                      // Eliminar el nodo
    }

    // Reiniciar punteros
    q.delante = NULL;
    q.atras = NULL;
}

// Función que muestra el menú y devuelve la opción elegida
int menu() {
    int op = 0;
    system("cls");                        // Limpiar pantalla
    cout << endl << "[...] COLAS          "
         << endl << "  0.  SALIR          "
         << endl << "  1.  ENCOLAR        "
         << endl << "  2.  DESENCOLAR     "
         << endl << "  3.  MOSTRAR COLA   "
         << endl << "  4.  VACIAR COLA    "
         << endl << "\n INGRESE OPCION:   ";
    cin >> op;                            // Leer opción
    return op;
}

// Función principal
int main() {
    struct cola q;                        // Crear cola
    q.delante = NULL;                     // Inicializar como vacía
    q.atras = NULL;

    int dato;                             // Valor a encolar
    int x;                                // Valor desencolado

    system("color 0b");                   // Cambiar color de consola (opcional)

    do {
        switch (menu()) {                 // Ejecutar según opción del menú
            case 0:
                exit(0);                  // Salir del programa

            case 1:
                cout << "\n NUMERO A ENCOLAR: ";
                cin >> dato;              // Leer número
                encolar(q, dato);         // Encolarlo
                cout << "\n\t\tNumero " << dato << " encolado...\n";
                break;

            case 2:
                x = desencolar(q);        // Desencolar
                cout << "\n\t\tNumero " << x << " desencolado...\n";
                break;

            case 3:
                cout << "\n MOSTRANDO COLA\n";
                if (q.delante != NULL)    // Si no está vacía
                    muestraCola(q);       // Mostrar elementos
                else
                    cout << "\n\tCola vacia...!" << endl;
                break;

            case 4:
                vaciaCola(q);             // Vaciar la cola
                cout << "\n\t\tHecho...\n";
                break;
        }

        cout << endl << endl;
        system("pause");                  // Pausar hasta que el usuario presione una tecla
    } while (true);                       // Repetir indefinidamente

    return 0;
}
