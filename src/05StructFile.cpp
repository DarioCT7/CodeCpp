#include <string>
#include <vector>
#include <cstring>  
#include <fstream>
#include <iostream>
#include "../lib/toolbox.h"

#define  SEPARADOR ','
using namespace std;

struct  Mascota
{
    int     id;
    string  tipo;
    string  nombre;
};
struct  Alumno
{
    int      id;
    string   nombre;
    Mascota  mascota;
};
vector<Alumno> lstAlumno;

void showAlumnoMascota(Alumno a)
{
    cout<< COLOR_BLUE   << endl
        <<"[+] Datos de Alumnos     "       << endl
        <<" -  Alumno.Id          : "       << a.id             << endl
        <<" -  Alumno.nombre      : "       << a.nombre         << endl
        <<" -  mascotita.Id       : "       << a.mascota.id     << endl
        <<" -  mascotita.tipo     : "       << a.mascota.tipo   << endl
        <<" -  mascotita.nombre   : "       << a.mascota.nombre << endl << endl;
}

void writeFileAlumno(const string filePath)
{
    ofstream f(filePath, ios::out | ios::trunc); 
    if (!f) {
        cerr << "Error al abrir el archivo: " << filePath << endl;
        return;
    }
    cout<< COLOR_RED << "Guardando:"<< endl;
    for (auto &&a : lstAlumno)
    {
        f   << a.id << SEPARADOR << a.nombre << SEPARADOR  << a.mascota.id  << SEPARADOR  << a.mascota.tipo << SEPARADOR  << a.mascota.nombre <<endl;
        cout<< a.id << SEPARADOR << a.nombre << SEPARADOR  << a.mascota.id  << SEPARADOR  << a.mascota.tipo << SEPARADOR  << a.mascota.nombre <<endl;
    }
    f.close();
}
void readFileAlumno(const string filePath)
{
    int     count = 1;
    string  line  = "";
    ifstream f(filePath, ios::in);
    
    if (!f)
    {
        cerr << "error al abrir el archivo: " << filePath << endl ;
        return;
    }
    while (getline(f, line))
    {
        Alumno a;
        vector<string> dataLine = splitString(line, SEPARADOR);
        cout<< COLOR_RED << showWaiting (line) << COLOR_BLUE   << endl;
        a.id             = count++; //stoi(dataLine[0]);
        a.nombre         = dataLine[1];
        a.mascota.id     = stoi(dataLine[2]);
        a.mascota.tipo   = dataLine[3];
        a.mascota.nombre = dataLine[4];
        lstAlumno.push_back(a);
        //showAlumnoMascota(a);
    }
}

void showListaAlumno()
{
    cout<< COLOR_BLUE << "ALUMNOS: "<< endl;
    for (auto &&a : lstAlumno)
        showAlumnoMascota(a);
} 
void addListaAlumno()
{
    Alumno a;
    cout<< COLOR_RED <<"[+] ADD ALUMNO           "      << endl;
    //a.id    = getConsoleNumero(" -  Alumno.Id    : ", 1,100);
    a.id = lstAlumno.size()+1;
    cout<<" -  Alumno.nombre      : ";     cin>>   a.nombre         ;
    cout<<" -  mascotitas.Id      : ";     cin>>   a.mascota.id     ;
    cout<<" -  mascotitas.tipo    : ";     cin>>   a.mascota.tipo   ;
    cout<<" -  mascotitas.nombre  : ";     cin>>   a.mascota.nombre ;
    lstAlumno.push_back(a);
    cout<< COLOR_BLUE << "Registro con exito..!" << endl;
}  
Alumno findListaAlumno()
{
    Alumno alumno;
    int id = 0;
    cout<< COLOR_RESET << "BUSCANDO..."    <<endl;
    id = getConsoleNumero("Ingrese el id del alumno: ", 1, lstAlumno.size());
    for (auto &&a : lstAlumno)
        if(a.id == id)
        {
            alumno = a;
            break;
        }
    showAlumnoMascota(alumno);
    return alumno;
}
void alterListaAlumno()
{
    Alumno a;
    string rta;
    a = findListaAlumno();
    cout<<"Esta seguro que desea modificar al alumno (s=Si / n=No)?: ";
    cin>>rta;
    if(rta != "s")
        return;

    cout<< COLOR_RED <<"[+] MODIFICAR ALUMNO          "      << endl;
    //a.id = lstAlumno.size()+1;
    cout<<" -  Alumno.nombre      : ";     cin>>    a.nombre         ;
    cout<<" -  mascotitas.Id      : ";     cin>>    a.mascota.id     ;
    cout<<" -  mascotitas.tipo    : ";     cin>>    a.mascota.tipo   ;
    cout<<" -  mascotitas.nombre  : ";     cin>>    a.mascota.nombre ;
    
    int index_to_insert = a.id-1;
    //cout << "index_to_insert : " << index_to_insert << endl;
    lstAlumno.erase(lstAlumno.begin()  + index_to_insert);
    lstAlumno.insert(lstAlumno.begin() + index_to_insert, a);

    cout<< COLOR_BLUE << "Registro con exito..!" << endl;
}
void delListaAlumno()
{

}  

int main()
{
    int opc=0;
    string dataFilename="datos.csv";

    cout<< COLOR_RED << "Procesando "<< dataFilename << endl;
    readFileAlumno(dataFilename);

    while (true)
    {
        system("cls");
        cout<< COLOR_GREEN << "[+] ALUMNO DE PROGRAMACION I"<< endl
            << " 1. Mostrar   "     <<endl
            << " 2. Agregar   "     <<endl
            << " 3. Eliminar  "     <<endl
            << " 4. Buscar    "     <<endl
            << " 5. Modificar "     <<endl
            << " 6. Respaldar paralelo"   <<endl
            << " 7. Salir"                <<endl;
        opc = getConsoleNumero("Ingrese una opcion: ", 1,7);
        switch (opc)
        {
            case 1: showListaAlumno();              break;
            case 2: addListaAlumno ();              break;
            case 3: delListaAlumno ();              break;
            case 4: findListaAlumno ();             break;
            case 5: alterListaAlumno ();            break;
            case 6: writeFileAlumno(dataFilename);  break;
            case 7: exit(0);
        }
        cout<< COLOR_RED << endl;
        system("pause"); 
    }
    return 0;
}