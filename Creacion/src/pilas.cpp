#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    // Declara una pila de cadenas de texto
    stack<string> miPila;

    // Agregar elementos (push)
    miPila.push("Hola");
    miPila.push("Mundo");
    miPila.push("C++");

    // El último elemento en entrar es C++
    cout << "Elemento superior de la pila: " << miPila.top() << endl; // Salida: C++

    // Quitar elementos (pop)
    miPila.pop(); // Quita C++

    // El nuevo elemento superior es Mundo
    cout << "Nuevo elemento superior: " << miPila.top() << endl; // Salida: Mundo

    // Quitar todos los elementos
    while (!miPila.empty()) {
        cout << "Sacando: " << miPila.top() << endl;
        miPila.pop();
    }
    
    // Ahora la pila está vacía
    if (miPila.empty()) {
        cout << "La pila esta vacia." << endl;
    }

    return 0;
}