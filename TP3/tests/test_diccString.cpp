
#include <ostream>
#include <iostream>
#include <sstream>
using namespace std;
#include "../diccString.h"
#include "../aed2.h"


void test_DefinidoDS(){
    DiccString<string> d;
    assert(not d.DefinidoDS("2"));
    d.DefinirDS("2", "Juan");
    assert(d.DefinidoDS("2"));
    d.DefinirDS("2", "Pedro");
    assert(d.DefinidoDS("2"));
    d.DefinirDS("3", "Lucas");
    assert(d.DefinidoDS("2"));
    assert(d.DefinidoDS("3"));
    assert(not(d.DefinidoDS("30")));
    cout << "OK: test_DefinidoDS" << endl;
}

void test_ObtenerDS(){
    DiccString<string> d;
    d.DefinirDS("2", "Juan");
    assert(d.ObtenerDS("2") == "Juan");
    d.DefinirDS("2", "Pedro");
    assert(d.DefinidoDS("2"));
    d.DefinirDS("3", "Lucas");
    assert(d.ObtenerDS("3") == "Lucas");
    cout << "OK: test_ObtenerDS" << endl;
}

void test_ClavesDS(){
    DiccString<string> d;
    d.DefinirDS("2", "Juan");
    d.DefinirDS("2", "Pedro");
    d.DefinirDS("3", "Lucas");
    d.DefinirDS("6", "Nicolas");
    Conj<string> c;
    c.AgregarRapido("2");
    c.AgregarRapido("3");
    c.AgregarRapido("6");
    assert(d.ClavesDS() == c);
    c.AgregarRapido("14");
    assert(not(d.ClavesDS() == c));
    d.DefinirDS("14", "Carla");
    assert(d.ClavesDS() == c);
    cout << "OK: test_ClavesDS" << endl;
}

void test_equal(){
    DiccString<string> d1;
    d1.DefinirDS("2", "Juan");
    d1.DefinirDS("2", "Pedro");
    d1.DefinirDS("3", "Lucas");
    d1.DefinirDS("6", "Nicolas");
    DiccString<string> d2;
    d2.DefinirDS("6", "Nicolas");
    d2.DefinirDS("2", "Juan");
    assert(not(d1 == d2));
    d2.DefinirDS("3", "Lucas");
    assert(not(d1 == d2));
    d2.DefinirDS("2", "Pedro");
    assert(d1 == d2);
    cout << "OK: test_equal" << endl;
}

void test_mostrar(){
    DiccString<string> d1;
    d1.DefinirDS("2", "Pedro");
    d1.DefinirDS("3", "Lucas");
    d1.DefinirDS("6", "Nicolas");
    std::ostringstream os;
    os << d1;
    std::string s = os.str();
    std::ostringstream os_endl;
    os_endl << endl;
    std::string s_endl = os_endl.str();
    string prueba = "[(6,Nicolas) ; (3,Lucas) ; (2,Pedro)]" + s_endl;
    assert(s == prueba);
    cout << "OK: test_mostrar" << endl;
}

void test_constructor_copia(){
    DiccString<string> d1;
    d1.DefinirDS("2", "Pedro");
    d1.DefinirDS("3", "Lucas");
    d1.DefinirDS("6", "Nicolas");
    d1.DefinirDS("6", "Agus");
    DiccString<string> d2(d1);
    assert(d1 == d2);
    cout << "OK: test_constructor_copia" << endl;
}

int main()
{
    test_DefinidoDS();
    test_ObtenerDS();
    test_ClavesDS();
    test_equal();
    test_mostrar();
    test_constructor_copia();
    return 0;
}

