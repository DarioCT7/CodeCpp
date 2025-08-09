#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <string>

using namespace std;

int main() {
    queue<string> colaDeTareas;
    stack<string> pilaDeDeshacer;
    list<string> listaDeCompletadas;

    // Paso 1: Añadir nuevas tareas a la cola
    colaDeTareas.push("Tarea 1: Escribir código");
    colaDeTareas.push("Tarea 2: Realizar pruebas");
    colaDeTareas.push("Tarea 3: Documentar");

    // Paso 2: Procesar las tareas de la cola (FIFO)
    cout << "Procesando tareas..." << endl;
    while (!colaDeTareas.empty()) {
        string tareaActual = colaDeTareas.front();
        colaDeTareas.pop();

        cout << "  -> Procesando: " << tareaActual << endl;

        // La tarea procesada se guarda en el historial y en la pila de deshacer
        listaDeCompletadas.push_back(tareaActual);
        pilaDeDeshacer.push(tareaActual);
    }
    cout << "Todas las tareas han sido procesadas." << endl;

    // Paso 3: Usar la pila para deshacer la última tarea
    cout << "\nÚltima tarea completada (deshacer): " << pilaDeDeshacer.top() << endl;
    pilaDeDeshacer.pop();

    // Paso 4: Mostrar el historial completo de tareas
    cout << "\nHistorial de tareas completadas:" << endl;
    for (const auto& tarea : listaDeCompletadas) {
        cout << "  - " << tarea << endl;
    }

    return 0;
}