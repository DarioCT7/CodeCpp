#include <string>
#include <cstring>  
#include <fstream>
#include <iostream>
using namespace std;

struct  Mascota
{
    int     edad;
    char    tipo[20];
    string  nombre;
};
struct  Alumno
{
    int      id
            ,edad;
    char     nombre[20];
    Mascota  mascotita;
};

int main()
{
    int     a;
    Alumno  a0;
    a=0;
    int     aa= 10;
    Alumno  a1= {1,20,"Pepe", {1,"pez","firulais"}};
    Alumno  a2= {2,20,"luis"};

    int arr[10];
    Alumno lst[]    ={a0
                    , a2 
                    , a1
                    , {3,20,"luisa",   {1,"perro","trini"}  }
                    , {3,20,"Luchita", {1,"perro","max"}    }
                    };

    a0.id           = 0;
    a0.edad         = 21;
    strcpy(a0.nombre, "Ana"); 
    a0.mascotita.edad   = 1;
    a0.mascotita.nombre = "niko";

    strcpy(lst[4].nombre, "Juana"); 

    cout<< "Datos de Alumno a0   " << endl
        <<"a0.id                 " << a0.id                 << endl
        <<"a0.edad               " << a0.edad               << endl
        <<"a0.nombre             " << a0.nombre             << endl
        <<"a0.mascotita.edad     " << a0.mascotita.edad     << endl
        <<"a0.mascotita.tipo[0]  " << a0.mascotita.tipo[0]  << endl
        <<"a0.mascotita.nombre   " << a0.mascotita.nombre   << endl ;

    cout<<"[+] Datos de Alumno lst[4]    " << endl
        <<" -  lst[4].id                 " << lst[4].id                 << endl
        <<" -  lst[4].edad               " << lst[4].edad               << endl
        <<" -  lst[4].nombre             " << lst[4].nombre             << endl
        <<" -  lst[4].mascotita.edad     " << lst[4].mascotita.edad     << endl
        <<" -  lst[4].mascotita.tipo[0]  " << lst[4].mascotita.tipo[0]  << endl
        <<" -  lst[4].mascotita.nombre   " << lst[4].mascotita.nombre   << endl ;
    
    for (auto &&a : lst)
    {
        cout<<"[+] Datos de Alumnos" << endl
        <<" -  id                 " << a.id                 << endl
        <<" -  edad               " << a.edad               << endl
        <<" -  nombre             " << a.nombre             << endl
        <<" -  mascotita.edad     " << a.mascotita.edad     << endl
        <<" -  mascotita.tipo[0]  " << a.mascotita.tipo[0]  << endl
        <<" -  mascotita.nombre   " << a.mascotita.nombre   << endl ;
            
    }
    
    
    Alumno *persona = new Alumno[5];
 
    for (int i=0; i<5; i++)
    {
        cout << "Dime el nombre de la persona " << i << endl;
        cin >> persona[i].nombre;
    }
    cout << "La persona 3 es " << persona[2].nombre << endl;
    cout << "fin" << endl;
    return 0;
}

