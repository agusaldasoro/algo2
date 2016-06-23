#ifndef INFO_PROMESA_H_
#define INFO_PROMESA_H_


#include "aed2.h"
#include "promesa.h"

using namespace aed2;
typedef unsigned int Cliente;
    class Info_Promesa{
        public:

            /**
             * Crea una nueva InfoProm
             */
            Info_Promesa(Cliente c, Promesa p, Nat* n);

            /**
             * Constructor por copia
             */
            Info_Promesa(const Info_Promesa& otro);

            /**
             * Destructor.  Borra la InfoProm
             */
            ~Info_Promesa();

            /**
             * Devuelve el cliente de la InfoProm
             */
            Cliente DameCliente();
            const Cliente DameCliente() const;

            /**
             * Devuelve la promeas de la InfoProm
             */
            Promesa& DamePromesa();
            const Promesa& DamePromesa() const;

            /**
             * Devuelve la cantidad de acciones del cliente
             */
            Nat AccionesDelCliente();
            const Nat AccionesDelCliente() const;

        private:
            Cliente c;
            Promesa p;
            Nat* acc;
    };

	bool operator==(const Info_Promesa& a, const Info_Promesa& b);

	bool operator!=(const Info_Promesa& a, const Info_Promesa& b);

	std::ostream& operator<<(std::ostream& os, const Info_Promesa&);

#endif
