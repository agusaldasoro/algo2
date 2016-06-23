
#include <ostream>
#include <iostream>
using namespace std;
#include "../promesa.h"


int main()
{
Promesa p("juancho", 600, 2, compra);
Promesa p2(p);
assert(p==p2);
assert(not(p!=p2));
std::cout << p << std::endl;
return 0;

}
