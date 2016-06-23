#include "titulo.h"

Titulo::Titulo()
    :maxCant(0),coti(0),nombreTitulo(""),ENAlza(true){};


Titulo::Titulo(String nom, Nat tope, Nat cot)
     :maxCant(tope), coti(cot), nombreTitulo(nom), ENAlza(true){};

Titulo::Titulo(const Titulo& otro){
    nombreTitulo = otro.nombreT();
    maxCant = otro.maximaCantidad();
    coti = otro.cotizacion();
    ENAlza = otro.enAlza();
}


Nat Titulo::maximaCantidad(){
    return maxCant;
}

const Nat Titulo::maximaCantidad() const{
    return maxCant;
}

String Titulo::nombreT(){
    return nombreTitulo;
}

const String Titulo::nombreT() const{
    return nombreTitulo;
}

bool Titulo::enAlza(){
    return ENAlza;
}

const bool Titulo::enAlza() const{
    return ENAlza;
}

Nat Titulo::cotizacion(){
    return coti;
}

const Nat Titulo::cotizacion() const{
    return coti;
}

void Titulo::recotizar(Nat d){
    if (d>coti){
        ENAlza = true;
    }else {
        ENAlza = false;
    }
    coti = d;
}



bool Titulo::operator==(const Titulo& otro) const {
    return maxCant == otro.maxCant && coti == otro.coti && nombreTitulo == otro.nombreTitulo && ENAlza == otro.ENAlza;
}

bool Titulo::operator!=(const Titulo otro) const {
    return !(*this==otro);
}

std::ostream& operator<<(ostream& os, const Titulo& t) {
    os << "...TITULO..." << endl;
    os << "Nombre: " << t.nombreT() << endl;
    os << "Cotizacion: " << t.cotizacion() << endl;
    os <<"Maxima cantidad: " << t.maximaCantidad() << endl;
    os <<"En alza: " << t.enAlza() << endl;
    os << "............." << endl;
    return os;
}
