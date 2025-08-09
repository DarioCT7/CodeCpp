#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <windows.h> 
#include "../lib/toolboxs.h"
using namespace std;

// Variables globales
const int coAlHoras = 24;
const int coAlDias = 5;
string coAlDiasSemana[coAlDias] = {"Lune", "Martes", "Miercoles", "Jueves", "Viernes"};
string coAlNombre = "Coral Tonguino Alex Dario";
string coAlCedula = "1726248915";
string coAlNacimiento = "1997-07-29";
string coAlEdad = "28";
string coAlArchivo; 
string coAlLetraOrigen = "Coral Tonguino Alex Dario";
// Matriz de horario
string coAlHorario[coAlHoras][coAlDias];

// Función para obtener el directorio del ejecutable y establecer la ruta de datafile
string getProjectRootPath() {
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH); // Obtiene la ruta completa del ejecutable
    string exePath = path;
    // Retroceder desde src\output al directorio raíz del proyecto (dos niveles arriba)
    size_t pos = exePath.find_last_of("\\");
    if (pos != string::npos) {
        exePath = exePath.substr(0, pos); // Elimina el nombre del ejecutable
        pos = exePath.find_last_of("\\");
        if (pos != string::npos) {
            exePath = exePath.substr(0, pos); // Retrocede a src
            pos = exePath.find_last_of("\\");
            if (pos != string::npos) {
                exePath = exePath.substr(0, pos); // Retrocede al directorio raíz
            }
        }
    }
    return exePath + "\\datafile\\CoralAlex.csv";
}
// Función para generar el CSV según caso impar (ultimo digito = 5)
void coAlGenerarCSV() {
    // Crear el directorio 'datafile' si no existe
    string folderPath = coAlArchivo.substr(0, coAlArchivo.find_last_of("\\"));
    CreateDirectory(folderPath.c_str(), NULL);
    ofstream archivo(coAlArchivo);
    archivo << "HORA,LETRA\n";
    string letra = coAlLetraOrigen;
    // NUEVO: Cédula + Fecha sin guiones + Edad
    string digitos = "172624891519970729"; 
    size_t digIndex = 0; // Usamos size_t para evitar advertencia
    for (char c : letra) {
        char dig = digitos[digIndex];
        int hora = dig - '0'; // Convertir char a digito entero
        archivo << hora << "," << c << "\n";

        digIndex++;
        if (digIndex == digitos.size()) digIndex = 0;
    }
    archivo.close();
    cout << "Archivo generado: " << coAlArchivo << endl;
}
// Leer archivo y llenar horario
void coAlCargarHorarioDesdeCSV() {
    ifstream archivo(coAlArchivo);
    string linea;
    getline(archivo, linea); // Encabezado
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        size_t coma = linea.find(",");
        int hora = stoi(linea.substr(0, coma));
        char letra = linea[coma + 1];
        if (hora < 0 || hora >= coAlHoras) continue;
        for (int d = 0; d < coAlDias; d++) {
            if (coAlHorario[hora][d] == "") {
                coAlHorario[hora][d] = letra;
                break;
            }
        }
    }
    archivo.close();
}
// Mostrar horario con colores
void coAlMostrarHorario() {
    map<int, int> conteoHoras;
    int maxOcurrencias = 0;
    // Contar ocurrencias por hora
    for (int h = 0; h < coAlHoras; h++) {
        int total = 0;
        for (int d = 0; d < coAlDias; d++) {
            if (!coAlHorario[h][d].empty()) total++;
        }
        conteoHoras[h] = total;
        if (total > maxOcurrencias) maxOcurrencias = total;
    }
    // Mostrar encabezado
    cout << setw(6) << "Hora";
    for (string dia : coAlDiasSemana) {
        cout << setw(6) << COLOR_GREEN << dia << COLOR_RESET;
    }
    cout << endl;
    // Mostrar cada fila
    for (int h = 0; h < coAlHoras; h++) {
        if (conteoHoras[h] == maxOcurrencias && maxOcurrencias > 0)
            cout << COLOR_RED;
        else if (conteoHoras[h] == 0)
            cout << COLOR_YELLOW;
        cout << setw(6) << h;
        for (int d = 0; d < coAlDias; d++) {
            cout << setw(6) << (coAlHorario[h][d].empty() ? " " : coAlHorario[h][d]);
        }
        cout << COLOR_RESET << endl;
    }
    cout << "\nHora mas concurrida: ";
    for (auto& par : conteoHoras) {
        if (par.second == maxOcurrencias && maxOcurrencias > 0)
            cout << par.first << " ";
    }
    cout << "\nHoras libres: ";
    for (auto& par : conteoHoras) {
        if (par.second == 0)
            cout << par.first << " ";
    }
    cout << endl;
}
int main() {
       coAlArchivo = getProjectRootPath();
    cout << "Programacion en C++" << endl;
    cout << "Cedula: " << coAlCedula << endl;
    cout << "Nombre: " << coAlNombre << endl;
    cout << "Cedula termina en impar\n";
    coAlGenerarCSV();
    coAlCargarHorarioDesdeCSV();
    coAlMostrarHorario();
    return 0;
}