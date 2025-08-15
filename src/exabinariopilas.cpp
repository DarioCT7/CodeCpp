#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack> // Se incluye la librería para usar la pila (std::stack)

using namespace std;

// --- Estructuras de datos ---
typedef struct Segmento {
    string caracterDecorado;
    string caracterOriginal;
    Segmento *nextSeg;
} *TTroncoSeg;

struct CienPie {
    string nombre;
    string cabeza;
    string cola;
    TTroncoSeg tronco = NULL;
};
typedef CienPie *TCienPie;

// Estructura para el Nodo de Árbol Binario
struct NodoArbolCienPie {
    TCienPie cienpie;
    NodoArbolCienPie *hijoIzquierdo = NULL;
    NodoArbolCienPie *hijoDerecho = NULL;
};
typedef NodoArbolCienPie *TArbolCienPie;

typedef struct Atomo{
    int pesoAtomico=0;
    string datoAtomico= "";
    Atomo *enlaceAtom= NULL;
} *TAtomo;

struct Molecula {
    int cargaMolecula = 0;
    TAtomo nexConsonante = NULL;
    TAtomo nexVocal = NULL;
};

// --- Funciones para los Cienpiés (con árbol binario) ---
TTroncoSeg coAlNewSegmento(string c) {
    string decorado = "-=< " + c + " >=-";
    return new Segmento{decorado, c, NULL};
}

void coAlAddTronco(TTroncoSeg &tronco, string c) {
    TTroncoSeg nuevo = coAlNewSegmento(c);
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

void coAlShowCienPie(const CienPie &cienpie) {
    cout << "Nombre: " << cienpie.nombre << endl;
    cout << cienpie.cabeza << endl;
    TTroncoSeg actual = cienpie.tronco;
    while (actual != NULL) {
        cout << actual->caracterDecorado << endl;
        actual = actual->nextSeg;
    }
    cout << cienpie.cola << endl << endl;
}

void insertarCienPie(TArbolCienPie &arbol, TCienPie nuevoCienpie) {
    if (arbol == NULL) {
        arbol = new NodoArbolCienPie{nuevoCienpie, NULL, NULL};
    } else if (nuevoCienpie->nombre < arbol->cienpie->nombre) {
        insertarCienPie(arbol->hijoIzquierdo, nuevoCienpie);
    } else if (nuevoCienpie->nombre > arbol->cienpie->nombre) {
        insertarCienPie(arbol->hijoDerecho, nuevoCienpie);
    } else {
        cout << "Advertencia: El Cienpiés con el nombre '" << nuevoCienpie->nombre << "' ya existe y no será agregado." << endl;
        delete nuevoCienpie;
    }
}

void coAlCrearCienPie(TArbolCienPie &arbol, const string nombre) {
    TCienPie nuevo = new CienPie{nombre, "     /\\ \n  (5)", "/\\"};
    vector<char> vocales;
    vector<char> consonantes;

    for (char i : nombre) {
        char lower_i = tolower(i);
        if (lower_i == 'a' || lower_i == 'e' || lower_i == 'i' || lower_i == 'o' || lower_i == 'u')
            vocales.push_back(i);
        else
            consonantes.push_back(i);
    }
    for (char v : vocales)
        coAlAddTronco(nuevo->tronco, string(1, v));
    for (char c : consonantes)
        coAlAddTronco(nuevo->tronco, string(1, c));

    insertarCienPie(arbol, nuevo);
}

void coAlShowArbolCienPie(const TArbolCienPie &arbol) {
    if (arbol != NULL) {
        coAlShowArbolCienPie(arbol->hijoIzquierdo);
        coAlShowCienPie(*arbol->cienpie);
        coAlShowArbolCienPie(arbol->hijoDerecho);
    }
}

void coAlExportarCienpiesCSV(const TArbolCienPie &arbol, ofstream &archivo) {
    if (arbol != NULL) {
        coAlExportarCienpiesCSV(arbol->hijoIzquierdo, archivo);
        
        TTroncoSeg actualSeg = arbol->cienpie->tronco;
        while (actualSeg != NULL) {
            archivo << arbol->cienpie->nombre << "," << actualSeg->caracterOriginal << "\n";
            actualSeg = actualSeg->nextSeg;
        }
        coAlExportarCienpiesCSV(arbol->hijoDerecho, archivo);
    }
}

// --- Funciones para las Moléculas (con uso de pila) ---
void coAlNewEnlaceAtomico(TAtomo &mol, int peso, string dato) {
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

void coAlShowEnlaceAtomico(const TAtomo &atom) {
    TAtomo actual = atom;
    cout << "             ";
    while (actual != NULL) {
        cout << "+--+ ( " << actual->datoAtomico << ")";
        actual = actual->enlaceAtom;
    }
    cout << endl;
}

void coAlCrearMoleculaYExportar(ofstream &archivo, const string &nombre) {
    if (nombre.empty()) {
        cout << "No se encontro un nombre para crear la molecula." << endl;
        return;
    }

    Molecula mol;
    mol.cargaMolecula = 5;
    stack<char> consonantes_pila; // Se declara la pila para las consonantes.
    
    for (char i : nombre) {
        char lower_i = tolower(i);
        if (lower_i == 'a' || lower_i == 'e' || lower_i == 'i' || lower_i == 'o' || lower_i == 'u')
            coAlNewEnlaceAtomico(mol.nexVocal, -1, string(1, i));
        else
            consonantes_pila.push(i); // Las consonantes se añaden a la pila.
    }

    // Se extraen las consonantes de la pila y se añaden a la lista.
    while (!consonantes_pila.empty()) {
        coAlNewEnlaceAtomico(mol.nexConsonante, 1, string(1, consonantes_pila.top()));
        consonantes_pila.pop();
    }
    
    archivo << "---,---" << endl;
    archivo << "Molecula," << nombre << endl;
    archivo << "Consonantes,";
    TAtomo cons = mol.nexConsonante;
    while (cons != NULL) {
        archivo << cons->datoAtomico;
        cons = cons->enlaceAtom;
    }
    archivo << endl;
    archivo << "Vocales,";
    TAtomo vocal = mol.nexVocal;
    while (vocal != NULL) {
        archivo << vocal->datoAtomico;
        vocal = vocal->enlaceAtom;
    }
    archivo << endl;
    
    coAlShowEnlaceAtomico(mol.nexConsonante);
    cout << "             /\n"
         << "Molecula: (" << mol.cargaMolecula << ")\n"
         << "             \\" << endl;
    coAlShowEnlaceAtomico(mol.nexVocal);
}

// --- Modificación de la lectura de archivos para el árbol ---
string coAlLeerDatosDesdeCSV(TArbolCienPie &p, const string &filename) {
    string primerNombre = "";
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo de datos '" << filename << "'." << endl;
        return primerNombre;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string item;
        
        while (getline(ss, item, ',')) {
            if (primerNombre.empty()) {
                primerNombre = item;
            }
            coAlCrearCienPie(p, item);
        }
    }
    archivo.close();
    return primerNombre;
}

// --- Función Principal (main) modificada ---
int main() {
    TArbolCienPie cienpies = NULL;
    const string filename = "cienpies.csv";
    const string datafile = "datos.csv";

    string nombreParaMolecula = coAlLeerDatosDesdeCSV(cienpies, datafile);
    
    if (cienpies != NULL) {
        cout << "--- Cienpiés procesados (ordenados alfabéticamente) ---" << endl << endl;
        coAlShowArbolCienPie(cienpies);

        ofstream archivoSalida(filename);
        if (!archivoSalida.is_open()) {
            cerr << "Error al abrir el archivo de salida " << filename << endl;
            return 1;
        }

        archivoSalida << "NombreCienPie,Segmento\n";
        coAlExportarCienpiesCSV(cienpies, archivoSalida);
        archivoSalida.close();
        
        cout << "Archivo creado y actualizado: " << filename << endl;

    } else {
        cout << "No se encontraron nombres en el archivo de datos para procesar." << endl;
    }
    
    coAlCrearMoleculaYExportar(cout, nombreParaMolecula);

    return 0;
}