#ifndef _VECTOR_H_
#define _VECTOR_H_

#pragma once

#include <iostream>

class Vector {
    int* m_arr;
    size_t m_size;

public:
    Vector(size_t s, int* arr);
    Vector(const Vector&) = delete;
    Vector& operator=(const Vector&) = delete;
    ~Vector();

// normal iterator implementation
    class Iterator {
    private:
        int* ptr;

    public:
        Iterator(int* p) : ptr(p) {}

        int& operator*();

        Iterator& operator ++();
        Iterator operator ++ (int);

        bool operator != (const Iterator& other) const;
    };
    
    Iterator begin();
    Iterator end();

// const iterator 
    class ConstIterator {
    private:
        const int* ptr;
    public:
        ConstIterator(const int* p) : ptr(p) {}
        const int& operator*() const;
        ConstIterator& operator++();
        bool operator!=(const ConstIterator& other) const;
    };
    
    ConstIterator const_begin() const;
    ConstIterator const_end() const;
};

#endif