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
bool operator==(const Containers::String& a,const Containers::String& b)
{
    if(a.size != b.size)
        return false;
    
    for(int i = 0; i < a.size; i++)
        if(a.buffer[i] != b.buffer[i])
            return false;
    return true;
}
//------------------------------------------------------------------------------------------------------------
bool operator<=(const Containers::String& a,const Containers::String& b)
{
    if(a.size > b.size)
        return false;
    return true;
}
//------------------------------------------------------------------------------------------------------------
bool operator>=(const Containers::String& a,const Containers::String& b)
{
    if(a < b)
        return false;
    return true;
}
//------------------------------------------------------------------------------------------------------------
bool operator>(const Containers::String& a,const Containers::String& b)
{
    if (a.size > b.size)
        return true;
    return false;
}
//------------------------------------------------------------------------------------------------------------
bool operator<(const Containers::String& a,const Containers::String& b)
{
    if(a.size < b.size)
        return true;
    return false;
}
//------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& a,const Containers::String& b)
{
    for(int i = 0;i < b.size;i++)
        a << b.buffer[i];
    return a;
}

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
unsigned size;
inline int hashFunction(T& key);
public:
HashTable() : Bucket{0}, size{0} {}//dafault constructor
HashTable(unsigned&& bucketSize) : Bucket{bucketSize}, size{0} {temp = new Containers::LinkedList<T>[bucketSize];}
HashTable(unsigned& bucketSize) : Bucket{bucketSize}, size{0} {temp = new Containers::LinkedList<T>[bucketSize];}

void insert(T& item);
void insert(T&& item);
void erase(int& key);
void erase(int&& key);

int getBucketSize() const noexcept {return Bucket;}
int getSize() const noexcept {return size;}

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
