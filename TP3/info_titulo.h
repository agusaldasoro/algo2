
#ifndef INFO_TITULO_H_
#define INFO_TITULO_H_

#include "aed2.h"
#include "titulo.h"
#include "arreglo_ordenable.h"

using namespace std;

class info_titulo{

		public:

            //constructor vacio:
            info_titulo();

			//constructor por defecto:
			info_titulo(Conj<Titulo>::Iterador t,Conj<Info_Promesa> vt,Arreglo_Ordenable cp, Nat d);

			//constructor por copia:
			info_titulo(const info_titulo& otra);

			~info_titulo();

			void Recotizar(Nat cot);

			// Devuelve un conjunto de info promesas del tipo venta:
			Conj<Info_Promesa>& ventas() ;
			const Conj<Info_Promesa>& ventas() const;

			// Devuelve un arreglo ordenable de info promesas del tipo compra:
			Arreglo_Ordenable& compras() ;
			const Arreglo_Ordenable& compras() const;

			// Devuelve cantidad de acciones disponibles:
			Nat& disponibles();
			const Nat& disponibles() const;

			const Titulo& DameTitulo() const;

			bool operator==(const info_titulo& b);
			bool operator!=(const info_titulo& b);


		private:
			Conj<Titulo>::Iterador iteradorAtit_;
			Conj<Info_Promesa> ventas_;
			Arreglo_Ordenable compras_;
			Nat disponibles_;
	};

	ostream& operator<<(ostream& os, const info_titulo& i);

#endif
