#include "Driver.h"


Driver::Driver(const Conj<Cliente>& clientes)
{
	wolfie_ = Wolfie(clientes);
}

Driver::~Driver(){
}

void Driver::AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones)
{
	Titulo t = Titulo(nombre, max_acciones, cotizacion);
    wolfie_.agregarTitulo(t);
}

void Driver::ActualizarCotizacion(const NombreTitulo& nombre, Nat cotizacion)
{
	wolfie_.actualizarCotizacion(nombre, cotizacion);
}

void Driver::AgregarPromesaDeCompra(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	Promesa p = Promesa(titulo, limite, cantidad, compra);
    wolfie_.agregarPromesa(cliente,p);
}

void Driver::AgregarPromesaDeVenta(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	Promesa p = Promesa(titulo, limite, cantidad, venta);
    wolfie_.agregarPromesa(cliente,p);
}

Nat Driver::CantidadDeClientes() const
{
    return wolfie_.cantClientes();
}

/**PRE:: WOLFIE TIENE AL MENOS i CLIENTES**/


Cliente Driver::IesimoCliente(Nat i) const
{
    Conj<Cliente>::const_Iterador cl = wolfie_.clientes();
    while(cl.HaySiguiente())
	cl.Avanzar();
    Nat j = 0;
    while(j < i){
        cl.Retroceder();
        j++;
    }
    return cl.Anterior();
}

Nat Driver::CantidadDeTitulos() const
{
    Conj<Titulo>::const_Iterador it = wolfie_.titulos();
	Nat cant = 0;
	while(it.HaySiguiente()){
        cant++;
        it.Avanzar();
	}
    return cant;
}

NombreTitulo Driver::IesimoTitulo(Nat i) const
{
    Conj<Titulo>::const_Iterador ct = wolfie_.titulos();
    while(ct.HaySiguiente())
	ct.Avanzar();
    Nat j = 0;
    while(j < i){
        ct.Retroceder();
        j++;
    }
    return ct.Anterior().nombreT();
}

Nat Driver::MaxAccionesDe(const NombreTitulo& nombre_titulo) const
{
	Conj<Titulo>::const_Iterador ct = wolfie_.titulos();
    Nat maxima = 0;
    while (ct.HaySiguiente()){
        if ( ct.Siguiente().nombreT() == nombre_titulo ){
            maxima = ct.Siguiente().maximaCantidad();
        }
        ct.Avanzar();
    }
    return maxima;
}

Dinero Driver::CotizacionDe(const NombreTitulo& nombre_titulo) const
{
	Conj<Titulo>::const_Iterador ct = wolfie_.titulos();
    Dinero coti;
    while (ct.HaySiguiente()){
        if ( ct.Siguiente().nombreT() == nombre_titulo ){
            coti = ct.Siguiente().cotizacion();
        }
        ct.Avanzar();
    }
    return coti;
}

bool Driver::EnAlza(const NombreTitulo& nombre_titulo) const
{
	Conj<Titulo>::const_Iterador ct = wolfie_.titulos();
    while (ct.HaySiguiente() && ct.Siguiente().nombreT() != nombre_titulo){
        ct.Avanzar();
    }
    return ct.Siguiente().enAlza();
}

Nat Driver::AccionesTotalesDe(const Cliente& cliente) const
{
	Conj<Titulo>::const_Iterador ct = wolfie_.titulos();
    Nat acciones = 0;
    while(ct.HaySiguiente()){
        acciones = acciones + wolfie_.accionesPorCliente(ct.Siguiente().nombreT(), cliente);
        ct.Avanzar();
    }
    return acciones;
}

Nat Driver::AccionesPorCliente(const Cliente& cliente, const NombreTitulo& nombre_titulo) const
{
	return wolfie_.accionesPorCliente(nombre_titulo, cliente);
}


Nat Driver::AccionesDisponibles(const NombreTitulo& nombre_titulo) const
{
    Conj<Titulo>::const_Iterador itT = wolfie_.titulos();
    while(itT.Siguiente().nombreT() != nombre_titulo){
            itT.Avanzar();
    }
    Nat disp = itT.Siguiente().maximaCantidad();
    Conj<Cliente>::const_Iterador itC = wolfie_.clientes();
    while(itC.HaySiguiente()){
        disp = disp - wolfie_.accionesPorCliente(nombre_titulo, itC.Siguiente());
        itC.Avanzar();
    }
    return disp;
}

bool Driver::PrometeComprar(const Cliente& cliente, const NombreTitulo& titulo) /*const*/
{
	Conj<Promesa>::const_Iterador cp = wolfie_.promesasDe(cliente).CrearIt();
    while (cp.HaySiguiente()){
        if ((cp.Siguiente().nombreP() == titulo) && (cp.Siguiente().tipoP() == compra)){
            return true;
        }
        cp.Avanzar();
    }
    return false;
}

Nat Driver::CantidadAComprar(const Cliente& cliente, const NombreTitulo& titulo) /*const*/
{
	Conj<Promesa>::const_Iterador cp = wolfie_.promesasDe(cliente).CrearIt();
    Nat cant = 0;
    bool encontro = false;
    while (cp.HaySiguiente() && !encontro){
        if ((cp.Siguiente().nombreP() == titulo) && (cp.Siguiente().tipoP() == compra)){
            cant = cp.Siguiente().cantidadP();
            encontro = true;
        }
        cp.Avanzar();
    }
    return cant;
}

Dinero Driver::ValorEsperadoParaComprar(const Cliente& cliente, const NombreTitulo& titulo) /*const*/
{
	Conj<Promesa>::const_Iterador cp = wolfie_.promesasDe(cliente).CrearIt();
    Dinero valor;
    bool encontro = false;
    while (cp.HaySiguiente() && !encontro){
        if (cp.Siguiente().nombreP() == titulo && cp.Siguiente().tipoP()== compra){
            valor = cp.Siguiente().limiteP();
            encontro = true;
        }
        cp.Avanzar();
    }
    return valor;
}

bool Driver::PrometeVender(const Cliente& cliente, const NombreTitulo& titulo) /*const*/
{
	Conj<Promesa>::const_Iterador cp = wolfie_.promesasDe(cliente).CrearIt();
    while (cp.HaySiguiente()){
        if (cp.Siguiente().nombreP() == titulo && cp.Siguiente().tipoP() == venta){
            return true;
        }
        cp.Avanzar();
    }
    return false;
}


Nat Driver::CantidadAVender(const Cliente& cliente, const NombreTitulo& titulo) /*const*/
{
	Conj<Promesa>::const_Iterador cp = wolfie_.promesasDe(cliente).CrearIt();
    Nat cant = 0;
    bool encontro = false;
        while (cp.HaySiguiente() && !encontro){
            if (cp.Siguiente().nombreP() == titulo && cp.Siguiente().tipoP() == venta){
                cant = cp.Siguiente().cantidadP();
                encontro = true;
            }
        cp.Avanzar();
        }
    return cant;
}

Dinero Driver::ValorEsperadoParaVender(const Cliente& cliente, const NombreTitulo& titulo) /*const*/
{
	Conj<Promesa>::const_Iterador cp = wolfie_.promesasDe(cliente).CrearIt();
    Dinero valor;
    bool encontro = false;
    while (cp.HaySiguiente() && !encontro){
        if (cp.Siguiente().nombreP() == titulo && cp.Siguiente().tipoP()== venta){
            valor = cp.Siguiente().limiteP();
            encontro = true;
        }
        cp.Avanzar();
    }
    return valor;
}
