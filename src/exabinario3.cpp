#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

typedef struct Segmento {
    string caracterDecorado; 
    string caracterOriginal; 
    Segmento *nextSeg;
} *TTroncoSeg;

struct CienPie {
    string      nombre;
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
    cout << cienpie.cabeza << endl;
    TTroncoSeg actual = cienpie.tronco;
    while (actual != NULL) {
        cout << actual->caracterDecorado << endl;
        actual = actual->nextSeg;
    }
    cout << cienpie.cola << endl << endl;
}

void coAlCrearCienPie(TCienPie &p, const string nombre) {
    TCienPie nuevo = new CienPie{nombre, "     /\\ \n   (5)", "/\\"};
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

    if (p == NULL) {
        p = nuevo;
    } else {
        TCienPie actual = p;
        while (actual->nextAmigo != NULL) {
            actual = actual->nextAmigo;
        }
        actual->nextAmigo = nuevo;
    }
}

void coAlShowAmigosCienPie(const TCienPie &p) {
    TCienPie cienpie = p;
    while (cienpie != NULL) {
        coAlShowCienPie(*cienpie);
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
        showArbolAtomico(arbol->derecha, nivel + 1);
        for (int i = 0; i < nivel; i++) cout << "   ";
        cout << "+--+ ( " << arbol->datoAtomico << ", peso: " << arbol->pesoAtomico << " )" << endl;
        showArbolAtomico(arbol->izquierda, nivel + 1);
    }
}

// Recolectar vocales y consonantes para exportar
void recolectarAtomos(const TAtomo &arbol, string &vocales, string &consonantes) {
    if (arbol != NULL) {
        recolectarAtomos(arbol->izquierda, vocales, consonantes);
        char c = tolower(arbol->datoAtomico[0]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            vocales += arbol->datoAtomico;
        else
            consonantes += arbol->datoAtomico;
        recolectarAtomos(arbol->derecha, vocales, consonantes);
    }
}

void coAlCrearMoleculaYExportar(ofstream &archivo, const string &nombre) {
    if (nombre.empty()) {
        cout << "No se encontro un nombre para crear la molecula." << endl;
        return;
    }

    Molecula mol;
    mol.cargaMolecula = 5;
    for (char i : nombre) {
        char lower_i = tolower(i);
        int peso = (lower_i == 'a' || lower_i == 'e' || lower_i == 'i' || lower_i == 'o' || lower_i == 'u') ? -1 : 1;
        insertarAtomo(mol.arbolAtomos, peso, string(1, i));
    }

    // Mostrar en consola
    cout << "Molecula: (" << mol.cargaMolecula << ") para " << nombre << endl;
    cout << "Arbol de atomos (ordenado alfabeticamente):" << endl;
    showArbolAtomico(mol.arbolAtomos);

    // Exportar a CSV
    string vocales, consonantes;
    recolectarAtomos(mol.arbolAtomos, vocales, consonantes);
    archivo << "---,---" << endl;
    archivo << "Molecula," << nombre << endl;
    archivo << "Consonantes," << consonantes << endl;
    archivo << "Vocales," << vocales << endl;
}

string coAlLeerDatosDesdeCSV(TCienPie &p, const string &filename) {
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
        getline(ss, item, ',');
        getline(ss, item, ',');
        string nombreCompleto = "";
        string primerNombreLinea = "";
        
        while (ss >> item) {
            if (primerNombre.empty()) {
                primerNombre = item;
            }
            if (primerNombreLinea.empty()) {
                primerNombreLinea = item;
            }
            coAlCrearCienPie(p, item);
        }
    }
    archivo.close();
    return primerNombre;
}

int main() {
    TCienPie amigosCienpies = NULL;
    const string filename = "cienpies.csv";
    const string datafile = "datos.csv";

    // Leer los nombres y crear los cienpiés
    string nombreParaMolecula = coAlLeerDatosDesdeCSV(amigosCienpies, datafile);

    ofstream archivoSalida(filename);
    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo de salida " << filename << endl;
        return 1;
    }
    
    // Exportar el encabezado del archivo CSV
    archivoSalida << "NombreCienPie,Segmento\n";

    TCienPie actual = amigosCienpies;
    while (actual != NULL) {
        coAlShowCienPie(*actual); // Mostrar los cienpiés en consola 
        TTroncoSeg actualSeg = actual->tronco;
        while (actualSeg != NULL) {
            archivoSalida << actual->nombre << "," << actualSeg->caracterOriginal << "\n";
            actualSeg = actualSeg->nextSeg;
        }
        coAlCrearMoleculaYExportar(archivoSalida, actual->nombre); // Crear la molécula
        actual = actual->nextAmigo;
    }

    archivoSalida.close();
    cout << "Archivo creado y actualizado: " << filename << endl;
    return 0;
}