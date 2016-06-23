#include "aed2.h"
namespace aed2 {

template<class S>
    class Diccionario_Finito{
        public:

            /**
             * Crea un diccionario con n como cantidad maxima de elementos.
             */
            Diccionario_Finito(Nat n);

            /**
             * Destructor.  Borra lo que hubiera en el diccionario.
             */
            ~Diccionario_Finito();

            /**
             * Inserta un nuevo valor.  Devuelve this
             */
            Diccionario_Finito<S>& Definir(Nat c, const S& sig);

            /**
             * Devuelve true si la clave fue definida
             */
            bool Definida(Nat c) const;


            /**
             * Devuelve el significado de la clave
             * Requiere: Definida?(clave)
             */
            const S& Obtener(Nat c) const;

            /**
             * Devuelve el significado de la clave
             * Requiere: Definida?(clave)
             */
            S& Obtener(Nat c);

            /**
             * Devuelve la cantidad de elementos definidos
             */
            Nat Tamanho() const;

            /**
             * Devuelve la cant maxima de elementos a definir
             */
            Nat TamanhoMax() const;

            /**
             * Devuelve un conjunto con todas las claves
             */
            Conj<Nat> Claves() const;

            /**
             * Operadores
             */
            bool operator==(const Diccionario_Finito<S>&) const;

            /**Lo declaro acá para poder acceder a la parte privada*/
            template <typename K>
            friend std::ostream& operator<<(std::ostream& os, const Diccionario_Finito<K>&);


        private:
            struct Info{
                Nat clave;
                S significado;
                bool operator==(const Info& otro) const{
                    return clave == otro.clave && significado == otro.significado;
                }
            };
            friend std::ostream& operator<<(std::ostream& os, const Info& i){
                os << "(" << i.clave << "," << i.significado << ")";
                return os;
            }
            Nat tam;
            Arreglo<Info> arr;
    };

template<class S>
Diccionario_Finito<S>::Diccionario_Finito(Nat tamanio){
    tam = 0;
    arr = Arreglo<Info>(tamanio);
}

template<class S>
Diccionario_Finito<S>::~Diccionario_Finito() {
}

template<class S>
Diccionario_Finito<S>& Diccionario_Finito<S>::Definir(Nat c, const S& sig){
    Info info;
    info.clave = c;
    info.significado = sig;
    if(!Definida(c)){
        assert(tam < arr.Tamanho());
        arr.Definir(tam, info);
        Nat i = tam;
        while (i > 0 && arr[i].clave < arr[i - 1].clave){
            arr.Swap(i, i - 1);
            i--;
        }
        tam++;
    }else{
        for(Nat k = 0; k < tam; k++){
            if(arr[k].clave == c){
                arr.Definir(k, info);
                k = tam;
            }
        }
    }
    return *this;
}

template<class S>
bool Diccionario_Finito<S>::Definida(Nat c) const {
    Nat i = 0;
    Nat d = tam - 1;
    Nat m;
    bool res = false;
    if(tam == 0|| c < arr[i].clave || c > arr[d].clave){
        res = false;
    }else{
        do{
            m = (i + d)/2;
            if(c == arr[m].clave){
                i = m; d = m;
            }else if(c < arr[m].clave){
                d = m;
            }else{
                i = m;
            }
            res = (arr[i].clave == c || arr[d].clave == c);
        }while (d > i + 1);
    }
    return res;
}

template<class S>
const S& Diccionario_Finito<S>::Obtener(Nat c) const {
    assert(Definida(c));
    Nat i = 0;
    Nat d = tam - 1;
    Nat m;
    while (d > i + 1){
        m = (i + d)/2;
        if(c == arr[m].clave){
            i = m; d = m;
        }else if(c < arr[m].clave){
            d = m;
        }else{
            i = m;
        }
    }
    if(c == arr[i].clave){
        return arr[i].significado;
    }else{
        return arr[d].significado;
    }
}

template<class S>
S& Diccionario_Finito<S>::Obtener(Nat c) {
    assert(Definida(c));
    Nat i = 0;
    Nat d = tam - 1;
    Nat m;
    while (d > i + 1){
        m = (i + d)/2;
        if(c == arr[m].clave){
            i = m; d = m;
        }else if(c < arr[m].clave){
            d = m;
        }else{
            i = m;
        }
    }
    if(c == arr[i].clave){
        return arr[i].significado;
    }else{
        return arr[d].significado;
    }
}

template<class S>
Conj<Nat> Diccionario_Finito<S>::Claves() const{
    Conj<Nat> c;
    for(Nat i = 0; i < tam; i++){
        c.AgregarRapido(arr[i].clave);
    }
    return c;
}

template<class S>
Nat Diccionario_Finito<S>::Tamanho() const {
    return tam;
}

template<class S>
Nat Diccionario_Finito<S>::TamanhoMax() const {
    return arr.Tamanho();
}

template<class S>
bool Diccionario_Finito<S>::operator==(const Diccionario_Finito<S>& otro) const{
    return tam == otro.tam && arr == otro.arr;
}


template<class S>
std::ostream& operator<<(std::ostream& os, const Diccionario_Finito<S>& d){
    os << "[";
    for(Nat i = 0; i < d.tam; i++){
        if(i > 0) os << ",";
        os << d.arr[i];
    }
    for(Nat i = d.tam;i < d.arr.Tamanho(); i++){
        if(i > 0) os << ",";
        os << "NULL";
    }
    return os << "]";
}
}
