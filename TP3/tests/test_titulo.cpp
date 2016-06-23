
#include <ostream>
#include <iostream>
using namespace std;
#include "../titulo.h"


void test_CrearPorCopia(){
    Titulo t1("Facebook", 3, 5);
    Titulo t2(t1);
    assert(t1==t2);
    cout << "OK: test_CrearPorCopia" << endl;
}

void test_maximaCantidad(){
    Titulo t1("Facebook", 3, 5);
    assert(t1.maximaCantidad()==3);
    cout << "OK: test_maximaCantidad" << endl;
}

void test_nombreT(){
    Titulo t1("Facebook", 3, 5);
    assert(t1.nombreT()=="Facebook");
    cout << "OK: test_nombreT" << endl;
}

void test_cotizacion(){
    Titulo t1("Facebook", 3, 5);
    assert(t1.cotizacion()==5);
    cout << "OK: test_cotizacion" << endl;
}

void test_recotizar(){
    Titulo t1("Facebook", 3, 5);
    t1.recotizar(6);
    assert(t1.cotizacion()==6);
    cout << "OK: test_recotizar" << endl;
}

void test_enAlza(){
    Titulo t1("Facebook", 3, 5);
    assert(t1.enAlza()==false);
    t1.recotizar(6);
    assert(t1.enAlza()==true);
    t1.recotizar(2);
    assert(t1.enAlza()==false);
    cout << "OK: test_enAlza" << endl;
}

void test_equal(){
    Titulo t1("Facebook", 3, 5);
    Titulo t2("Twitter", 3, 5);
    assert(not(t1==t2));
    Titulo t3("Facebook", 3, 3);
    assert(not(t1==t3));
    t3.recotizar(5);
    assert(not(t1==t3));
    t3.recotizar(13);
    t3.recotizar(5);
    assert(t1==t3);
    cout << "OK: test_equal" << endl;
}

void test_mostrar(){
    Titulo t1("Facebook", 3, 5);
    cout << t1 << endl;
    cout << "OK: test_mostrar" << endl;
}

int main(){
    test_CrearPorCopia();
    test_maximaCantidad();
    test_nombreT();
    test_cotizacion();
    test_recotizar();
    test_enAlza();
    test_equal();
    test_mostrar();
    return 0;
}
