#include <iostream>      // Para imprimir en consola
#include <string>        // Para manipular cadenas de texto
#include <vector>        // Para usar vectores (listas dinámicas)
#include <fstream>       // Para leer y escribir archivos
#include "../lib/toolbox.h" // Librería personalizada (colores, funciones auxiliares)
using namespace std;

// Variables globales para almacenar datos del alumno y el cronograma
string alumnoNombre, alumnoCedula;
vector<vector<string>> cronograma; // Matriz de 24 horas x 6 columnas (hora + días)
void initialize() {
    alumnoCedula = "111234567890";           // Cédula base del alumno
    alumnoNombre = "Aaalex Juan Perez Sang"; // Nombre del alumno

    alumnoCedula = alumnoCedula + alumnoCedula; // Duplica la cédula (ahora tiene 24 caracteres)

    // Primera fila del cronograma: encabezado con días de la semana
    cronograma = { { "Hora", "Lun", "Mar", "Mie", "Jue", "Vie" } };

    // Redimensiona el cronograma a 24 filas (una por hora), cada una con 6 columnas
    cronograma.resize(24, vector<string>(6, ""));

    // Asigna el número de hora en la primera columna de cada fila
    for (int i = 1; i <= 23; ++i)
        cronograma[i][0] = to_string(i); // Ejemplo: fila[1] = {"1", "", "", "", "", ""}
}
void writeFile(const string& fileName) {
    ofstream f(fileName, ios::out | ios::trunc); // Abre archivo para escritura (borra contenido previo)
    if (!f) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return;
    }

    f << "HORA, LETRA" << endl; // Encabezado del archivo

    // Recorre cada carácter de la cédula
    for (size_t i = 0; i < alumnoCedula.length(); i++)
        if (i <= alumnoNombre.length()) // Solo si hay letra correspondiente en el nombre
            f << alumnoCedula[i] << ", " << alumnoNombre[i] << endl; // Ejemplo: "1, A"
    
    f.close(); // Cierra el archivo
}
void readFile(const string& fileName) {
    ifstream f(fileName); // Abre archivo para lectura
    string line;

    if (!f) {
        cerr << "Error con el archivo: " << fileName << endl;
        return;
    }

    getline(f, line); // Ignora la primera línea (encabezado)

    while (getline(f, line)) {
        // Extrae la hora (parte antes de la coma)
        int hora = stoi(line.substr(0, line.find(',')));

        // Extrae la letra (parte después de la coma)
        string letra = line.substr(line.find(',') + 1);

        if (letra.empty()) // Si no hay letra, salta esta línea
            continue;

        // Asigna la letra al día lunes (columna 1) en la fila correspondiente a la hora
        cronograma[hora][1] += letra;
    }

    f.close(); // Cierra el archivo
}
int main() {
    int f = 0, fMax = 0;           // f: índice de fila actual, fMax: hora más concurrida
    size_t maxLogCel = 0;         // Longitud máxima de letras en una celda
    string fVacia = "";           // Lista de horas vacías
    string nombreArchivo = "../../datafile/pruebaAlumno.csv"; // Ruta del archivo

    initialize();                 // Inicializa datos y cronograma
    writeFile(nombreArchivo);    // Escribe archivo con pares cédula-nombre
    readFile(nombreArchivo);     // Lee archivo y llena el cronograma

    // Muestra encabezado con datos del alumno
    cout << COLOR_BLUE
         << "\t__________________________" << endl
         << "\t - MATERIA:  " << "Programacio I" << endl
         << "\t - CEDULA:   " << alumnoCedula << endl
         << "\t - NOMBRE:   " << alumnoNombre << endl
         << "\t__________________________" << endl
         << COLOR_RESET;

    // Recorre el cronograma para mostrarlo y analizarlo
    for (const auto& fila : cronograma) {
        for (const auto& celda : fila)
            cout << (celda.empty() ? "" : celda) << "\t"; // Muestra cada celda

        // Si la celda del lunes está vacía, guarda la hora
        if (cronograma[f][1].empty())
            fVacia += to_string(f) + ", ";

        // Si la celda del lunes tiene más letras que el máximo anterior
        if (cronograma[f][1].length() > maxLogCel) {
            maxLogCel = cronograma[f][1].length();
            fMax = f; // Guarda la hora más concurrida
        }

        cout << endl;
        f++; // Avanza a la siguiente fila
    }

    // Muestra estadísticas finales
    cout << COLOR_BLUE << "Horas vacías: " << fVacia << endl;
    cout << COLOR_RED  << "Hora más concurrida: " << fMax << endl;

    return 0;
}
