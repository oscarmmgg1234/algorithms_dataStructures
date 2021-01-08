/* 
Author: Oscar Maldonado
Datastruct: Dynamic array(similar to  vector)
Description: This data structure will allow you to allocate the a array on the heap and allow you to dynamicly manipulate 
the array at runtime 

*/
#ifndef CONTAINERS
#define CONTAINERS 



namespace Containers {

//**************************************************************************************
//Linked List
//**************************************************************************************

template <typename T>
class LinkedList{
    struct Node {
        Node* prev;
        Node* next;
        T data;

        Node():next{nullptr},prev{nullptr}{}
        Node(const T& val,Node* p = nullptr, Node* n = nullptr) : next{n}, prev{p}, data{val} {}
        Node(T&& val, Node* p = nullptr, Node* n = nullptr) : next{n}, prev{p}, data{std::move(val)}{}
    };
    
    unsigned int size;

    Node *head;
    Node *tail;
    
    void init(); 

    public: 
    class const_iterator;
    class iterator;

    LinkedList(); //default constructor
    LinkedList(const LinkedList& c); //copy constructor
    LinkedList(LinkedList&& m); //move constructor
    ~LinkedList(); //destructor

    LinkedList<T> & operator=(const LinkedList& c); //copy assignment operator
    LinkedList<T> & operator=(LinkedList&& m); //move assignment operator 

    iterator begin() {return  head->next;} 
    const_iterator begin() const {return head->next;}
    iterator end() {return tail;}
    const_iterator end() const {return tail;}

    T & operator[](unsigned int index);
    T& front(){ return *begin();}
    const T& front() const {return *begin();}
    T& back(){return *--end();}
    const T& back() const {return *--back();}

    int getSize() const {return size;}

    //size_t getByteSize(const int index) const {return std::sizeof()}

    bool empty() const {return size == 0;}
    void clear();

    void push_front(const T& val) {insert(begin(),val);}
    void push_front(T&& val) {insert(begin(), std::move(val));}
    void push_back(const T& val) {insert(end(),val);}
    void push_back(T&& val) {insert(end(),std::move(val));}

    void pop_front() { erase(begin());}
    void pop_back() { erase(end());}

    iterator insert(iterator, const T&);
    iterator insert(iterator, T&&);

    iterator erase(iterator);
    iterator erase(iterator, iterator);
    

};
//-----------------------------------------------------------------------
template <typename T>
void Containers::LinkedList<T>::init(){
    this->size = 0;
    head = new Node();
    tail = new Node();
    tail->prev = head;
    head->next = tail;

}
//-----------------------------------------------------------------------
template <typename T> //default constructor
Containers::LinkedList<T>::LinkedList(){
    init();
}
//-----------------------------------------------------------------------
template <typename T>
Containers::LinkedList<T>::~LinkedList(){
Containers::LinkedList<T>::clear();
delete head;
delete tail;
}
//-----------------------------------------------------------------------
template <typename T>
void Containers::LinkedList<T>::clear(){
    while(!empty())
    Containers::LinkedList<T>::pop_front();
}
//-----------------------------------------------------------------------
template <typename T>
class Containers::LinkedList<T>::const_iterator {
public: 
const_iterator() : current{nullptr} {}
const T& operator*() const { return Containers::LinkedList<T>::const_iterator::retrive(); }
const_iterator & operator++();
const_iterator operator++(int);

const_iterator & operator--();
const_iterator operator--(int);

bool operator==(const const_iterator & rhs) const {return current == rhs.current; }
bool operator!=(const const_iterator & rhs) const {return current != rhs.current; }

protected: 
Node* current;
T& retrive()const{return current->data;}
const_iterator(Node *p) : current{p} {}
friend class Containers::LinkedList<T>;
};
//-----------------------------------------------------------------------

template <typename T>
typename Containers::LinkedList<T>::const_iterator & Containers::LinkedList<T>::const_iterator::operator++(){
    current = current->next;
    return *this; //returns reference to this object
}
//-----------------------------------------------------------------------
template <typename T>
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
    T& operator*() {return const_iterator::retrive();}
    const T& operator*() const {return Containers::LinkedList<T>::const_iterator::operator*(); }

    iterator & operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);

    protected: 
    iterator(Node* n): Containers::LinkedList<T>::const_iterator{n} {}
    friend class Containers::LinkedList<T>;

};
//-----------------------------------------------------------------------
template <typename T>
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::iterator::operator--(int){
Containers::LinkedList<T>::iterator copy = *this;
--(*this);
return copy;
}
//-----------------------------------------------------------------------
template <typename T>
typename Containers::LinkedList<T>::iterator& Containers::LinkedList<T>::iterator::operator--(){
this->current = this->current->prev;
return *this;
}
//-----------------------------------------------------------------------
template <typename T>
typename Containers::LinkedList<T>::iterator& Containers::LinkedList<T>::iterator::operator++(){
this->current = this->current->next;
return *this;
}
//-----------------------------------------------------------------------
template <typename T>
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::iterator::operator++(int){
Containers::LinkedList<T>::iterator copy = *this;
++(*this);
return copy;
}
//-----------------------------------------------------------------------
template <typename T>
Containers::LinkedList<T>::LinkedList(const Containers::LinkedList<T> & rhs)
{
    init();
    for(auto& val : rhs)
        push_back(val);
}
//-----------------------------------------------------------------------
template <typename T>
Containers::LinkedList<T> & Containers::LinkedList<T>::operator=(LinkedList && rhs)
{
    std::swap(size,rhs.size);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}
//-----------------------------------------------------------------------
template <typename T>
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::insert(iterator itr, const T& val)
{
    Node* p = itr.current;
    Node* newNode = new Node(val, p->prev, p);
    size++;
    return p->prev = p->prev->next = newNode;
}
//-----------------------------------------------------------------------
template <typename T>
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::insert(iterator itr, T&& val){
    Node* p = itr.current;
    Node* newNode = new Node(std::move(val),p->prev,p);
    size++;
    return p->prev = p->prev->next = newNode;
}
//-----------------------------------------------------------------------
template <typename T>
Containers::LinkedList<T>::LinkedList(LinkedList && rhs) : size(rhs.size), head{rhs.head}, tail{rhs.tail}
{
    rhs.size = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}
//-----------------------------------------------------------------------
template <typename T>
typename Containers::LinkedList<T>::iterator LinkedList<T>::erase(LinkedList<T>::iterator from, LinkedList<T>::iterator to){
    for(LinkedList<T>::iterator itr = from; itr != to;)
        itr = LinkedList<T>::erase(itr);
}
//-----------------------------------------------------------------------
template <typename T>
typename Containers::LinkedList<T>::iterator LinkedList<T>::erase(LinkedList<T>::iterator itr){
    Node* p = itr.current;
    LinkedList<T>::iterator retVal{p->next};
    p->prev->next = p->next;
    p->prev->prev = p->prev;
    delete p;
    size--;
    return retVal;

}

//**************************************************************************************
//Custom Vector
//**************************************************************************************

template <class T>
class Vector
{
public:

    typedef T * iterator;

    Vector(unsigned int size = 0, const T & initial = T()); // default constructor
    Vector(const Containers::Vector<T> & v);                            // copy constructor
    Vector(Containers::Vector<T> && v);                                 // move constructor
    ~Vector();                                              // destructor
    Containers::Vector<T> & operator=(const Containers::Vector<T> & v);             // copy assignment
    Containers::Vector<T> & operator=(Containers::Vector<T> && v);                  // move assignment

    unsigned int capacity() const;
    unsigned int size() const;
    bool empty() const;

    iterator begin();                    // return iterator to first element
    iterator end();                        // return iterator to past last element
    T & front();                           // return reference to first element
    T & back();                            // return reference to last element
    void push_back(const T & value);
    void push_back(T && value);
    void pop_back();

    void reserve(unsigned int capacity);   // adjust capacity
    void resize(unsigned int size);        // adjust size

    T & operator[](unsigned int index);
    void erase(iterator);                  // erase elem iterator points to (shift left from iterator)

private:
    unsigned int my_size;
    unsigned int my_capacity;
    T * buffer;
};
//-------------------------------------------------------------------------------------------------------------
template <typename T>
typename Containers::Vector<T>::iterator Containers::Vector<T>::end() { return &buffer[my_size-1];}
//-------------------------------------------------------------------------------------------------------------
template <typename T>
typename Containers::Vector<T>::iterator Containers::Vector<T>::begin() {return &buffer[0]; }
//-------------------------------------------------------------------------------------------------------------
template <typename T>
T& Containers::Vector<T>::front() {return buffer[0];}
//-------------------------------------------------------------------------------------------------------------
template <typename T>
T& Containers::Vector<T>::back() {return buffer[my_size-1];}
//-------------------------------------------------------------------------------------------------------------
template <typename T>
void Containers::Vector<T>::push_back( T &&value)
{
    if(my_size == my_capacity)
        reserve(2 * my_capacity + 1);
    buffer[my_size++] = std::move(value);
}
//-------------------------------------------------------------------------------------------------------------
template <typename T>
void Containers::Vector<T>::push_back(const T &value)
{
if(my_size == my_capacity)
    reserve(2 * my_capacity + 1);
buffer[my_size++] = value;
}
//-------------------------------------------------------------------------------------------------------------
template <typename T>
void Containers::Vector<T>::pop_back()
{
    this->erase(this->end());
    --my_size;
}
//------------------------------------------------------------------------------------------------------------
template <typename T>
bool Containers::Vector<T>::empty() const //returns wether empty
{
    if(buffer == nullptr)
        return false;
}
//------------------------------------------------------------------------------------------------------------
template <typename T>
unsigned Containers::Vector<T>::size() const
{
    return my_size;
}
//------------------------------------------------------------------------------------------------------------
template <typename T>
unsigned Containers::Vector<T>::capacity() const {return my_capacity;}
//------------------------------------------------------------------------------------------------------------
// default constructor
template <class T>
Containers::Vector<T>::Vector(unsigned int size, const T & initial)
{
    my_size = size;
    my_capacity = size;
    if (size == 0)
        buffer = nullptr;
    else {
        buffer = new T[size];
    }

    for (int i = 0; i < size; i++)
        buffer[i] = initial;
}
//------------------------------------------------------------------------------------------------------------
// copy constructor
template <class T>
Containers::Vector<T>::Vector(const Containers::Vector<T> & v)
{
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = new T[my_capacity];
    assert(buffer != nullptr);

    for (int i = 0; i < my_size; i++)
        buffer[i] = v.buffer[i];
}
//------------------------------------------------------------------------------------------------------------
// move constructor
template <class T>
Containers::Vector<T>::Vector(Containers::Vector<T> && v)
{
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = v.buffer;
    v.my_size = 0;
    v.my_capacity = 0;
    v.buffer = nullptr;
}
//------------------------------------------------------------------------------------------------------------
template <class T>
Containers::Vector<T>::~Vector()
{
    my_size = 0;
    my_capacity = 0;
    delete [] buffer;
}
//------------------------------------------------------------------------------------------------------------
// copy assignment
template <class T>
Containers::Vector<T> & Containers::Vector<T>::operator=(const Containers::Vector<T> & v)
{
    T * temp = new T[v.my_capacity];
    assert(temp != nullptr);

    for (int i = 0; i < v.my_size; i++)
        temp[i] = v.buffer[i];

    delete [] buffer;
    buffer = temp;
    my_size = v.my_size;
    my_capacity = v.my_capacity;

    return *this;

/* alternate implementation
    Containers::Vector<T> copy = v;
    swap(*this, copy);
    return *this;
*/
}
//------------------------------------------------------------------------------------------------------------
// move assignment
template <class T>
Containers::Vector<T> & Containers::Vector<T>::operator=(Containers::Vector<T> && v)
{
/* alternate implementation
    swap(my_size, v.my_size);
    swap(my_capacity, v.my_capacity);
    swap(buffer, v.buffer);
*/
    my_size = v.my_size;
    v.my_size = 0;
    my_capacity = v.my_capacity;
    v.my_capacity = 0;
    delete [] buffer;
    buffer = v.buffer;
    v.buffer = 0;

    return *this;
}
//------------------------------------------------------------------------------------------------------------
template <class T>
void Containers::Vector<T>::reserve(unsigned int capacity)//reserves the capacity of the container
{
    if (capacity <= my_capacity)
        return;

    T * new_buffer = new T[capacity];
    assert(new_buffer != nullptr);

    my_capacity = capacity;
    int size;
    for (size = 0; size < my_size; size++)
        new_buffer[size] = buffer[size];

    delete [] buffer;
    buffer = new_buffer;
}
//------------------------------------------------------------------------------------------------------------
template <class T>
void Containers::Vector<T>::resize(unsigned int size)//resize the container
{
    if (size > my_capacity)
        reserve(size*2);

    if (size > my_size)
        for (; my_size < size; my_size++)
            buffer[my_size] = T();
    else my_size = size;
}
//------------------------------------------------------------------------------------------------------------
template <class T>
T & Containers::Vector<T>::operator[](unsigned int a){
    return buffer[a];
}
};



#endif