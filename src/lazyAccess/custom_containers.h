#ifndef CUSTOM_CONTAINERS
#define CUSTOM_CONTAINERS
#include "../source/containers.cpp"

//auto instances
template <typename T>
Containers::LinkedList<T> List() noexcept {
    Containers::LinkedList<T> instance;
    return instance;
} 

template <typename T>
typename Containers::LinkedList<T>::iterator List(char a) noexcept {
    if(a == 'i'){
        typename Containers::LinkedList<T>::iterator instance;
        return instance;
    }
} 
template <typename T>
Containers::Vector<T> Vector() noexcept {
    Containers::Vector<T> instance;
    return instance;
} 

template <typename T>
typename Containers::Vector<T>::iterator Vector(char a) noexcept {
    if(a == 'i'){
    typename Containers::Vector<T>::iterator instance;
    return instance;
    }
} 
template <typename T>
Containers::queue<T> Queue() noexcept {
    Containers::queue<T> instance;
    return instance;
} 

template <typename T>
typename Containers::queue<T>::iterator Queue(char a) noexcept {
    if(a == 'i'){
    typename Containers::queue<T>::iterator instance;
    return instance;
    }
} 

template <typename T, class container = Containers::Vector<T>>
Containers::Stack<T> Stack(){
    Containers::Stack<T> instance;
    return instance;
}


#endif