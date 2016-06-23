#include "Driver.h"

#include "aed2/mini_test.h"

#include "aed2/Lista.h"

#include "aed2/Conj.h"



#include <string>

#include <iostream>



using namespace aed2;



/** 

 * Imprime un elemento a un string, en vez de a una pantalla, 

 * a través del operador << 

 */

template <typename T>

std::string to_str(const T& t)

{

	std::stringstream ss;

	ss << t;



	return ss.str();

}



/**

 * Esta función se puede utilizar para comparar dos colecciones

 * iterables que representen conjuntos, es decir, que no tengan 

 * elementos repetidos.

 */

template<typename T, typename S>

bool Comparar(const T& t, const S& s)

{

  typename T::const_Iterador it1 = t.CrearIt();

  typename S::const_Iterador it2 = s.CrearIt();



	// me fijo si tienen el mismo tamanho



	Nat len1 = 0;

	while( it1.HaySiguiente() ) {

		len1++;

		it1.Avanzar();

	}



	Nat len2 = 0;

	while( it2.HaySiguiente() ) {

		len2++;

		it2.Avanzar();

	}



	if ( len1 != len2 )

		return false;



	it1 = t.CrearIt();

	it2 = s.CrearIt();



	// me fijo que tengan los mismos elementos



	while( it1.HaySiguiente() )

	{

		bool esta = false;

		it2 = s.CrearIt();



		while( it2.HaySiguiente() ) {

		  if ( it1.Siguiente() == it2.Siguiente() ) {

			esta = true;

			break;

		  }

		  it2.Avanzar();

		}



		if ( !esta ) {

			return false;

		}

			

		it1.Avanzar();

	}

  

  return true;

}





// ---------------------------------------------------------------------



/**

 * Ejemplo de caso de test, con llamadas a las rutinas de aserción 

 * definidas en mini_test.h

 */

void test_wolfie_simple()

{

	Conj<Cliente> clientes;

	clientes.Agregar(1);

	clientes.Agregar(5);



	Driver wolfie(clientes);



	ASSERT(wolfie.CantidadDeClientes() == clientes.Cardinal());



	for(Nat i=0; i<wolfie.CantidadDeClientes(); i++) {

		ASSERT( clientes.Pertenece( wolfie.IesimoCliente(i) ) );

	}



	ASSERT_EQ(wolfie.CantidadDeTitulos(), 0);

}



void test_clientes(){

    Conj<Cliente> cs;

    cs.Agregar(2);

    cs.Agregar(7);

    cs.Agregar(2000);

    cs.Agregar(12);

    cs.Agregar(6);

    cs.Agregar(8);

    Driver d(cs);

    ASSERT(d.CantidadDeClientes() == 6);

    Conj<Cliente> cs2;

    Nat i = 0;

    while(i < d.CantidadDeClientes()){

	cs2.Agregar(d.IesimoCliente(i));

	i++;

    }

    ASSERT(cs == cs2);

}



void test_titulos(){

    Conj<Cliente> cs;

    cs.Agregar(2);

    cs.Agregar(7);

    cs.Agregar(2000);

    cs.Agregar(12);

    cs.Agregar(6);

    cs.Agregar(8);

    Driver d(cs);



    d.AgregarTitulo("Google", 9, 3);

    d.AgregarTitulo("Facebook", 6, 15);

    d.AgregarTitulo("Line", 6, 15);

    

    NombreTitulo nt = d.IesimoTitulo(0);

    ASSERT(d.MaxAccionesDe(nt) == 3);

	ASSERT(d.CotizacionDe(nt) == 9);

	ASSERT(d.EnAlza(nt) == true);



	nt = d.IesimoTitulo(1);

    ASSERT(d.MaxAccionesDe(nt) == 15);

	ASSERT(d.CotizacionDe(nt) == 6);

	ASSERT(d.EnAlza(nt) == true);



	nt = d.IesimoTitulo(2);

    ASSERT(d.MaxAccionesDe(nt) == 15);

	ASSERT(d.CotizacionDe(nt) == 6);

	ASSERT(d.EnAlza(nt) == true);

    

}



void test_promesasDe(){

    Conj<Cliente> cs;

    cs.Agregar(2);

    cs.Agregar(7);

    cs.Agregar(2000);

    cs.Agregar(12);

    cs.Agregar(6);

    cs.Agregar(8);

    Driver d(cs);



    d.AgregarTitulo("Google", 9, 3);

    d.AgregarTitulo("Facebook", 6, 15);

    d.AgregarTitulo("Yahoo", 6, 15);



    d.AgregarPromesaDeCompra(8, "Google", 8, 3);

    d.AgregarPromesaDeCompra(2000, "Google", 8, 3);

    d.AgregarPromesaDeCompra(7, "Facebook", 8, 3);

    d.AgregarPromesaDeCompra(7, "Yahoo", 8, 3);

    d.AgregarPromesaDeCompra(12, "Yahoo", 8, 3);



    ASSERT(d.PrometeComprar(2, "Google") == false);

    ASSERT(d.PrometeComprar(2, "Facebook") == false);

    ASSERT(d.PrometeComprar(2, "Yahoo") == false);



    ASSERT(d.PrometeComprar(7, "Google") == false);

    ASSERT(d.PrometeComprar(7, "Facebook") == true);

    	ASSERT(d.CantidadAComprar(7, "Facebook") == 3);

    	ASSERT(d.ValorEsperadoParaComprar(7, "Facebook") == 8);

    ASSERT(d.PrometeComprar(7, "Yahoo") == true);

    	ASSERT(d.CantidadAComprar(7, "Yahoo") == 3);

    	ASSERT(d.ValorEsperadoParaComprar(7, "Yahoo") == 8);



    ASSERT(d.PrometeComprar(2000, "Google") == true);

    	ASSERT(d.CantidadAComprar(2000, "Google") == 3);

    	ASSERT(d.ValorEsperadoParaComprar(2000, "Google") == 8);

    ASSERT(d.PrometeComprar(2000, "Facebook") == false);

    ASSERT(d.PrometeComprar(2000, "Yahoo") == false);



    ASSERT(d.PrometeComprar(12, "Google") == false);

    ASSERT(d.PrometeComprar(12, "Facebook") == false);

    ASSERT(d.PrometeComprar(12, "Yahoo") == true);

    	ASSERT(d.CantidadAComprar(12, "Yahoo") == 3);

    	ASSERT(d.ValorEsperadoParaComprar(12, "Yahoo") == 8);



    ASSERT(d.PrometeComprar(6, "Google") == false);

    ASSERT(d.PrometeComprar(6, "Facebook") == false);

    ASSERT(d.PrometeComprar(6, "Yahoo") == false);



    ASSERT(d.PrometeComprar(8, "Google") == true);

    	ASSERT(d.CantidadAComprar(8, "Google") == 3);

    	ASSERT(d.ValorEsperadoParaComprar(8, "Google") == 8);

    ASSERT(d.PrometeComprar(8, "Facebook") == false);

    ASSERT(d.PrometeComprar(8, "Yahoo") == false);





}



void test_accionesPorCliente(){

    Conj<Cliente> cs;

    cs.Agregar(2);

    Driver d(cs);



	d.AgregarTitulo("Google", 4, 20);

	ASSERT(d.AccionesPorCliente(2, "Google") == 0);



    d.AgregarPromesaDeCompra(2, "Google", 8, 3);

    ASSERT(d.AccionesPorCliente(2, "Google") == 0);



    d.ActualizarCotizacion("Google", 10);

    ASSERT(d.AccionesPorCliente(2, "Google") == 3);



    d.AgregarPromesaDeVenta(2, "Google", 12, 2);

    ASSERT(d.AccionesPorCliente(2, "Google") == 3);



    d.ActualizarCotizacion("Google", 10);

    ASSERT(d.AccionesPorCliente(2, "Google") == 1);

}



void test_actualizarCotizacion(){

    Conj<Cliente> cs;

    cs.Agregar(2);

    cs.Agregar(5);

    cs.Agregar(21);

    Driver d(cs);



    d.AgregarTitulo("Google", 4, 20);

    d.AgregarTitulo("Facebook", 6, 15);

    d.AgregarTitulo("Line", 4, 50);



    d.AgregarPromesaDeCompra(2, "Google", 5, 10);

    d.AgregarPromesaDeCompra(5, "Google", 5, 3);                        



    d.ActualizarCotizacion("Google", 6);



    ASSERT(d.AccionesPorCliente(2, "Google") == 10);

    ASSERT(d.AccionesPorCliente(2, "Facebook") == 0);

    ASSERT(d.AccionesPorCliente(2, "Line") == 0);



    ASSERT(d.AccionesPorCliente(5, "Google")==3);

    ASSERT(d.AccionesPorCliente(5, "Facebook") == 0);

    ASSERT(d.AccionesPorCliente(5, "Line") == 0);



    d.AgregarPromesaDeCompra(21, "Facebook", 8, 50);

    d.AgregarPromesaDeCompra(2, "Line", 8, 30);

    d.AgregarPromesaDeCompra(5, "Line", 8, 30);



    d.ActualizarCotizacion("Line", 10);



    ASSERT(d.AccionesPorCliente(2, "Line") == 30);

    ASSERT(d.AccionesPorCliente(5, "Line") == 0);



    d.AgregarPromesaDeVenta(2, "Line", 10, 28);



    d.ActualizarCotizacion("Line", 9);



    ASSERT(d.AccionesPorCliente(2, "Line") == 2);

    ASSERT(d.AccionesPorCliente(5, "Line") == 30);



    d.ActualizarCotizacion("Facebook", 4);



    ASSERT(d.AccionesPorCliente(2, "Facebook")==0);

    ASSERT(d.AccionesPorCliente(5, "Facebook")==0);

    ASSERT(d.AccionesPorCliente(21, "Facebook")==0);



    d.ActualizarCotizacion("Facebook", 40);



    ASSERT(d.AccionesPorCliente(21, "Facebook")==0);



}







int main(int argc, char **argv)

{

	RUN_TEST(test_wolfie_simple);

	RUN_TEST(test_clientes);

	RUN_TEST(test_titulos);

	RUN_TEST(test_promesasDe);

	RUN_TEST(test_accionesPorCliente);

	RUN_TEST(test_actualizarCotizacion);





	/******************************************************************

	 * TODO: escribir casos de test exhaustivos para todas            *

	 * las funcionalidades del módulo.                                *

	 * La interacción con el TAD Wolfie se debe hacer exclusivamente  *

	 * a través de la interfaz del driver.                            *

	 ******************************************************************/



	return 0;

}

