#include <ostream>
#include <iostream>
#include <sstream>
using namespace std;
#include "../arreglo_ordenable.h"

void test_constructor_copia(){
    aed2::Nat k = 10;
    Promesa p1("Juan", 2, 3, venta);
    Promesa p2("Juan", 2, 3, compra);
    Info_Promesa i1(5, p1, &k);
    Info_Promesa i2(5, p2, &k);
    Info_Promesa i3(15, p1, &k);
    Arreglo_Ordenable a1(9);
    a1.Insertar(i1);
    a1.Insertar(i2);
    a1.Insertar(i3);
    Arreglo_Ordenable a2(a1);
    assert(a1 == a2);
    cout << "OK: test_constructor_copia" << endl;
}
void test_definido(){
    aed2::Nat k = 10;
    Promesa p1("Juan", 2, 3, venta);
    Promesa p2("Juan", 2, 3, compra);
    Info_Promesa i1(5, p1, &k);
    Info_Promesa i2(5, p2, &k);
    Info_Promesa i3(15, p1, &k);
    Arreglo_Ordenable p(9);
    p.Insertar(i1);
    p.Insertar(i2);
    p.Insertar(i3);
    assert(p.Definido(0));
    assert(p.Definido(1));
    assert(p.Definido(2));
    assert(not p.Definido(3));
    cout << "OK: test_definido" << endl;
}
void test_dame_indice(){
    aed2::Nat k = 10;
    Promesa p1("Juan", 2, 3, venta);
    Promesa p2("Juan", 2, 3, compra);
    Info_Promesa i1(5, p1, &k);
    Info_Promesa i2(5, p2, &k);
    Info_Promesa i3(15, p1, &k);
    Arreglo_Ordenable p(9);
    p.Insertar(i1);
    p.Insertar(i2);
    p.Insertar(i3);
    assert(p.DameIndice(0) == i1);
    assert(p.DameIndice(2) == i3);
    cout << "OK: test_dame_indice" << endl;
}
void test_borrar(){
    aed2::Nat k = 10;
    Promesa p1("Juan", 2, 3, venta);
    Promesa p2("Juan", 2, 3, compra);
    Info_Promesa i1(5, p1, &k);
    Info_Promesa i2(5, p2, &k);
    Info_Promesa i3(15, p1, &k);
    Arreglo_Ordenable p(9);
    p.Insertar(i1);
    p.Insertar(i2);
    p.Insertar(i3);
    p.Borrar(1);
    assert(p.Definido(0));
    assert(not p.Definido(1));
    assert(p.Definido(2));
    cout << "OK: test_borrar" << endl;
}
void test_tamanho(){
    Arreglo_Ordenable p1(9);
    assert(p1.Tamanho() == 9);
    Arreglo_Ordenable p2(10);
    assert(p2.Tamanho() == 10);
    cout << "OK: test_tamanho" << endl;
}
void test_dame_promesas(){
    aed2::Nat k = 10;
    Promesa p1("Juan", 2, 3, venta);
    Promesa p2("Juan", 2, 3, compra);
    Info_Promesa i1(5, p1, &k);
    Info_Promesa i2(5, p2, &k);
    Info_Promesa i3(15, p1, &k);
    Arreglo_Ordenable p(9);
    p.Insertar(i1);
    p.Insertar(i2);
    p.Insertar(i3);
    Conj<Info_Promesa> c1;
    c1.AgregarRapido(i1);
    c1.AgregarRapido(i2);
    c1.AgregarRapido(i3);
    Conj<Info_Promesa> c2;
    c2.AgregarRapido(i1);
    c2.AgregarRapido(i3);
    assert(p.DamePromesas() == c1);
    p.Borrar(1);
    assert(p.DamePromesas() == c2);
    cout << "OK: test_dame_promesas" << endl;
}
void test_ordenar(){
    aed2::Nat k = 10;
    aed2::Nat q = 9;
    aed2::Nat l = 15;
    Promesa p1("Juan", 2, 3, venta);
    Promesa p2("Juan", 2, 3, compra);
    Info_Promesa i1(5, p1, &k);
    Info_Promesa i2(5, p2, &q);
    Info_Promesa i3(15, p1, &l);
    Arreglo_Ordenable a1(9);
    a1.Insertar(i1);
    a1.Insertar(i2);
    a1.Insertar(i3);
    Arreglo_Ordenable a4(9);
    a4.Insertar(i1);
    a4.Insertar(i2);
    a4.Insertar(i3);
    Arreglo_Ordenable a2(9);
    a2.Insertar(i3);
    a2.Insertar(i1);
    Arreglo_Ordenable a3(9);
    a3.Insertar(i3);
    a3.Insertar(i1);
    a3.Insertar(i2);
    a1.Ordenar();
    assert(a1 == a3);
    a4.Borrar(1);
    a4.Ordenar();
    assert(a4 == a2);
    cout << "OK: test_ordenar" << endl;
}
void test_equal(){
    aed2::Nat k = 10;
    aed2::Nat q = 9;
    aed2::Nat l = 15;
    Promesa p1("Juan", 2, 3, venta);
    Promesa p2("Juan", 2, 3, compra);
    Info_Promesa i1(5, p1, &k);
    Info_Promesa i2(5, p2, &q);
    Info_Promesa i3(15, p1, &l);
    Arreglo_Ordenable a1(9);
    a1.Insertar(i1);
    a1.Insertar(i2);
    a1.Insertar(i3);
    Arreglo_Ordenable a2(9);
    a2.Insertar(i1);
    a2.Insertar(i2);
    assert(not (a1 == a2));
    a2.Insertar(i3);
    assert(a1 == a2);
    cout << "OK: test_equal" << endl;
}
void test_mostrar(){
    aed2::Nat k = 10;
    aed2::Nat q = 9;
    aed2::Nat l = 15;
    Promesa p1("Juan", 2, 3, venta);
    Promesa p2("Juan", 2, 3, compra);
    Info_Promesa i1(5, p1, &k);
    Info_Promesa i2(5, p2, &q);
    Info_Promesa i3(15, p1, &l);
    Arreglo_Ordenable a(5);
    a.Insertar(i1);
    a.Insertar(i2);
    a.Insertar(i3);
    ostringstream info_prom_os1, info_prom_os2, info_prom_os3;
    info_prom_os1 << i1;
    info_prom_os2 << i2;
    info_prom_os3 << i3;
    string info_prom_str1(info_prom_os1.str());
    string info_prom_str2(info_prom_os2.str());
    string info_prom_str3(info_prom_os3.str());
    ostringstream arr_os;
    arr_os << a;
    string arr_str = arr_os.str();
    assert(arr_str ==  ("[" + info_prom_str1 + "," + info_prom_str2 + "," + info_prom_str3  + ",Null,Null]"));
    cout << "OK: test_mostrar" << endl;
}

int main()
{
    test_constructor_copia();
    test_definido();
    test_dame_indice();
    test_borrar();
    test_tamanho();
    test_dame_promesas();
    test_ordenar();
    test_equal();
    test_mostrar();
    return 0;
}
