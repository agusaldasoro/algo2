#include <ostream>
#include <iostream>
#include <sstream>

using namespace std;
#include "../wolfie.h"

void test_cantClientes(){
    Conj<Cliente> cs;
    cs.Agregar(2);
    cs.Agregar(7);
    cs.Agregar(2000);
    cs.Agregar(12);
    cs.Agregar(6);
    cs.Agregar(8);
    Wolfie w(cs);
    assert(w.cantClientes() == 6);
    cout << "OK: test_cantClientes" << endl;
}

void test_titulos(){
    Conj<Cliente> cs;
    cs.Agregar(2);
    cs.Agregar(7);
    cs.Agregar(2000);
    cs.Agregar(12);
    cs.Agregar(6);
    cs.Agregar(8);
    Wolfie w(cs);
    Titulo t1 = Titulo("Google", 3, 9);
    Titulo t2 = Titulo("Facebook", 15, 6);
    Titulo t3 = Titulo("Line", 15, 6);
    w.agregarTitulo(t1);
    w.agregarTitulo(t2);
    w.agregarTitulo(t3);
    Conj<Titulo>::Iterador it = w.titulos();
    assert(it.Siguiente() == t3);
    it.Avanzar();
    assert(it.Siguiente() == t2);
    it.Avanzar();
    assert(it.Siguiente() == t1);
    cout << "OK: test_titulos" << endl;
}

void test_clientes(){
    Conj<Cliente> cs;
    cs.Agregar(2);
    cs.Agregar(7);
    cs.Agregar(2000);
    cs.Agregar(12);
    cs.Agregar(6);
    cs.Agregar(8);
    Wolfie w(cs);
    Conj<Cliente>::Iterador it = w.clientes();
    assert(it.Siguiente() == 8);
    it.Avanzar();
    assert(it.Siguiente() == 6);
    it.Avanzar();
    assert(it.Siguiente() == 12);
    it.Avanzar();
    assert(it.Siguiente() == 2000);
    it.Avanzar();
    assert(it.Siguiente() == 7);
    it.Avanzar();
    assert(it.Siguiente() == 2);
    cout << "OK: test_clientes" << endl;
}

void test_promesasDe(){
    Conj<Cliente> cs;
    cs.Agregar(2);
    cs.Agregar(7);
    cs.Agregar(2000);
    cs.Agregar(12);
    cs.Agregar(6);
    cs.Agregar(8);
    Wolfie w(cs);
    Titulo t1 = Titulo("Google", 3, 9);
    Titulo t2 = Titulo("Facebook", 15, 6);
    Titulo t3 = Titulo("Yahoo", 15, 6);
    Titulo t4 = Titulo("Microchot", 15, 6);
    w.agregarTitulo(t1);
    w.agregarTitulo(t2);
    w.agregarTitulo(t3);
    w.agregarTitulo(t4);
    Promesa p1("Google", 8, 3, compra);
    Promesa p3("Google", 8, 3, venta);
    Promesa p2("Facebook", 8, 3, compra);
    Promesa p4("Yahoo", 8, 3, compra);
    Promesa p5("Microchot", 8, 3, compra);
    w.agregarPromesa(8, p1);
    w.agregarPromesa(8, p2);
    w.agregarPromesa(8, p3);
    w.agregarPromesa(7, p4);
    w.agregarPromesa(6, p5);
    Conj<Promesa> c8;
    c8.Agregar(p1);
    c8.Agregar(p2);
    c8.Agregar(p3);
    assert(w.promesasDe(8) == c8);
    Conj<Promesa> c7;
    c7.Agregar(p4);
    assert(w.promesasDe(7) == c7);
    Conj<Promesa> c6;
    c6.Agregar(p5);
    assert(w.promesasDe(6) == c6);
    Conj<Promesa> c2000;
    assert(w.promesasDe(2000) == c2000);
    cout << "OK: test_promesasDe" << endl;
}

void test_accionesPorCliente(){
    Conj<Cliente> cs;
    cs.Agregar(2);
    Wolfie w(cs);
//  Titulo(string nom, Nat tope, Nat cot);
    Titulo t1 = Titulo("Google", 20, 4);
    w.agregarTitulo(t1);
    w.accionesPorCliente("Google",2);
//  Promesa(String nom, Nat lim, Nat c, CompraVenta tip);
    Promesa p1("Google", 8, 3, compra);
    w.agregarPromesa(2, p1);
    assert(w.accionesPorCliente("Google",2)==0);
//  (cant <= info.disponibles() && cot >= prom.limiteP())
    w.actualizarCotizacion("Google", 10);
    assert(w.accionesPorCliente("Google",2)==3);
    Promesa p2("Google", 12, 2, venta);
    w.agregarPromesa(2, p2);
    assert(w.accionesPorCliente("Google",2)==3);
    w.actualizarCotizacion("Google", 10);
    assert(w.accionesPorCliente("Google",2)==1);
    cout << "OK: test_accionesPorCliente" << endl;
}

void test_MALISIMO(){
    Conj<Cliente> cs;
    cs.Agregar(2);
    cs.Agregar(5);
    cs.Agregar(21);
    Wolfie w(cs);
//  Titulo(string nom, Nat disp, Nat cot);
    Titulo t1 = Titulo("Google", 20, 4);
    Titulo t2 = Titulo("Facebook", 15, 6);
    Titulo t3 = Titulo("Line", 50, 4);
    w.agregarTitulo(t1);
    w.agregarTitulo(t2);
    w.agregarTitulo(t3);

    assert(w.accionesPorCliente("Google",2)==0);
    assert(w.accionesPorCliente("Google",5)==0);
    assert(w.accionesPorCliente("Google",21)==0);

    assert(w.accionesPorCliente("Facebook",2)==0);
    assert(w.accionesPorCliente("Facebook",5)==0);
    assert(w.accionesPorCliente("Facebook",21)==0);

    assert(w.accionesPorCliente("Line",2)==0);
    assert(w.accionesPorCliente("Line",5)==0);
    assert(w.accionesPorCliente("Line",21)==0);

//  Promesa(String nom, Nat lim, Nat cant, CompraVenta tip);
    Promesa p1("Google", 5, 10, compra);
    w.agregarPromesa(2, p1);

    Promesa p2("Google", 5, 3, compra);
    w.agregarPromesa(5, p2);

/**     COMPRA: (cant <= info.disponibles() && cot >= prom.limiteP())
        VENTA:  (cot < sig.DamePromesa().limiteP())                          **/

    w.actualizarCotizacion("Google", 6);

    assert(w.accionesPorCliente("Google",2)==10);
    assert(w.accionesPorCliente("Google",5)==3);

    Promesa p3("Facebook", 8, 50, compra);
    w.agregarPromesa(21, p3);

    assert(w.accionesPorCliente("Facebook",21)==0);

    Promesa p4("Line", 8, 30, compra);
    w.agregarPromesa(2, p4);
    Promesa p5("Line", 8, 30, compra);
    w.agregarPromesa(5, p5);

    assert(w.accionesPorCliente("Google",2)==10);
    assert(w.accionesPorCliente("Google",5)==3);
    assert(w.accionesPorCliente("Line",2)==0);
    assert(w.accionesPorCliente("Line",5)==0);

    w.actualizarCotizacion("Line", 10);

    assert(w.accionesPorCliente("Line",2)==30);
    assert(w.accionesPorCliente("Line",5)==0);

    Promesa p6("Line", 10, 28, venta);
    w.agregarPromesa(2, p6);
    w.actualizarCotizacion("Line", 9);

    assert(w.accionesPorCliente("Line",2)==2);
    assert(w.accionesPorCliente("Line",5)==30);

    w.actualizarCotizacion("Facebook", 4);

    assert(w.accionesPorCliente("Facebook",2)==0);
    assert(w.accionesPorCliente("Facebook",5)==0);
    assert(w.accionesPorCliente("Facebook",21)==0);

    w.actualizarCotizacion("Facebook", 40);

    assert(w.accionesPorCliente("Facebook",21)==0);

    cout << "OK: test_MALISIMO" << endl;
}


int main(){
    test_cantClientes();
    test_titulos();
    test_clientes();
    test_promesasDe();
    test_accionesPorCliente();
    test_MALISIMO();
    return 0;
}
