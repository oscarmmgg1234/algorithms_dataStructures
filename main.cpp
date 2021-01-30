#include <iostream> 
#include "src/lazyAccess/primitive_type_containers.h"
#include "src/lazyAccess/custom_containers.h"



int main(){

Containers::HashTable<int> o;
o.insert(12);
o.erase(2);

}
