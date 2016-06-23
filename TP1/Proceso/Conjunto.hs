module Conjunto (Conjunto(..), conjuntoVacio, vacio, dameUno, sinUno, resta, u, pertenece)
	where
	
data Conjunto a = Nil | Ag a (Conjunto a)
	deriving Show 


conjuntoVacio :: Conjunto a
conjuntoVacio = Nil

vacio :: Conjunto a -> Bool
vacio Nil = True
vacio _ = False

dameUno :: Conjunto a -> a
dameUno (Ag x c) = x

sinUno :: Conjunto a -> Conjunto a
sinUno (Ag x c) = c

pertenece :: Eq a => a -> Conjunto a -> Bool
pertenece _ Nil = False
pertenece x (Ag y c)
		| x == y = True
		| otherwise = pertenece x c

resta ::  Eq a => Conjunto a -> Conjunto a -> Conjunto a
resta Nil _ = Nil
resta (Ag x c1) c2
		| pertenece x c2 = resta c1 c2
		| otherwise = Ag x (resta c1 c2)

u :: Conjunto a -> Conjunto a -> Conjunto a
u c1 Nil = c1
u c1 (Ag x c2) = u (Ag x c1) c2