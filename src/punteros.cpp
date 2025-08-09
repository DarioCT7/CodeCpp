#include <iostream>

int main() {
    int num = 100; // Declara una variable entera 'num' y la inicializa con 100
    int *apuntador_num; // Declara un puntero a un entero
    apuntador_num = &num; // Asigna al puntero la direccion de memoria de 'num'

    std::cout << "num: " << num << std::endl; // Muestra el valor de 'num'
    std::cout << "&num: " << &num << std::endl; // Muestra la direccion de memoria de 'num'
    std::cout << "apuntador_num: " << apuntador_num << std::endl; // Muestra el contenido del puntero (la direccion de 'num')
    std::cout << "*apuntador_num: " << *apuntador_num << std::endl; // Muestra el valor al que apunta el puntero
    std::cout << "&apuntador_num: " << &apuntador_num << std::endl; // Muestra la direccion de memoria del puntero en si

    char letra; // Declara una variable de tipo char
    char *apuntador; // Declara un puntero a un caracter
    apuntador = &letra; // Asigna la direccion de 'letra' al puntero
    *apuntador = 'x'; // Usa el puntero para asignar el valor 'x' a la variable 'letra'
    std::cout << "letra: " << letra << std::endl; // Muestra el valor de 'letra'
    
    return 0;
}