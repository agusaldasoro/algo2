#include "diccIncep.h"
DiccInception::DiccInception()
	: e(typename Diccionario_Finito<Tupla>::Diccionario_Finito(0)) {
}

DiccInception::DiccInception(Nat n)
	: e(typename Diccionario_Finito<Tupla>::Diccionario_Finito(n)) {
}


void DiccInception::AgregarClienteDI(Cliente cliente){
	assert(DefinidoDI(cliente) == false);
	Tupla nueva;
	nueva.titulos = typename DiccString<Nat>::DiccString();
	nueva.accionesTotales = 0;
	e.Definir(cliente, nueva);
}

DiccInception::~DiccInception(){
}


bool DiccInception::DefinidoDI(Cliente cliente){
	return e.Definida(cliente);
}


const Conj<Cliente> DiccInception::ClientesDI(){
	return e.Claves();
}


void DiccInception::AgregarTitulo(Cliente cliente, Nombre nt, Nat n){
    assert(not(TitulosDe(cliente).Pertenece(nt)));
    e.Obtener(cliente).titulos.DefinirDS(nt, n);
	Nat& r = e.Obtener(cliente).accionesTotales;
    r = r + n;
}



void DiccInception::SumarAcciones(Cliente cliente, Nombre nt, Nat n){
	assert(e.Definida(cliente));
	if(not(e.Obtener(cliente).titulos.DefinidoDS(nt))){
        AgregarTitulo(cliente, nt, n);
	}else{
        Nat& m = e.Obtener(cliente).titulos.ObtenerDS(nt);
        m = m + n;
        Nat& r = e.Obtener(cliente).accionesTotales;
        r = r + n;
	}
}


void DiccInception::RestarAcciones(Cliente cliente, Nombre nt, Nat n){
	assert(e.Definida(cliente));
	assert(e.Obtener(cliente).titulos.DefinidoDS(nt));
	Nat& m = e.Obtener(cliente).titulos.ObtenerDS(nt);
	m = m - n;
	Nat& r = e.Obtener(cliente).accionesTotales;
	r = r - n;
}


const Conj<string> DiccInception::TitulosDe(Cliente cliente){
	assert(e.Definida(cliente));
	Conj<string> c;
	c = e.Obtener(cliente).titulos.ClavesDS();
	typename Conj<string>::Iterador it = c.CrearIt();
	while(it.HaySiguiente()){
        if(e.Obtener(cliente).titulos.ObtenerDS(it.Siguiente()) == 0){
            it.EliminarSiguiente();
        }else{
            it.Avanzar();
        }
	}
	return c;
}


Nat DiccInception::Cantidad(Cliente cliente, Nombre nt) const{
    if(e.Obtener(cliente).titulos.DefinidoDS(nt)){
        return e.Obtener(cliente).titulos.ObtenerDS(nt);
    }else{
        return 0;
    }
}

Nat& DiccInception::AccionesTotales(Cliente cliente){
	return e.Obtener(cliente).accionesTotales;
}


bool DiccInception::operator==(const DiccInception& otro)const{
    if(not(e.Claves()==otro.e.Claves())){
        return false;
    }else{
        Conj<Nat> c(otro.e.Claves());
        Conj<Nat>::const_Iterador it = c.CrearIt();
        while(it.HaySiguiente()){
            Nat clave = it.Siguiente();
               if(not(e.Obtener(clave).titulos == otro.e.Obtener(clave).titulos)){
                return false;
            }
            it.Avanzar();
        }
    }
    return true;
}




std::ostream& operator<<(std::ostream& o, const DiccInception& d){
	Conj<Nat> c(d.e.Claves());
    Conj<Nat>::const_Iterador it = c.CrearIt();
    o << '{' << endl ;
    while(it.HaySiguiente()){
        Nat clave = it.Siguiente();
    	o << "------------" << endl;
        o << clave << endl;
    	o << endl;
        Nat n = d.e.Obtener(clave).accionesTotales;
    	o << "Cantidad de Acciones Totales: " << n << endl;
    	o << endl;
    	o << "Total de Titulos:" << endl;
        o << d.e.Obtener(clave).titulos << endl;
    	o << "------------" << endl;
       it.Avanzar() ;
    }
    o << '}' << endl;
    return o;
}
