#include "arreglo_ordenable.h"

Arreglo_Ordenable::Arreglo_Ordenable() : datos(), ult(0), arr() {}

Arreglo_Ordenable::Arreglo_Ordenable(Nat tamanio){
    ult = 0;
    arr = Arreglo< typename Conj<Info_Promesa>::Iterador >(tamanio);
    datos = Conj<Info_Promesa>();
}

Arreglo_Ordenable::Arreglo_Ordenable(const Arreglo_Ordenable& otro){
    ult = otro.ult;
    arr = Arreglo< typename Conj<Info_Promesa>::Iterador >(otro.arr);
    datos = Conj<Info_Promesa>(otro.datos);
}

Arreglo_Ordenable::~Arreglo_Ordenable() {
}

const Info_Promesa& Arreglo_Ordenable::DameIndice(Nat pos) const {
    assert(Definido(pos));
    return arr[pos].Siguiente();
}

const Info_Promesa& Arreglo_Ordenable::DameIndice(Nat pos) {
    assert(Definido(pos));
    return arr[pos].Siguiente();
}

Arreglo_Ordenable& Arreglo_Ordenable::Insertar(Info_Promesa& valor) {
    typename Conj<Info_Promesa>::Iterador it(datos.AgregarRapido(valor));
    arr.Definir(ult, it);
    ult++;
    return *this;
}

Arreglo_Ordenable& Arreglo_Ordenable::Borrar(Nat pos) {
    arr[pos].EliminarSiguiente();
    arr.Borrar(pos);
    return *this;
}

bool Arreglo_Ordenable::Definido(Nat pos) const {
    return arr.Definido(pos);
}

Nat Arreglo_Ordenable::Tamanho() const {
    return arr.Tamanho();
}

const Conj<Info_Promesa>& Arreglo_Ordenable::DamePromesas() const{
    return datos;
}

Arreglo_Ordenable& Arreglo_Ordenable::Ordenar(){
    MergeSort(arr);
    ult = 0;
    while(Definido(ult)){
        ult++;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Arreglo_Ordenable& a) {
    os << "[";
    for(Nat p = 0; p < a.Tamanho(); p++) {
        if(p > 0) os << ",";
        if(a.Definido(p)){
            os << a.DameIndice(p);
        }else{
            os << "Null";
        }
    }
    return os << "]";
}

bool operator==(const Arreglo_Ordenable& a, const Arreglo_Ordenable& b) {
    bool retval = a.Tamanho() == b.Tamanho();
    for(Nat p = 0; p < a.Tamanho() && retval; p++) {
        retval = a.Definido(p) == b.Definido(p);
        if(retval && a.Definido(p))retval = a.DameIndice(p) == b.DameIndice(p);
    }
    return retval;
}



