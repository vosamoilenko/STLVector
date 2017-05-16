#ifndef VECTOR_H
#define VECTOR_H
#define MIN_SIZE 1

#include <iostream>
#include <algorithm>

using namespace std;

class My_Exception : public exception {
    virtual const char* what() const noexcept {
        return "MyException";
    }
};


template <typename T>
class Vector {
public:
    using value_type = T;
    using const_value_type = const T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
public:
    class iterator {
        pointer ptr;
    public:
        using iterator_category = forward_iterator_tag;
        using self_type = iterator;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = ptrdiff_t;

    public:
        iterator(pointer);
        self_type operator++();
        self_type operator++(int);
        self_type& operator--();
        self_type& operator--(int);
        reference operator*();
        pointer operator->();
        bool operator==(const self_type&);
        bool operator!=(const self_type&);
        difference_type operator-(const self_type&);
    };
    class const_iterator {
        pointer ptr;
    public:
        using iterator_category = forward_iterator_tag;
        using self_type = const_iterator;
        using const_value_type = T;
        using const_reference = T&;
        using const_pointer = T*;
        using difference_type = ptrdiff_t;
    public:
        const_iterator(pointer);
        self_type& operator+(size_type);
        self_type& operator++();
        self_type operator++(int);
        self_type& operator--();
        self_type& operator--(int);
        const_reference operator*();
        const_pointer operator->();
        bool operator==(const self_type&);
        bool operator!=(const self_type&);
        difference_type operator-(const self_type&);
    };
private:
    size_t max_sz;
    pointer ptr;
    size_t sz;

    void re_allocator();
    void re_allocator(size_t);
public:
    Vector();
    Vector(size_t);
    Vector(initializer_list<value_type>);
    iterator begin();
    iterator begin() const;
    iterator end();
    iterator end() const;
    const_iterator cbegin();
    const_iterator cend();
    size_t size();
    const size_t size() const;
    void push_back(value_type);
    value_type pop_back();
    const_iterator erase(const_iterator);
    const_iterator insert(const_iterator,const value_type&);
    iterator erase(iterator);
    iterator insert(iterator,const value_type&);
    bool empty();
    void clear();
    void reserve(size_type);
    void shrink_to_fit();
    reference operator[](size_type);
    const_reference operator[](size_type) const;
    bool operator==(const Vector<T>&);
    bool operator!=(const Vector<T>&);
    Vector<T> operator=(const Vector<T>&);
    template <typename U>
    friend ostream& operator<<(ostream& os, const Vector<U>& v);
};



#include "vector.cpp"

#endif
