#ifndef TITULO_H_
#define TITULO_H_

#include "aed2.h"
using namespace std;

class Titulo {

public:

    Titulo();

    Titulo(String nom, Nat tope, Nat cot);

    Titulo(const Titulo& otro);

    const Nat maximaCantidad() const;

    Nat maximaCantidad();

    const String nombreT() const;

    String nombreT();

    const bool enAlza() const;

    bool enAlza();

    const Nat cotizacion() const;

    Nat cotizacion();

    void recotizar(Nat d) ;

    bool operator==(const Titulo& otro) const;

    bool operator!=(const Titulo otro) const;

private:

    Nat maxCant;
    Nat coti;
    String nombreTitulo;
    bool ENAlza;

};

std::ostream& operator<<(ostream& os, const Titulo& t);

#endif
