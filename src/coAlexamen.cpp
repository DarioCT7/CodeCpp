#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct Segmento {
    string caracter;
    Segmento *nextSeg;
} *TTroncoSeg;

struct CienPie {
    string      cabeza;
    string      cola;
    TTroncoSeg  tronco = NULL;
    CienPie     *nextAmigo = NULL;
};
typedef CienPie *TCienPie;

typedef struct Atomo{
    int     pesoAtomico=0;
    string  datoAtomico= "";
    Atomo   *enlaceAtom= NULL;
    } *TAtomo;  

struct Molecula {
    int     cargaMolecula = 0;
    TAtomo  nexConsonante = NULL;
    TAtomo  nexVocal = NULL;
};

TTroncoSeg newSegmento(string c) 
{
    c=  "-=< "  + c + " >-=";
    return new Segmento{c, NULL};
}
void addTronco(TTroncoSeg &tronco, string c)
{
    TTroncoSeg nuevo = newSegmento(c);
    if (tronco == NULL) {
        tronco = nuevo;
    } else {
        TTroncoSeg actual = tronco;
        while (actual->nextSeg != NULL) {
            actual = actual->nextSeg;
        }
        actual->nextSeg = nuevo;
    }
}

void showCienPie( const CienPie &cienpie)
{
    cout << cienpie.cabeza << endl;
    TTroncoSeg actual = cienpie.tronco;
    while (actual != NULL) {
        cout << actual->caracter << endl;
        actual = actual->nextSeg;
    }
    cout << cienpie.cola << endl;
    cout <<endl;
}

void crearCienPie(TCienPie &p, const string nombre)
{
    TCienPie auxCienpie = new CienPie{"     /\\ \n  (5)", " /\\"};
    for(auto &&i: nombre) 
        addTronco(auxCienpie->tronco, string(1,i));
    //showCienPie(*auxCienpie);
    auxCienpie->nextAmigo = p;
    p = auxCienpie;
}
void showAmigosCienPie(const TCienPie &p)
{
    TCienPie cienpie = p;
    while (cienpie != NULL) {
        showCienPie(*cienpie);
        cienpie = cienpie->nextAmigo;
    }
    cout << endl;
}

void newEnlaceAtomico(TAtomo &mol, int peso, string dato)
{
    TAtomo nuevo = new Atomo{peso, dato, NULL};
    if (mol == NULL) {
        mol = nuevo;
    } else {
        TAtomo actual = mol;
        while (actual->enlaceAtom != NULL) {
            actual = actual->enlaceAtom;
        }
        actual->enlaceAtom = nuevo;
    }
}
void showEnlaceAtomico(const TAtomo &atom)
{
    TAtomo actual = atom;

    cout<< "            ";
    while (actual != NULL)
    {
        cout<<"+--+ ( "<< actual->datoAtomico<< ")";
        actual = actual->enlaceAtom;
    }
    cout << endl;
}

void crearMolecula(){
    Molecula mol;
    string nombre= "patricio";

    mol.cargaMolecula = 5;
    for (auto &&i: nombre) 
    {
        if (i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u') 
            newEnlaceAtomico(mol.nexVocal,  -1, string(1, i));
        else
            newEnlaceAtomico(mol.nexConsonante, 1, string(1, i));
        }
    showEnlaceAtomico(mol.nexConsonante);
    cout<< "            /"<<endl
        << "Molecula: ("<<mol.cargaMolecula <<")"<< endl
        << "            \\"<<endl;
    showEnlaceAtomico(mol.nexVocal);
}

int main() {
    TCienPie amigosCienpies = NULL;

    crearCienPie(amigosCienpies, "Tonguino");
    crearCienPie(amigosCienpies, "Dario");
    showAmigosCienPie(amigosCienpies);
    crearMolecula();
    return 0;
}   