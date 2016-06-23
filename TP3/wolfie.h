#ifndef WOLFIE_H_INCLUDED
#define WOLFIE_H_INCLUDED

#include "aed2.h"
#include "diccString.h"
#include "titulo.h"
#include "promesa.h"
#include "diccIncep.h"
#include "diccMemory.h"
#include "info_titulo.h"
#include "info_promesa.h"

using namespace aed2;

class Wolfie {

public:

    Wolfie();

    Wolfie(Conj<Cliente> &cs);

    Wolfie(const Conj<Cliente> &cs);

    ~Wolfie();

    Nat cantClientes() const;

    Conj<Titulo>::const_Iterador titulos() const;

    Conj<Cliente>::const_Iterador clientes() const;

    Nat accionesPorCliente(String nt, Cliente c) const;

    const Conj<Promesa>& promesasDe(Cliente c);

    void agregarPromesa(Cliente c, Promesa &p);

    void agregarTitulo(Titulo &t);

    void actualizarCotizacion(String nt, Nat cot);


private:
  DiccInception diccClientesAcciones;
  diccMemory diccPromesas;
  Conj<Cliente> conjuntoClientes;
  Conj<Titulo> conjuntoTitulos;

  bool HayPromesa(Cliente c, String nt, CompraVenta tipo);

};



#endif // WOLFIE_H_INCLUDED
