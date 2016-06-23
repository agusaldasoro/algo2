
#include <ostream>
#include <iostream>
#include <sstream>
using namespace std;
#include "../diccIncep.h"
#include "../aed2.h"


void test_DefinidoDI(){
    DiccInception d(10);
    assert(not(d.DefinidoDI(2)));
    d.AgregarClienteDI(2);
    d.AgregarClienteDI(5);
    assert(d.DefinidoDI(2));
    assert(d.DefinidoDI(5));
    assert(not(d.DefinidoDI(10)));
    assert(not(d.DefinidoDI(146640)));
    d.AgregarClienteDI(4354657);
    assert(d.DefinidoDI(4354657));
    cout << "OK: test_DefinidoDI" << endl;
}

void test_ClientesDI(){
    DiccInception d(10);
    assert(d.ClientesDI().EsVacio());
    d.AgregarClienteDI(2);
    d.AgregarClienteDI(5);
    d.AgregarClienteDI(7);
    Conj<Nat> c;
    c.Agregar(2);
    c.Agregar(5);
    assert(not(d.ClientesDI() == c));
    c.Agregar(7);
    assert(d.ClientesDI() == c);
    assert(d.ClientesDI().Pertenece(2));
    assert(not(d.ClientesDI().Pertenece(32)));
    cout << "OK: test_ClientesDI" << endl;
}

void test_AgregarTitulo(){
    DiccInception d(10);
    d.AgregarClienteDI(2);
    d.AgregarClienteDI(5);
    d.AgregarClienteDI(7);
    d.AgregarTitulo(2, "Facebook", 5);
    d.AgregarTitulo(2, "Twitter", 10);
    d.AgregarTitulo(5, "Facebook", 8);
    Conj<string> c1;
    d.TitulosDe(7);
    assert(d.TitulosDe(7) == c1);
    Conj<string> c2;
    c2.Agregar("Facebook");
    c2.Agregar("Twitter");
    assert(d.TitulosDe(2) == c2);
    Conj<string> c3;
    c3.Agregar("Facebook");
    assert(d.TitulosDe(5) == c3);
    cout << "OK: test_AgregarTitulo" << endl;
}

void test_SumarAcciones(){
    DiccInception d(10);
    d.AgregarClienteDI(2);
    d.AgregarTitulo(2, "Facebook", 5);
    d.AgregarTitulo(2, "Twitter", 10);
    d.SumarAcciones(2, "Facebook", 3);
    d.Cantidad(2, "Facebook");
    assert(d.Cantidad(2, "Facebook") == 8);
    assert(d.Cantidad(2, "Twitter") == 10);
    cout << "OK: test_SumarAcciones" << endl;
}

void test_RestarAcciones(){
    DiccInception d(10);
    d.AgregarClienteDI(2);
    d.AgregarTitulo(2, "Facebook", 5);
    d.AgregarTitulo(2, "Twitter", 10);
    d.RestarAcciones(2, "Facebook", 3);
    assert(d.Cantidad(2, "Facebook") == 2);
    assert(d.Cantidad(2, "Twitter") == 10);
    cout << "OK: test_RestarAcciones" << endl;
}

void test_AccionesTotales(){
    DiccInception d(10);
    d.AgregarClienteDI(2);
    d.AgregarTitulo(2, "Facebook", 5);
    d.AgregarTitulo(2, "Twitter", 10);
    assert(d.AccionesTotales(2) == 15);
    cout << "OK: test_AccionesTotales" << endl;
}

void test_equal(){
    DiccInception d1(10);
    d1.AgregarClienteDI(2);
    d1.AgregarClienteDI(5);
    d1.AgregarClienteDI(7);
    d1.AgregarTitulo(2, "Facebook", 5);
    d1.AgregarTitulo(2, "Twitter", 10);
    d1.AgregarTitulo(5, "Facebook", 8);
    DiccInception d2(10);
    d1 == d2;
    assert(not(d1 == d2));
    d2.AgregarClienteDI(2);
    d2.AgregarClienteDI(5);
    d2.AgregarClienteDI(7);
    d2.AgregarTitulo(2, "Twitter", 10);
    d2.AgregarTitulo(5, "Facebook", 8);
    assert(not(d1 == d2));
    d2.AgregarTitulo(2, "Facebook", 5);
    assert(d1 == d2);
    cout << "OK: test_equal" << endl;
}

void test_mostrar(){
    DiccInception d1(10);
    d1.AgregarClienteDI(2);
    d1.AgregarClienteDI(5);
    d1.AgregarClienteDI(7);
    d1.AgregarTitulo(2, "Facebook", 5);
    d1.AgregarTitulo(2, "Twitter", 10);
    d1.AgregarTitulo(5, "Facebook", 8);
    d1.SumarAcciones(2, "Twitter", 10);
    cout << d1 << endl;
    cout << "OK: test_mostrar" << endl;
}

int main(){
    test_DefinidoDI();
    test_ClientesDI();
    test_AgregarTitulo();
    test_SumarAcciones();
    test_RestarAcciones();
    test_AccionesTotales();
    test_equal();
    test_mostrar();
    return 0;
}

