#include "Vector.h"

Vector::Vector(size_t s, int* arr) : m_size(s)
{
    m_arr = new int[m_size];

    for (int i = 0; i < m_size; ++i)
        m_arr[i] = arr[i];
}
Vector::~Vector()
{
    delete[] m_arr;
}

// normal iterator implementation
int& Vector::Iterator::operator*() {
    return *ptr;
}

Vector::Iterator& Vector::Iterator::operator ++() {
    ++ptr;
    // Тук евентуално е необходима по-сложна логика при друга структура данни

    std::cout << "iterator called\n"; 
    return *this;
}
Vector::Iterator Vector::Iterator::operator ++ (int) {
    Iterator prev = *this;
    operator ++ ();
    
    return prev;
}

bool Vector::Iterator::operator != (const Iterator& other) const
{
    return ptr != other.ptr;
}
    
Vector::Iterator Vector::begin()
{
    return Vector::Iterator(m_arr);
}
Vector::Iterator Vector::end()
{
    return Vector::Iterator(m_arr + m_size);
}

// const iterator 
const int& Vector::ConstIterator::operator *() const
{
    return *ptr;
}
Vector::ConstIterator& Vector::ConstIterator::operator ++()
{
    ++ptr;
    std::cout << "const iterator called\n"; 
    return *this;
}
bool Vector::ConstIterator::operator !=(const ConstIterator& other) const
{
    return ptr != other.ptr;
}

Vector::ConstIterator Vector::const_begin() const
{
    return Vector::ConstIterator(m_arr);
}
Vector::ConstIterator Vector::const_end() const
{
    return Vector::ConstIterator(m_arr + m_size);
}