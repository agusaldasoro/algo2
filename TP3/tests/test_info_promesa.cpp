#include <ostream>
#include <iostream>
#include <sstream>
using namespace std;
#include "../info_promesa.h"

void test_dame_cliente(){
    aed2::Nat k = 10;
    Promesa p("Juan", 2, 3, venta);
    Info_Promesa i(5, p, &k);
    assert(i.DameCliente() == 5);
    cout << "OK: test_dame_cliente" << endl;
}
void test_dame_promesa(){
    aed2::Nat k = 10;
    Promesa p("Juan", 2, 3, venta);
    Info_Promesa i(5, p, &k);
    assert(i.DamePromesa() == p);
    cout << "OK: test_dame_promesa" << endl;
}
void test_acciones_del_cliente(){
    aed2::Nat k = 10;
    Promesa p("Juan", 2, 3, venta);
    Info_Promesa i(5, p, &k);
    assert(i.AccionesDelCliente() == 10);
    k = 20;
    assert(i.AccionesDelCliente() == 20);
    k = 59;
    assert(i.AccionesDelCliente() == 59);
    cout << "OK: test_acciones_del_cliente" << endl;
}
void test_equal(){
    aed2::Nat k = 10;
    Promesa p1("Juan", 2, 3, venta);
    Info_Promesa i1(5, p1, &k);
    Promesa p2("Juan", 2, 3, compra);
    Info_Promesa i2(5, p2, &k);
    k = 20;
    Info_Promesa i3(5, p1, &k);
    assert(not(i1 == i2));
    assert(i1 == i3);
    cout << "OK: test_equal" << endl;
}
void test_mostrar(){
    aed2::Nat k = 10;
    Promesa p("Juan", 2, 3, venta);
    Info_Promesa i(5, p, &k);
    std::ostringstream pro_os;
    pro_os << p;
    std::string pro_str = "Cliente: 5, Promesa: " + pro_os.str() + + ", AccionesDelCliente: 10";
    std::ostringstream info_os;
    info_os << i;
    std::string info_str = info_os.str();
    assert(info_str ==  pro_str);
    cout << "OK: test_mostrar" << endl;
}

int main(){
    test_dame_cliente();
    test_dame_promesa();
    test_acciones_del_cliente();
    test_equal();
    test_mostrar();
    return 0;
}
