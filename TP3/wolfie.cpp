#include "wolfie.h"
Wolfie::Wolfie()
    :diccClientesAcciones(), diccPromesas(), conjuntoClientes(), conjuntoTitulos(){
}


Wolfie::Wolfie(Conj<Cliente> &cs){
    assert(not(cs.EsVacio()));
    conjuntoTitulos = Conj<Titulo>();
    conjuntoClientes = Conj<Cliente>(cs);
    diccPromesas = diccMemory();
    diccClientesAcciones = DiccInception(cs.Cardinal());
    Conj<Cliente>::const_Iterador it = cs.CrearIt();
    while (it.HaySiguiente()){
        diccClientesAcciones.AgregarClienteDI(it.Siguiente());
        it.Avanzar();
    }
}

Wolfie::Wolfie(const Conj<Cliente> &cs){
    assert(not(cs.EsVacio()));
    conjuntoTitulos = Conj<Titulo>();
    conjuntoClientes = Conj<Cliente>(cs);
    diccPromesas = diccMemory();
    diccClientesAcciones = DiccInception(cs.Cardinal());
    Conj<Cliente>::const_Iterador it = cs.CrearIt();
    while (it.HaySiguiente()){
        diccClientesAcciones.AgregarClienteDI(it.Siguiente());
        it.Avanzar();
    }
}


Wolfie::~Wolfie(){
}

Nat Wolfie::cantClientes() const{
    return conjuntoClientes.Cardinal();
}

Conj<Titulo>::const_Iterador Wolfie::titulos() const{
  return conjuntoTitulos.CrearIt();
}

Conj<Cliente>::const_Iterador Wolfie::clientes() const{
  return conjuntoClientes.CrearIt();
}

Nat Wolfie::accionesPorCliente(String nt, Cliente c) const{
    assert(conjuntoClientes.Pertenece(c));
    assert(diccPromesas.titulosDM().Pertenece(nt));
    return diccClientesAcciones.Cantidad(c,nt);
}

const Conj<Promesa>& Wolfie::promesasDe(Cliente c){
    assert(conjuntoClientes.Pertenece(c));
    return diccPromesas.promesasDeDM(c);
}

bool Wolfie::HayPromesa(Cliente c, String nt, CompraVenta tipo){
    Conj<Promesa> csP = promesasDe(c);
    Conj<Promesa>::Iterador it = csP.CrearIt();
    while(it.HaySiguiente()){
        Promesa prom = it.Siguiente();
        if(prom.tipoP()==tipo && prom.nombreP()==nt){
            return true;
        }
        it.Avanzar();
    }
    return false;
}


void Wolfie::agregarPromesa(Cliente c, Promesa &p){
    string nombre =  p.nombreP();
    assert(diccPromesas.titulosDM().Pertenece(nombre));
    assert(conjuntoClientes.Pertenece(c));
    assert(HayPromesa(c, p.nombreP(), p.tipoP()) == false);
    diccPromesas.AgregarPromesa(p, c, &diccClientesAcciones.AccionesTotales(c));
}

void Wolfie::agregarTitulo (Titulo &t){
    assert(not(diccPromesas.titulosDM().Pertenece(t.nombreT())));
    Conj<Titulo>::Iterador it = conjuntoTitulos.AgregarRapido(t);
    diccPromesas.agregarTituloDM(it, conjuntoClientes.Cardinal());
}

void Wolfie::actualizarCotizacion (String nt, Nat cot){
    assert(diccPromesas.titulosDM().Pertenece(nt));

    info_titulo& info = diccPromesas.obtenerDM(nt);
    info.Recotizar(cot);
    // Primero recorro las ventas.
    Conj<Info_Promesa>::Iterador it = info.ventas().CrearIt();
    while (it.HaySiguiente()){
        const Info_Promesa& sig = it.Siguiente();
        if (cot < sig.DamePromesa().limiteP()){
            diccClientesAcciones.RestarAcciones(sig.DameCliente(), sig.DamePromesa().nombreP(), sig.DamePromesa().cantidadP());
            info.disponibles() += sig.DamePromesa().cantidadP();
            it.EliminarSiguiente();
        }else{
            it.Avanzar();
        }
    }
    // Despues recorro las compras.
    info.compras().Ordenar();
    Nat i = 0;
    while(i < (info.compras()).Tamanho()){
        if(info.compras().Definido(i)){
            const Promesa& prom = info.compras().DameIndice(i).DamePromesa();
            Nat cant = prom.cantidadP();
            if (cant <= info.disponibles() && cot > prom.limiteP()){
                diccClientesAcciones.SumarAcciones(info.compras().DameIndice(i).DameCliente(), prom.nombreP(), prom.cantidadP());
                info.disponibles() -= prom.cantidadP();
                info.compras().Borrar(i);
            }

        }
        i++;
    }
    info.compras().Ordenar();
}
