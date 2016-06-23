#ifndef ARREGLO_ORDENABLE_H
#define ARREGLO_ORDENABLE_H

#include "aed2.h"
#include "info_promesa.h"

using namespace aed2;

    class Arreglo_Ordenable{
        public:
            /**
             * Crea un arreglo de tamaño 0.
             */
            Arreglo_Ordenable();

            /**
             * Crea un arreglo de tamaño tam, donde todas las posiciones
             * son nulas.
             */
            Arreglo_Ordenable(Nat tam);

            /**
             * Constructor por copia
             */
            Arreglo_Ordenable(const Arreglo_Ordenable& otro);

            /**
             * Destructor.  Borra lo que hubiera en el arreglo.
             */
            ~Arreglo_Ordenable();

            /**
             * Devuelve el elemento en la posicion pos.
             * Requiere: Definido(pos)
             */
            const Info_Promesa& DameIndice(Nat pos) const;

            /**
             * Devuelve el elemento en la posicion pos.
             * Requiere: Definido(pos)
             */
            const Info_Promesa& DameIndice(Nat pos);

            /**
             * Inserta un nuevo valor.  Devuelve this
             */
            Arreglo_Ordenable& Insertar(Info_Promesa& valor);

            /**
             * Indefine el elemento en pos.
             * No requiere que el elemento este definido.
             * Devuelve this.
             */
            Arreglo_Ordenable& Borrar(Nat pos);

            /**
             * Ordena el arreglo
             * Devuelve this.
             */
            Arreglo_Ordenable& Ordenar();

            /**
             * Devuelve true si en la posicion pos fue definido algun
             * elemento.
             */
            bool Definido(Nat pos) const;

            /**
             * Devuelve el tamaño del arreglo
             */
            Nat Tamanho() const;

            /**
             * Devuelve las promeas guardadas
             */
            const Conj<Info_Promesa>& DamePromesas() const;

        private:

            void MergeSort(Arreglo< typename Conj<Info_Promesa>::Iterador >& a){
                if(a.Tamanho() > 1){
                    Nat m = a.Tamanho() / 2;
                    Arreglo< typename Conj<Info_Promesa>::Iterador > b(a);
                    SubArreglo(b, 0, m - 1);
                    Arreglo< typename Conj<Info_Promesa>::Iterador > c(a);
                    SubArreglo(c, m, a.Tamanho() - 1);
                    MergeSort(b);
                    MergeSort(c);
                    Merge(a, b, c);
                }
            }

            template<class T>
            void SubArreglo(Arreglo<T>& a, Nat i, Nat d) {
                if(i > 0){
                    for(Nat k = 0; k <= d - i; k++){
                        if(a.Definido(i + k)){
                            a.Definir(k, a[i + k]);
                        }else{
                            a.Borrar(k);
                        }
                    }
                }
                a.Redimensionar(d - i + 1);
            }

            void Merge(Arreglo< typename Conj<Info_Promesa>::Iterador >& a, Arreglo< typename Conj<Info_Promesa>::Iterador >& b, Arreglo< typename Conj<Info_Promesa>::Iterador >& c){
                Nat ib = 0;
                Nat ic = 0;
                for (Nat i = 0; i < a.Tamanho(); i++){
                    if (ib < b.Tamanho() && (not(ic < c.Tamanho()) || (not(c.Definido(ic)) || (b.Definido(ib) && b[ib].Siguiente().AccionesDelCliente() > c[ic].Siguiente().AccionesDelCliente())))) {
                        if(b.Definido(ib)){
                            a.Definir(i, b[ib]);
                        }else{
                            a.Borrar(i);
                        }
                        ib++;
                    }else{
                        if(c.Definido(ic)){
                            a.Definir(i, c[ic]);
                        }else{
                            a.Borrar(i);
                        }
                        ic++;
                    }
                }
            }

            Conj<Info_Promesa> datos;
            Nat ult;
            Arreglo< typename Conj<Info_Promesa>::Iterador > arr;

    };


	std::ostream& operator<<(std::ostream& os, const Arreglo_Ordenable& a);

	bool operator==(const Arreglo_Ordenable& a, const Arreglo_Ordenable& b);
#endif
