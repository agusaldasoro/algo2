module Promesa (Promesa, NombreCliente, promesaDeCompra, promesaDeVenta, nombreDuenio, nombreEmpresa, cota, cantidad, esDeCompra, esDeVenta)
	where
	
type Nat = Int --Esto no es necesario aclararlo en el trabajo
type NombreCliente = String
type NombreTitulo = String
type Precio = Nat

--GENERADORES
data Promesa = Compra NombreCliente NombreTitulo Nat Nat | Venta NombreCliente NombreTitulo Nat Nat
	deriving (Show,Eq)


promesaDeCompra :: NombreCliente -> NombreTitulo -> Nat -> Nat -> Promesa
promesaDeCompra c t cota cant = Compra c t cota cant

promesaDeVenta :: NombreCliente -> NombreTitulo -> Nat -> Nat -> Promesa
promesaDeVenta c t cota cant = Venta c t cota cant

--OBSERVADORES
nombreDuenio :: Promesa -> NombreCliente
nombreDuenio (Venta c t co ca) = c
nombreDuenio (Compra c t co ca) = c

nombreEmpresa :: Promesa -> NombreTitulo
nombreEmpresa (Venta c t co ca) =  t
nombreEmpresa (Compra c t co ca) =  t

cota :: Promesa -> Nat
cota (Venta c t co ca) =  co 
cota (Compra c t co ca) =  co

cantidad :: Promesa -> Nat
cantidad (Venta c t co ca)= ca
cantidad (Compra c t co ca) = ca

esDeCompra :: Promesa -> Bool
esDeCompra (Compra _ _ _ _) = True
esDeCompra (Venta _ _ _ _) = False

--OTRAS OPERACIONES
esDeVenta :: Promesa -> Bool
esDeVenta t = not(esDeCompra t)