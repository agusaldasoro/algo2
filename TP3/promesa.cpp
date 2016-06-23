#include "promesa.h"
Promesa::Promesa()
    :limite(0),cant(0),nombrePromesa(""),tipo(venta){
}

Promesa::Promesa(String nom, Nat lim, Nat c, CompraVenta tip)
    :limite(lim), cant(c), nombrePromesa(nom), tipo(tip){
}

Promesa::Promesa(const Promesa& otra){
    limite = otra.limiteP();
    cant = otra.cantidadP();
    nombrePromesa = otra.nombreP();
    tipo = otra.tipoP();
}

const String Promesa::nombreP() const{
    return nombrePromesa;
}

String Promesa::nombreP(){
    return nombrePromesa;
}

Nat Promesa::limiteP(){
    return limite;
}

const Nat Promesa::limiteP() const{
    return limite;
}

const Nat Promesa::cantidadP() const{
    return cant;
}

Nat Promesa::cantidadP(){
    return cant;
}

CompraVenta Promesa::tipoP(){
    return tipo;
}

const CompraVenta Promesa::tipoP() const{
    return tipo;
}

bool Promesa::operator==(const Promesa& otra) const{
    return (nombrePromesa == otra.nombrePromesa && cant == otra.cant && limite == otra.limite && tipo == otra.tipo);
}

bool Promesa::operator!=(const Promesa& otra) const{
    return not(*this == otra);
}


ostream& operator<<(ostream& os, const Promesa& p) {
    os << "{NombreP: " << p.nombreP() << ", " ;
    os << "Limite: " << p.limiteP() << ", " ;
    os << "Cantidad: " << p.cantidadP() << ", " ;
    os << "Tipo: " ;
    if(p.tipoP()==compra){
        os << "compra" ;
    }else{
        os << "venta" ;
    }
    os <<  "}";
    return os;
}

