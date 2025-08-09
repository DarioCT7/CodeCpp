#ifndef TOOLBOXS_H
#define TOOLBOXS_H

#include <string>
#include <limits>
#include <vector>
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

using namespace std;

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"

vector<string> splitString(const string& s, const char delimiter) 
{
    vector<string> tokens;
    string token;
    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != string::npos) {
        token = s.substr(start, end - start);
        tokens.push_back(token);
        start = end + 1;
        end = s.find(delimiter, start);
    }
    tokens.push_back(s.substr(start)); 
    return tokens;
}

string getConsoleCadena(const string& mensaje = "Ingrese una cadena: ") 
{
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

int getConsoleNumero(const string& mensaje = "Ingrese un numero: ", int minimo = 0, int maximo = 10) 
{
    int valor;
    cout << mensaje;

    while (true) {
        cin >> valor;
        if (!cin.fail() && valor >= minimo && valor <= maximo)
            break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ":( valor entre " << minimo << " - " << maximo << ", " << mensaje;
    }
    return valor;
}

// Spinner especial según último dígito de la cédula
inline void mostrarSpinner(char ultimoDigito) {
    vector<char> spinner = {'|', '/', '-', '\\'};
    int repeticiones = (ultimoDigito - '0') + 1;

    for (int i = 0; i < repeticiones; ++i) {
        for (char c : spinner) {
            cout << "\rProcesando " << c << flush;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    cout << "\rProcesamiento finalizado." << endl;
}

// Animación estilo "o0o"
string showWaiting(const string msg = "")
{
    vector<string> animacion = {"0oo", "o0o", "oo0", "o0o"};
    size_t animacionLength = animacion.size();

    for (size_t i = 0; i <= 20; i++)
    {
        cout << "\r" << animacion[i % animacionLength] << " ... " + msg;
        Sleep(100);
    }
    cout.flush();
    return "";
}

#endif
