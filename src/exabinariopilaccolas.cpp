#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

// Estructura para un segmento del tronco de un CienPie
typedef struct Segmento {
    string caracterDecorado; 
    string caracterOriginal; 
    Segmento *nextSeg;
} *TTroncoSeg;

// Estructura para un nodo de la pila de segmentos
typedef struct NodoPila {
    TTroncoSeg segmento;
    NodoPila *siguiente;
} *TPila;

// Estructura para un CienPie
struct CienPie {
    string nombre;
    string cabeza;
    string cola;
    TTroncoSeg tronco = nullptr;
};
typedef CienPie *TCienPie;

// Estructura para un nodo de la cola de CienPies
typedef struct NodoCola {
    TCienPie cienPie;
    NodoCola *siguiente;
} *TCola;

// Estructura para un Atomo en un árbol AVL
typedef struct Atomo {
    int pesoAtomico = 0;
    string datoAtomico = "";
    int altura = 1; // Altura para balanceo AVL
    Atomo *izquierda = nullptr;
    Atomo *derecha = nullptr;
} *TAtomo;

// Estructura para una Molecula
struct Molecula {
    int cargaMolecula = 0;
    TAtomo arbolAtomos = nullptr;
};

// Estructura para la cola de CienPies
struct ColaCienPies {
    TCola frente = nullptr;
    TCola final = nullptr;
};

// --- Funciones para la pila de segmentos ---

// Apilar un segmento en la pila
void pushPila(TPila &pila, TTroncoSeg segmento) {
    TPila nuevo = new NodoPila{segmento, pila};
    pila = nuevo;
}

// Desapilar un segmento de la pila
TTroncoSeg popPila(TPila &pila) {
    if (!pila) return nullptr;
    TTroncoSeg segmento = pila->segmento;
    TPila temp = pila;
    pila = pila->siguiente;
    delete temp;
    return segmento;
}

// Liberar memoria de la pila
void liberarPila(TPila &pila) {
    while (pila) {
        TPila temp = pila;
        pila = pila->siguiente;
        delete temp;
    }
}

// --- Funciones para la cola de CienPies ---

// Encolar un CienPie
void enqueueCola(ColaCienPies &cola, TCienPie cienPie) {
    TCola nuevo = new NodoCola{cienPie, nullptr};
    if (cola.final == nullptr) {
        cola.frente = cola.final = nuevo;
    } else {
        cola.final->siguiente = nuevo;
        cola.final = nuevo;
    }
}

// Desencolar un CienPie
TCienPie dequeueCola(ColaCienPies &cola) {
    if (cola.frente == nullptr) return nullptr;
    TCola temp = cola.frente;
    TCienPie cienPie = temp->cienPie;
    cola.frente = cola.frente->siguiente;
    if (cola.frente == nullptr) cola.final = nullptr;
    delete temp;
    return cienPie;
}

// Liberar memoria de la cola
void liberarCola(ColaCienPies &cola) {
    while (cola.frente) {
        TCola temp = cola.frente;
        cola.frente = cola.frente->siguiente;
        delete temp->cienPie; // Liberar el CienPie
        delete temp;
    }
    cola.final = nullptr;
}

// --- Funciones para el árbol AVL ---

// Obtener altura de un nodo AVL
int altura(TAtomo nodo) {
    return nodo ? nodo->altura : 0;
}

// Calcular factor de balanceo
int factorBalanceo(TAtomo nodo) {
    return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
}

// Actualizar altura de un nodo
void actualizarAltura(TAtomo nodo) {
    if (nodo) {
        nodo->altura = max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    }
}

// Rotación derecha para balanceo AVL
TAtomo rotarDerecha(TAtomo y) {
    TAtomo x = y->izquierda;
    TAtomo T2 = x->derecha;
    x->derecha = y;
    y->izquierda = T2;
    actualizarAltura(y);
    actualizarAltura(x);
    return x;
}

// Rotación izquierda para balanceo AVL
TAtomo rotarIzquierda(TAtomo x) {
    TAtomo y = x->derecha;
    TAtomo T2 = y->izquierda;
    y->izquierda = x;
    x->derecha = T2;
    actualizarAltura(x);
    actualizarAltura(y);
    return y;
}

// Crear un nuevo átomo
TAtomo newAtomo(int peso, string dato) {
    TAtomo nuevo = nullptr;
    try {
        nuevo = new Atomo{peso, dato, 1, nullptr, nullptr};
    } catch (const bad_alloc &e) {
        throw runtime_error("Error: No se pudo asignar memoria para un átomo.");
    }
    return nuevo;
}

// Insertar un átomo en el árbol AVL, manejando duplicados
TAtomo insertarAtomo(TAtomo arbol, int peso, string dato) {
    if (arbol == nullptr) {
        return newAtomo(peso, dato);
    }
    if (dato < arbol->datoAtomico) {
        arbol->izquierda = insertarAtomo(arbol->izquierda, peso, dato);
    } else if (dato > arbol->datoAtomico) {
        arbol->derecha = insertarAtomo(arbol->derecha, peso, dato);
    } else {
        return arbol; // Ignorar duplicados
    }

    // Actualizar altura
    actualizarAltura(arbol);

    // Balancear el árbol
    int balance = factorBalanceo(arbol);
    if (balance > 1) {
        if (dato < arbol->izquierda->datoAtomico) {
            return rotarDerecha(arbol);
        } else {
            arbol->izquierda = rotarIzquierda(arbol->izquierda);
            return rotarDerecha(arbol);
        }
    }
    if (balance < -1) {
        if (dato > arbol->derecha->datoAtomico) {
            return rotarIzquierda(arbol);
        } else {
            arbol->derecha = rotarDerecha(arbol->derecha);
            return rotarIzquierda(arbol);
        }
    }
    return arbol;
}

// Mostrar el árbol AVL en orden in-order
void showArbolAtomico(const TAtomo &arbol, int nivel = 0) {
    if (arbol != nullptr) {
        showArbolAtomico(arbol->derecha, nivel + 1);
        for (int i = 0; i < nivel; i++) cout << "   ";
        cout << "+--+ ( " << arbol->datoAtomico << ", peso: " << arbol->pesoAtomico << " )" << endl;
        showArbolAtomico(arbol->izquierda, nivel + 1);
    }
}

// Recolectar vocales y consonantes del árbol
void recolectarAtomos(const TAtomo &arbol, string &vocales, string &consonantes) {
    if (arbol != nullptr) {
        recolectarAtomos(arbol->izquierda, vocales, consonantes);
        char c = tolower(arbol->datoAtomico[0]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            vocales += arbol->datoAtomico + "(" + to_string(arbol->pesoAtomico) + ")";
        else
            consonantes += arbol->datoAtomico + "(" + to_string(arbol->pesoAtomico) + ")";
        recolectarAtomos(arbol->derecha, vocales, consonantes);
    }
}

// Liberar memoria del árbol AVL
void liberarArbol(TAtomo &arbol) {
    if (arbol != nullptr) {
        liberarArbol(arbol->izquierda);
        liberarArbol(arbol->derecha);
        delete arbol;
        arbol = nullptr;
    }
}

// Crear un nuevo segmento
TTroncoSeg coAlNewSegmento(string c) {
    string decorado = "-=< " + c + " >=-";
    TTroncoSeg nuevo = nullptr;
    try {
        nuevo = new Segmento{decorado, c, nullptr};
    } catch (const bad_alloc &e) {
        throw runtime_error("Error: No se pudo asignar memoria para un segmento.");
    }
    return nuevo;
}

// Añadir segmento al tronco
void coAlAddTronco(TTroncoSeg &tronco, string c) {
    TTroncoSeg nuevo = coAlNewSegmento(c);
    if (tronco == nullptr) {
        tronco = nuevo;
    } else {
        TTroncoSeg actual = tronco;
        while (actual->nextSeg != nullptr) {
            actual = actual->nextSeg;
        }
        actual->nextSeg = nuevo;
    }
}

// Mostrar CienPie en consola (orden normal)
void coAlShowCienPie(const CienPie &cienpie) {
    cout << "CienPie: " << cienpie.nombre << endl;
    cout << cienpie.cabeza << endl;
    TTroncoSeg actual = cienpie.tronco;
    while (actual != nullptr) {
        cout << actual->caracterDecorado << endl;
        actual = actual->nextSeg;
    }
    cout << cienpie.cola << endl;
}

// Mostrar CienPie en orden inverso usando pila
void coAlShowCienPieInverso(const CienPie &cienpie) {
    cout << "CienPie (inverso): " << cienpie.nombre << endl;
    cout << cienpie.cabeza << endl;
    TPila pila = nullptr;
    TTroncoSeg actual = cienpie.tronco;
    while (actual != nullptr) {
        pushPila(pila, actual);
        actual = actual->nextSeg;
    }
    while (pila != nullptr) {
        TTroncoSeg seg = popPila(pila);
        cout << seg->caracterDecorado << endl;
    }
    cout << cienpie.cola << endl << endl;
    liberarPila(pila);
}

// Crear un nuevo CienPie
void coAlCrearCienPie(ColaCienPies &cola, const string nombre) {
    if (nombre.empty()) {
        cout << "Advertencia: Nombre vacio ignorado." << endl;
        return;
    }
    TCienPie nuevo = nullptr;
    try {
        nuevo = new CienPie{nombre, "     /\\ \n   (5)", "/\\"};
    } catch (const bad_alloc &e) {
        throw runtime_error("Error: No se pudo asignar memoria para un CienPie.");
    }

    TTroncoSeg vocales = nullptr, consonantes = nullptr;
    TTroncoSeg *ultimaVocal = &vocales, *ultimaConsonante = &consonantes;
    for (char i : nombre) {
        if (!isalpha(i)) continue;
        char lower_i = tolower(i);
        TTroncoSeg nuevoSeg = coAlNewSegmento(string(1, i));
        if (lower_i == 'a' || lower_i == 'e' || lower_i == 'i' || lower_i == 'o' || lower_i == 'u') {
            *ultimaVocal = nuevoSeg;
            ultimaVocal = &(nuevoSeg->nextSeg);
        } else {
            *ultimaConsonante = nuevoSeg;
            ultimaConsonante = &(nuevoSeg->nextSeg);
        }
    }
    *ultimaVocal = consonantes;
    nuevo->tronco = vocales;
    enqueueCola(cola, nuevo);
}

// Crear y mostrar molécula
void coAlCrearMolecula(const string &nombre, Molecula &mol) {
    mol.cargaMolecula = 5;
    for (char i : nombre) {
        if (!isalpha(i)) continue;
        char lower_i = tolower(i);
        int peso = (lower_i == 'a' || lower_i == 'e' || lower_i == 'i' || lower_i == 'o' || lower_i == 'u') ? -1 : 1;
        mol.arbolAtomos = insertarAtomo(mol.arbolAtomos, peso, string(1, i));
    }
}

// Exportar molécula a CSV
void coAlExportarMolecula(ofstream &archivo, const string &nombre, const Molecula &mol) {
    string vocales, consonantes;
    recolectarAtomos(mol.arbolAtomos, vocales, consonantes);
    archivo << "---,---" << endl;
    archivo << "Molecula," << nombre << endl;
    archivo << "Consonantes," << (consonantes.empty() ? "Ninguna" : consonantes) << endl;
    archivo << "Vocales," << (vocales.empty() ? "Ninguna" : vocales) << endl;
}

// Leer datos desde CSV
string coAlLeerDatosDesdeCSV(ColaCienPies &cola, const string &filename) {
    string primerNombre = "";
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << filename << "'." << endl;
        return primerNombre;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue; // Ignorar líneas vacías
        stringstream ss(linea);
        string item;
        getline(ss, item, ','); // Ignorar primer campo
        getline(ss, item, ','); // Ignorar segundo campo
        while (getline(ss, item, ',')) {
            if (item.empty()) continue;
            if (primerNombre.empty()) primerNombre = item;
            coAlCrearCienPie(cola, item);
        }
    }
    archivo.close();
    return primerNombre;
}

// Función principal
int main() {
    ColaCienPies colaCienPies;
    const string filename = "cienpies.csv";
    const string datafile = "datos.csv";

    try {
        // Leer datos desde CSV
        string primerNombre = coAlLeerDatosDesdeCSV(colaCienPies, datafile);
        
        // Abrir archivo de salida
        ofstream archivoSalida(filename);
        if (!archivoSalida.is_open()) {
            throw runtime_error("Error: No se pudo abrir el archivo '" + filename + "'.");
        }
        
        archivoSalida << "NombreCienPie,Segmento\n";
        
        // Procesar CienPies usando la cola
        cout << "Procesando CienPies en orden FIFO:" << endl;
        TCola actualCola = colaCienPies.frente;
        while (actualCola != nullptr) {
            TCienPie cienPie = actualCola->cienPie;
            coAlShowCienPie(*cienPie); // Mostrar en orden normal
            coAlShowCienPieInverso(*cienPie); // Mostrar en orden inverso usando pila

            // Exportar segmentos al CSV
            TTroncoSeg actualSeg = cienPie->tronco;
            while (actualSeg != nullptr) {
                archivoSalida << cienPie->nombre << "," << actualSeg->caracterOriginal << "\n";
                actualSeg = actualSeg->nextSeg;
            }

            // Crear y exportar molécula
            Molecula mol;
            coAlCrearMolecula(cienPie->nombre, mol);
            cout << "Molecula: (" << mol.cargaMolecula << ") para " << cienPie->nombre << endl;
            cout << "Arbol de atomos (ordenado alfabeticamente):" << endl;
            showArbolAtomico(mol.arbolAtomos);
            cout << endl;
            coAlExportarMolecula(archivoSalida, cienPie->nombre, mol);
            liberarArbol(mol.arbolAtomos);

            actualCola = actualCola->siguiente;
        }

        archivoSalida.close();
        cout << "Archivo creado y actualizado: " << filename << endl;

        // Liberar memoria
        liberarCola(colaCienPies);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        liberarCola(colaCienPies);
        return 1;
    }

    return 0;
}