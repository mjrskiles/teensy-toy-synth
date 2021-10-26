//
// Created by Michael Skiles on 10/22/21.
//

#ifndef TEENSY_STATIC_ORDERED_LIST_H
#define TEENSY_STATIC_ORDERED_LIST_H

#include <cstdint>
#include <iostream>

const uint16_t SOL_BUFFER_SIZE {4};

template <class T>
        class StaticOrderedList {
        public:
            void print();
            void putInString(char *ret_buffer);
            void push(T &item);
            void insertAtIndex(T &item, uint16_t index);
            T* pop();
            T* removeAtIndex(uint16_t index);
            uint16_t head();
            uint16_t tail();
            bool isEmpty() { return _size == 0; }
            bool isFull() {return _size == SOL_BUFFER_SIZE; }
            bool contains(T item);
            uint16_t indexOf(T val);
            uint16_t size();
            uint16_t maxSize() { return SOL_BUFFER_SIZE; }

            // for testing
            bool compareTList(T list[SOL_BUFFER_SIZE], int size);
        protected:
            T* _list[SOL_BUFFER_SIZE];
            uint16_t _size;
            uint16_t _head;
            uint16_t _tail;
        };

template<class T>
        void StaticOrderedList<T>::print() {
            std::cout << "List | Head: " << _head << " Tail: " << _tail << std::endl;
            for (int i = 0; i < SOL_BUFFER_SIZE; i++) {
                std::cout << _list[i] << std::endl;
            }

        }

template<class T>
        void StaticOrderedList<T>::putInString(char *ret_buffer) {

        }

/*
 * Insert a new item as the head.
 * The list should grow from 0 to the max size and then wrap around to the beginning of the array
 * to discard the oldest items first. This avoids needing to move items within the array when possible.
 */
template<class T>
void StaticOrderedList<T>::push(T &item) {
    if (_size == 0) {
        _list[_head] = &item;
    } else {
        _head = (_head + 1) % SOL_BUFFER_SIZE;
        _list[_head] = &item;
    }

    if (_size == SOL_BUFFER_SIZE) {
        _tail = (_tail + 1) % SOL_BUFFER_SIZE;
    } else {
        _size += 1;
    }
}

template<class T>
void StaticOrderedList<T>::insertAtIndex(T &item, uint16_t index) {
    if (index >= _size) {
        push(item);
    } else {
        T *swap = _list[_tail + index];
        _list[(_tail + index) % SOL_BUFFER_SIZE] = &item;
        if (_size < SOL_BUFFER_SIZE) {
            _size += 1;
        } else {
            _tail = (_tail + 1) % SOL_BUFFER_SIZE;
        }
        _head = (_head + 1) % SOL_BUFFER_SIZE;
        for (uint32_t i = _tail + index + 1; i < _tail + _size; i++) {
            T *swap2 = _list[i % SOL_BUFFER_SIZE];
            _list[i % SOL_BUFFER_SIZE] = swap;
            swap = swap2;
        }
    }
}

template<class T>
T *StaticOrderedList<T>::pop() {
    if (_size == 0) {
        return nullptr;
    }
    else {
        T *popped;
        popped = _list[_head];
        _list[_head] = nullptr;
        _head = (_head - 1) % SOL_BUFFER_SIZE;
        _size = _size - 1;
        return popped;
    }
}

template<class T>
T *StaticOrderedList<T>::removeAtIndex(uint16_t index) {
    if (index > _size) return nullptr;
    T *removed = _list[(_tail + index) % SOL_BUFFER_SIZE];
    _list[(_tail + index) % SOL_BUFFER_SIZE] = nullptr;
    for (uint32_t i = _tail + index; i < _tail + _size; i++) {
        _list[i % SOL_BUFFER_SIZE] = _list[(i + 1) % SOL_BUFFER_SIZE];
    }
    _size -= 1;
    _head = (_head - 1) % SOL_BUFFER_SIZE;
    return removed;
}

template<class T>
uint16_t StaticOrderedList<T>::size() {
    return _size;
}

template<class T>
uint16_t StaticOrderedList<T>::head() {
    return _head;
}

template<class T>
uint16_t StaticOrderedList<T>::tail() {
    return _tail;
}

template<class T>
bool StaticOrderedList<T>::compareTList(T *list, int size) {
    for (int i = 0; i < size; i++) {
        if (list[i] != *(_list[i])) return false;
    }
    return true;
}

template<class T>
bool StaticOrderedList<T>::contains(T item) {
    bool found = false;
    for (int i = 0; i < SOL_BUFFER_SIZE; i++) {
        T *curr = _list[i];
        if (curr != nullptr) {
            if (*curr == item) found = true;
        }
    }
    return found;
}

template<class T>
uint16_t StaticOrderedList<T>::indexOf(T val) {
    for (uint16_t i = 0; i < SOL_BUFFER_SIZE; i++) {
        if (*(_list[i]) == val) {
            return i;
        }
    }
    return -1;
}

#endif //STATIC_ORDERED_LIST_STATIC_ORDERED_LIST_H
