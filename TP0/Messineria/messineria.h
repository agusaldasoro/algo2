#ifndef MESSINERIA_H_
#define MESSINERIA_H_

#include <iostream>
#include <cassert>
using namespace std;
/*ASUMIMOS:
- Que no se puede tener más de un T iguales alabando al todopoderoso Messi.
- Que no se puede pasar un T para borrar el cual no exista ya en la Messineria.
- Si se va el adepto que está alabando actualmente, inmediatamente le toca a quien está a su derecha.
- Si el Elegido había interrumpido a X y se va el Elegido antes de que termine de alabar, le tocará a X.
- Que si el Elegido interrumpe a X y X se va antes de que el Elegido termine. Cuando este termine,
  le tocara a Y, quien estaba a la derecha de X.
*/

/*
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */

typedef unsigned long Nat;
template<typename T>
class Messineria {

  public:

	Messineria();

	Messineria(const Messineria<T>&);

	~Messineria();

	void golDeMessi(const T&);

	void golDeCristiano(const T&);

	const T& adeptoAlabando() const;

	const T& alabarMessi();

	void olvideAlabarloUnPocoMas();

	void escogerElegido();

	bool hayElegido() const;

	void traidor();

	void interrumpirTurno();

	const T& dameElegido() const;

	bool esVacia() const;

	int tamanio() const;

	bool operator==(const Messineria<T>&) const;

	ostream& mostrarMessineria(ostream&) const;

  private:
	//No se puede modificar esta funcion.
	Messineria<T>& operator=(const Messineria<T>& otra) {
		assert(false);
		return *this;
	}

	// Aca va la implementación del nodo.
	struct Nodo {
		T adepto;
		Nodo* der;
		Nodo* izq;
	};
	Nodo* actual;
	Nodo* elegido;
	Nodo* pendiente;
	Nat len;

};

template<class T>
ostream& operator<<(ostream& out, const Messineria<T>& a) {
	return a.mostrarMessineria(out);
}

// Implementación a hacer por los alumnos.

//Crea una secta nueva sin adeptos.
template <typename T>
Messineria<T>::Messineria()
	: len(0), actual(NULL), elegido(NULL), pendiente(NULL) {
}

//Una vez copiada, ambas Messinerias deben ser independientes, es decir, cuando se borre una no debe borrar la otra.
template <typename T>
Messineria<T>::Messineria(const Messineria<T>& otra){
	len = 0;
	actual = NULL;
	elegido = NULL;
	pendiente = NULL;
	if(!otra.esVacia()){
		if(otra.hayElegido()){
			golDeMessi((*otra.elegido).adepto);
			escogerElegido();
			Nodo *copiar = (*otra.elegido).der;
			while(copiar != otra.elegido){
				golDeMessi((*copiar).adepto);
				if(copiar == otra.actual){
					actual = (*actual).izq;
				}else if(copiar == otra.pendiente){
					pendiente = (*actual).izq;
				}
                copiar = (*copiar).der;
			}
		}else{
			Nodo* copiar = otra.actual;
			do{
				golDeMessi((*copiar).adepto);
				copiar = (*copiar).der;
			}while(copiar != otra.actual);
		}

	}
}

//Acordarse de liberar toda la memoria!
template <typename T>
Messineria<T>::~Messineria() {
	while(!esVacia()){
		golDeCristiano(adeptoAlabando());
	}
}

/*
 * Agrega un nuevo adepto a la Messineria. Si ya tenemos al Elegido
 * el nuevo adepto deberá arrodillarse a la izquierda de él. En caso
 * contrario, se arrodillará a la izquierda del que está alabando.
 */
template <typename T>
void Messineria<T>::golDeMessi(const T& nuevoAdepto){
	Nodo* nuevo = new Nodo();
	(*nuevo).adepto = nuevoAdepto;
	if(esVacia()){
		(*nuevo).izq = nuevo;
		(*nuevo).der = nuevo;
		actual = nuevo;
	}else{
		if(hayElegido()){
			(*elegido).izq->der = nuevo;
			(*nuevo).izq = (*elegido).izq;
			(*nuevo).der = elegido;
			(*elegido).izq = nuevo;
		}else{
			(*actual).izq->der = nuevo;
			(*nuevo).izq = (*actual).izq;
			(*nuevo).der = actual;
			(*actual).izq = nuevo;
		}
	}
	len++;
}
/*
 * Elimina de la secta al adepto pasado por parámetro. Si el mismo tenía
 * el turno de alabar, debe pasar al siguiente (en caso de que haya).
 */
template <typename T>
void Messineria<T>::golDeCristiano(const T& adepto){
	Nodo* eliminar = actual;
	while((*eliminar).adepto != adepto){
		eliminar = (*eliminar).der;
	}
	(*eliminar).izq->der = (*eliminar).der;
	(*eliminar).der->izq = (*eliminar).izq;
	if(eliminar == actual){
		if(len == 1){
			actual = NULL;
			elegido = NULL;
		}else if(actual == elegido){
			elegido = NULL;
			if(pendiente != NULL){
				actual = pendiente;
				pendiente = NULL;
			}else{
				actual = (*actual).der;
			}
		}else{
			actual = (*actual).der;
		}
	}else if(eliminar == pendiente){
		pendiente = (*pendiente).der;
	}
	len--;
	delete eliminar;
}

//Devuelve el adepto que está albando. PRE: Hay adeptos en la Messineria.
template <typename T>
const T& Messineria<T>::adeptoAlabando() const{
	return (*actual).adepto;
}

//Devuelve el próximo elemento según el orden dado.
//Quien alaba debe cambiar. Con lo cual sucesivas llamadas a esta función retornan distintos valores.
// PRE: Hay adeptos en la Messineria.
template <typename T>
const T& Messineria<T>::alabarMessi(){
	if (actual == elegido && pendiente != NULL){
		actual = pendiente;
		pendiente = NULL;
	}else{
		actual = (*actual).der;
	}
    return adeptoAlabando();
}

// Cambia el turno de alabar al inmediato anterior.
template <typename T>
void Messineria<T>::olvideAlabarloUnPocoMas(){
	if (pendiente == NULL){
		actual = (*actual).izq;
	}else{
		actual = (*pendiente).izq;
		pendiente = NULL;
	}
}

// Selecciona al adepto que está alabando como el Elegido.
// PRE: Hay adeptos en la Messineria y no hay Elegido.
template <typename T>
void Messineria<T>::escogerElegido(){
	elegido = actual;
}

// Indica si esta presente el Elegido entre los adeptos.
template <typename T>
bool Messineria<T>::hayElegido() const{
	return elegido != NULL;
}

//Elimina de la secta al Elegido. PRE: hay Elegido en la Messinería.
template <typename T>
void Messineria<T>::traidor(){
	golDeCristiano(dameElegido());
}

//El Elegido interrumpe el turno y pasa a ser el que está alabando. PRE: hay Elegido en la Messinería.
template <typename T>
void Messineria<T>::interrumpirTurno(){
	if (actual != elegido){
		pendiente = actual;
		actual = elegido;
	}
}

// Devuelve al Elegido. PRE: Hay Elegido en la Messineria.
template <typename T>
const T& Messineria<T>::dameElegido() const{
	return (*elegido).adepto;
}

//Dice si la Messineria tiene o no adeptos.
template <typename T>
bool Messineria<T>::esVacia() const{
	return len == 0;
}

//Devuelve la cantidad de adeptos a la Messineria.
template <typename T>
int Messineria<T>::tamanio() const{
	return len;
}

//Devuelve true si las Messinerias son iguales.
template <typename T>
bool Messineria<T>::operator==(const Messineria<T>& otra) const{
	bool respuesta = true;
	respuesta = tamanio() == otra.tamanio() && hayElegido() == otra.hayElegido();
	if (respuesta && tamanio() > 0){
		Nodo* compara1 = actual;
		Nodo* compara2 = otra.actual;
		do{
			respuesta =  (*compara1).adepto == (*compara2).adepto;
			compara1 = (*compara1).der;
			compara2 = (*compara2).der;
		}while(respuesta && compara1 != actual);
		if (hayElegido()){
			respuesta = dameElegido() == otra.dameElegido() && pendiente == otra.pendiente;
			if (respuesta && pendiente != NULL){
				respuesta = (*pendiente).adepto != (*otra.pendiente).adepto;
			}
		}
	}
	return respuesta;
}

/*
 * Debe mostrar la ronda por el ostream (y retornar el mismo).
 * Messineria vacio: []
 * Messineria con 2 elementos (e1 es el actual): [e1, e2]
 * Messineria con 2 elementos (e2 es el actual y e1 es el Elegido): [e2, e1*]
 * Messineria con 3 elementos (e1 es el actual, e2 fue agregado antes que e3, e1 fue agregado antes que e2): [e1, e2, e3]
 */
template <typename T>
ostream& Messineria<T>::mostrarMessineria(ostream& o) const{
	o << '[';
	if(!esVacia()){
		Nodo* mostrar = actual;
		do{
            if(mostrar != actual) o << ", ";
			o << (*mostrar).adepto;
			if(mostrar == elegido) o << "*";
			mostrar = (*mostrar).der;
		}while(mostrar != actual);
	}
	o << ']'; //<< endl;
	return o;
}

#endif //MESSINERIA_H_
