#include <iostream>
using namespace std;

int main()
{
    int edad = 0;
    cout << "Ingresa tu edad: ";
    cin >> edad;

    if (edad < 0) 
        cout << "Edad no puede ser negativa." << endl;
    
    if (edad < 18) 
        cout << "Eres menor de edad." << endl;
    else
        cout << "Eres adulto." << endl;

}
