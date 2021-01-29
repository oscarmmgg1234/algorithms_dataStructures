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
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::erase(LinkedList<T>::iterator from, LinkedList<T>::iterator to){
    for(LinkedList<T>::iterator itr = from; itr != to;)
        itr = LinkedList<T>::erase(itr);
}
//-----------------------------------------------------------------------
template <typename T> //TM => O(1)
typename Containers::LinkedList<T>::iterator Containers::LinkedList<T>::erase(LinkedList<T>::iterator itr){
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

template <typename T>
class Containers::Vector<T>::iterator{
protected: 
friend class Containers::Vector<T>;
T* itr;

iterator(T* ptr){itr = ptr;}
inline T& retrive() const {return *itr;}//TM => O(1)
public:
iterator() : itr{nullptr}{};//default constructor
iterator(const iterator& copy) : itr(copy.itr){}; //TM => O(1) //copy constructor

iterator& operator=(const iterator& copy);//assigment operator
inline T&  operator*() const {return this->retrive();}

iterator& operator++();//preincrement
iterator operator++(int);//postincrement
iterator& operator--();
iterator operator--(int);

bool operator==(const iterator& temp){return itr == temp.itr; }//TM => O(1)
bool operator!=(const iterator& temp){return itr != temp.itr; }//TM => O(1)

};
//-----------------------------------------------------------------------
template <typename T>//TM => O(1)
typename Containers::Vector<T>::iterator&  Containers::Vector<T>::iterator::operator=(const iterator& copy){
itr = copy.itr;
return *this;
}
//-----------------------------------------------------------------------
template <typename T>//TM => O(1)
typename Containers::Vector<T>::iterator& Containers::Vector<T>::iterator::operator++(){
Containers::Vector<T>::iterator copy = *this;
itr++;
return copy;
}
//-----------------------------------------------------------------------
template <typename T>//TM => O(1)
typename Containers::Vector<T>::iterator Containers::Vector<T>::iterator::operator++(int){
itr++;
return *this;
} 
//-----------------------------------------------------------------------
template <typename T>//TM => O(1)
typename Containers::Vector<T>::iterator Containers::Vector<T>::iterator::operator--(int){
itr--;
return *this;
} 
//-----------------------------------------------------------------------
template <typename T>//TM => O(1)
typename Containers::Vector<T>::iterator& Containers::Vector<T>::iterator::operator--(){
Containers::Vector<T>::iterator copy = *this;
itr--;
return copy;
}
//-----------------------------------------------------------------------
template <typename T>
T& Containers::Vector<T>::front() const {return buffer[0];}//TM => O(1)
//-------------------------------------------------------------------------------------------------------------
template <typename T>
T& Containers::Vector<T>::back() const {return buffer[my_size-1];}//TM => O(1)
//-------------------------------------------------------------------------------------------------------------
template <typename T> //TM => O(1)
void Containers::Vector<T>::push_back( T &&value)
{
    if(my_size == my_capacity)
        reserve(2 * my_capacity + 1);
    buffer[my_size++] = value;
}

//-------------------------------------------------------------------------------------------------------------
template <typename T>
void Containers::Vector<T>::pop_back() //TM => O(n)
{
    if(my_size > 0){
    T* copy = new T[my_capacity];
    for(int i = 0;i < my_size-1;i++)
    copy[i] = buffer[i];
    delete [] buffer;
    buffer = copy;
    --my_size;
    }else return;
}
//------------------------------------------------------------------------------------------------------------
template <typename T>//TM => O(1)
bool Containers::Vector<T>::empty() const //returns wether empty
{
    if(buffer == nullptr)
        return false;
}
//------------------------------------------------------------------------------------------------------------
template <typename T>//TM => O(1)
unsigned Containers::Vector<T>::size() const
{
    return my_size;
}
//------------------------------------------------------------------------------------------------------------
template <typename T>//TM => O(1)
unsigned Containers::Vector<T>::capacity() const {return my_capacity;}
//------------------------------------------------------------------------------------------------------------
// default constructor
template <class T>//TM => O(n)
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
template <class T>//TM => O(n)
Containers::Vector<T>::Vector(const Containers::Vector<T> & v)
{
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = new T[my_capacity];
    for (int i = 0; i < my_size; i++)
        buffer[i] = v.buffer[i];
}
//------------------------------------------------------------------------------------------------------------
// move constructor
template <class T>//TM => O(1)
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
template <class T>//TM => O(1)
Containers::Vector<T>::~Vector()
{
    my_size = 0;
    my_capacity = 0;
    delete [] buffer;
}
//------------------------------------------------------------------------------------------------------------
// copy assignment
template <class T>//TM => O(n)
Containers::Vector<T> & Containers::Vector<T>::operator=(const Containers::Vector<T> & v)
{
    T * temp = new T[v.my_capacity];

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
template <class T>//TM => O(n)
Containers::Vector<T> & Containers::Vector<T>::operator=(Containers::Vector<T> && v) noexcept
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
template <class T>//TM => O(n)
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
template <class T>//TM => O(n)
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
template <class T>//TM => O(1)
T & Containers::Vector<T>::operator[](unsigned int a) {
    if(a < my_size)
    return buffer[a];
}
//------------------------------------------------------------------------------------------------------------
template <class T>//TM => O(n)
void Containers::Vector<T>::pop_front()
{
    if(my_size > 0){
    T* copy = new T[my_capacity];
    int count = 0;
    for(int i = 1;i< my_size;i++){
        copy[count] = buffer[i];
        count++;
    }
    delete [] buffer;
    buffer = copy;
    --my_size;
    } else return;
}
//------------------------------------------------------------------------------------------------------------
template <class T>//TM => O(n)
void Containers::Vector<T>::pop_at(unsigned int index){
    if(my_size > 0){
        T* copy = new T[my_capacity];
        int count = 0;
        for(int i = 0;i < my_size;i++){
            if(index == i)
            continue;
            copy[count] = buffer[i];
            count++;
        }
        delete [] buffer;
        buffer = copy;
        my_size--;
    }else return;
}
//**************************************************************************************
//String
//**************************************************************************************
Containers::String::String()
{
    size = 0;
    buffer = nullptr;
}
//------------------------------------------------------------------------------------------------------------
Containers::String::String(const String& op)// copy constructor
{
    size = op.size;
    buffer = op.buffer;
}
//------------------------------------------------------------------------------------------------------------
Containers::String::String(String&& op): size{op.size},buffer{op.buffer}
{
    
    op.size = 0;
    op.buffer = nullptr;
}
//------------------------------------------------------------------------------------------------------------
Containers::String::String(const char* op)//move construnctor
{
    size = 0;
    
    for(const char* a = op;*a;a++)
        size++;
    
    buffer = new char[size];
    for(int i = 0;i < size; i++)
        buffer[i] = op[i];
}
//------------------------------------------------------------------------------------------------------------
Containers::String::String(char op)
{
    size = 1;
    buffer = new char[size];
    buffer[0] = op;
}
//------------------------------------------------------------------------------------------------------------
Containers::String::~String()
{
    delete [] buffer;
}
//------------------------------------------------------------------------------------------------------------
int Containers::String::length()
{
    return size;
}
//------------------------------------------------------------------------------------------------------------
char& Containers::String::operator[](const int a)
{
    return buffer[a];
}
//------------------------------------------------------------------------------------------------------------
Containers::String& Containers::String::operator=(const String& op) // String a = b;
{
    size = op.size;
    buffer = op.buffer;
    return *this;
}
//------------------------------------------------------------------------------------------------------------
Containers::String& Containers::String::operator+=(const String &op)// String a += b;
{
    char *temp = buffer;
    buffer = nullptr;
    int x = 0;
    buffer = new char[size + op.size];
    for(int i = 0;i < size;i++)
    {
        if(i <= size)
            buffer[i] = temp[i];
        
        if(i >size)
            buffer[i] = op.buffer[x];
        x++;
        
    }
    size = size + op.size;
    return *this;
}
//------------------------------------------------------------------------------------------------------------
Containers::String& Containers::String::operator=(String&& op)
{
    size = op.size;
    buffer = op.buffer;
    
    op.size = 0;
    op.buffer = nullptr;
    return *this;
}
//------------------------------------------------------------------------------------------------------------
char*& Containers::String::returnC()
{
    return buffer;
}
//**************************************************************************************
//BST
//**************************************************************************************
template <typename Comparable> Containers::BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree && rhs)
{
root = rhs.root; // root = move(rhs.root); is not necessary since
rhs.root = nullptr; }
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
Containers::BinarySearchTree<Comparable> & Containers::BinarySearchTree<Comparable>::operator=(const BinarySearchTree & rhs) {
    BinarySearchTree copy = rhs; // uses copy constructor
    std::swap(*this, copy);
 
    return *this;
}
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
Containers::BinarySearchTree<Comparable> & Containers::BinarySearchTree<Comparable>::operator=(BinarySearchTree && rhs)
{
std::swap(root, rhs.root); return *this;
}
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
void Containers::BinarySearchTree<Comparable>::printTree(std::ostream & out, BinaryNode * t, std::string indent, const std::string & tag) const
{
    if (t == nullptr)
return;
out << indent << tag << t->element << std::endl;
indent += " ";
printTree(out,t->left, indent, "L ");
printTree(out, t->right, indent, "R ");
}
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
void Containers::BinarySearchTree<Comparable>::printTree(std::ostream & out) const {
    std::cout << "Print Tree\n";
    printTree(out, root, "", "");
}
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
void Containers::BinarySearchTree<Comparable>::inorder(BinaryNode * t) const
{
    if (t == nullptr)
return;
inorder(t->left);
std::cout << t->element << " "; 
inorder(t->right);
}
//------------------------------------------------------------------------------------------------------------
template <class Comparable>
void Containers::BinarySearchTree<Comparable>::preorder(BinaryNode * t) const
{
    if (t == nullptr)
        return;

std::cout << t->element << " "; 
preorder(t->left);
preorder(t->right); }
//------------------------------------------------------------------------------------------------------------

template <typename Comparable>
void Containers::BinarySearchTree<Comparable>::postorder(BinaryNode * t) const
{
    if (t == nullptr)
        return;
postorder(t->left);
postorder(t->right); std::cout << t->element << " "; }
//------------------------------------------------------------------------------------------------------------
template <typename Comparable>
bool Containers::BinarySearchTree<Comparable>::contains(const Comparable &x)
const //
{
    return contains(x,root);
}
//------------------------------------------------------------------------------------------------------------
template <typename Comparable>
bool Containers::BinarySearchTree<Comparable>::contains(const Comparable &x, BinarySearchTree<Comparable>::BinaryNode *t) const
{
    if(t == nullptr)
    {
        return false;
}
else if(x < t->element)
return contains(x,x->left); else if(t->element < x)
return contains(x,t->right); else
return true;
}
//------------------------------------------------------------------------------------------------------------
template <typename Comparable>
void Containers::BinarySearchTree<Comparable>::insert(const Comparable& x,BinaryNode*& t)
{
if(t == nullptr)
 
t = new BinaryNode{x, nullptr, nullptr}; else if(x < t->element)
insert (x,x->left); else if(t->element < x) insert(x,t->right);
else
;
}
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
void Containers::BinarySearchTree<Comparable>::insert(Comparable&& x,BinaryNode*& t)
{
    if(t == nullptr)
t = new BinaryNode{std::move(x),nullptr,nullptr}; else if(x < t->element)
insert(std::move(x),t->left); else if(t->element < x)
insert(std::move(x),t->right);
else
; }
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
typename Containers::BinarySearchTree<Comparable>::BinaryNode* findMin( typename Containers::BinarySearchTree<Comparable>::BinaryNode* t)
{
    if(t == nullptr)
return nullptr; if(t->left == nullptr)
return t;
return findMin(t->left);
}
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
typename Containers::BinarySearchTree<Comparable>::BinaryNode* findMax( typename Containers::BinarySearchTree<Comparable>::BinaryNode* t)
{
    if(t == nullptr)
return nullptr; if(t->right == nullptr)
return t;
return findMax(t->right );
}
//-------------------------------------------------------------------- --------------------------------------------------
template <typename obj>
void Containers::BinarySearchTree<obj>::remove(const obj &x,
BinarySearchTree<obj>::BinaryNode *&t)
{
    if(t == nullptr)
        return;
if(x < t->left) remove(x,t->left);
else if(t->element < x) remove(x,t->right);
else if (t->left != nullptr && t->right != nullptr) {
t->element = findMin(t->right)->element;
remove(t->element,t->right); }
else
{
BinaryNode* oldNode = t;
t = (t->left != nullptr) ? t->left : t->right; delete oldNode;
} }
//-------------------------------------------------------------------- --------------------------------------------------
template <typename obj>
void Containers::BinarySearchTree<obj>::makeEmpty(BinarySearchTree<obj>::BinaryNode *&t)
{
    if(t != nullptr)
{
makeEmpty(t->left); makeEmpty(t->right); delete t;
}
t = nullptr; }
//-------------------------------------------------------------------- --------------------------------------------------
template <typename obj>
typename Containers::BinarySearchTree<obj>::BinaryNode * Containers::BinarySearchTree<obj>::clone(BinarySearchTree<obj>::BinaryNode *t) const
{
    if(t == nullptr)
        return nullptr;
    else return new BinaryNode{t->element,clone(t->left), clone(t->right)};
}