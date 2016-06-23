#include "info_titulo.h"

info_titulo::info_titulo()
    :iteradorAtit_(), ventas_(), compras_(), disponibles_(0){
}

info_titulo::info_titulo(Conj<Titulo>::Iterador t, Conj<Info_Promesa> vt, Arreglo_Ordenable cp, Nat d)
    :iteradorAtit_(t), ventas_(vt), compras_(cp), disponibles_(d){
}

info_titulo::~info_titulo(){}

bool info_titulo::operator==(const info_titulo& b){
    if(not(iteradorAtit_.Siguiente()==b.iteradorAtit_.Siguiente())){
        return false;
    }
    if(not(compras_==b.compras_)){
        return false;
    }
    if(not(disponibles_==b.disponibles_)){
        return false;
    }
    if(not(ventas_==b.ventas_)){
        return false;
    }
	return true;
}

bool info_titulo::operator!=(const info_titulo& b){
	return !(*this == b);
}
std::ostream& operator<<(std::ostream& os, info_titulo& i);


info_titulo::info_titulo(const info_titulo& otra){
	iteradorAtit_=otra.iteradorAtit_;
	ventas_=otra.ventas_;
	compras_=otra.compras_;
	disponibles_=otra.disponibles_;
}

void info_titulo::Recotizar(Nat cot){
    Titulo nuevoTitulo(iteradorAtit_.Siguiente());
    nuevoTitulo.recotizar(cot);
    iteradorAtit_.EliminarSiguiente();
    iteradorAtit_.AgregarComoSiguiente(nuevoTitulo);
}

Conj<Info_Promesa>& info_titulo::ventas(){
	return ventas_;
}

const Conj<Info_Promesa>& info_titulo::ventas() const{
    return ventas_;
}

Arreglo_Ordenable& info_titulo::compras(){
	return compras_;
}

const Arreglo_Ordenable& info_titulo::compras() const{
    return compras_;
}

Nat& info_titulo::disponibles(){
	return disponibles_;
}

const Nat& info_titulo::disponibles() const{
    return disponibles_;
}

const Titulo& info_titulo::DameTitulo() const{
    return iteradorAtit_.Siguiente();
}

std::ostream& operator<<(ostream& os, const info_titulo& i){
    os << "---Informacion de Titulo---" << endl;
	os <<  endl << i.DameTitulo() << endl;
	os << "PROMESAS DE VENTA:"<< endl << i.ventas() << endl << endl;
	os << "PROMESAS DE COMPRA:"<< endl << i.compras() << endl << endl;
	os << "CANTIDAD DE ACCIONES DISPONIBLES:"<< endl << i .disponibles() << endl;
	os << "---------------------------" << endl;
    return os;
}
