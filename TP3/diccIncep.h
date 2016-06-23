#ifndef algoritmos
   #include "aed2.h"
   #define algoritmos
#endif


#include "diccionario_finito.h"

#ifndef diccString
   #include "diccString.h"
   #define diccString
#endif

using namespace aed2;
typedef unsigned int Cliente;
typedef string Nombre;


class DiccInception{
	public:

		/**
		CONSTRUCTOR
		*Construye un diccionario Vacio.
		**/
		DiccInception();

		/**
		CONSTRUCTOR
		*Construye un diccionario Vacio para un tamanho de n claves.
		**/
		DiccInception(Nat n);

		/**
		DESTRUCTOR
		**/
		~DiccInception();

		/**
		AGREGAR CLIENTE
		*Define una nueva clave con su significado vacio.
		*Es decir, un cliente sin acciones.
		**/
		void AgregarClienteDI(Nat cliente);

		/**
		DEFINIDO?
		*Devuelve un bool que es true si el cliente esta definido.
		**/
		bool DefinidoDI(Cliente cliente);

		/**
		CLAVES
		*Devuelve el conjunto de todos los clientes.
		--NO PRODUCE ALIASING--
		**/
		const Conj<Cliente> ClientesDI();

		/**
		AGREGAR TITULO
		*Define un titulo en el significado de su cliente.
		**/
		void AgregarTitulo(Cliente cliente, Nombre nt, Nat n);

		/**
		SUMAR ACCIONES
		*Suma n acciones a la cantidad de acciones de ese cliente sobre ese titulo.
		--NO PRODUCE ALIASING--
		**/
		void SumarAcciones(Cliente cliente, Nombre nt, Nat n);

		/**
		SUMAR ACCIONES
		*Resta n acciones a la cantidad de acciones de ese cliente sobre ese titulo.
		*
		--NO PRODUCE ALIASING--
		**/
		void RestarAcciones(Cliente cliente, Nombre nt, Nat n);

		/**
		TITULOS DE
		*Dado un cliente, devuelve un conjunto de titulos.
		--NO PRODUCE ALIASING--
		**/
		const Conj<string> TitulosDe(Cliente cliente);

		/**
		CANTIDAD
		*Dado un cliente y un titulo, dice cuantas acciones tiene sobre el mismo.
		--NO PRODUCE ALIASING--
		**/
		Nat Cantidad(Cliente cliente, Nombre nt) const;

		/**
		ACCIONES TOTALES
		*Dado un cliente, devuelve la cantidad de acciones que tiene sobre todos los titulos.
		**/
		Nat& AccionesTotales(Cliente cliente);

        bool operator==(const DiccInception& otro)const;

        friend std::ostream& operator<<(std::ostream& os, const DiccInception&);

	private:

		struct Tupla{
				DiccString<Nat> titulos;
				Nat accionesTotales;
			};
		Diccionario_Finito<Tupla> e;

};


