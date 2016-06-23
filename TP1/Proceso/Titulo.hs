module Titulo (Titulo, NombreTitulo, Precio, crearTitulo, nombre, maxCant, cotizacionInicial)
	where
	
type Nat = Int --Esto no es necesario aclararlo en el trabajo
type NombreTitulo = String
type Precio = Nat

--GENERADORES
data Titulo = T String Int Int
	deriving (Show,Eq)

--OBSERVADORES
crearTitulo :: NombreTitulo -> Nat -> Precio -> Titulo
crearTitulo n m p = T n m p

nombre :: Titulo -> NombreTitulo
nombre (T n m p) = n

maxCant :: Titulo -> Nat
maxCant (T n m p) = m

cotizacionInicial :: Titulo -> Precio
cotizacionInicial (T n m p) = p
