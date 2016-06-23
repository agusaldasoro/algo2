
#include <ostream>
#include <iostream>
#include <sstream>
using namespace std;
#include "../diccionario_finito.h"

void test_definida(){
    Diccionario_Finito<string> d(10);
    assert(not d.Definida(2));
    d.Definir(2, "Juan");
    assert(d.Definida(2));
    d.Definir(2, "Pedro");
    assert(d.Definida(2));
    d.Definir(3, "Lucas");
    assert(d.Definida(2));
    assert(d.Definida(3));
    cout << "OK: test_definida" << endl;
}
void test_obtener(){
    Diccionario_Finito<string> d(10);
    d.Definir(2, "Juan");
    assert(d.Obtener(2) == "Juan");
    d.Definir(2, "Pedro");
    assert(d.Definida(2));
    d.Definir(3, "Lucas");
    assert(d.Obtener(3) == "Lucas");
    cout << "OK: test_obtener" << endl;
}
void test_claves(){
    Diccionario_Finito<string> d(10);
    d.Definir(2, "Juan");
    d.Definir(2, "Pedro");
    d.Definir(3, "Lucas");
    d.Definir(6, "Nicolas");
    Conj<Nat> c;
    c.AgregarRapido(2);
    c.AgregarRapido(3);
    c.AgregarRapido(6);
    assert(d.Claves() == c);
    cout << "OK: test_claves" << endl;
}
void test_tamanhos(){
    Diccionario_Finito<string> d(10);
    d.Definir(2, "Juan");
    d.Definir(2, "Pedro");
    d.Definir(3, "Lucas");
    d.Definir(6, "Nicolas");
    assert(d.TamanhoMax() == 10);
    assert(d.Tamanho() == 3);
    cout << "OK: test_tamanhos" << endl;
}
void test_equal(){
    Diccionario_Finito<string> d1(10);
    d1.Definir(2, "Juan");
    d1.Definir(2, "Pedro");
    d1.Definir(3, "Lucas");
    d1.Definir(6, "Nicolas");
    Diccionario_Finito<string> d2(10);
    d2.Definir(6, "Nicolas");
    d2.Definir(2, "Juan");
    d2.Definir(3, "Lucas");
    assert(not(d1 == d2));
    d2.Definir(2, "Pedro");
    assert(d1 == d2);
    cout << "OK: test_equal" << endl;
}
void test_mostrar(){
    Diccionario_Finito<string> d1(5);
    d1.Definir(2, "Pedro");
    d1.Definir(3, "Lucas");
    d1.Definir(6, "Nicolas");
    std::ostringstream os;
    os << d1;
    std::string s = os.str();;
    assert(s == "[(2,Pedro),(3,Lucas),(6,Nicolas),NULL,NULL]");
    cout << "OK: test_mostrar" << endl;
}
int main()
{
    test_definida();
    test_obtener();
    test_claves();
    test_tamanhos();
    test_equal();
    test_mostrar();
    return 0;
}
