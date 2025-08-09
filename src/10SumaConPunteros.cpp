#include <iostream>
using namespace std;
// Variable global, aunque no se usa en la funcion 'sum'
int * a;
// Funcion recursiva para sumar los elementos de un array
int sum(int* a, int n) {
    // Caso base: si ya no quedan elementos, la suma es 0
    if (n == 0) {
        return 0;
    }
    // Paso recursivo: suma el ultimo elemento y llama a la funcion con un elemento menos
    return sum(a, n - 1) + a[n - 1];
}
int main() {
    int n = 0;
    int * a;
    cout<<"Ingresa cantidad de elementos:" <<endl;
    cin >> n;
    if( n <= 0) // Valida que la cantidad sea positiva
        return 0;
    // Reserva memoria dinamica para 'n' enteros en el heap
    a = new int[n];
    cout<<"Ingresa elementos:" <<endl;
    for( int i = 0; i < n; i++)
        cin >> a[i]; // Lee cada entero y lo guarda en el array
    cout<<"La suma es:" <<endl;
    cout << sum(a, n) << endl; // Llama a la funcion recursiva
    // Libera la memoria que fue reservada con 'new'
    // Esto es muy importante para evitar fugas de memoria
    delete[] a;
    return 0;
}