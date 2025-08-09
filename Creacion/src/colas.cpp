#include <iostream>
#include <queue>

using namespace std;

int main() {
    // Declara una cola de caracteres
    queue<char> miCola;

    // Agregar elementos (push)
    miCola.push('A');
    miCola.push('B');
    miCola.push('C');

    // El primer elemento en entrar es A
    cout << "Primer elemento en la cola: " << miCola.front() << endl; // Salida: A

    // Quitar elementos (pop)
    miCola.pop(); // Quita A

    // El nuevo primer elemento es B
    cout << "Nuevo primer elemento: " << miCola.front() << endl; // Salida: B

    // Quitar todos los elementos
    while (!miCola.empty()) {
        cout << "Atendiendo: " << miCola.front() << endl;
        miCola.pop();
    }
    
    // Ahora la cola está vacía
    if (miCola.empty()) {
        cout << "La cola de atencion esta vacia." << endl;
    }

    return 0;
}