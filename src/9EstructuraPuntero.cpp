#include <iostream>
#include <string.h> 
using namespace std;

// Define la estructura para una mascota
struct mascota
{
    //int  id; // Una variable que podria ser el ID, pero esta comentada.
    char name[20]; // Un array de caracteres para el nombre de la mascota
    char *ptrName; // Un puntero a un caracter (se usara para apuntar al nombre)
};

// Declara una estructura 'gatito' y un puntero 'ptrGatito'
// que apunta a la direccion de 'gatito'
mascota gatito, *ptrGatito = &gatito;

// Funcion para ingresar datos usando un puntero global
void datosGatito() {
    cout << "Ingrese su nombre: ";
    // Lee una linea de texto y la guarda en el nombre de la estructura
    // Se usa ptrGatito->name para acceder al miembro a traves del puntero
    cin.getline(ptrGatito->name, 50, '\n');
    // Muestra el nombre usando el puntero y la variable de estructura
    cout << "ptrGatito: "   << ptrGatito->name  << endl;
    cout << "gatito: "      << gatito.name  << endl;
}
// Funcion para ingresar datos usando un puntero pasado por parametro
void datosGatitoParametro(struct mascota *ptrCat) {
    cout << "Ingrese su nombre: ";
    cin.getline(ptrCat->name, 50, '\n');

    // Muestra el nombre usando el puntero pasado
    cout << "ptrCat: "   << ptrCat->name  << endl;
    // La linea de abajo esta comentada porque ptrCat es un puntero, no una estructura
    //cout << "cat: "      << ptrCat.name  << endl;
}
int main()
{
    // Bloque 1: Usa la funcion con la variable global
    datosGatito();
    cin.get(); // Pausa la ejecucion
    // Bloque 2: Usa un array de estructuras y gestiona memoria dinamica
    mascota lstMascotas[2]; // Array de 2 mascotas en el stack
    for (int i = 0; i < 2; i++)
    {
        cout<<"Nombre de mascota: ";
        fgets(lstMascotas[i].name,20,stdin); // Lee el nombre
        int len = strlen(lstMascotas[i].name); // Obtiene la longitud del nombre
        // Asigna memoria dinamicamente para el nombre
        lstMascotas[i].ptrName = (char *)malloc(len * sizeof(char));
        if(NULL == lstMascotas[i].ptrName )
            cout<<"No hay memoria";
        else{
            // Copia el nombre al espacio de memoria recien creado
            strcpy(lstMascotas[i].ptrName , lstMascotas[i].name );
            //free(lstMascotas->ptrName); // Esto libera la memoria, pero esta comentada
        }
    }
    // Recorre el array y muestra los nombres usando el puntero
    for (auto &&m : lstMascotas)
        cout<<m.ptrName;
    // Bloque 3: Usa new para crear una estructura dinamica y la pasa a una funcion
    mascota *p =  new  struct mascota; // Crea una mascota en el heap y asigna su direccion a 'p'
    datosGatitoParametro(p); // Pasa el puntero a la funcion
    cin.get(); // Pausa la ejecucion
    return 0; 
}