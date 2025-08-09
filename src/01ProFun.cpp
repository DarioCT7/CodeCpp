#include <iostream>
using namespace std;

void sumar(){
    int a;
    char nro1[]="   "; 
    do
    {
        cout << "Ingresa un numero: ";
        cin >> nro1;
        cout << "El numero ingresado es: " <<nro1 << endl;
        if(isdigit(nro1[0]) == 0) {
            cout << "Por favor, ingresa un numero valido." << endl;
            continue;
        }
        a = atoi(nro1);
    } while (a < 0);

    cout << "La suma es: " << (a + 10) << endl;
}

int main() {
    sumar();
    return 0;
}