#include<iostream>
using namespace std;

// Funcion que recibe un parametro por valor
// Crea una copia de 'valor' y trabaja solo con la copia
int funcion(int valor)
{
    valor = valor + 10; // Solo se le suma 10 a la copia local
    return valor;
}

// Funcion que recibe un puntero (referencia)
// Trabaja directamente con la direccion de memoria de la variable original
int funcionPunteros(int* valor)
{
    *valor = *valor + 10; // Accede al valor original y lo modifica
    return *valor;
}

int main()
{
    int numero = 10;
    cout << "Param X Valor ";
    cout << "Antes de funcion " << numero << "\n"; // Salida: 10
    funcion(numero); // Se pasa el valor 10. La copia dentro de la funcion se modifica, no el original.
    cout << "Despues de funcion " << numero << "\n"; // Salida: 10 (El valor original no cambio)

    cout << "Param X Referencia ";
    cout << "Antes de funcionPunteros " << numero << "\n"; // Salida: 10
    funcionPunteros(&numero); // Se envia la direccion de memoria de 'numero'
    cout << "Despues de funcionPunteros " << numero << "\n"; // Salida: 20 (El valor original cambio)

    system("pause"); // Pausa la ejecucion en sistemas Windows
    return 0;
}