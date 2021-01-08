#include <iostream> 
#include "containers.h"


int main(){
//custom vector
Containers::Vector<int> a;
a.push_back(12);
//Linked List
Containers::LinkedList<int> b;
b.push_back(12);
std::cout << b.back();
}
