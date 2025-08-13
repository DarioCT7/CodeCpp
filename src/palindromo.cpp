#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "../lib/toolbox.h" // Librería personalizada con funciones como splitString, showWaiting, COLOR_BLUE, etc.
using namespace std;

string textFile = ""; // Acumula la visualización del análisis recursivo
int memo = 0;         // Controla la indentación visual en el archivo

// Estructura para almacenar cada línea del archivo
struct Dato {
    string caso;
    string texto;
    bool esPalindromo = false;
};

vector<Dato> lstDato; // Lista de datos leídos

// Elimina espacios en blanco de un string
string trimString(string str) {
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    return str;
}

// Muestra un dato en consola con formato
void showAlumnoMascota(Dato d) {
    cout << COLOR_BLUE << endl
         << "[+] DATO " << endl
         << " -  caso        : " << d.caso << endl
         << " -  texto       : " << d.texto << endl
         << " -  esPalindromo: " << d.esPalindromo << endl;
}

// Lee el archivo CSV y llena lstDato
void readFileAlumno(const string filePath) {
    string line = "";
    ifstream f(filePath, ios::in);
    
    if (!f) {
        cerr << "error al abrir el archivo: " << filePath << endl;
        return;
    }

    getline(f, line); // Ignora la primera línea (cabecera)
    while (getline(f, line)) {
        Dato d;
        vector<string> dataLine = splitString(line, ','); // Divide por coma
        cout << COLOR_RED << endl << showWaiting(line) << COLOR_BLUE;
        d.caso = dataLine[0];
        d.texto = trimString(dataLine[1]);
        lstDato.push_back(d);
        showAlumnoMascota(d);
    }
}

// Repite un carácter n veces (usado para visualización)
string repetirCaracter(const char c, int n) {
    if (n == 0) return "";
    return c + repetirCaracter(c, --n);
}

// Verifica si una palabra es palíndromo usando recursión
bool esPalindromo(const string palabra, int posIni = 0) {
    int posFin = palabra.length() - 1 - posIni;

    // Visualización del paso actual
    textFile += repetirCaracter(' ', memo++) +
                palabra[posIni] +
                repetirCaracter('.', posFin * 2) +
                palabra[posIni] + "\n";

    if (posIni == posFin) {
        memo += palabra.length(); // Ajuste visual
        return true;
    }

    if (palabra[posIni] == palabra[posFin])
        return esPalindromo(palabra, posIni + 1);

    memo = 0; // Reinicia indentación si falla
    return false;
}

// Escribe la visualización en un archivo
void writeFileAlumno(const string filePath) {
    ofstream f(filePath, ios::out | ios::app); 
    if (!f) {
        cerr << "Error al abrir el archivo: " << filePath << endl;
        return;
    }
    f << textFile;
    f.close();
}

// Función principal
int main() {
    readFileAlumno("../../datafile/examen.csv");

    cout << endl << endl
         << "------------ PROGRAMACION I ------------" << endl
         << "pat_mic" << endl
         << "caso A" << endl << endl
         << "PALINDROMA \tTEXTO" << endl;

    for (auto &&d : lstDato) {
        if (d.caso == "A") {
            textFile = ""; // Reinicia visualización
            if (esPalindromo(d.texto)) {
                d.esPalindromo = true;
                writeFileAlumno("palindromo.txt");
                cout << COLOR_BLUE << d.esPalindromo << "\t\t" << d.texto << endl;
            } else {
                cout << COLOR_RED << d.esPalindromo << "\t\t" << d.texto << endl;
            }
        }
    }

    return 0;
}
