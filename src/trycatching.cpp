#include <iostream>
#include <windows.h>  // Para SetConsoleOutputCP en Windows
using namespace std;

// Enumeración para codificar errores específicos
enum ERRORES {
    E_DIVISION = 500,     // División por cero
    E_NUM_NEGATIVO,       // Números negativos
    E_NUM_MAX             // b mayor que a
};

int main()
{
    int a, b, c;

    // Solicitar valores al usuario
    cout << " ingresa a: "; cin >> a;
    cout << " ingresa b : "; cin >> b;

    try
    {
        // Validaciones antes de realizar la división
        if (b == 0)
            throw 500;  // Lanzar excepción: división por cero

        if (a < 0 || b < 0)
            throw 501;  // Lanzar excepción: número negativo

        if (b > a)
            throw 502;  // Lanzar excepción: b mayor que a

        // Si todo está bien, realizar la división
        c = a / b;
        cout << "La division es : " << c << endl << endl;
    }
    catch (const int e)  // Captura de excepción por código
    {
        SetConsoleOutputCP(CP_UTF8);  // Activar salida UTF-8 para mostrar emojis

        // Mensaje genérico de error
        cout << " 💀 quisiste verme morir...." << endl;

        // Interpretar el código de error
        switch (e)
        {
            case E_DIVISION:
                cout << "Error: División por cero no permitida." << endl;
                break;

            case E_NUM_NEGATIVO:
                cout << "Error: Números negativos no permitidos." << endl;
                break;

            case E_NUM_MAX:
                cout << "Error: El divisor es mayor que el dividendo." << endl;
                break;

            default:
                cout << "Error desconocido." << endl;
                break;
        }
    }

    // Mensaje final
    cout << " -- FIN -- " << endl << endl;
}
