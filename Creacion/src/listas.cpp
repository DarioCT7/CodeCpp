#include <iostream>
#include <list>

using namespace std;

int main() {
    // Declara una lista de enteros
    list<int> miLista = {10, 20, 30};

    // Agregar un elemento al principio
    miLista.push_front(5);

    // Agregar un elemento al final
    miLista.push_back(40);

    // Iterar y mostrar la lista
    cout << "Lista despues de agregar elementos:" << endl;
    for (int elemento : miLista) {
        cout << elemento << " ";
    }
    cout << endl; // Salida: 5 10 20 30 40

    // Eliminar un elemento (por ejemplo, 20)
    miLista.remove(20);

    // Mostrar la lista después de la eliminación
    cout << "Lista despues de eliminar 20:" << endl;
    for (int elemento : miLista) {
        cout << elemento << " ";
    }
    cout << endl; // Salida: 5 10 30 40

    return 0;
}