#include <iostream> 
#include "primitive_type_containers.h"
#include "containers.h"

int main(){
int_list a;
int_queue b;
int_vector c;
Containers::queue<int, Containers::LinkedList<int>> d; //using custom container => linked list
d.enqueue(12);

}
