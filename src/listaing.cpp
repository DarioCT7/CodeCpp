#include <iostream>
#include <stdlib.h>
#include <windows.h>  // Para usar SetConsoleOutputCP en Windows
using namespace std;

// Estructura de un nodo de la lista
struct nodo {
    int nro;             // Dato que guarda el nodo
    struct nodo *sgte;   // Puntero al siguiente nodo
};

// Definimos un tipo de dato puntero a nodo
typedef struct nodo *Tlista;

// Inserta un nodo al inicio de la lista
void insertarInicio(Tlista &lista, int valor) {
    Tlista q = new(struct nodo);   // Crear nuevo nodo
    q->nro = valor;                // Asignar valor
    q->sgte = lista;               // Enlazar al anterior primer nodo
    lista = q;                     // Actualizar el inicio de la lista
}

// Inserta un nodo al final de la lista
void insertarFinal(Tlista &lista, int valor) {
    Tlista t, q = new(struct nodo);  // Crear nuevo nodo
    q->nro = valor;
    q->sgte = NULL;

    if (lista == NULL)               // Si la lista está vacía
        lista = q;                   // El nuevo nodo es el primero
    else {
        t = lista;
        while (t->sgte != NULL)      // Recorrer hasta el último nodo
            t = t->sgte;
        t->sgte = q;                 // Enlazar el nuevo nodo al final
    }
}

// Muestra opciones para insertar antes o después de una posición
int insertarAntesDespues() {
    int _op, band;
    cout << endl;
    cout << "\t 1. Antes de la posicion           " << endl;
    cout << "\t 2. Despues de la posicion         " << endl;
    cout << "\n\t Opcion : "; cin >> _op;

    if (_op == 1)
        band = -1;  // Insertar antes
    else
        band = 0;   // Insertar después

    return band;
}

// Inserta un nodo en una posición específica
void insertarElemento(Tlista &lista, int valor, int pos) {
    Tlista q, t;
    int i;
    q = new(struct nodo);  // Crear nuevo nodo
    q->nro = valor;

    if (pos == 1) {         // Insertar en la primera posición
        q->sgte = lista;
        lista = q;
    } else {
        int x = insertarAntesDespues();  // Determinar si antes o después
        t = lista;
        for (i = 1; t != NULL; i++) {
            if (i == pos + x) {          // Posición encontrada
                q->sgte = t->sgte;
                t->sgte = q;
                return;
            }
            t = t->sgte;
        }
        cout << "   Error...Posicion no encontrada..!" << endl;
    }
}

// Busca un elemento en la lista
void buscarElemento(Tlista lista, int valor) {
    Tlista q = lista;
    int i = 1, band = 0;

    while (q != NULL) {
        if (q->nro == valor) {
            cout << endl << " Encontrada en posicion " << i << endl;
            band = 1;
        }
        q = q->sgte;
        i++;
    }

    if (band == 0)
        cout << "\n\n Numero no encontrado..!" << endl;
}

// Muestra todos los elementos de la lista con formato visual
void reportarLista(Tlista lista) {
    int i = 0;
    SetConsoleOutputCP(CP_UTF8);  // Establece salida UTF-8 para caracteres especiales

    while (lista != NULL) {
        cout << "╔═══════╗" << endl
             << "║   " << lista->nro << "   ║   " << ++i << endl
             << "╚═══════╝" << endl
             << "    ║    " << endl;
        lista = lista->sgte;
    }
}

// Elimina el primer nodo con el valor especificado
void eliminarElemento(Tlista &lista, int valor) {
    Tlista p, ant;
    p = lista;

    if (lista != NULL) {
        while (p != NULL) {
            if (p->nro == valor) {
                if (p == lista)           // Si es el primer nodo
                    lista = lista->sgte;
                else
                    ant->sgte = p->sgte;  // Enlazar el anterior con el siguiente

                delete(p);                // Liberar memoria
                return;
            }
            ant = p;
            p = p->sgte;
        }
    } else
        cout << " Lista vacia..!";
}

// Elimina todos los nodos con el valor especificado
void eliminaRepetidos(Tlista &lista, int valor) {
    Tlista q, ant;
    q = lista;
    ant = lista;

    while (q != NULL) {
        if (q->nro == valor) {
            if (q == lista) {             // Si es el primer nodo
                lista = lista->sgte;
                delete(q);
                q = lista;
            } else {
                ant->sgte = q->sgte;
                delete(q);
                q = ant->sgte;
            }
        } else {
            ant = q;
            q = q->sgte;
        }
    }

    cout << "\n\n Valores eliminados..!" << endl;
}

// Muestra el menú y devuelve la opción elegida
int menu() {
    int op;
    cout << "\n\t\tLISTA ENLAZADA SIMPLE\n\n";
    cout << " 1. INSERTAR AL INICIO               " << endl;
    cout << " 2. INSERTAR AL FINAL                " << endl;
    cout << " 3. INSERTAR EN UNA POSICION         " << endl;
    cout << " 4. REPORTAR LISTA                   " << endl;
    cout << " 5. BUSCAR ELEMENTO                  " << endl;
    cout << " 6. ELIMINAR ELEMENTO 'V'            " << endl;
    cout << " 7. ELIMINAR ELEMENTOS CON VALOR 'V' " << endl;
    cout << " 8. SALIR                            " << endl;

    cout << "\n INGRESE OPCION: ";
    cin >> op;

    if (op < 1 || op > 8) {
        cout << "\n\n OPCION NO VALIDA..!" << endl;
        system("pause");
        return menu();  // Volver a mostrar el menú si la opción es inválida
    }

    return op;
}

// Función principal
int main() {
    Tlista lista = NULL;  // Inicializar lista vacía
    int _dato;            // Valor a insertar, buscar o eliminar
    int pos;              // Posición para insertar

    do {
        switch (menu()) {
            case 1:
                cout << "\n NUMERO A INSERTAR: "; cin >> _dato;
                insertarInicio(lista, _dato);
                break;

            case 2:
                cout << "\n NUMERO A INSERTAR: "; cin >> _dato;
                insertarFinal(lista, _dato);
                break;

            case 3:
                cout << "\n NUMERO A INSERTAR: "; cin >> _dato;
                cout << " Posicion : "; cin >> pos;
                insertarElemento(lista, _dato, pos);
                break;

            case 4:
                cout << "\n\n MOSTRANDO LISTA\n\n";
                reportarLista(lista);
                break;

            case 5:
                cout << "\n Valor a buscar: "; cin >> _dato;
                buscarElemento(lista, _dato);
                break;

            case 6:
                cout << "\n Valor a eliminar: "; cin >> _dato;
                eliminarElemento(lista, _dato);
                break;

            case 7:
                cout << "\n Valor repetido a eliminar: "; cin >> _dato;
                eliminaRepetidos(lista, _dato);
                break;
        }

        cout << endl << endl;
    } while (true);  // Repetir indefinidamente

    return 0;
}
