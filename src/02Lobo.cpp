#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "../lib/toolbox.h"
using namespace std;

bool    EstamoIzq       = true;
int     rioLength       = 20;
string  rio(rioLength, '_'),
        barca           = "<_O_,_?_>",
        barcaRio        = barca + rio, 
        personajeSelec  = "";
vector<string> ladoIzq  = {"O","L","C","U"},    ladoDer  = {"","","",""};

string  getPersonaje(const vector<string>& arr) 
{
    string lstPersonaje= "";
    for (auto &&p : arr)
        lstPersonaje += (p != "")  ?  p + ", " : " , ";
    return  "  "+lstPersonaje+"  ";
}
void    moverBarca(int opcion = 0) 
{
    barca= "<_O_,_"+personajeSelec+"_>";
    for (int i = 0; i <= rioLength; i++)
    {
        string  rioIzq(i, '_'), 
                rioDer(rioLength - i, '_');
        barcaRio =  EstamoIzq ? rioIzq + barca + rioDer : rioDer + barca + rioIzq;
        cout <<  "\r" << getPersonaje(ladoIzq) << barcaRio << getPersonaje(ladoDer);
        Sleep(100);
    }
    barcaRio.replace(barcaRio.find(','), 3, ",_?"); 
   // cout << endl << "opcion: " << opcion << endl;
    ladoIzq[0] = ladoDer[0] = ladoIzq[opcion] = ladoDer[opcion] = ""; 
    if(EstamoIzq) 
    {
        ladoDer[0] = "O";  
        ladoDer[opcion] = personajeSelec;  
    }
    else
    {
        ladoIzq[0] = "O";        
        ladoIzq[opcion] = personajeSelec;        
    } 
    EstamoIzq = !EstamoIzq;   // Cambia el lado del obstáculo
}
int     getPersonajeMenu() 
{
    int opc  = -1;
    system("cls");
    cout<< "\r" << getPersonaje(ladoIzq) << barcaRio << getPersonaje(ladoDer) << endl << endl
        << "0. Vikingo"    << endl
        << "1. Lobo"       << endl
        << "2. Caperusita" << endl
        << "3. Uva"        << endl  
        << "4. Salir"      << endl;
    do{
        opc = getConsoleNumero("Ingrese (0-4): ", 0, 4);
        if(opc == 4) 
            exit(0);
        personajeSelec = (EstamoIzq) ? ladoIzq[opc] : ladoDer[opc]; 
        if (personajeSelec == "") {
            cout << "No hay personaje." << endl;
            opc  = -1; 
        }
    }while (opc < 0 || opc > 4);
    return opc;
}
bool    validarReglas() 
{
    string msg = "";
    if( (EstamoIzq && ladoDer[1] != "" && ladoDer[2] != "") || (!EstamoIzq && ladoIzq[1] != "" && ladoIzq[2] != ""))
        msg += "\n:( El lobo se comio a la caperucita ";
    if( (EstamoIzq && ladoDer[2] != "" && ladoDer[3] != "") || (!EstamoIzq && ladoIzq[2] != "" && ladoIzq[3] != ""))
        msg += "\n:( La caperucita se comio las uvas " ;
    if( ladoDer[0] != "" && ladoDer[1] != "" && ladoDer[2] != "" && ladoDer[3] != "")
        msg += "\n:) Lo lograstes campeon...! ";
    if (msg != "")
    {
        cout << msg;
        exit(0);
    }
    return true;
    //if (EstamoIzq)
    // {
    //     // regla 1: El lobo se come a la caperucita.
    //     msg += (ladoDer[1] != "" && ladoDer[2] != "") ? "El lobo se comió a la caperucita. " : "";
    //     // regla 2: La caperucita se come a la uvas
    //     msg += (ladoDer[2] != "" && ladoDer[3] != "") ? "La caperucita se comió las uvas. " : "";

    // }
    // else
    // {
    //     // regla 1: El lobo se come a la caperucita.
    //     msg += (ladoIzq[1] != "" && ladoIzq[2] != "") ? "El lobo se comió a la caperucita. " : "";
    //     // regla 2: La caperucita se come a la uvas
    //     msg += (ladoIzq[2] != "" && ladoIzq[3] != "") ? "La caperucita se comió las uvas. " : "";
    // }
}

int main()  
{
    do
        moverBarca( getPersonajeMenu() );
    while (validarReglas());
    return 0;
}