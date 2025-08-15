#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

typedef struct Segmento {
    string caracter;
    Segmento *nextSeg;
} *TTroncoSeg;

struct CienPie {
    string      cabeza;
    string      cola;
    TTroncoSeg  tronco = NULL;
    CienPie     *nextAmigo = NULL;
};
typedef CienPie *TCienPie;

typedef struct Atomo {
    int pesoAtomico = 0;
    string datoAtomico = "";
    Atomo *izquierda = NULL;  // Hijo izquierdo
    Atomo *derecha = NULL;    // Hijo derecho
} *TAtomo;

struct Molecula {
    int cargaMolecula = 0;
    TAtomo arbolAtomos = NULL; // Árbol binario de átomos
};

TTroncoSeg newSegmento(string c) 
{
    c = "-=< " + c + " >-=";
    return new Segmento{c, NULL};
}

void addTronco(TTroncoSeg &tronco, string c)
{
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

void showCienPie(const CienPie &cienpie)
{
    cout << cienpie.cabeza << endl;
    TTroncoSeg actual = cienpie.tronco;
    while (actual != NULL) {
        cout << actual->caracter << endl;
        actual = actual->nextSeg;
    }
    cout << cienpie.cola << endl;
    cout << endl;
}

void crearCienPie(TCienPie &p, const string nombre)
{
    TCienPie auxCienpie = new CienPie{"     /\\ \n  (5)", " /\\"};
    for (auto &&i : nombre) 
        addTronco(auxCienpie->tronco, string(1, i));
    auxCienpie->nextAmigo = p;
    p = auxCienpie;
}

void showAmigosCienPie(const TCienPie &p)
{
    TCienPie cienpie = p;
    while (cienpie != NULL) {
        showCienPie(*cienpie);
        cienpie = cienpie->nextAmigo;
    }
    cout << endl;
}

// Crear un nuevo átomo
TAtomo newAtomo(int peso, string dato) {
    TAtomo nuevo = new Atomo{peso, dato, NULL, NULL};
    return nuevo;
}

// Insertar un átomo en el árbol binario
void insertarAtomo(TAtomo &arbol, int peso, string dato) {
    if (arbol == NULL) {
        arbol = newAtomo(peso, dato);
    } else {
        if (dato < arbol->datoAtomico) {
            insertarAtomo(arbol->izquierda, peso, dato);
        } else {
            insertarAtomo(arbol->derecha, peso, dato);
        }
    }
}

// Mostrar los átomos en orden (in-order traversal)
void showArbolAtomico(const TAtomo &arbol, int nivel = 0) {
    if (arbol != NULL) {
        // Mostrar subárbol derecho (para que aparezca primero en orden descendente)
        showArbolAtomico(arbol->derecha, nivel + 1);
        // Imprimir nodo actual con indentación
        for (int i = 0; i < nivel; i++) cout << "   ";
        cout << "+--+ ( " << arbol->datoAtomico << ", peso: " << arbol->pesoAtomico << " )" << endl;
        // Mostrar subárbol izquierdo
        showArbolAtomico(arbol->izquierda, nivel + 1);
    }
}

// Modificar crearMolecula para usar el árbol binario
void crearMolecula() {
    Molecula mol;
    string nombre = "patricio";

    mol.cargaMolecula = 5;
    for (auto &&i : nombre) {
        int peso = (i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u') ? -1 : 1;
        insertarAtomo(mol.arbolAtomos, peso, string(1, i));
    }

    cout << "Molecula: (" << mol.cargaMolecula << ")" << endl;
    cout << "Arbol de atomos (ordenado alfabeticamente):" << endl;
    showArbolAtomico(mol.arbolAtomos);
}

int main() {
    TCienPie amigosCienpies = NULL;

    crearCienPie(amigosCienpies, "Tonguino");
    crearCienPie(amigosCienpies, "Dario");
    showAmigosCienPie(amigosCienpies);
    crearMolecula();
    return 0;
}