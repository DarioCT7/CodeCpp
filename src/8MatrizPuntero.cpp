#include <iostream>
using namespace std;

// Función para mostrar un vector, recibe un array de enteros y su tamaño
void showVector(int v[], int c){
    for (int i = 0; i < c; i++)
        cout<<v[i]<<"\t";
    cout<<endl;
}
// Función para mostrar un vector usando un puntero a entero
// (Un array se puede pasar como un puntero al primer elemento)
void showPtrVector(int *pv, int c){
    for (int i = 0; i < c; i++)
        cout<<pv[i]<<"\t"; // Se accede al elemento como si fuera un array
    cout<<endl;
}
// Función para mostrar una matriz, el compilador necesita el tamaño de las columnas
void showMatriz(int m[][3], int f, int c){
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
            cout<< m[i][j] <<"\t";
        cout<< endl;
    }
}
// Función para tratar una matriz como un vector de una sola dimensión
// La fórmula i*c+j calcula el índice del elemento m[i][j] en un array plano
void showMatrizComoVector(int mv[], int f, int c){
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
            cout<< mv[i*c+j] <<"\t";
        cout<< endl;
    }
}
// Función para mostrar una matriz usando un puntero simple a su primer elemento
// Accede a los elementos usando aritmética de punteros
void showPtrMatriz(int *p, int f,int c)
{
   for (int i = 0; i < f; i++)
   {
        for (int j = 0; j < c; j++)
            cout<< *(p+i * c+j) <<"\t"; // (p + i*c) es el puntero a la fila i, +j es el elemento j
        cout<< endl;
   }
}
// Función para mostrar una matriz usando un array de punteros a enteros
void showVectorPtrMatriz(int *vp[], int f,int c)
{
   for (int i = 0; i < f; i++)
   {
        for (int j = 0; j < c; j++)
            cout<< vp[i][j] <<"\t"; // Accede a cada elemento a traves del array de punteros
        cout<< endl;
   }
}
// Función para mostrar una matriz usando un puntero de punteros a enteros
// Es la forma más flexible para matrices dinámicas
void showPtrDobleMatriz(int **pd, int f,int c)
{
   for (int i = 0; i < f; i++)
   {
        for (int j = 0; j < c; j++)
            cout<< pd[i][j] <<"\t";
        cout<< endl;
   }
}
// Muestra las opciones de uso de un array de punteros
void showArrayVector(){
    int ai[]={1,3,5,7,9};
    int *pi;
    pi = ai; // El puntero pi apunta al inicio del array ai
    *(pi+0) = 10;   // Se cambia el primer elemento del array a traves del puntero
    showPtrVector(pi,5); // Muestra el array modificado
}
int main(void)
{
    cout<<endl<<endl<<"Iniciando con vectores y punteros"<<endl;
    showArrayVector();
    // Matriz de 4 filas y 3 columnas, inicializada con valores
    const int f=4, c=3;
    int m[f][c] = { {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}};
    cout<<endl<<endl<<"0. showVector(int a[], int c)"<<endl;
    // Pasa una fila de la matriz (m[0]) como un vector
    showVector(m[0] , c) ;
    showVector(m[1] , c) ;
    cout<<endl<<endl<<"1. showMatriz: (int m[][3], int f, int c)"<<endl;
    // Pasa la matriz completa a una funcion que espera una matriz
    showMatriz(m ,f, c) ;
    cout<<endl<<endl<<"2. showMatrizComoVector: (int mv[], int f, int c)"<<endl;
    // Pasa la direccion del primer elemento para tratar la matriz como un vector
    showMatrizComoVector(&m[0][0] ,f, c);
    cout<<endl<<endl<<"3. showPtrMatriz: (int *p, int f,int c)"<<endl;
    // Pasa la direccion del primer elemento para usar aritmetica de punteros
    showPtrMatriz(&m[0][0] ,f, c);
    // Array de punteros que apunta a la primera columna de cada fila de la matriz
    int *p[f];
    for (int i = 0; i < f; i++)
        p[i] = &m[i][0];
    cout<<endl<<endl<<"4. showVectorPtrMatriz: (int *vp[], int f,int c)"<<endl;
    // Pasa el array de punteros a la funcion
    showVectorPtrMatriz(p,f,c);
    // Puntero doble que apunta al array de punteros 'p'
    int **pd = p;
    cout<<endl<<endl<<"5. showPtrDobleMatriz: (int **pd, int f,int c)"<<endl;
    // Pasa el puntero doble a la funcion
    showPtrDobleMatriz(pd,f,c);
    cout<<endl<<endl<<"6. matriz -> showPtrVector: (int *pv, int c)"<<endl;
    for (int i = 0; i < f; i++) {
        // Incrementa el puntero doble 'pd' para apuntar a la siguiente fila
        // y pasa la fila como un puntero a un vector
        showPtrVector(*pd++, c);
    }
    cout<<endl<<endl<<"7. matriz -> showVector(int a[], int c)"<<endl;
    // Vuelve a mostrar las filas de la matriz una por una
    for (int i = 0; i < f; i++)
        showVector(m[i] , c) ;

    return 0;
}