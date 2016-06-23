#ifndef PROMESA_H_
#define PROMESA_H_

#include "aed2.h"
using namespace std;
using namespace aed2;

enum CompraVenta {compra, venta};

class Promesa {

    public:

        Promesa();

        Promesa(String nom, Nat lim, Nat c, CompraVenta tip);

        Promesa(const Promesa& otra);

        const String nombreP() const;
        String nombreP();

        Nat limiteP();
        const Nat limiteP() const;

        Nat cantidadP();
        const Nat cantidadP() const;

        CompraVenta tipoP();
        const CompraVenta tipoP() const;

        bool operator==(const Promesa& otra) const;

        bool operator!=(const Promesa& otra) const;

	


    private:

      Nat limite, cant;
      String nombrePromesa;
      CompraVenta tipo;

};

	ostream& operator<<(ostream& os, const Promesa& p);

#endif
