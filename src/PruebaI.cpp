#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../lib/toolbox.h"
using namespace std;

string  alumnoNombre,  alumnoCedula;
vector<vector<string>> cronograma;

void initialize() {
    alumnoCedula = "111234567890";  
    alumnoNombre = "Aaalex Juan Perez Sang";
    alumnoCedula = alumnoCedula + alumnoCedula;  
    cronograma   = { {  "Hora", "Lun","Mar","Mie","Jue","Vie"}   };
    cronograma.resize(24, vector<string>(6, "")); // 24 horas + 1 encabezado, hora y 5 días
    for (int i = 1; i <= 23; ++i)       
        cronograma[i][0] = to_string(i);   // <-- {i,   "" ,  "" ,  ""  , "" ,  ""} 
}
void writeFile(const string& fileName) {
    ofstream f(fileName, ios::out | ios::trunc); 
    if (!f) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return;
    }
    // Escribir los datos en el archivo
    f << "HORA, LETRA" << endl; 
    for (size_t   i = 0; i < alumnoCedula.length() ; i++)
        if (i <= alumnoNombre.length())
             f << alumnoCedula[i] << ", "<< alumnoNombre[i] << endl ;
    f.close();
}
void readFile(const string& fileName) {
    ifstream f(fileName); 
    string line;

    if (!f) {
        cerr << "Error con el archivo: " << fileName << endl;
        return;
    }
    
    getline(f, line);
    while (getline(f, line)) {
        int hora    = stoi(line.substr(0, line.find(',')));  // Extrae la hora de line = "01,A"
        string letra= line.substr(line.find(',') + 1);      // Extrae la letra de line = "01,A"
        //cout << hora << "\t"<< letra << endl; 
        if (letra.empty() )  // vsalidar hora
            continue;                   // Si la letra está vacía, no hacer nada
        cronograma[hora][1] += letra;   // Asigna la letra a la hora correspondiente en el cronograma
    }
    f.close();
}

int main() {
    int f=0,fMax=0;
    size_t  maxLogCel=0;
    string  fVacia = "",
            nombreArchivo = "../../datafile/pruebaAlumno.csv";
    
    initialize();
    writeFile(nombreArchivo);
    readFile(nombreArchivo);

    cout<< COLOR_BLUE
        << "\t__________________________"       << endl
        << "\t - MATERIA:  "  << "Programacio I"<< endl
        << "\t - CEDULA:   "  <<  alumnoCedula  << endl 
        << "\t - NOMBRE:   "  <<  alumnoNombre  << endl
        << "\t__________________________"       << endl
        << COLOR_RESET;

    for (const auto& fila : cronograma) {
        for (const auto& celda : fila) 
            cout << (celda.empty() ? "" : celda) << "\t";

        if (cronograma[f][1].empty()) 
            fVacia += to_string(f) + ", ";

        if (cronograma[f][1].length() > maxLogCel) 
        {
            maxLogCel = cronograma[f][1].length();
            fMax=f;
        }
        cout << endl;
        f++;
    }
    cout << COLOR_BLUE << "Horas vacias: "           << fVacia << endl;
    cout << COLOR_RED  << "Hora mas concurrida: "    << fMax   << endl;
    return 0;
}