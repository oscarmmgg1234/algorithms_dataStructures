#include <iostream> 
#include "primitive_type_containers.h"


struct lamp {};;
int main(){
int_list a;
int_queue b;
int_vector c;
//for custom containers use 
auto instance = List<lamp>();//returns List instance and instance uses copy constructor to copy the value 
int_list example = a; //uses copy constructor
auto itr = List<string>('i');//return iterator
auto in = Vector<int>();
in.push_back(12);
string we = "oscar";


}
