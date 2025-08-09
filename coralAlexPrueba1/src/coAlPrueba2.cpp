#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
#include "../lib/toolboxs.h" 

using namespace std;

// Datos del estudiante
string coAlCedula = "1726248915";
string coAlNombreCompleto = "Coral Alex";
string coAlMateria = "Programacion I";
string coAlCasoEstudio = "Palindromos";

// Estructura para cada palabra
struct coAlRegistro {
    string coAlCaso;
    string coAlTexto;
    bool coAlEsPalindromo = false;
};

// Funcion recursiva para verificar e imprimir letras en forma escalonada
bool coAlEsPalindromoRecursivo(const string& coAlTexto, int coAlInicio, int coAlFin, int coAlNivel, ofstream& coAlArchivoEscritura, bool& coAlEsPalindromoFinal) {
    if (coAlInicio > coAlFin) {
        coAlEsPalindromoFinal = true;
        return true;
    }

    int coAlEspacios = coAlNivel * 2;
    coAlArchivoEscritura << string(coAlEspacios, ' ') << coAlTexto[coAlInicio];

    if (coAlInicio != coAlFin) {
        int coAlDistancia = (coAlTexto.length() - 1 - coAlNivel * 2) * 2;
        coAlArchivoEscritura << string(coAlDistancia, ' ') << coAlTexto[coAlFin];
    }
    coAlArchivoEscritura << endl;


    if (coAlTexto[coAlInicio] != coAlTexto[coAlFin]) {
        coAlEsPalindromoFinal = false;
        return false;
    }

    return coAlEsPalindromoRecursivo(coAlTexto, coAlInicio + 1, coAlFin - 1, coAlNivel + 1, coAlArchivoEscritura, coAlEsPalindromoFinal);
}

//  Procesar archivo y guardar resultados
void coAlProcesarDatos() {
    ifstream coAlArchivoLectura("examen.csv");
    if (!coAlArchivoLectura.is_open()) {
        cerr << COLOR_RED << "Error: No se pudo abrir el archivo 'examen.csv'." << COLOR_RESET << endl;
        return;
    }

    ofstream coAlArchivoEscritura("CoralAlex.csv");
    if (!coAlArchivoEscritura.is_open()) {
        cerr << COLOR_RED << "Error: No se pudo crear el archivo 'CoralAlex.csv'." << COLOR_RESET << endl;
        coAlArchivoLectura.close();
        return;
    }

    string coAlLinea;
    getline(coAlArchivoLectura, coAlLinea); // Omitir encabezado

    while (getline(coAlArchivoLectura, coAlLinea)) {
        vector<string> coAlPartes = splitString(coAlLinea, ',');
        if (coAlPartes.size() >= 2) {
            coAlRegistro coAlRegistroDatos;
            coAlRegistroDatos.coAlCaso = coAlPartes[0];
            coAlRegistroDatos.coAlTexto = coAlPartes[1];

            mostrarSpinner(coAlCedula.back()); //muesta el espinner

            coAlArchivoEscritura << "Texto: " << coAlRegistroDatos.coAlTexto << endl;
            int coAlNivelRecursion = 0;
            bool coAlEsPalindromoFinal = false;

            coAlEsPalindromoRecursivo(
                coAlRegistroDatos.coAlTexto,
                0,
                coAlRegistroDatos.coAlTexto.length() - 1,
                coAlNivelRecursion,
                coAlArchivoEscritura,
                coAlEsPalindromoFinal
            );

            coAlArchivoEscritura << (coAlEsPalindromoFinal ? "palindromo" : "no es palindromo") << endl;
            coAlArchivoEscritura << endl;
        }
    }

    coAlArchivoLectura.close();
    coAlArchivoEscritura.close();
    cout << "Procesamiento finalizado. Resultados guardados en 'CoralAlex.csv'." << endl;
}

// Mostrar resultados por consola
void coAlPresentarResultados() {
    cout << COLOR_YELLOW << "Materia: " << coAlMateria << COLOR_RESET << endl;
    cout << COLOR_YELLOW << "Cedula: " << coAlCedula << COLOR_RESET << endl;
    cout << COLOR_YELLOW << "Nombre completo: " << coAlNombreCompleto << COLOR_RESET << endl;
    cout << COLOR_YELLOW << "Caso de estudio: " << coAlCasoEstudio << COLOR_RESET << endl;
    cout << "------------------------------------------" << endl;

    ifstream coAlArchivoLectura("CoralAlex.csv");
    if (!coAlArchivoLectura.is_open()) {
        cerr << COLOR_RED << "Error: No se pudo abrir el archivo de resultados." << COLOR_RESET << endl;
        return;
    }

    string coAlLinea;
    while (getline(coAlArchivoLectura, coAlLinea)) {
        if (coAlLinea.find("palindromo") != string::npos) {
            cout << COLOR_BLUE << coAlLinea << COLOR_RESET << endl;
        } else if (coAlLinea.find("no es palindromo") != string::npos) {
            cout << COLOR_RED << coAlLinea << COLOR_RESET << endl;
        } else {
            cout << coAlLinea << endl;
        }
    }
    coAlArchivoLectura.close();
}

int main() {
    coAlProcesarDatos();
    coAlPresentarResultados();
    return 0;
}
