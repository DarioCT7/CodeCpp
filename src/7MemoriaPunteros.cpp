#include <iostream>
#include <stdlib.h> 
using namespace std;

// Funcion para crear una matriz usando malloc
int **crearMatrizMalloc(int f, int c)
{
    int **m=NULL;
    // Asigna un array de 'f' punteros a enteros
    m = (int **) malloc(f*sizeof(int *));
    for (int i = 0; i < f; i++)
        // Para cada puntero, asigna un array de 'c' enteros
        m[i] = (int *) malloc(c*sizeof(int));
    return m;
}
// Funcion para crear una matriz usando calloc (inicializa a cero)
int **crearMatrizCalloc(int f, int c)
{
    int **m=NULL;
    // Asigna y limpia la memoria con ceros
    m = (int **) calloc(f, sizeof(int *));
    for (int i = 0; i < f; i++)
        m[i] = (int *) calloc(c, sizeof(int));
    return m;
}
// Funcion para crear una matriz usando new de C++
int **crearMatrizNew(int f, int c)
{
    int **m=NULL;
    // Asigna un array de punteros
    m = new int*[f];
    for (int i = 0; i < f; i++)
        // Para cada puntero, asigna un array de enteros
        m[i] = new int[c];
    return m;
}
// Funcion para mostrar la matriz en la consola
void showMatriz(int **pd, int f,int c)
{
    for (int i = 0; i < f; i++)
    {
            for (int j = 0; j < c; j++)
                cout<< pd[i][j] <<"\t";
            cout<< endl;
    }
}
int main()
{
    int f = 0, c = 0;
    int **pd=NULL;
    cout<<"Ingresa fila y columnas de la matriz : ";
    cin>> f >> c;
    // Llama a la funcion para crear la matriz usando 'new'
    pd = crearMatrizNew(f,c);
    // Rellena la matriz con numeros aleatorios
    for (int i = 0; i < f; i++)
        for (int j = 0; j < c; j++)
            pd[i][j] = rand() % 10;
    // Muestra la matriz
    showMatriz(pd,f,c);
    // Es importante liberar la memoria, lo cual falta en este codigo
    // por lo que generaria una fuga de memoria.
    for (int i = 0; i < f; ++i) {
        delete[] pd[i];
    }
    delete[] pd;

    return 0;
}