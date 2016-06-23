#include "info_promesa.h"

Info_Promesa::Info_Promesa(Cliente cli, Promesa pro, Nat* n){
    c = cli;
    p = pro;
    acc = n;
}

Info_Promesa::Info_Promesa(const Info_Promesa& otro){
    c = otro.c;
    p = otro.p;
    acc = otro.acc;
}

Info_Promesa::~Info_Promesa() {
}

Cliente Info_Promesa::DameCliente(){
    return c;
}

const Cliente Info_Promesa::DameCliente() const{
    return c;
}

Promesa& Info_Promesa::DamePromesa(){
    return p;
}

const Promesa& Info_Promesa::DamePromesa() const{
    return p;
}

Nat Info_Promesa::AccionesDelCliente(){
    return *acc;
}

const Nat Info_Promesa::AccionesDelCliente() const{
    return *acc;
}


bool operator==(const Info_Promesa& a, const Info_Promesa& b){
    return a.DameCliente() == b.DameCliente() && a.AccionesDelCliente() == b.AccionesDelCliente() && a.DamePromesa() == b.DamePromesa();
}
bool operator !=(const Info_Promesa& a, const Info_Promesa& b){
    return !(a==b);
}

std::ostream& operator<<(std::ostream& os, const Info_Promesa& i){
    os << "Cliente: " << i.DameCliente() << ", Promesa: " << i.DamePromesa()<< ", AccionesDelCliente: " << i.AccionesDelCliente();
    return os;
}
