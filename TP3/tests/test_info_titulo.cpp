#include <ostream>
#include "mini_test.h"

#include <iostream>
#include <sstream>
using namespace std;
#include "../info_titulo.h"

void test_constructor_copia(){
    Nat k = 10;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("decro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it = titulos.CrearIt();
    Promesa p1("Juan", 2, 3, venta);
    Info_Promesa i(5, p1, &k);
    Nat j = 20;
    Promesa p2("Juan",5,10,compra);
    Info_Promesa i2(6, p2, &j);
    Conj<Info_Promesa> ventas;
    ventas.Agregar(i);
    Arreglo_Ordenable c(8);
    c.Insertar(i2);
    Titulo titulo1("facebook",15 ,6);
    info_titulo infoT1(it, ventas, c, 20);
    info_titulo infoT2(infoT1);
    info_titulo infoT3(it, ventas, c, 50);
    assert(infoT1 == infoT2);
    assert(infoT1 != infoT3);
    cout << "OK: test_constructor_copia" << endl;
}

void test_dame_titulo(){
    aed2::Nat k = 10;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("decro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    Conj<Titulo>::Iterador it = titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Promesa p1("Juan", 2, 3, venta);
    Info_Promesa i(5, p1, &k);
    Nat j = 20;
    Promesa p2("Juan",5,10,compra);
    Info_Promesa i2(6, p2, &j);
    Conj<Info_Promesa> ventas;
    ventas.Agregar(i);
    Arreglo_Ordenable c(8);
    c.Insertar(i2);
    Nat disp=10;
    info_titulo infoT1(it, ventas, c, disp);
    assert(t1 == infoT1.DameTitulo());
    cout << "OK: test_dame_titulo" << endl;
}

void test_ventas(){
    Nat k = 10;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("decro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it=titulos.CrearIt();
    Promesa p1("Juan", 2, 3, venta);
    Info_Promesa i(5, p1, &k);
    aed2::Nat j = 20;
    Promesa p2("Juan",5,10,compra);
    Info_Promesa i2(6, p2, &j);
    Conj<Info_Promesa> ventas;
    ventas.Agregar(i);
    Arreglo_Ordenable c(8);
    c.Insertar(i2);
    Nat disp=10;
    info_titulo infoT1(it, ventas, c, disp);
    ASSERT(infoT1.ventas()==ventas);
    cout << "OK: test_ventas" << endl;
}

void test_compras(){
    aed2::Nat k = 10;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("decro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    typename Conj<Titulo>::Iterador it=titulos.CrearIt();
    Promesa p1("Juan", 2, 3, venta);
    Info_Promesa i(5, p1, &k);
    aed2::Nat j = 20;
    Promesa p2("Juan",5,10,compra);
    Info_Promesa i2(6, p2, &j);
    Conj<Info_Promesa> ventas;
    ventas.Agregar(i);
    Arreglo_Ordenable c(8);
    c.Insertar(i2);
    Nat disp=10;
    info_titulo infoT1(it, ventas, c, disp);
    assert(infoT1.compras()==c);
    cout << "OK: test_compras"<<endl;
}

void test_disponibles(){
    aed2::Nat k = 10;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("decro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it=titulos.CrearIt();
    Promesa p1("Juan", 2, 3, venta);
    Info_Promesa i(5, p1, &k);
    aed2::Nat j = 20;
    Promesa p2("Juan",5,10,compra);
    Info_Promesa i2(6, p2, &j);
    Conj<Info_Promesa> ventas;
    ventas.Agregar(i);
    Arreglo_Ordenable c(8);
    c.Insertar(i2);
    Nat disp=10;
    info_titulo infoT1(it, ventas, c, disp);
    assert(infoT1.disponibles() == 10);
    infoT1.disponibles() = 20;
    assert(infoT1.disponibles() == 20);
    cout << "OK: test_disponibles" << endl;
}

void test_equal(){
    aed2::Nat k = 10;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("decro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it=titulos.CrearIt();
    Promesa p1("Juan", 2, 3, venta);
    Info_Promesa i(5, p1, &k);
    aed2::Nat j = 20;
    Promesa p2("Juan",5,10,compra);
    Info_Promesa i2(6, p2, &j);
    Conj<Info_Promesa> ventas;
    ventas.Agregar(i);
    Arreglo_Ordenable c(8);
    c.Insertar(i2);
    Nat disp=10;
    info_titulo infoT1(it, ventas, c, disp);
    info_titulo infoT2(it, ventas, c, 15);
    assert(infoT1 != infoT2);
    infoT2.disponibles() = 10;
    assert(infoT1 == infoT2);
    cout << "OK: test_equal"<<endl;
}

void test_mostrar(){
    aed2::Nat k = 10;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("decro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it=titulos.CrearIt();
    Promesa p1("Juan", 2, 3, venta);
    Info_Promesa i(5, p1, &k);
    aed2::Nat j = 20;
    Promesa p2("Juan",5,10,compra);
    Info_Promesa i2(6, p2, &j);
    Conj<Info_Promesa> ventas;
    ventas.Agregar(i);
    Arreglo_Ordenable c(8);
    c.Insertar(i2);
    Nat disp=10;
    info_titulo infoT1(it, ventas, c, disp);
    //cout << infoT1 << endl;
    cout << "OK: test_mostrar"<<endl;
}
int main()
{
    test_constructor_copia();
    test_dame_titulo();
    test_ventas();
    test_compras();
    test_disponibles();
    test_equal();
    test_mostrar();
    return 0;
}
