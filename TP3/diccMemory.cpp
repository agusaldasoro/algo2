#include "diccMemory.h"
diccMemory::diccMemory()
:fueModificado_(true),cliente_(0),ultimasPromesas_(Conj<Promesa>()),diccPorTitulo_(DiccString<info_titulo>()) {}

void diccMemory::agregarTituloDM(Conj<Titulo>::Iterador t, Nat num){
	string nombre = t.Siguiente().nombreT();
    assert(not(definidoDM(nombre)));
    info_titulo nuevoInfoT(t, Conj<Info_Promesa>(), Arreglo_Ordenable(num), t.Siguiente().maximaCantidad());
    diccPorTitulo_.DefinirDS(nombre, nuevoInfoT);
}

bool diccMemory::definidoDM(String nt){
	return diccPorTitulo_.DefinidoDS(nt);
}

info_titulo& diccMemory::obtenerDM(string nt){
    assert(definidoDM(nt)==true);
	return diccPorTitulo_.ObtenerDS(nt);
}

Conj<string> diccMemory::titulosDM() const{
	return diccPorTitulo_.ClavesDS();
}

void diccMemory::AgregarPromesa(Promesa p, Cliente cl, Nat* n){
    assert(definidoDM(p.nombreP()));
	fueModificado_= true;
	Info_Promesa datosProm(cl, p, n);
	if (p.tipoP() == venta){
		diccPorTitulo_.ObtenerDS(p.nombreP()).ventas().AgregarRapido(datosProm);
	}else{
		diccPorTitulo_.ObtenerDS(p.nombreP()).compras().Insertar(datosProm);
	}
}

const Conj<Promesa>& diccMemory::promesasDeDM(Cliente cl){
	if (!fueModificado_ && cliente_== cl){
		return ultimasPromesas_;
	}else{
	    ultimasPromesas_ = Conj<Promesa>();
		Conj<string>::const_Iterador it = diccPorTitulo_.ClavesDS().CrearIt();
		while(it.HaySiguiente()){
            ///Recorro ventas
            Conj<Info_Promesa>& ventas = diccPorTitulo_.ObtenerDS(it.Siguiente()).ventas();
			Conj<Info_Promesa>::const_Iterador itVentas = ventas.CrearIt();
			while(itVentas.HaySiguiente() && itVentas.Siguiente().DameCliente() != cl){
				itVentas.Avanzar();
			}
			if(itVentas.HaySiguiente())
                ultimasPromesas_.AgregarRapido(itVentas.Siguiente().DamePromesa());
            ///Recorro compras
			Nat i = 0;
			Arreglo_Ordenable& compras = diccPorTitulo_.ObtenerDS(it.Siguiente()).compras();
			while(i < compras.Tamanho()){
				if(compras.Definido(i) && compras.DameIndice(i).DameCliente() == cl){
					ultimasPromesas_.AgregarRapido(compras.DameIndice(i).DamePromesa());
                    i = compras.Tamanho();
				}else{
					i++;
				}
			}
			it.Avanzar();
		}
		fueModificado_ = false;
		cliente_ = cl;
		return ultimasPromesas_;
	}
}

bool diccMemory::operator==(const diccMemory& otro)const{
    return fueModificado_ == otro.fueModificado_ && cliente_ == otro.cliente_ && ultimasPromesas_ == otro.ultimasPromesas_ && diccPorTitulo_ == otro.diccPorTitulo_;
}


std::ostream& operator<<(std::ostream& os, const diccMemory& d){
    os << "___***Diccionario Con Memoria***___" << endl << endl;
	if(d.fueModificado_==false){
        os << "No tiene promesas guardadas que sirvan." << endl ;
	}else{
        os <<  "Tiene Promesas Guardadas..." << endl ;
        os <<  "Cliente:" << d.cliente_ << endl ;
        os <<  d.ultimasPromesas_ << endl ;
	}
    os << endl;
    os << "Su diccionario es..." << endl;
    os << d.diccPorTitulo_ << endl;
	os << "___________________________________" << endl;
    return os;
}


