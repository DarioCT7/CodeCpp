#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <conio.h>
#include <iomanip>
using namespace std;

// Estructura que representa un nodo del árbol binario
struct registro {
    int  NR;         // Número de registro
    char dato[12];   // Dato (nombre)
    int  PD;         // Puntero al hijo derecho
    int  PI;         // Puntero al hijo izquierdo
    int  ARE;        // Área reservada (no usada aquí)
} r, a;

// Estructura del encabezado del archivo
struct encabezado {
    int NRS;         // Número total de registros
    int RAIZ;        // Posición del nodo raíz
    int URE;         // Área reservada (no usada aquí)
} e;

FILE *fd;            // Puntero al archivo
int lr, le;          // Tamaño de registro y encabezado

/*                Funcion Escribir Archivo
---------------------------------------------------------*/
void escribir()
{
    int x, pos;
    char rpt, lado;

    // Crear archivo en modo escritura
    if ((fd = fopen("arbol_binario.txt", "w+")) == NULL) {
        cout << " No se creo el archivo arbol_binario.txt" << endl;
        return;
    }

    // Inicializar encabezado
    e.NRS  = 0;
    e.RAIZ = -1;
    e.URE  = -1;
    fwrite(&e, le, 1, fd);  // Escribir encabezado al inicio

    do {
        r.NR = ++e.NRS;     // Asignar número de registro
        fflush(stdin);
        cout << " Nombre : "; gets(r.dato);  // Leer nombre
        r.PI = -1;
        r.PD = -1;
        r.ARE = 0;

        fseek(fd, 0, 2);    // Ir al final del archivo
        fwrite(&r, lr, 1, fd);  // Escribir registro

        if (e.RAIZ == -1) {
            e.RAIZ = r.NR;  // Si es el primer registro, es la raíz
            cout << " * Raiz" << endl;
        } else {
            x = e.RAIZ;

            // Buscar posición donde insertar el nuevo nodo
            while (x != -1) {
                pos = (x - 1) * lr + le;
                fseek(fd, pos, SEEK_SET);
                fread(&a, lr, 1, fd);

                if (strcmp(r.dato, a.dato) > 0) {
                    x = a.PD;
                    lado = 'D';
                    continue;
                }
                if (strcmp(r.dato, a.dato) < 0) {
                    x = a.PI;
                    lado = 'I';
                    continue;
                }
            }

            // Insertar en el lado correspondiente
            if (lado == 'D') {
                a.PD = r.NR;
                cout << " * Lado der. de " << a.dato << endl;
            }
            if (lado == 'I') {
                a.PI = r.NR;
                cout << " * Lado izq. de " << a.dato << endl;
            }

            fseek(fd, pos, SEEK_SET);
            fwrite(&a, lr, 1, fd);  // Actualizar nodo padre
        }

        cout << " Mas registros [s/n]: "; cin >> rpt;
        cout << endl;
    } while (rpt != 'n');

    fseek(fd, 0, SEEK_SET);
    fwrite(&e, le, 1, fd);  // Actualizar encabezado
    fclose(fd);
}

/*                Funcion Mostrar Archivo
---------------------------------------------------------*/
void mostrar()
{
    // Abrir archivo en modo lectura
    if ((fd = fopen("arbol_binario.txt", "r")) == NULL) {
        cout << " No se pudo abrir el archivo" << endl;
        return;
    }

    fread(&e, le, 1, fd);  // Leer encabezado

    // Mostrar encabezado
    cout << " -----------------------------------" << endl;
    cout << " |  NRS: " << e.NRS << "    RAIZ: " << e.RAIZ << "    URE: " << e.URE << "   |" << endl;
    cout << " -----------------------------------" << endl << endl;

    // Mostrar registros en formato tabular
    cout << setw(3) << "NR" << setw(10) << "NOMBRE" << setw(5);
    cout << "PI" << setw(5) << "PD" << setw(6) << "ARE" << endl << endl;

    while (fread(&r, lr, 1, fd) != NULL) {
        cout << " " << r.NR << "\t" << r.dato;
        cout << "\t" << r.PI << "\t" << r.PD;
        cout << "\t" << r.ARE << endl;
    }

    fclose(fd);
}

/*                   Funcion Leer
---------------------------------------------------------*/
void leer()
{
    int x, pos;
    bool band;
    char v_dato[12];

    // Abrir archivo en modo lectura
    if ((fd = fopen("arbol_binario.txt", "r")) == NULL) {
        cout << " No se pudo abrir el archivo" << endl;
        return;
    }

    fflush(stdin);
    cout << " Nombre : "; gets(v_dato);  // Leer nombre a buscar
    fread(&e, le, 1, fd);  // Leer encabezado
    x = e.RAIZ;
    band = false;

    // Recorrer el árbol buscando el dato
    while (x != -1) {
        pos = (x - 1) * lr + le;
        fseek(fd, pos, SEEK_SET);
        fread(&r, lr, 1, fd);

        if (strcmp(v_dato, r.dato) > 0) {
            x = r.PD;
            continue;
        }
        if (strcmp(v_dato, r.dato) < 0) {
            x = r.PI;
            continue;
        }

        band = true;
        cout << "\n >> Dato " << r.dato << " encontrado..!" << endl;
        break;
    }

    if (!band)
        cout << "\n\n >> No existe..!" << endl;

    fclose(fd);
}

/*                  Funcion Insertar
---------------------------------------------------------*/
void insertar()
{
    int x, pos;
    char rpt, lado;

    // Abrir archivo en modo lectura/escritura
    if ((fd = fopen("arbol_binario.txt", "r+")) == NULL) {
        cout << " No se pudo abrir el archivo" << endl;
        return;
    }

    fread(&e, le, 1, fd);  // Leer encabezado

    do {
        r.NR = ++e.NRS;
        fflush(stdin);
        cout << " Nombre : "; gets(r.dato);
        r.PI = -1;
        r.PD = -1;
        r.ARE = 0;

        fseek(fd, 0, SEEK_END);  // Ir al final
        fwrite(&r, lr, 1, fd);   // Escribir nuevo registro

        if (e.RAIZ == -1) {
            e.RAIZ = r.NR;
            cout << " * Raiz" << endl;
        } else {
            x = e.RAIZ;

            // Buscar posición donde insertar
            while (x != -1) {
                pos = (x - 1) * lr + le;
                fseek(fd, pos, SEEK_SET);
                fread(&a, lr, 1, fd);

                if (strcmp(r.dato, a.dato) > 0) {
                    x = a.PD;
                    lado = 'D';
                    continue;
                }
                if (strcmp(r.dato, a.dato) < 0) {
                    x = a.PI;
                    lado = 'I';
                    continue;
                }
            }

            // Insertar en el lado correspondiente
            if (lado == 'D') {
                a.PD = r.NR;
                cout << " * Lado der. de " << a.dato << endl;
            }
            if (lado == 'I') {
                a.PI = r.NR;
                cout << " * Lado izq. de " << a.dato << endl;
            }

            fseek(fd, pos, SEEK_SET);
            fwrite(&a, lr, 1, fd);  // Actualizar nodo padre
        }

        cout << " Insertar mas registros [s/n]: "; cin >> rpt;
        cout << endl;
    } while (rpt != 'n');

    fseek(fd, 0, SEEK_SET);
    fwrite(&e, le, 1, fd);  // Actualizar encabezado
    fclose(fd);
}

/*                 Funcion Eliminar Registro
---------------------------------------------------------*/
void eliminar_registro()
{
    // Función aún no implementada
    cout << "\n\n Implementando..!" << endl;
}

/*                 Funcion Eliminar Archivo
---------------------------------------------------------*/
void eliminar_archivo()
{
    // Elimina el archivo físico del árbol binario
    remove("arbol_binario.txt");
    cout << " >> Archivo arbol_binario.txt eliminado..!" << endl;
}

/*                 Menu de Opcion
---------------------------------------------------------*/
void menu()
{
    // Muestra el menú principal con las opciones disponibles
    cout << "\t\t ARBOLES BINARIOS DE BUSQUEDA EN ARCHIVOS \n\n";
    cout << "\t 1. Escribir              \n";           // Crear archivo y escribir registros
    cout << "\t 2. Mostrar               \n";           // Mostrar todos los registros
    cout << "\t 3. Leer                  \n";           // Buscar un registro por nombre
    cout << "\t 4. Insertar              \n";           // Insertar nuevos registros
    cout << "\t 5. Eliminar Registro     \n";           // (Pendiente) Eliminar un registro
    cout << "\t 6. Eliminar Archivo      \n";           // Eliminar el archivo completo
    cout << "\t 7. Salir                 \n";           // Salir del programa
    cout << "\t >> Ingrese opcion:  ";
}

/*                 Funcion Principal
---------------------------------------------------------*/
int main()
{
    int op;  // Variable para almacenar la opción del menú

    // Inicializar tamaños de estructuras
    lr = sizeof(struct registro);    // Longitud de un registro
    le = sizeof(struct encabezado);  // Longitud del encabezado

    do
    {
        menu();                      // Mostrar menú
        cin >> op;                   // Leer opción
        cout << "\n\n";

        // Ejecutar la opción seleccionada
        switch(op)
        {
            case 1: escribir();             break;  // Crear archivo y escribir registros
            case 2: mostrar();              break;  // Mostrar registros
            case 3: leer();                 break;  // Buscar registro
            case 4: insertar();             break;  // Insertar nuevo registro
            case 5: eliminar_registro();    break;  // Eliminar registro (pendiente)
            case 6: eliminar_archivo();     break;  // Eliminar archivo
            case 7: exit(0);                break;  // Salir del programa
        }

        cout << "\n\n ";
        // Puedes activar estas líneas si deseas limpiar la pantalla y pausar
        // system("pause");
        // system("cls");

    } while(op > 0);  // Repetir mientras la opción sea válida

    return 0;
}
