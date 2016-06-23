#include <ostream>
#include <iostream>
#include <sstream>
#include "../diccMemory.h"
using namespace std;


void test_definidoDM(){
    diccMemory nuevoDicc;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("dedro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it = titulos.CrearIt();
    nuevoDicc.agregarTituloDM(it,5);
    it.Avanzar();
    nuevoDicc.agregarTituloDM(it,5);
    assert(nuevoDicc.definidoDM("facebook"));
    assert(nuevoDicc.definidoDM("dedro"));
    assert(!nuevoDicc.definidoDM("pedro"));
    cout << "OK: test_definidoDM" <<endl;
}

void test_obtenerDM(){
    diccMemory nuevoDicc;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("dedro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it = titulos.CrearIt();
    info_titulo infoT1(it, Conj<Info_Promesa>(), Arreglo_Ordenable(5), 15);
    nuevoDicc.agregarTituloDM(it,5);
    it.Avanzar();
    info_titulo infoT2(it, Conj<Info_Promesa>(), Arreglo_Ordenable(5), 15);
    nuevoDicc.agregarTituloDM(it,5);
    assert(nuevoDicc.obtenerDM("facebook") == infoT1);
    assert(nuevoDicc.obtenerDM("dedro") == infoT2);
    cout << "OK: test_obtenerDM" << endl;
}

void test_titulosDM(){
    diccMemory nuevoDicc;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("pedro", 3, 9);
    Titulo t2 = Titulo("dedro", 15, 6);
    Titulo t3 = Titulo("facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it = titulos.CrearIt();
    nuevoDicc.agregarTituloDM(it,5);
    it.Avanzar();
    nuevoDicc.agregarTituloDM(it,5);
    Conj<string> claves;
    claves.Agregar("dedro");
    claves.Agregar("facebook");
    assert(nuevoDicc.titulosDM() == claves);
    it.Avanzar();
    nuevoDicc.agregarTituloDM(it,5);
    claves.Agregar("pedro");
    assert(nuevoDicc.titulosDM() == claves);
    cout << "OK: test_titulosDM" << endl;
}

void test_promesasDeDM(){
	diccMemory nuevoDicc;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("Google", 3, 9);
    Titulo t2 = Titulo("Yahoo", 15, 6);
    Titulo t3 = Titulo("Facebook", 15, 6);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it = titulos.CrearIt();

    Nat k = 10;
    Promesa p1("Facebook", 2, 3, venta);
    Info_Promesa i1(5, p1, &k);
    Nat j = 20;
    Promesa p2("Yahoo",5,10,compra);
    Info_Promesa i2(6, p2, &j);

    Conj<Promesa> ventas;
    ventas.Agregar(p1);

    Conj<Promesa> compras;
    compras.Agregar(p2);

    nuevoDicc.agregarTituloDM(it,8);

    it.Avanzar();
    nuevoDicc.agregarTituloDM(it,8);

    nuevoDicc.AgregarPromesa(p1, 5, &k);
    nuevoDicc.AgregarPromesa(p2, 6, &j);

    assert(nuevoDicc.promesasDeDM(5) == ventas);
    assert(nuevoDicc.promesasDeDM(6) == compras);
    cout << "OK: test_promesasDeDM" << endl;
}

void test_agregarTituloDM(){
    diccMemory dicc;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("Facebook", 3, 9);
    Titulo t2 = Titulo("Twitter", 15, 6);
    Titulo t3 = Titulo("Fotolog", 1, 8);
    Titulo t4 = Titulo("Terra", 57, 10);
    Titulo t5 = Titulo("Nike", 1, 8);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it = titulos.CrearIt();
    dicc.agregarTituloDM(it, 20);
    it.Avanzar();
    dicc.agregarTituloDM(it, 14);
    it.Avanzar();
    dicc.agregarTituloDM(it, 6);
    Conj<Titulo> titulos2;
    titulos2.Agregar(t4);
    Conj<Titulo>::Iterador it2 = titulos2.CrearIt();
    dicc.agregarTituloDM(it2, 30);
    assert(dicc.definidoDM("Facebook"));
    assert(dicc.definidoDM("Twitter"));
    assert(dicc.definidoDM("Fotolog"));
    assert(dicc.definidoDM("Terra"));
    assert(not(dicc.definidoDM("Nike")));
    cout << "OK: test_agregarTituloDM" << endl;
}

void test_equal(){
    diccMemory dicc1;
    diccMemory dicc2;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("Facebook", 3, 9);
    Titulo t2 = Titulo("Twitter", 15, 6);
    Titulo t3 = Titulo("Fotolog", 1, 8);
    Titulo t4 = Titulo("Terra", 57, 10);
    Titulo t5 = Titulo("Nike", 1, 8);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it = titulos.CrearIt();
    dicc1.agregarTituloDM(it, 20);
    dicc2.agregarTituloDM(it, 20);
    it.Avanzar();
    dicc1.agregarTituloDM(it, 14);
    dicc2.agregarTituloDM(it, 14);
    it.Avanzar();
    dicc1.agregarTituloDM(it, 6);
    dicc2.agregarTituloDM(it, 6);
    Conj<Titulo> titulos2;
    titulos2.Agregar(t4);
    Conj<Titulo>::Iterador it2 = titulos2.CrearIt();
    dicc1.agregarTituloDM(it2, 30);
    assert(not(dicc1==dicc2));
    dicc2.agregarTituloDM(it2, 30);
    assert(dicc1==dicc2);
    cout << "OK: test_equal" << endl;
}

void test_mostrar(){
    diccMemory dicc;
    Conj<Titulo> titulos;
    Titulo t1 = Titulo("Facebook", 3, 9);
    Titulo t2 = Titulo("Twitter", 15, 6);
    Titulo t3 = Titulo("Fotolog", 1, 8);
    Titulo t4 = Titulo("Terra", 57, 10);
    Titulo t5 = Titulo("Nike", 1, 8);
    titulos.Agregar(t1);
    titulos.Agregar(t2);
    titulos.Agregar(t3);
    Conj<Titulo>::Iterador it = titulos.CrearIt();
    dicc.agregarTituloDM(it, 20);
    it.Avanzar();
    dicc.agregarTituloDM(it, 14);
    it.Avanzar();
    dicc.agregarTituloDM(it, 6);
    Conj<Titulo> titulos2;
    titulos2.Agregar(t4);
    Conj<Titulo>::Iterador it2 = titulos2.CrearIt();
    dicc.agregarTituloDM(it2, 30);
    //cout << dicc << endl;
    cout << "OK: test_mostrar" << endl ;
}
int main(){
    test_definidoDM();
    test_obtenerDM();
    test_titulosDM();
    test_promesasDeDM();
    test_agregarTituloDM();
    test_equal();
    test_mostrar();
    return 0;
}
