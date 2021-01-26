//this file will contain all ds and algo implementations
#include "containers.h"

//**************************************************************************************
//**************************************************************************************
//Data-Structures Implementation
//**************************************************************************************
//**************************************************************************************
    
//**************************************************************************************
//Linked List && Doubly Linked List
//**************************************************************************************
template <typename T>
void Containers::LinkedList<T>::init(){
    this->size = 0;
    head = new Node();
    tail = new Node();
    tail->prev = head;
    head->next = tail;

}
//-----------------------------------------------------------------------
template <typename T> //default constructor TM => O(1)
Containers::LinkedList<T>::LinkedList(){ 
    init();
}
//-----------------------------------------------------------------------
template <typename T> // TM => O(n)
Containers::LinkedList<T>::~LinkedList(){
this->clear();
delete head;
delete tail;
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(n)
void Containers::LinkedList<T>::clear(){
    while(!empty())
    Containers::LinkedList<T>::pop_front();
}
//-----------------------------------------------------------------------
template <typename T> 
class Containers::LinkedList<T>::const_iterator {
public: 
const_iterator() : current{nullptr} {}
const T& operator*() const { return Containers::LinkedList<T>::const_iterator::retrive(); } //TM => O(1)
const_iterator & operator++();
const_iterator operator++(int);

const_iterator & operator--();
const_iterator operator--(int);

bool operator==(const const_iterator & rhs) const {return current == rhs.current; } //TM => O(1)
bool operator!=(const const_iterator & rhs) const {return current != rhs.current; } //TM => O(1)

protected: 
Node* current;
T& retrive()const{return current->data;} //TM => O(1)
const_iterator(Node *p) : current{p} {} //TM => O(1)
friend class Containers::LinkedList<T>;
};
//-----------------------------------------------------------------------

template <typename T> //TM => O(1)
typename Containers::LinkedList<T>::const_iterator & Containers::LinkedList<T>::const_iterator::operator++(){
    current = current->next;
    return *this; //returns reference to this object
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(1)
typename Containers::LinkedList<T>::const_iterator Containers::LinkedList<T>::const_iterator::operator++(int){
    Containers::LinkedList<T>::const_iterator copy = *this;
    ++(*this);
    return copy;

}
//-----------------------------------------------------------------------
template <typename T> 
class Containers::LinkedList<T>::iterator : public Containers::LinkedList<T>::const_iterator{
public: 
    iterator() {}
    T& operator*() {return const_iterator::retrive();} //TM => O(1)
    const T& operator*() const {return Containers::LinkedList<T>::const_iterator::operator*(); } //TM => O(1)

    iterator & operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);

    protected: 
    iterator(Node* n): Containers::LinkedList<T>::const_iterator{n} {} //TM => O(1)
    friend class Containers::LinkedList<T>;

};
//-----------------------------------------------------------------------
template <typename T> //TM => O(1)
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::iterator::operator--(int){
Containers::LinkedList<T>::iterator copy = *this;
--(*this);
return copy;
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(1)
typename Containers::LinkedList<T>::iterator& Containers::LinkedList<T>::iterator::operator--(){
this->current = this->current->prev;
return *this;
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(1)
typename Containers::LinkedList<T>::iterator& Containers::LinkedList<T>::iterator::operator++(){
this->current = this->current->next;
return *this;
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(1)
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::iterator::operator++(int){
Containers::LinkedList<T>::iterator copy = *this;
++(*this);
return copy;
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(n)
Containers::LinkedList<T>::LinkedList(const Containers::LinkedList<T> & rhs)
{
    init();
    for(auto& val : rhs)
        push_back(val);
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(1)
Containers::LinkedList<T> & Containers::LinkedList<T>::operator=(LinkedList && rhs) noexcept
{
    size,rhs.size;
    head, rhs.head;
    tail, rhs.tail;
    return *this;
}
//-----------------------------------------------------------------------
template <typename T>//TM => O(1)
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::insert(iterator itr, const T& val)
{
    Node* p = itr.current;
    Node* newNode = new Node(val, p->prev, p);
    size++;
    return p->prev = p->prev->next = newNode;
}
//-----------------------------------------------------------------------
template <typename T>//TM => O(1)
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::insert(iterator itr, T&& val){
    Node* p = itr.current;
    Node* newNode = new Node(val,p->prev,p);
    size++;
    return p->prev = p->prev->next = newNode;
}
//-----------------------------------------------------------------------
template <typename T>//TM => O(1)
Containers::LinkedList<T>::LinkedList(LinkedList && rhs) noexcept
{
    size = rhs.size;
    head = rhs.head;
    tail = rhs.tail;
    rhs.size = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(n)
typename Containers::LinkedList<T>::iterator LinkedList<T>::erase(LinkedList<T>::iterator from, LinkedList<T>::iterator to){
    for(LinkedList<T>::iterator itr = from; itr != to;)
        itr = LinkedList<T>::erase(itr);
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(1)
typename Containers::LinkedList<T>::iterator LinkedList<T>::erase(LinkedList<T>::iterator itr){
    Node* p = itr.current;
    LinkedList<T>::iterator retVal{p->next};
    p->prev->next = p->next;
    p->prev->prev = p->prev;
    delete p;
    size--;
    return retVal;
}


