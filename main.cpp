#include <iostream> 
#include "primitive_type_containers.h"
#include "containers.h"

struct lamp {};;
int main(){
int_list a;
int_queue b;
int_vector c;
//for custom containers use 
auto instance = List<lamp>();//returns List 
auto itr = List<lamp>('i');//return iterator
auto in = Vector<int>();
in.push_back(12);
std::cout << in[0];


}
