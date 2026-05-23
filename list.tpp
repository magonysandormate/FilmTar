#include "list.hpp"
#include <iostream>

template <typename T>
LinkedList<T>::LinkedList(const T& data) : data(data), next(NULL) {}

template <typename T>
LinkedList<T>::Iterator::Iterator(LinkedList<T>* ptr) : current(ptr) {}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin(){
    return Iterator(this);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end(){
    return Iterator(NULL);
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++(){
    current = current->next;
    return *this;
}

template <typename T>
T LinkedList<T>::Iterator::operator*(){
    return current->data;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const{
    return current != other.current;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    delete next;
}