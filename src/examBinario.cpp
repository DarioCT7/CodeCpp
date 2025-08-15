#include<iostream>
#include<stdlib.h>
using namespace std;

// --- Estructuras originales del código ---
typedef struct Segmento {
    string caracter;
    Segmento *nextSeg;
} *TTroncoSeg;

struct CienPie {
    string nombre; // Nuevo campo para almacenar el nombre.
    string cabeza;
    string cola;
    TTroncoSeg tronco = NULL;
};
typedef CienPie *TCienPie;

typedef struct Atomo{
    int pesoAtomico = 0;
    string datoAtomico = "";
    Atomo *enlaceAtom = NULL;
} *TAtomo;

struct Molecula {
    int cargaMolecula = 0;
    TAtomo nexConsonante = NULL;
    TAtomo nexVocal = NULL;
};

// --- Estructura para el Nodo de Árbol Binario ---
// Representa un nodo en el árbol que contendrá un Cienpiés.
struct NodoArbolCienPie {
    TCienPie cienpie; // Puntero al objeto Cienpiés.
    NodoArbolCienPie *hijoIzquierdo = NULL; // Puntero al sub-árbol izquierdo.
    NodoArbolCienPie *hijoDerecho = NULL;  // Puntero al sub-árbol derecho.
};
typedef NodoArbolCienPie *TArbolCienPie;

// --- Funciones originales del código (para Cienpiés y Moléculas) ---
TTroncoSeg newSegmento(string c) {
    c = "-=< " + c + " >-=";
    return new Segmento{c, NULL};
}
void addTronco(TTroncoSeg &tronco, string c) {
    TTroncoSeg nuevo = newSegmento(c);
    if (tronco == NULL) {
        tronco = nuevo;
    } else {
        TTroncoSeg actual = tronco;
        while (actual->nextSeg != NULL) {
            actual = actual->nextSeg;
        }
        actual->nextSeg = nuevo;
    }
}
void showCienPie( const CienPie &cienpie) {
    cout << "Nombre: " << cienpie.nombre << endl; // Muestra el nombre.
    cout << cienpie.cabeza << endl;
    TTroncoSeg actual = cienpie.tronco;
    while (actual != NULL) {
        cout << actual->caracter << endl;
        actual = actual->nextSeg;
    }
    cout << cienpie.cola << endl;
    cout <<endl;
}

void newEnlaceAtomico(TAtomo &mol, int peso, string dato) {
    TAtomo nuevo = new Atomo{peso, dato, NULL};
    if (mol == NULL) {
        mol = nuevo;
    } else {
        TAtomo actual = mol;
        while (actual->enlaceAtom != NULL) {
            actual = actual->enlaceAtom;
        }
        actual->enlaceAtom = nuevo;
    }
}
void showEnlaceAtomico(const TAtomo &atom) {
    TAtomo actual = atom;
    cout << "             ";
    while (actual != NULL) {
        cout << "+--+ ( " << actual->datoAtomico << " )";
        actual = actual->enlaceAtom;
    }
    cout << endl;
}
void crearMolecula(){
    Molecula mol;
    string nombre = "patricio";
    mol.cargaMolecula = 5;
    for (auto &&i: nombre) {
        if (i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u')
            newEnlaceAtomico(mol.nexVocal, -1, string(1, i));
        else
            newEnlaceAtomico(mol.nexConsonante, 1, string(1, i));
    }
    showEnlaceAtomico(mol.nexConsonante);
    cout << "             /" << endl
         << "Molecula: (" << mol.cargaMolecula << ")" << endl
         << "             \\" << endl;
    showEnlaceAtomico(mol.nexVocal);
}

// --- Nuevas funciones para el Árbol Binario de Cienpiés ---

// Función recursiva para insertar un nuevo Cienpiés en el árbol.
// Lo inserta de forma ordenada alfabéticamente por su nombre.
void insertarCienPie(TArbolCienPie &arbol, TCienPie nuevoCienpie) {
    // Si el árbol está vacío, el nuevo nodo se convierte en la raíz.
    if (arbol == NULL) {
        arbol = new NodoArbolCienPie{nuevoCienpie, NULL, NULL};
    }
    // Si el nombre del nuevo Cienpiés es menor, se inserta en el sub-árbol izquierdo.
    else if (nuevoCienpie->nombre < arbol->cienpie->nombre) {
        insertarCienPie(arbol->hijoIzquierdo, nuevoCienpie);
    }
    // Si el nombre del nuevo Cienpiés es mayor, se inserta en el sub-árbol derecho.
    else if (nuevoCienpie->nombre > arbol->cienpie->nombre) {
        insertarCienPie(arbol->hijoDerecho, nuevoCienpie);
    }
    // Si el nombre ya existe, se ignora (no se permiten duplicados en este caso).
    else {
        cout << "Error: El Cienpiés con el nombre " << nuevoCienpie->nombre << " ya existe." << endl;
        delete nuevoCienpie; // Liberamos la memoria del duplicado.
    }
}

// Crea un Cienpiés y lo inserta en el árbol.
void crearCienPie(TArbolCienPie &arbol, const string nombre) {
    TCienPie auxCienpie = new CienPie{nombre, "     /\\ \n  (5)", " /\\"};
    for (char i : nombre) {
        addTronco(auxCienpie->tronco, string(1, i));
    }
    insertarCienPie(arbol, auxCienpie);
}

// Muestra los Cienpiés en el árbol en un recorrido in-order (izquierdo -> raíz -> derecho).
// Esto los mostrará ordenados alfabéticamente.
void showArbolCienPie(const TArbolCienPie &arbol) {
    if (arbol != NULL) {
        showArbolCienPie(arbol->hijoIzquierdo); // Primero, recorre el sub-árbol izquierdo.
        showCienPie(*arbol->cienpie);           // Luego, muestra el cienpiés actual (la "raíz").
        showArbolCienPie(arbol->hijoDerecho);   // Finalmente, recorre el sub-árbol derecho.
    }
}

// --- Función Principal (main) modificada ---
int main() {
    TArbolCienPie cienpies = NULL; // Puntero inicial para el árbol de cienpiés.

    crearCienPie(cienpies, "Tonguino"); // Agregamos "Tonguino" al árbol.
    crearCienPie(cienpies, "Dario");    // Agregamos "Dario" al árbol.
    crearCienPie(cienpies, "Carlos");   // Agregamos un tercer cienpiés para demostrar el orden.
    crearCienPie(cienpies, "Dario");    // Intentamos agregar un duplicado.

    cout << "--- Cienpiés ordenados alfabéticamente ---" << endl << endl;
    showArbolCienPie(cienpies); // Mostramos los cienpiés ordenados por nombre.

    crearMolecula();
    return 0;
}