#include <iostream>
#include <stdlib.h>
#include <windows.h>
using namespace std;

// Estructura para representar un átomo con hasta dos enlaces
struct Atomo {
    string nombre;       // Nombre del átomo (ej. "O", "H")
    Atomo* enlace1 = NULL; // Primer enlace
    Atomo* enlace2 = NULL; // Segundo enlace
};

// Estructura para representar una base genética en una cadena
struct Gen {
    char base;           // Base genética: A, T, C, G
    Gen* siguiente;      // Puntero al siguiente gen
};

// Estructura para representar un nodo con dos números y dos enlaces
struct NodoNum {
    int num1;
    int num2;
    NodoNum* izq;        // Enlace izquierdo
    NodoNum* der;        // Enlace derecho
};

// Función para crear y enlazar 10 nodos con lógica condicional
void crearNodosAleatorios() {
    NodoNum* inicio = nullptr;  // Primer nodo
    NodoNum* actual = nullptr;  // Nodo actual para enlazar

    for (int i = 0; i < 10; ++i) {
        NodoNum* nuevo = new NodoNum;
        nuevo->num1 = rand() % 10;  // Número aleatorio entre 0 y 9
        nuevo->num2 = rand() % 10;
        nuevo->izq = nullptr;
        nuevo->der = nullptr;

        cout << "Nodo " << i + 1 << ": [" << nuevo->num1 << ", " << nuevo->num2 << "]";

        if (inicio == nullptr) {
            // Primer nodo
            inicio = nuevo;
            actual = nuevo;
            cout << " (inicio)" << endl;
        } else {
            // Enlazar según condición
            if (nuevo->num1 == nuevo->num2) {
                actual->der = nuevo;  // Enlace por derecha si los números son iguales
                cout << " -> derecha" << endl;
            } else {
                actual->izq = nuevo;  // Enlace por izquierda si son distintos
                cout << " -> izquierda" << endl;
            }
            actual = nuevo;
        }
    }

    // Liberar memoria de todos los nodos creados
    actual = inicio;
    while (actual) {
        NodoNum* next = (actual->der) ? actual->der : actual->izq;
        delete actual;
        actual = next;
    }
}

// Función para mostrar una cadena genética visualmente
void mostrarCadenaGenetica(Gen* inicio) {
    cout << "Cadena genética (visual):" << endl;
    Gen* actual = inicio;

    // Parte superior de la cadena
    while (actual != nullptr) {
        cout << "+---+  ";
        actual = actual->siguiente;
    }
    cout << endl;

    // Bases con enlaces
    actual = inicio;
    while (actual != nullptr) {
        cout << "| " << actual->base << " |";
        if (actual->siguiente) cout << "--";
        cout << "  ";
        actual = actual->siguiente;
    }
    cout << endl;

    // Parte inferior de la cadena
    actual = inicio;
    while (actual != nullptr) {
        cout << "+---+  ";
        actual = actual->siguiente;
    }
    cout << endl;
}

// Función para mostrar una molécula de agua con enlaces
void mostrarMolecula(Atomo* inicio) {
    // Diagrama ASCII de la molécula de agua
    cout << "      +-------+      " << endl;
    cout << "      |   O   |      " << endl;
    cout << "      +-------+      " << endl;
    cout << "         /   \\     " << endl;
    cout << "        /     \\    " << endl;
    cout << " +-------+   +-------+ " << endl;
    cout << " | H1   |   | H2   | " << endl;
    cout << " +-------+   +-------+ " << endl;
    cout << "   Hidrógeno   Hidrógeno" << endl << endl;

    // Mostrar enlaces desde el átomo central
    cout << "Átomo central: " << inicio->nombre << " (Oxígeno)" << endl;
    if (inicio->enlace1)
        cout << "Enlace 1: " << inicio->enlace1->nombre << " (Hidrógeno 1)" << endl;
    if (inicio->enlace2)
        cout << "Enlace 2: " << inicio->enlace2->nombre << " (Hidrógeno 2)" << endl;
}

// Función principal
int main() {
    // Crear átomos para la molécula de agua
    Atomo* hidrogeno1 = new Atomo{"H", nullptr, nullptr};
    Atomo* hidrogeno2 = new Atomo{"H", nullptr, nullptr};
    Atomo* oxigeno = new Atomo{"O", hidrogeno1, hidrogeno2};

    // Enlazar hidrógenos al oxígeno
    hidrogeno1->enlace1 = oxigeno;
    hidrogeno2->enlace1 = oxigeno;

    // Mostrar la molécula de agua
    mostrarMolecula(oxigeno);

    // Crear cadena genética: A-T-G-C
    Gen* g1 = new Gen{'A', nullptr};
    Gen* g2 = new Gen{'T', nullptr};
    Gen* g3 = new Gen{'G', nullptr};
    Gen* g4 = new Gen{'C', nullptr};

    // Enlazar genes
    g1->siguiente = g2;
    g2->siguiente = g3;
    g3->siguiente = g4;

    // Mostrar cadena genética (desactivado en este ejemplo)
    // mostrarCadenaGenetica(g1);

    // Liberar memoria de genes
    delete g1;
    delete g2;
    delete g3;
    delete g4;

    // Crear y mostrar 10 nodos con números aleatorios
    crearNodosAleatorios();

    // Liberar memoria de átomos
    delete hidrogeno1;
    delete hidrogeno2;
    delete oxigeno;

    return 0;
}
