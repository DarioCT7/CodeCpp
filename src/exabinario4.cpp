#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Estructura para un segmento del tronco de un CienPie.
// Cada segmento almacena el carácter decorado (para mostrar), el original (para exportar) y un puntero al siguiente.
typedef struct Segmento {
    string caracterDecorado; 
    string caracterOriginal; 
    Segmento *nextSeg;
} *TTroncoSeg;

// Estructura para un CienPie.
// Contiene el nombre, cabeza y cola gráficas, el tronco como lista enlazada, y un puntero al siguiente amigo.
struct CienPie {
    string      nombre;
    string      cabeza;
    string      cola;
    TTroncoSeg  tronco = NULL;
    CienPie     *nextAmigo = NULL;
};
typedef CienPie *TCienPie;

// Estructura para un Atomo en el árbol binario.
// Incluye peso (1 para consonantes, -1 para vocales), el dato (carácter), y punteros a hijos izquierdo y derecho.
typedef struct Atomo {
    int pesoAtomico = 0;
    string datoAtomico = "";
    Atomo *izquierda = NULL;  // Hijo izquierdo (valores menores alfabéticamente)
    Atomo *derecha = NULL;    // Hijo derecho (valores mayores alfabéticamente)
} *TAtomo;

// Estructura para una Molecula.
// Contiene la carga (fija en 5) y la raíz del árbol binario de átomos.
struct Molecula {
    int cargaMolecula = 0;
    TAtomo arbolAtomos = NULL; // Árbol binario que organiza todos los átomos alfabéticamente
};

// Función para crear un nuevo segmento del tronco.
// Decora el carácter con "-=< c >=-" y lo devuelve como un nuevo nodo.
TTroncoSeg coAlNewSegmento(string c) {
    string decorado = "-=< " + c + " >=-";
    return new Segmento{decorado, c, NULL};
}

// Función para añadir un segmento al tronco (lista enlazada).
// Si el tronco es NULL, lo inicia; si no, lo añade al final.
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

// Función para mostrar un CienPie en la consola.
// Imprime cabeza, cada segmento del tronco, y cola.
void coAlShowCienPie(const CienPie &cienpie) {
    cout << cienpie.cabeza << endl;
    TTroncoSeg actual = cienpie.tronco;
    while (actual != NULL) {
        cout << actual->caracterDecorado << endl;
        actual = actual->nextSeg;
    }
    cout << cienpie.cola << endl << endl;
}

// Función para crear un nuevo CienPie.
// Separa vocales y consonantes del nombre, añade vocales primero al tronco, luego consonantes.
// Añade el nuevo CienPie al final de la lista de amigos.
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

// Función para mostrar todos los amigos CienPie en la consola.
// Recorre la lista enlazada y llama a showCienPie para cada uno.
void coAlShowAmigosCienPie(const TCienPie &p) {
    TCienPie cienpie = p;
    while (cienpie != NULL) {
        coAlShowCienPie(*cienpie);
        cienpie = cienpie->nextAmigo;
    }
    cout << endl;
}

// Función para crear un nuevo átomo en el árbol binario.
// Inicializa con peso, dato y punteros a NULL.
TAtomo newAtomo(int peso, string dato) {
    TAtomo nuevo = new Atomo{peso, dato, NULL, NULL};
    return nuevo;
}

// Función recursiva para insertar un átomo en el árbol binario.
// Ordena alfabéticamente por datoAtomico: menor a izquierda, mayor a derecha.
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

// Función recursiva para mostrar el árbol binario en orden in-order (derecha-raíz-izquierda para orden descendente).
// Usa indentación para mostrar la jerarquía.
void showArbolAtomico(const TAtomo &arbol, int nivel = 0) {
    if (arbol != NULL) {
        showArbolAtomico(arbol->derecha, nivel + 1);  // Primero el subárbol derecho
        for (int i = 0; i < nivel; i++) cout << "   ";  // Indentación por nivel
        cout << "+--+ ( " << arbol->datoAtomico << ", peso: " << arbol->pesoAtomico << " )" << endl;
        showArbolAtomico(arbol->izquierda, nivel + 1);  // Luego el subárbol izquierdo
    }
}

// Función recursiva para recolectar vocales y consonantes del árbol (en orden alfabético).
// Usa recorrido in-order (izquierda-raíz-derecha) para mantener el orden.
void recolectarAtomos(const TAtomo &arbol, string &vocales, string &consonantes) {
    if (arbol != NULL) {
        recolectarAtomos(arbol->izquierda, vocales, consonantes);  // Subárbol izquierdo
        char c = tolower(arbol->datoAtomico[0]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            vocales += arbol->datoAtomico;
        else
            consonantes += arbol->datoAtomico;
        recolectarAtomos(arbol->derecha, vocales, consonantes);  // Subárbol derecho
    }
}

// Función para crear una molécula y exportar sus datos.
// Inserta todos los caracteres en el árbol binario, muestra en consola y exporta vocales/consonantes al CSV.
void coAlCrearMoleculaYExportar(ofstream &archivo, const string &nombre) {
    if (nombre.empty()) {
        cout << "No se encontro un nombre para crear la molecula." << endl;
        return;
    }

    Molecula mol;
    mol.cargaMolecula = 5;  // Carga fija de la molécula
    for (char i : nombre) {
        char lower_i = tolower(i);
        int peso = (lower_i == 'a' || lower_i == 'e' || lower_i == 'i' || lower_i == 'o' || lower_i == 'u') ? -1 : 1;
        insertarAtomo(mol.arbolAtomos, peso, string(1, i));  // Insertar en el árbol
    }

    // Mostrar en consola
    cout << "Molecula: (" << mol.cargaMolecula << ") para " << nombre << endl;
    cout << "Arbol de atomos (ordenado alfabeticamente):" << endl;
    showArbolAtomico(mol.arbolAtomos);
    cout << endl;  // Espacio para separar en consola

    // Exportar a CSV (recolectando vocales y consonantes ordenadas)
    string vocales, consonantes;
    recolectarAtomos(mol.arbolAtomos, vocales, consonantes);
    archivo << "---,---" << endl;
    archivo << "Molecula," << nombre << endl;
    archivo << "Consonantes," << consonantes << endl;
    archivo << "Vocales," << vocales << endl;
}

// Función para leer nombres desde un archivo CSV.
// Crea un CienPie por cada nombre encontrado y devuelve el primer nombre (aunque no se usa en main).
string coAlLeerDatosDesdeCSV(TCienPie &p, const string &filename) {
    string primerNombre = "";
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo de datos '" << filename << "'." << endl;
        return primerNombre;
    }

    string linea;
    while (getline(archivo, linea)) {  // Leer línea por línea
        stringstream ss(linea);
        string item;

        getline(ss, item, ',');  // Ignorar posible campo vacío
        getline(ss, item, ',');  // Ignorar otro posible campo
        string nombreCompleto = "";
        string primerNombreLinea = "";
        
        while (ss >> item) {  // Leer cada nombre en la línea
            if (primerNombre.empty()) {
                primerNombre = item;
            }
            if (primerNombreLinea.empty()) {
                primerNombreLinea = item;
            }
            coAlCrearCienPie(p, item);  // Crear CienPie para cada item (nombre)
        }
    }
    archivo.close();
    return primerNombre;
}

// Función principal.
// Lee datos de CSV, crea CienPies y moléculas, muestra en consola y exporta a CSV.
int main() {
    TCienPie amigosCienpies = NULL;
    const string filename = "cienpies.csv";  // Archivo de salida
    const string datafile = "datos.csv";     // Archivo de entrada

    // Leer nombres desde datos.csv y crear CienPies
    string nombreParaMolecula = coAlLeerDatosDesdeCSV(amigosCienpies, datafile);

    ofstream archivoSalida(filename);
    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo de salida " << filename << endl;
        return 1;
    }
    
    // Escribir encabezado en el CSV
    archivoSalida << "NombreCienPie,Segmento\n";

    TCienPie actual = amigosCienpies;
    while (actual != NULL) {
        coAlShowCienPie(*actual);  // Mostrar CienPie en consola
        
        TTroncoSeg actualSeg = actual->tronco;
        while (actualSeg != NULL) {
            // Escribir cada segmento en el CSV
            archivoSalida << actual->nombre << "," << actualSeg->caracterOriginal << "\n";
            actualSeg = actualSeg->nextSeg;
        }
        
        // Crear y exportar molécula para este nombre
        coAlCrearMoleculaYExportar(archivoSalida, actual->nombre);
        
        actual = actual->nextAmigo;  // Pasar al siguiente amigo
    }

    archivoSalida.close();
    cout << "Archivo creado y actualizado: " << filename << endl;
    return 0;
}