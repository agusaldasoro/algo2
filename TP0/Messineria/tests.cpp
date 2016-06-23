// g++ -g tests.cpp -o tests
// valgrind --leak-check=full ./tests

#include "mini_test.h"
#include "messineria.h"

/*
 * Crea una messineria de int vacia y no agrega elementos
 */
void check_crear_messineria_vacia() {
  Messineria<int> messi;
  ASSERT_EQ(messi.esVacia(), true);
  ASSERT_EQ(messi.tamanio(), 0);
}
void messinerias_vacias_son_iguales() {
  Messineria<int> l1, l2;
  ASSERT(l1 == l2);
}
void agregar_un_elemento_incrementa_logitud() {
  Messineria<char> l;
  l.golDeMessi('a');
  ASSERT_EQ( l.tamanio(), 1 );
}
void eliminar_unico_elemento_deja_messineria_vacia() {
  Messineria<char> l;
  l.golDeMessi('a');
  ASSERT_EQ( l.tamanio(), 1 );
  l.golDeCristiano('a');
  ASSERT_EQ( l.tamanio(), 0 );
}
void crear_por_copia_y_modificar() {
  Messineria<char> l1;
  l1.golDeMessi('a');
  l1.golDeMessi('b');
  l1.golDeMessi('c');
  l1.alabarMessi();
  l1.escogerElegido();
  l1.alabarMessi();
  ostringstream os;
  Messineria<char>l2(l1);
  ASSERT(l1 == l2);
  l1.golDeCristiano('a');
  ASSERT(!(l1 == l2));
  ASSERT_EQ( l1.tamanio(), l2.tamanio() - 1);
  l1.golDeMessi('a');
  ASSERT(l1 == l2);
}
void interrumpir_turno_vuelve_al_pendiente() {
  Messineria<string> aGus;
  aGus.golDeMessi("x");
  aGus.golDeMessi("y");
  aGus.golDeMessi("z");
  aGus.golDeMessi("w");
  ASSERT_EQ( aGus.adeptoAlabando(),"x");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"y");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"z");
  aGus.escogerElegido();
  ASSERT_EQ( aGus.hayElegido(),true);
  ASSERT_EQ( aGus.adeptoAlabando(),"z");
  aGus.golDeMessi("o");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"w");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"x");
  aGus.olvideAlabarloUnPocoMas();
  ASSERT_EQ( aGus.adeptoAlabando(),"w");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"x");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"y");
  aGus.interrumpirTurno();
  ASSERT_EQ( aGus.adeptoAlabando(),"z");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"y");
}
void borrar_al_elegido_deja_todo_ok() {
  Messineria<string> aGus;
  aGus.golDeMessi("x");
  aGus.golDeMessi("y");
  aGus.golDeMessi("z");
  aGus.golDeMessi("w");
  ASSERT_EQ( aGus.adeptoAlabando(),"x");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"y");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"z");
  aGus.escogerElegido();
  ASSERT_EQ( aGus.hayElegido(),true);
  ASSERT_EQ( aGus.adeptoAlabando(),"z");
  aGus.golDeMessi("o");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"w");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"x");
  aGus.olvideAlabarloUnPocoMas();
  ASSERT_EQ( aGus.adeptoAlabando(),"w");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"x");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"y");
  aGus.interrumpirTurno();
  ASSERT_EQ( aGus.tamanio(),5);
  ASSERT_EQ(aGus.dameElegido(), "z");
  ASSERT_EQ( aGus.adeptoAlabando(),"z");
  aGus.traidor();
  ASSERT_EQ( aGus.hayElegido(),false);
  ASSERT_EQ( aGus.adeptoAlabando(),"y");
  aGus.escogerElegido();
  ASSERT_EQ( aGus.hayElegido(),true);
  ASSERT_EQ( aGus.dameElegido(), "y");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"o");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"w");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.adeptoAlabando(),"x");
  aGus.alabarMessi();
  ASSERT_EQ( aGus.tamanio(),4);
  ASSERT_EQ( aGus.adeptoAlabando(),"y");
  aGus.traidor();
  ASSERT_EQ( aGus.adeptoAlabando(),"o");
  ASSERT_EQ( aGus.tamanio(),3);
  ostringstream os;
  Messineria<string>tIna(aGus);
  ASSERT(aGus == tIna);
}
void probar_ejemplos_ostream() {
  Messineria<string> m1;
  m1.golDeMessi("e1");
  m1.golDeMessi("e2");
  ostringstream o1;
  o1 << m1;
  ASSERT(o1.str() == "[e1, e2]");
  Messineria<string> m2;
  m2.golDeMessi("e1");
  m2.escogerElegido();
  m2.golDeMessi("e2");
  m2.alabarMessi();
  ostringstream o2;
  o2 << m2;
  ASSERT(o2.str() == "[e2, e1*]");
  Messineria<string> m3;
  m3.golDeMessi("e1");
  m3.golDeMessi("e2");
  m3.golDeMessi("e3");
  ostringstream o3;
  o3 << m3;
  ASSERT(o3.str() == "[e1, e2, e3]");
}
void super_prueba(){
  Messineria<string> m;
   ASSERT_EQ(m.esVacia(), true);
  m.golDeMessi("Juan");
   ASSERT_EQ(m.adeptoAlabando(), "Juan");
  m.golDeMessi("Franco");
   ASSERT_EQ(m.tamanio(), 2);
   ASSERT_EQ(m.alabarMessi(), "Franco");
   ASSERT_EQ(m.hayElegido(), false);
  m.escogerElegido();
   ASSERT_EQ(m.hayElegido(), true);
   ASSERT_EQ(m.dameElegido(), "Franco");
   ASSERT_EQ(m.alabarMessi(), "Juan");
  m.golDeMessi("Eze");
   ASSERT_EQ(m.alabarMessi(), "Eze");
  m.golDeMessi("Pedro");
   ASSERT_EQ(m.alabarMessi(), "Pedro");
  m.olvideAlabarloUnPocoMas();
   ASSERT_EQ(m.adeptoAlabando(), "Eze");
  m.interrumpirTurno();
   ASSERT_EQ(m.adeptoAlabando(), m.dameElegido());
   ASSERT_EQ(m.alabarMessi(), "Eze");
  m.interrumpirTurno();
  m.golDeCristiano("Eze");
   ASSERT_EQ(m.alabarMessi(), "Pedro");
  m.golDeMessi("Nicolas");
  m.interrumpirTurno();
  m.golDeCristiano("Pedro");
  m.traidor();
   ASSERT_EQ(m.adeptoAlabando(), "Nicolas");
   ASSERT_EQ(m.tamanio(), 2);
}

int main() {
  RUN_TEST(check_crear_messineria_vacia);
  RUN_TEST(messinerias_vacias_son_iguales);
  RUN_TEST(agregar_un_elemento_incrementa_logitud);
  RUN_TEST(eliminar_unico_elemento_deja_messineria_vacia);
  RUN_TEST(crear_por_copia_y_modificar);
  RUN_TEST(interrumpir_turno_vuelve_al_pendiente);
  RUN_TEST(borrar_al_elegido_deja_todo_ok);
  RUN_TEST(probar_ejemplos_ostream);
  RUN_TEST(super_prueba);
  return 0;
  }

