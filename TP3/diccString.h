
#ifndef DICC_STRING_H_
#define	DICC_STRING_H_

#include "aed2.h"
#include <string>
#include <ostream>
#include <iostream>
using namespace std;
using namespace aed2;

template<typename T>
class DiccString{
	public:
		/**
		CONSTRUCTOR
		*Construye un diccionario vacio.
		**/
		DiccString();

        /**
        *Construye un diccionario por copia.
		**/
        DiccString(const DiccString<T>&);


		/**
		DESTRUCTOR
		**/
		~DiccString();

		/**
		DEFINIR
		*Recibe una clave con su significado de tipo T y la define.
		*Si ya estaba definida, la reescribe.
		**/
		void DefinirDS(std::string clave, T significado);

		/**
		DEFINIDO?
		*Devuelve un bool, que es true si la clave pasada esta definida en el diccionario.
		**/
		bool DefinidoDS(std::string clave) const;

		/**
		OBTENER
		*Dada una clave, devuelve su significado.
		*PRE: La clave esta definida.
		--PRODUCE ALIASING--
		**/
		T& ObtenerDS(std::string clave);
		const T& ObtenerDS(std::string clave) const;

		/**
		CLAVES
		*Devuelve las claves del diccionario.
		--NO PRODUCE ALIASING--
		**/
		const Conj<std::string>& ClavesDS() const;

        bool operator==(const DiccString<T>& otro) const;

	private:

		struct Nodo{
				Arreglo<Nodo*> siguientes;
				typename Lista<T>::Iterador definicion;
                Nodo():
                    siguientes(256), definicion(){}
        };

        void BorrarCadena(Nodo* nod);

		Nodo* definiciones;
		Conj<std::string> claves;
		Lista<T> significados;


};

template <typename T>
DiccString<T>::DiccString()
	: definiciones(NULL), claves(), significados() {
}

template <typename T>
DiccString<T>::DiccString(const DiccString& d){
	this->claves = Conj<std::string>();
	this->significados = Lista<T>();
	this->definiciones = NULL;
	Conj<string> c(d.ClavesDS());
	Conj<string>::const_Iterador it = c.CrearIt();
	while(it.HaySiguiente()){
        string clave(it.Siguiente());
        T sign(d.ObtenerDS(it.Siguiente()));
		DefinirDS(clave, sign);
		it.Avanzar();
	}
}

template <typename T>
DiccString<T>::~DiccString(){
	if(definiciones != NULL){
        BorrarCadena(definiciones);
	}
}
template <typename T>
void DiccString<T>::BorrarCadena(Nodo* nod){
    Arreglo<Nodo*> arr = (*nod).siguientes;
    for(Nat i = 0; i < arr.Tamanho(); i++){
        if(arr.Definido(i)){
            BorrarCadena(arr[i]);
        }
    }
    delete nod;
}

template <typename T>
void DiccString<T>::DefinirDS(std::string clave, T significado){
	claves.Agregar(clave);
	typename Lista<T>::Iterador it = significados.AgregarAtras(significado);
	if(definiciones == NULL){
        definiciones = new Nodo();
	}
	Nodo* actual = definiciones;
	for(Nat i = 0; i < clave.length();i++){
		if(actual->siguientes.Definido(int(clave[i]))==false){
			Nodo* nuevoNodo = new Nodo();
			actual->siguientes.Definir(int(clave[i]), nuevoNodo);
		}
        actual = actual->siguientes[int(clave[i])];
	}
	actual->definicion = it;
}


template <typename T>
bool DiccString<T>::DefinidoDS(std::string clave) const{
    return claves.Pertenece(clave);
}

template <typename T>
T& DiccString<T>::ObtenerDS(std::string clave){
	assert(DefinidoDS(clave));
	Nodo* actual;
	actual = definiciones;
	for (Nat i = 0; i < clave.length(); i++){
        actual = actual->siguientes[int(clave[i])];
	}
	typename Lista<T>::Iterador it;
	it = actual->definicion;
	return it.Siguiente();
}

template <typename T>
const T& DiccString<T>::ObtenerDS(std::string clave) const{
	assert(DefinidoDS(clave));
	Nodo* actual;
	actual = definiciones;
	for (Nat i = 0; i < clave.length(); i++){
        actual = actual->siguientes[int(clave[i])];
	}
	typename Lista<T>::Iterador it;
	it = actual->definicion;
	return it.Siguiente();
}


template <typename T>
const Conj<std::string>& DiccString<T>::ClavesDS() const{
	return claves;
}

template<typename T>
bool DiccString<T>::operator==(const DiccString<T>& otro) const{
    if(not(ClavesDS()==otro.ClavesDS())){
        return false;
    }else{
        Conj<string> c(otro.ClavesDS());
        Conj<string>::const_Iterador it = c.CrearIt();
        while(it.HaySiguiente()){
            std::string clave = it.Siguiente();
            T sig = ObtenerDS(clave);
            if(not( sig == otro.ObtenerDS(clave))){
                return false;
            }
            it.Avanzar();
        }
    }
    return true;
}


template<class T>
std::ostream& operator<<(std::ostream& o, const DiccString<T>& d){
	Conj<string> c(d.ClavesDS());
    Conj<string>::const_Iterador it = c.CrearIt();
    o << '[' ;
    while(it.HaySiguiente()){
    	std::string clave = it.Siguiente();
        T significado = d.ObtenerDS(clave);
    	o << '(' ;
    	o << clave ;
    	o << ',' ;
    	o << significado;
    	o << ')' ;
        it.Avanzar() ;
        if(it.HaySiguiente()){
            o << " ; " ;
        }
    }
    o << ']' << endl;
    return o;
}

#endif
