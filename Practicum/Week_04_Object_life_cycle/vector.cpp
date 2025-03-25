#include <iostream>
#include <fstream>

using namespace std;

class Vector {
    int *m_arr;
    size_t m_size;
    size_t m_capacity;

    void clear() {
        delete[] m_arr;
        m_size = 0;
        m_capacity = 0;
    }

    void copy(const Vector &other) {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_arr = new int[m_capacity];
        for(int i = 0; i < m_size; i++) {
            m_arr[i] = other.m_arr[i];
        }
    }
    void resize(size_t n) {
        m_capacity = n;
    
        int *temp = new int[m_capacity];
        for(int i = 0; i < m_size; i++) {
            temp[i] = m_arr[i];
        }
    
        delete[] m_arr;
        m_arr = temp;
    }

public:
    Vector() {
        m_size = 0;
        m_capacity = 16;
        m_arr = new int[m_capacity];
    }

    explicit Vector(size_t n) {
        m_size = n;
        m_capacity = n;
        m_arr = new int[m_capacity];
    }
    
    Vector(size_t n, int val) {
        m_size = n;
        m_capacity = n;
        m_arr = new int[m_capacity];
        for(int i = 0; i < m_size; i++) {
            m_arr[i] = val;
        }
    }

    Vector(const Vector &other) {
        copy(other);
    }
    
    Vector& operator=(const Vector &other) {
        if(this != &other) {
            clear();
            copy(other);
        }
        return *this;
    }

    ~Vector() {
        clear();
    }

    int& at(size_t index) {
        // if(index < 0 || index >= m_size) {
        //     throw out_of_range("Index out of range");
        // }
        return m_arr[index];
    }

    void push_back(int val) {
        if(m_size == m_capacity) {
            resize(m_capacity * 2);
        }
        m_arr[m_size++] = val;
    }
    
    bool empty() const {
        return m_size == 0;
    }

    size_t size() const {
        return m_size;
    }
    // void operator()(){
    //     cout<<"Hello"<<endl;
    // }
};


int main(){
}