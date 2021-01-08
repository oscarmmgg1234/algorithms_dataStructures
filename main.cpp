#include <iostream> 
#include "containers.h"


int main(){
//custom vector
Containers::Vector<int> a;
a.push_back(12);
//Linked List
Containers::LinkedList<int> b;
b.push_back(12);

b.push_back(13);
std::cout << b.front();
std::cout << b.back();
}
