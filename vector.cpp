#ifdef VECTOR_H

// vector methods
template <typename T>
Vector<T>::Vector() :sz{0},max_sz{MIN_SIZE} {
    ptr = new value_type[MIN_SIZE];
}
template <typename T>
Vector<T>::Vector(size_t _sz) : sz{0}, max_sz{_sz} {
    ptr = new value_type[max_sz];
}
template <typename T>
Vector<T>::Vector(initializer_list<value_type> _li) : sz{0}, max_sz{_li.size()}  {
    ptr = new value_type[max_sz];
    for (auto x: _li) {
        push_back(x);
    }
}
template <typename T>
void Vector<T>::re_allocator() {
    if (sz+1 >= max_sz) {
        pointer buff = ptr;
        ptr = new value_type[(max_sz*=2)];
        copy(buff, buff+sz, ptr);
    }
}
template <typename T>
void Vector<T>::re_allocator(size_t _sz) {
    pointer buff = ptr;
    if (_sz > sz) {
        ptr = new value_type[(max_sz = (sz = _sz))];
    }
    copy(buff, buff+sz, ptr);
}
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
    return iterator(ptr);
}
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const {
    return iterator(ptr);
}
template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
    return iterator(ptr+sz);
}
template <typename T>
typename Vector<T>::iterator Vector<T>::end() const {
    return iterator(ptr+sz);
}
template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() {
    return const_iterator(ptr);
}
template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() {
    return const_iterator(ptr+sz);
}
template <typename T>
size_t Vector<T>::size(){
    return sz;
}
template <typename T>
const size_t Vector<T>::size() const{
    return sz;
}
template <typename T>
void Vector<T>::push_back(value_type _elem){
    re_allocator();
    ptr[sz++] = _elem;
}
template <typename T>
typename Vector<T>::value_type Vector<T>::pop_back() {
    return ptr[--sz];
}
template <typename T>
typename Vector<T>::const_iterator Vector<T>::erase(typename Vector<T>::const_iterator it) {
    auto diff = it-cbegin();
    if (diff < 0 || static_cast<size_t>(diff)>=max_sz) {
        throw My_Exception();
    }
    size_t index = static_cast<size_t>(diff);
    for (size_t i = index; i < sz-1;++i) {
        ptr[i] = ptr[i+1];
    }
    --sz;
    return const_iterator(ptr+index);
}
template <typename T>
typename Vector<T>::const_iterator Vector<T>::insert(typename Vector<T>::const_iterator it, const value_type& elem) {
    auto diff = it-cbegin();
    if (diff < 0 || static_cast<size_t>(diff)>=max_sz) {
        throw My_Exception();
    }
    size_t index = static_cast<size_t>(diff);
    for (size_t i = sz-1; i >= index; --i) {
        ptr[i+1] = ptr[i];
    }
    ptr[index] = elem;
    ++sz;
    return const_iterator(ptr+index);
}
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(typename Vector<T>::iterator it) {
    auto diff = it-begin();
    if (diff < 0 || static_cast<size_t>(diff)>=max_sz) {
        throw My_Exception();
    }
    size_t index = static_cast<size_t>(diff);
    for (; index < sz-1;++index) {
        ptr[index] = ptr[index+1];
    }
    --sz;
    return iterator(ptr);
}
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::iterator it, const value_type& elem) {
    auto diff = it-begin();
    if (diff < 0 || static_cast<size_t>(diff)>=max_sz) {
        throw My_Exception();
    }
    size_t index = static_cast<size_t>(diff);
    for (size_t i = sz-1; i >= index; --i) {
        ptr[i+1] = ptr[i];
    }
    ptr[index] = elem;
    ++sz;
    return iterator(ptr+index);
}
template <typename T>
bool Vector<T>::empty(){
    if (!sz) { return true; } else { return false; }
}
template <typename T>
void Vector<T>::clear(){
    sz = 0;
}
template <typename T>
void Vector<T>::reserve(size_type _sz) {
    if (_sz < max_sz) {
        throw My_Exception();
    }
    re_allocator(_sz);
}
template <typename T>
void Vector<T>::shrink_to_fit() {
    max_sz = sz;
}
template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type _sz){
    if (_sz >= sz) {
        throw My_Exception();
    } else {
        return ptr[_sz];
    }
}
template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type _sz) const {
    if (_sz >= sz) {
        throw My_Exception();
    } else {
        return ptr[_sz];
    }
}
template <typename T>
bool Vector<T>::operator==(const Vector<T>& v){
    if (sz != v.sz) { return false;}
    for (size_t i = 0; i < sz; ++i) {
        if (*this[i] != v[i]) { return false;}
    }
    return true;
}
template <typename T>
bool Vector<T>::operator!=(const Vector<T>& v){
    return !(*this==v);
}
template <typename T>
Vector<T> Vector<T>::operator=(const Vector<T>& v){
    max_sz = v.max_sz;
    sz = v.sz;
    re_allocator(max_sz);
    copy(v.ptr, v.ptr+sz, ptr);
    return *this;
}
template <typename T>
ostream& operator<<(ostream& os, const Vector<T>& v) {
    os << '[';
    if (v.size() != 0) {
        for (size_t i = 0; i < v.size()-1; ++i) {
            os << v[i] << ',';
        }
        os << v[v.size()-1];
    }
    return os << ']';
}
// iterator methods
template <typename T>
Vector<T>::iterator::iterator(pointer _ptr) : ptr{_ptr} {}
template <typename T>
typename Vector<T>::iterator::self_type Vector<T>::iterator::operator++() {
    ++ptr;
    return *this;
}
template <typename T>
typename Vector<T>::iterator::self_type Vector<T>::iterator::operator++(int) {
    self_type it = *this;
    ptr++;
    return it;
}
template <typename T>
typename Vector<T>::iterator::self_type& Vector<T>::iterator::operator--() {
    --ptr;
    return *this;
}
template <typename T>
typename Vector<T>::iterator::self_type& Vector<T>::iterator::operator--(int) {
    self_type it = *this;
    ptr--;
    return it;
}
template <typename T>
typename Vector<T>::iterator::reference Vector<T>::iterator::operator*() {
    return *ptr;
}
template <typename T>
typename Vector<T>::iterator::pointer Vector<T>::iterator::operator->() {
    return ptr;
}
template <typename T>
bool Vector<T>::iterator::operator==(const self_type& rhs) {
    return ptr==rhs.ptr;
}
template <typename T>
bool Vector<T>::iterator::operator!=(const self_type& rhs) {
    return !(*this==rhs);
}
template <typename T>
typename Vector<T>::iterator::difference_type Vector<T>::iterator::operator-(const typename Vector<T>::iterator::self_type& rhs) {
    return  ptr - rhs.ptr;
}

// const_iterator methods
template <typename T>
Vector<T>::const_iterator::const_iterator(pointer _ptr) : ptr{_ptr}{}
template <typename T>
typename Vector<T>::const_iterator::self_type& Vector<T>::const_iterator::operator+(size_type x) {
    ptr+=3;
    return *this;
}
template <typename T>
typename Vector<T>::const_iterator::self_type& Vector<T>::const_iterator::operator++() {
    ++ptr;
    return *this;
}
template <typename T>
typename Vector<T>::const_iterator::self_type Vector<T>::const_iterator::operator++(int) {
    self_type it = *this;
    ptr++;
    return it;
}
template <typename T>
typename Vector<T>::const_iterator::self_type& Vector<T>::const_iterator::operator--() {
    --ptr;
    return *this;
}
template <typename T>
typename Vector<T>::const_iterator::self_type& Vector<T>::const_iterator::operator--(int) {
    self_type it = *this;
    ptr--;
    return it;
}
template <typename T>
typename Vector<T>::const_iterator::const_reference Vector<T>::const_iterator::operator*() {
    return *ptr;
}
template <typename T>
typename Vector<T>::const_iterator::const_pointer Vector<T>::const_iterator::operator->() {
    return ptr;
}
template <typename T>
bool Vector<T>::const_iterator::operator==(const self_type& rhs) {
    return ptr==rhs.ptr;
}
template <typename T>
bool Vector<T>::const_iterator::operator!=(const self_type& rhs) {
    return !(*this==rhs);
}
template <typename T>
// typename Vector<T>::difference_type operator-(const typename Vector<T>::const_iterator::self_type& lhs,const typename Vector<T>::const_iterator::self_type& rhs) {
typename Vector<T>::const_iterator::difference_type Vector<T>::const_iterator::operator-(const typename Vector<T>::const_iterator::self_type& rhs) {
    // return  lhs.ptr - rhs.ptr;
    return  ptr - rhs.ptr;
}

//
#endif
