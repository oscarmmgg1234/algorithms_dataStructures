/* 
Author: Oscar Maldonado
Description: Create data structures using best
pratices and best time complexity and eventually create a product ready dylib
*/
#ifndef CONTAINERS
#define CONTAINERS 
#include <ostream>
namespace Containers {

//**************************************************************************************
//**************************************************************************************
//Data-Structures 
//**************************************************************************************
//**************************************************************************************
    
//**************************************************************************************
//Linked List && Doubly Linked List
//**************************************************************************************

template <typename T>
class LinkedList{
    struct Node {
        Node* prev;
        Node* next;
        T data;

        Node():next{nullptr},prev{nullptr}{} //TM => O(1)
        Node(const T& val,Node* p = nullptr, Node* n = nullptr) : next{n}, prev{p}, data{val} {} //TM => O(1)
        Node(T&& val, Node* p = nullptr, Node* n = nullptr) : next{n}, prev{p}, data{std::move(val)}{} //TM => O(1)
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
    LinkedList(LinkedList&& m) noexcept; //move constructor
    ~LinkedList(); //destructor

    LinkedList<T> & operator=(const LinkedList& c); //copy assignment operator
    LinkedList<T> & operator=(LinkedList&& m) noexcept; //move assignment operator 

    iterator begin() {return  head->next;} 
    const_iterator begin() const {return head->next;}
    iterator end() {return tail;}
    const_iterator end() const {return tail;}

    inline T & operator[](unsigned int index) const;
    T& front(){ return *begin();}
    const T& front() const {return *begin();}
    T& back(){return *--end();}
    const T& back() const {return *--back();}

    inline int getSize() const {return size;}

    //size_t getByteSize(const int index) const {return std::sizeof()}

    inline bool empty() const {return size == 0;}
    void clear();

    void push_front(const T& val) {insert(begin(),val);}
    void push_front(T&& val) noexcept {insert(begin(), val);}
    void push_back(const T& val) {insert(end(),val);}
    void push_back(T&& val) noexcept {insert(end(),val);}
    

    void pop_front() { erase(begin());}
    void pop_back() { erase(end());}

    iterator insert(iterator, const T&);
    iterator insert(iterator, T&&);

    iterator erase(iterator);
    iterator erase(iterator, iterator);
    
};
//**************************************************************************************
//Custom Vector
//**************************************************************************************

template <class T>
class Vector
{
public:

    
    class iterator;
    Vector(unsigned int size = 0, const T & initial = T()); // default constructor
    Vector(const Vector<T> & v);                            // copy constructor
    Vector(Vector<T> && v);                                // move constructor
    ~Vector();                                              // destructor
    Vector<T> & operator=(const Vector<T> & v);             // copy assignment
    Vector<T> & operator=(Vector<T>&& v) noexcept;                  // move assignment

    unsigned int capacity() const;
    inline unsigned int size() const;
    inline bool empty() const;

    iterator begin(){return iterator(buffer);}
    iterator end(){return buffer + my_size;}
    
    inline T & front() const;                           // return reference to first element
    inline T & back() const;       
    void insert_at(const unsigned index,const T& value);
    void insert_at(const unsigned index, T&& value);
    void insert_at(iterator& itr);
    void push_back(const T & value);
    void push_back(T && value);
    void push_back(iterator itr);
    void push_front(const T& value);
    void push_front(T&& value);
    void push_front(iterator itr);
    void pop_back();
    void pop_front();
    void pop_at(unsigned int index);
    void erase(iterator& itr);
    
    void reserve(unsigned int capacity);   // adjust capacity
    void resize(unsigned int size);       // adjust size

    T & operator[](unsigned int index);

    bool operator==(const Vector<T> & temp){return buffer == temp.buffer;}
    bool operator!=(const Vector<T> & temp){return buffer != temp.buffer;}
   
private:
    unsigned int my_size;
    unsigned int my_capacity;
    T * buffer;
};
//-----------------------------------------------------------------------
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
//Queue
//**************************************************************************************

template <typename T, typename container = Vector<T>>
class queue  {
    public:
    queue(){}//default constructor
    queue(const queue & q){temp = q.temp;} //TM => O(1)//copy constructor
    
    queue & operator=(const queue& p){temp = p.temp; return *this;}//TM => O(1)
    queue & operator=(queue&& p) noexcept {temp = p;p.temp.clear();}//TM => O(1)

    void enqueue(T& val){temp.push_back(val);}//TM => O(n)
    void enqueue(T&& val) noexcept {temp.push_back(val);}//TM => O(n)
    void dequeue(){temp.pop_front();}//TM => O(n)

    inline T& getFirst() const noexcept {return temp.front();}//TM => O(1)
    
    private: 
    container temp;
};
//**************************************************************************************
//String
//******************************e********************************************************
class String {
    int size;
    char* buffer;
public:
    
    String();
    String(const String& op);//copy constructor
    String(String && op);//move constructors
    String(const char* op);
    String(char op);
    ~String();//destructor
    
    char*& returnC();
    int length();//return length of buffer
    char& operator[](const int a);//returns char at specified index in the array
    String& operator=(const String& op);//String a = "hello"
    String& operator+=(const String & op);
    String& operator=(String && op) ;
    
    
    friend bool operator==(const String& a,const String& b);
    friend bool operator<=(const String& a,const String& b);
    friend bool operator>= (const String& a,const String& b);
    friend bool operator>(const String& a,const String& b);
    friend bool operator<(const String& a,const String& b);
    
    friend std::ostream& operator<<(std::ostream& a, const String& b);
    
    
};
//------------------------------------------------------------------------------------------------------------
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
bool operator==(const String& a,const String& b)
{
    if(a.size != b.size)
        return false;
    
    for(int i = 0; i < a.size; i++)
        if(a.buffer[i] != b.buffer[i])
            return false;
    return true;
}
//------------------------------------------------------------------------------------------------------------
bool operator<=(const String& a,const String& b)
{
    if(a.size > b.size)
        return false;
    return true;
}
//------------------------------------------------------------------------------------------------------------
bool operator>=(const String& a,const String& b)
{
    if(a < b)
        return false;
    return true;
}
//------------------------------------------------------------------------------------------------------------
bool operator>(const String& a,const String& b)
{
    if (a.size > b.size)
        return true;
    return false;
}
//------------------------------------------------------------------------------------------------------------
bool operator<(const String& a,const String& b)
{
    if(a.size < b.size)
        return true;
    return false;
}
//------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& a,const String& b)
{
    for(int i = 0;i < b.size;i++)
        a << b.buffer[i];
    return a;
}
//------------------------------------------------------------------------------------------------------------
char*& Containers::String::returnC()
{
    return buffer;
}
//------------------------------------------------------------------------------------------------------------

//**************************************************************************************
//Max-Heap
//**************************************************************************************
//**************************************************************************************
//Min-Heap
//**************************************************************************************
//**************************************************************************************
//BST
//**************************************************************************************
template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree(): root{nullptr} { }
BinarySearchTree(const BinarySearchTree & rhs) { root = clone(rhs.root); }
BinarySearchTree(BinarySearchTree && rhs); ~BinarySearchTree() { makeEmpty(root); }
BinarySearchTree & operator=(const BinarySearchTree & rhs); BinarySearchTree & operator=(BinarySearchTree && rhs);
    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains(const Comparable & x) const;
    bool isEmpty() const { return root == nullptr; }
    void printTree(std::ostream & out = std::cout) const;
    void makeEmpty() { makeEmpty(root); }
    void insert(const Comparable & x) { insert(x, root); }
    void insert(Comparable && x) { insert(std::move(x), root); }
    void remove(const Comparable & x) { remove(x, root); }
    void inorder() const { inorder(root); }
    void preorder() const {preorder(root);}
    void postorder() const {postorder(root);}
private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode * left;
        BinaryNode * right;
        BinaryNode(const Comparable & theElement, BinaryNode * lt,BinaryNode * rt): element{theElement}, left{lt}, right{rt} { }
        BinaryNode(Comparable && theElement, BinaryNode * lt,BinaryNode * rt): element{std::move(theElement)}, left{lt}, right{rt}{}
};
    BinaryNode * root;
    void insert(const Comparable & x, BinaryNode * & t);
    void insert(Comparable && x, BinaryNode * & t);
    void remove(const Comparable & x, BinaryNode * & t);
    BinaryNode * findMin(BinaryNode * t) const;
    BinaryNode * findMax(BinaryNode * t) const;
    bool contains(const Comparable & x, BinaryNode * t) const;
    void makeEmpty(BinaryNode * & t);
    void printTree(std::ostream & out, BinaryNode * t, std::string indent, const std::string & tag) const; // added indent and tag
    BinaryNode * clone(BinaryNode * t) const;
    void inorder(BinaryNode * t) const;
    void postorder(BinaryNode* t) const;
    void preorder(BinaryNode* t) const;
};
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable> Containers::BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree && rhs)
{
root = rhs.root; // root = move(rhs.root); is not necessary since
rhs.root = nullptr; }
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
Containers::BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(const BinarySearchTree & rhs) {
    BinarySearchTree copy = rhs; // uses copy constructor
    std::swap(*this, copy);
 
    return *this;
}
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
Containers::BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(BinarySearchTree && rhs)
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
typename Containers::BinarySearchTree<Comparable>::BinaryNode* findMin( typename BinarySearchTree<Comparable>::BinaryNode* t)
{
    if(t == nullptr)
return nullptr; if(t->left == nullptr)
return t;
return findMin(t->left);
}
//-------------------------------------------------------------------- --------------------------------------------------
template <typename Comparable>
typename Containers::BinarySearchTree<Comparable>::BinaryNode* findMax( typename BinarySearchTree<Comparable>::BinaryNode* t)
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
    else
return new BinaryNode{t->element,clone(t->left), clone(t->right)};
}
//**************************************************************************************
//Stack
//**************************************************************************************
template <typename T, class container = Vector<T>>
class Stack{
protected:
container temp;

public: 
Stack(){};//constructor
Stack(T& val) : temp{val}{}
//We dont need big 6 because Stack already has them

Stack& operator=(const Stack<T>&);

bool empty(){return temp.empty();}

void push(const T& val){temp.push_back(val);}
void push(T&& val){temp.push_back(std::move(val));}

T& top(){return temp.back();}

void evaluatePostFix(Containers::String&);
void evaluatePreFix(Containers::String&);

void pop(){temp.pop_back();}
 
};
//**************************************************************************************
//Trie
//**************************************************************************************
//**************************************************************************************
//Hash Table
//**************************************************************************************
template <typename T>
class HashTable {
unsigned Bucket;
Containers::LinkedList<T>* temp;
public:
HashTable() : Bucket{0} {}//dafault constructor
HashTable(unsigned& bucketSize) : Bucket{bucketSize} {temp = new Containers::LinkedList<T>[bucketSize];}

void insert(T& item);
void erase(T& key);
    
inline int& hashFunction(T& key);

void displayHash();
};
//**************************************************************************************
//Graph
//**************************************************************************************
//**************************************************************************************
//Binary Tree
//**************************************************************************************
    
//**************************************************************************************
//**************************************************************************************
//Algorithms 
//**************************************************************************************
//**************************************************************************************
    
};//end of namespace

#endif
