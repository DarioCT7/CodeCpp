#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<vector>

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

typedef struct Atomo{
    int     pesoAtomico=0;
    string  datoAtomico= "";
    Atomo   *enlaceAtom= NULL;
    } *TAtomo;  

struct Molecula {
    int     cargaMolecula = 0;
    TAtomo  nexConsonante = NULL;
    TAtomo  nexVocal = NULL;
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
/* para lectura normal de nombres reemplaza abajo en vocales y consonantes
    for (auto &&i : nombre)
        coAlAddTronco(nuevo->tronco, string(1, i));
}*/

void coAlCrearCienPie(TCienPie &p, const string nombre) {
    TCienPie nuevo = new CienPie{nombre,"     /\\ \n   (5)", "/\\"};
    vector<char> vocales;// desde aqui para separar vocales y consonantes
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
        coAlAddTronco(nuevo->tronco, string(1, c));// hasta aqui para separar vocales y consonantes

    if (p == NULL) {
        p = nuevo;
    } else {
        TCienPie actual = p;
        while (actual->nextAmigo != NULL) {
            actual = actual->nextAmigo;
        }
        actual->nextAmigo = nuevo;
    }
    //para cambiar el orden de lectura del nombre comneta desde if hasta aqui
    // nuevo->nextAmigo = p;
    // p = nuevo;

}
void coAlShowAmigosCienPie(const TCienPie &p) {
    TCienPie cienpie = p;
    while (cienpie != NULL) {
        coAlShowCienPie(*cienpie);
        cienpie = cienpie->nextAmigo;
    }
    cout << endl;
}

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

// **Modificada:** ahora recibe el archivo por referencia.
void coAlExportarCienpiesCSV(const TCienPie &p, ofstream &archivo) {
    archivo << "NombreCienPie,Segmento\n";
    TCienPie actualCienpie = p;
    while (actualCienpie != NULL) {
        TTroncoSeg actualSeg = actualCienpie->tronco;
        while (actualSeg != NULL) {
            archivo << actualCienpie->nombre << "," << actualSeg->caracterOriginal << "\n";
            actualSeg = actualSeg->nextSeg;
        }
        actualCienpie = actualCienpie->nextAmigo;
    }
}

// **Modificada:** recibe el nombre para procesar y el archivo para escribir.
void coAlCrearMoleculaYExportar(ofstream &archivo, const string &nombre) {
    if (nombre.empty()) {
        cout << "No se encontro un nombre para crear la molecula." << endl;
        return;
    }

    Molecula mol;
    mol.cargaMolecula = 5;
    for (char i : nombre) {
        char lower_i = tolower(i);
        if (lower_i == 'a' || lower_i == 'e' || lower_i == 'i' || lower_i == 'o' || lower_i == 'u')
            coAlNewEnlaceAtomico(mol.nexVocal, -1, string(1, i));
        else
            coAlNewEnlaceAtomico(mol.nexConsonante, 1, string(1, i));
    }
    
    // Escribir los datos de la molécula en el archivo CSV.
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
    
    // También se muestra en la consola para la experiencia del usuario.
    coAlShowEnlaceAtomico(mol.nexConsonante);
    cout << "             /\n"
         << "Molecula: (" << mol.cargaMolecula << ")\n"
         << "             \\" << endl;
    coAlShowEnlaceAtomico(mol.nexVocal);
}

// **Modificada:** ahora devuelve el primer nombre para la molécula.
string coAlLeerDatosDesdeCSV(TCienPie &p, const string &filename) {
    string primerNombre = "";
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo de datos '" << filename << "'." << endl;
        return primerNombre;
    }

    string linea;
    while (getline(archivo, linea)) { // Bucle para leer cada línea
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

    // Leer los nombres y crear los cienpiés, y obtener el primer nombre.
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
        
        coAlShowCienPie(*actual);// Mostrar los cienpiés en consola 
                
        TTroncoSeg actualSeg = actual->tronco;
        while (actualSeg != NULL) {
            archivoSalida << actual->nombre << "," << actualSeg->caracterOriginal << "\n";
            actualSeg = actualSeg->nextSeg;
        }

        coAlCrearMoleculaYExportar(archivoSalida, actual->nombre);//crear la molecula
                actual = actual->nextAmigo;
    }

    archivoSalida.close();
    cout << "Archivo creado y actualizado: " << filename << endl;
    return 0;
}