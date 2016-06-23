module Wolfie (Wolfie(..), nombresTitulos, nombresClientes, dameTitulo, cotizacion, disponibles, promesasSinCumplir)
	where
	
import Titulo 
import Promesa 
import Conjunto

type Nat = Int --Esto no es necesario aclararlo en el trabajo

--GENERADORES 
data Wolfie = CrearW | AgregarTitulo Titulo Wolfie | AgregarCliente NombreCliente Wolfie | AgregarPromesa Promesa Wolfie | RecotizarTitulo NombreTitulo Precio Wolfie
	deriving Show

--OBSERVADORES
nombresTitulos :: Wolfie -> Conjunto NombreTitulo
nombresTitulos CrearW = conjuntoVacio
nombresTitulos (AgregarTitulo t w) = (Ag (nombre t) (nombresTitulos w))
nombresTitulos (AgregarCliente _ w)  = nombresTitulos w
nombresTitulos (AgregarPromesa _ w) = nombresTitulos w
nombresTitulos (RecotizarTitulo _ _ w) = nombresTitulos w

nombresClientes :: Wolfie -> Conjunto NombreCliente
nombresClientes CrearW = conjuntoVacio
nombresClientes (AgregarTitulo _ w) = nombresClientes w
nombresClientes (AgregarCliente c w) = Ag c (nombresClientes w)
nombresClientes (AgregarPromesa _ w) = nombresClientes w
nombresClientes (RecotizarTitulo _ _ w) = nombresClientes w

dameTitulo :: NombreTitulo -> Wolfie -> Titulo
dameTitulo nt (AgregarTitulo t w)
		| nt == nombre t = t 
		| otherwise = dameTitulo nt w
dameTitulo nt (AgregarCliente _ w) = dameTitulo nt w
dameTitulo nt (AgregarPromesa _ w) = dameTitulo nt w
dameTitulo nt (RecotizarTitulo _ _ w) = dameTitulo nt w
--Restriccion: nt pertenece (nombresTitulos w)

cotizacion :: NombreTitulo -> Wolfie -> Precio
cotizacion nt (AgregarTitulo t w) 
		| nt  == (nombre t) = cotizacionInicial t
		| otherwise = cotizacion nt w
cotizacion nt (AgregarCliente _ w) = cotizacion nt w
cotizacion nt (AgregarPromesa _ w) = cotizacion nt w
cotizacion nt (RecotizarTitulo t m w)
		| nt == t = m
		| otherwise = cotizacion nt w
--Restriccion: nt pertenece (nombresTitulos w)

promesasSinCumplir :: NombreTitulo -> Wolfie -> Conjunto Promesa
promesasSinCumplir nt CrearW = conjuntoVacio
promesasSinCumplir nt (AgregarTitulo _ w) = promesasSinCumplir nt w
promesasSinCumplir nt (AgregarCliente _ w) = promesasSinCumplir nt w
promesasSinCumplir nt (AgregarPromesa p w) = 
		if nt == nombreEmpresa p
		then if sePuedeEjecutar (cotizacion (nombreEmpresa p) w)  (disponibles (nombreEmpresa p) w) p
			then if esDeCompra p
				then (promesasSinCumplir nt w)
				else (revisarPendientes conjuntoVacio (cotizacion nt w) ((disponibles nt w) + (cantidad p)) (promesasSinCumplir nt w))
			else (Ag p (promesasSinCumplir nt w))
		else (promesasSinCumplir nt w)
promesasSinCumplir nt (RecotizarTitulo n m w) 
		| nt == n = revisarPendientes conjuntoVacio m (disponibles nt w) (promesasSinCumplir nt w)
		| otherwise = promesasSinCumplir nt w
--Restriccion: nt pertenece (nombresTitulos w)		

enAlza :: NombreTitulo -> Wolfie -> Bool
enAlza nt (AgregarPromesa _ w) = enAlza nt w
enAlza nt (AgregarCliente _ w) = enAlza nt w
enAlza nt (AgregarTitulo t w) 
		| nt == nombre t = True
		| otherwise = enAlza nt w
enAlza nt (RecotizarTitulo n m w)
		| nt == n = m > cotizacion n w
		| otherwise = enAlza nt w
--Restriccion: nt pertenece (nombresTitulos w)

accionesPorCliente :: NombreCliente -> NombreTitulo -> Wolfie -> Nat
accionesPorCliente nc nt (AgregarTitulo t w) 
					| nt == nombre t = 0
					| otherwise = accionesPorCliente nc nt w
accionesPorCliente nc nt (AgregarCliente c w) 
					| nc == c = 0
					| otherwise = accionesPorCliente nc nt w
accionesPorCliente nc nt (AgregarPromesa p w) =
		if nt == nombreEmpresa p && nc == nombreDuenio p && sePuedeEjecutar (cotizacion nt w) (disponibles nt w) p
			then if esDeVenta p
				then sumarCumplidas nc (promesasSinCumplir nt w) (promesasSinCumplir nt (AgregarPromesa p w)) - cantidad p + accionesPorCliente nc nt w
				else cantidad p + accionesPorCliente nc nt w
			else sumarCumplidas nc (promesasSinCumplir nt w) (promesasSinCumplir nt (AgregarPromesa p w)) + accionesPorCliente nc nt w
accionesPorCliente nc nt (RecotizarTitulo n c w) = 
		if nt == n
			then sumarCumplidas nc (promesasSinCumplir nt w) (promesasSinCumplir nt (RecotizarTitulo n c w)) + accionesPorCliente nc nt w
			else accionesPorCliente nc nt w
--Restriccion: nt pertenece (nombresTitulos w) && nc pertenece (nombresClientes w)

--OTRAS OPERACIONES
disponibles :: NombreTitulo -> Wolfie -> Nat
disponibles nt w = maxCant(dameTitulo nt w) - (accionesVendidas nt (nombresClientes w) w)
--Restriccion: nt pertenece (nombresTitulos w)

accionesVendidas :: NombreTitulo -> Conjunto NombreCliente -> Wolfie -> Nat
accionesVendidas nt c w
		| vacio c = 0
		| otherwise = (accionesPorCliente (dameUno c) nt w) + (accionesVendidas nt (sinUno c) w)
--Restriccion: nt pertenece (nombresTitulos w) && (nombresClientes w) contiene a c

sePuedeEjecutar :: Precio -> Nat -> Promesa -> Bool
sePuedeEjecutar c d p 
		| esDeCompra p = (cota p <= c) && (cantidad p <= d)
		| otherwise = cota p > c

revisarPendientes :: Conjunto Promesa -> Precio -> Nat -> Conjunto Promesa -> Conjunto Promesa 
revisarPendientes sinCumplir p d c = 
			if not(vacio c)
			then if sePuedeEjecutar p d (dameUno c) 
				then if esDeVenta (dameUno c)
					then revisarPendientes conjuntoVacio p (d + cantidad (dameUno c)) ((sinUno c) `u` sinCumplir)
					else revisarPendientes sinCumplir p (d - cantidad (dameUno c)) (sinUno c)
				else revisarPendientes (Ag (dameUno c) sinCumplir) p d (sinUno c)
			else sinCumplir
-- esta no tiene ninguna restriccion? (tampoco se me ocurre alguna jaja)

sumarCumplidas :: NombreCliente -> Conjunto Promesa -> Conjunto Promesa -> Nat
sumarCumplidas nc cViejo cNuevo =
		if vacio cViejo
			then 0
			else if nc == nombreDuenio (dameUno cViejo) && not (pertenece (dameUno cViejo) cNuevo)
				then if esDeVenta (dameUno cViejo)
						then sumarCumplidas nc (sinUno cViejo) cNuevo - cantidad (dameUno cViejo)
						else cantidad (dameUno cViejo) + sumarCumplidas nc (sinUno cViejo) cNuevo
				else sumarCumplidas nc (sinUno cViejo) cNuevo
-- Nico dijo que habia que poner restricciones aca, pero medio turbio...

p1 = promesaDeVenta "Juan" "Google" 10 10

w1 = AgregarPromesa (promesaDeCompra "Pedro" "Google" 3 15)(AgregarPromesa (promesaDeCompra "Juan" "Google" 3 10) (AgregarCliente "Pedro" 
	(AgregarCliente "Juan" (AgregarTitulo (crearTitulo "Google" 20 4) (AgregarTitulo (crearTitulo "Facebook" 10 5) CrearW)))))

w2 = AgregarPromesa (promesaDeVenta "Juan" "Google" 10 10)(AgregarPromesa (promesaDeCompra "Pedro" "Google" 3 15)
	(AgregarPromesa (promesaDeCompra "Juan" "Google" 3 10) (AgregarCliente "Pedro" (AgregarCliente "Juan" (AgregarTitulo (crearTitulo "Google" 20 5) 
		(AgregarTitulo (crearTitulo "Facebook" 10 5) CrearW))))))

wA = AgregarPromesa (promesaDeCompra "Pedro" "Google" 3 15)
	(AgregarPromesa (promesaDeCompra "Juan" "Google" 3 10) (AgregarCliente "Pedro" (AgregarCliente "Juan" (AgregarTitulo (crearTitulo "Google" 20 5) 
		(AgregarTitulo (crearTitulo "Facebook" 10 5) CrearW)))))

w3 = RecotizarTitulo "Google" 4 (AgregarPromesa (promesaDeVenta "Juan" "Google" 5 10)(AgregarPromesa (promesaDeCompra "Pedro" "Google" 3 15)
	(AgregarPromesa (promesaDeCompra "Juan" "Google" 3 10) (AgregarCliente "Pedro" (AgregarCliente "Juan" (AgregarTitulo (crearTitulo "Google" 20 10) 
		(AgregarTitulo (crearTitulo "Facebook" 10 5) CrearW)))))))

w4 = (AgregarPromesa (promesaDeCompra "Tomas" "Twitter" 1 3)(AgregarCliente "Tomas" (AgregarTitulo (crearTitulo "Twitter" 15 2)
	(AgregarPromesa (promesaDeCompra "Agustina" "Facebook" 20 5)(AgregarTitulo (crearTitulo "Facebook" 20 10) 
		(AgregarCliente "Juan" (AgregarCliente "Agustina" CrearW)))))))

w5 = AgregarPromesa (promesaDeVenta "Agustina" "Facebook" 30 5)(AgregarPromesa (promesaDeCompra "Juan" "Facebook" 5 20) (RecotizarTitulo "Facebook" 21 
		(AgregarPromesa (promesaDeCompra "Tomas" "Twitter" 1 3)(AgregarCliente "Tomas" (AgregarTitulo (crearTitulo "Twitter" 15 2)
			(AgregarPromesa (promesaDeCompra "Agustina" "Facebook" 20 5) (AgregarTitulo (crearTitulo "Facebook" 20 10)  
				(AgregarCliente "Juan" (AgregarCliente "Agustina" CrearW)))))))))
