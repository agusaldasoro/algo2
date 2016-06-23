
#ifndef DICC_MEMORY_H_
#define DICC_MEMORY_H_

#include <iostream>
#include "aed2.h"
#include "diccString.h"
#include "info_titulo.h"
#include "info_promesa.h"

using namespace aed2;
typedef unsigned int Cliente;


class diccMemory{

    public:

			/**
            CONSTRUCTOR POR DEFECTO
            **/
			diccMemory();

            /**
            AGREGAR TITULO
            Define el titulo pasado en el diccionario y el num representa a la cantidad de Clientes del Wolfie.
            **/
			void agregarTituloDM(Conj<Titulo>::Iterador t, Nat num);

			/**
            DEFINIDO DM
            Devuelve true si el nombre del titulo esta definido.
            **/
			bool definidoDM(string nt);

			/**
            OBTENER DM
            Devuelve el Info Titulo correspondiente al nombre pasado.
            **/
			info_titulo& obtenerDM(string nt);

			/**
            TITULOS DM
            Devuelve las claves del Diccionario, es decir todos los nombres de titulos.
            **/
			Conj<string> titulosDM() const;

			/**
            AGREGAR PROMESA
            Agrega la promesa en su lugar dentro del diccionario.
            **/
			void AgregarPromesa(Promesa p, Cliente cl, Nat* n);

			/**
            PROMESAS DE
            Dado un cliente, devuelve su conjunto de Promesas.
            **/
			const Conj<Promesa>& promesasDeDM(Cliente cl);

            bool operator==(const diccMemory& otro)const;

            friend std::ostream& operator<<(std::ostream& os, const diccMemory& d);


    private:

			bool fueModificado_;
			Cliente cliente_;
			Conj<Promesa> ultimasPromesas_;
			DiccString<info_titulo> diccPorTitulo_;
};


#endif
