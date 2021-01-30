#include <iostream> 
#include "src/lazyAccess/primitive_type_containers.h"
#include "src/lazyAccess/custom_containers.h"
#include "src/source/containers.h"

struct employee{
Containers::String name;
float earnings;
employee(Containers::String named, float ernings) : name{named}, earnings{ernings} {id =50;}
Containers::String getName() const noexcept {return name;}
float getEarnings() const noexcept {return earnings;}
int id;
};


int main(){

Containers::HashTable<employee> asds(12);
employee oscar("Oscar Maldonado",500.36);



}
