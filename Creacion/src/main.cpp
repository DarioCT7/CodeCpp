#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//  Función para crear carpeta
bool crearCarpeta(const string& ruta) {
    if (CreateDirectoryA(ruta.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        cout << " Carpeta '" << ruta << "' creada o ya existe.\n";
        return true;
    } else {
        cerr << " Error al crear carpeta. Codigo: " << GetLastError() << "\n";
        return false;
    }
}

//  Función para leer archivo CSV
vector<vector<string>> leerCSV(const string& archivoRuta) {
    ifstream archivo(archivoRuta);
    vector<vector<string>> datos;

    if (!archivo.is_open()) {
        cerr << " No se pudo abrir el archivo: " << archivoRuta << '\n';
        return datos;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string valor;
        vector<string> fila;

        while (getline(ss, valor, ',')) {
            fila.push_back(valor);
        }

        datos.push_back(fila);
    }

    archivo.close();
    cout << " Archivo leido correctamente: " << archivoRuta << '\n';
    return datos;
}

//  Función para escribir archivo CSV
bool escribirCSV(const string& archivoRuta, const vector<vector<string>>& datos) {
    ofstream archivo(archivoRuta);

    if (!archivo.is_open()) {
        cerr << " No se pudo abrir el archivo para escritura: " << archivoRuta << '\n';
        return false;
    }

    for (const auto& fila : datos) {
        for (size_t i = 0; i < fila.size(); ++i) {
            archivo << fila[i];
            if (i < fila.size() - 1) archivo << ',';
        }
        archivo << '\n';
    }

    archivo.close();
    cout << " Archivo guardado en: " << archivoRuta << '\n';
    return true;
}

//  Función principal
int main() {
    const string rutaCarpeta = "..\\..\\datafile";
    const string archivoEntrada = rutaCarpeta + "\\examen.csv";
    const string archivoSalida  = rutaCarpeta + "\\salida.csv";

    if (crearCarpeta(rutaCarpeta)) {
        auto contenido = leerCSV(archivoEntrada);

        // Puedes modificar 'contenido' aquí si lo deseas

        escribirCSV(archivoSalida, contenido);
    }

    return 0;
}
