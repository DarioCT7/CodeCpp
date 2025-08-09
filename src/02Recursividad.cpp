#include <iostream>
using namespace std;
int memo =0;

int factorial(int f)
{
    if(f==1)
        return f;
    return (f * factorial(f-1));  // 3 * 2!
}

int contadorDesc(int n)
{
    if(n==1)
    return n;
    cout << n << " ";
    return contadorDesc(n-1);
}

int multiplicacion(int a, int b)
{
    if(a==1)
        return b;
    return b + multiplicacion(a-1,b);
}

char showArrDesc(char arr[], int l)
{
    if(l==0)
        return arr[l];
    cout <<arr[l] << " ";
    return showArrDesc(arr, l-1);
}

string repetirCaracter(const char c, int n)
{
    if(n==0)
        return "";
    return c + repetirCaracter(c, n-1);
}
bool esPalindromo(const string palabra, int posIni =0)
{
    int posFin = palabra.length()-1 - posIni;
    //string espIni(memo++, ' ');
    cout<< repetirCaracter(' ', memo++)  
        << repetirCaracter(palabra[posIni], posFin) << endl;

    if( posIni == posFin )
        return true;
    
    if( palabra[posIni] == palabra[posFin] )
        return esPalindromo(palabra, posIni+1);
    memo=0;
    return false;
}


int main()
{
    string palabra = "rotor", palabra1= "ssdfss";
    char nombre[] = {'p','a','t','_','m','i','c'};
    cout<< "-----  Recursividad  ------"                   << endl
        << "Contador DESC: " << contadorDesc(10)           << endl
        << "multiplicacion:" << multiplicacion(3,6)        << endl
        << "factoruial     " << factorial(3)               << endl
        << "show array:    " << showArrDesc(nombre, 6 )    << endl
        << "Es palindromo "  << palabra << ": "  << endl   << esPalindromo(palabra)   << endl    
        << "Es palindromo "  << palabra << ": "  << endl   << esPalindromo(palabra)   << endl    
        << "Es palindromo "  << palabra1 << ": " << endl   << esPalindromo(palabra1)  << endl    
        << "Es palindromo "  << palabra << ": "  << endl   << esPalindromo(palabra)   << endl  
        << "repetirCaracter: " << repetirCaracter('-', 5 )    << endl;

    return 0;
}
/*
rrrrr
 ooo
  t
    r    r
     a  a
      d

*/