#include <iostream>

using namespace std;

class String{
    char *m_str;
    size_t m_size;
    
    void clear() {
        delete[] m_str;
        m_size = 0;
    }

    void copy(const char* str, size_t size) {
        m_size = size;
        m_str = new char[m_size + 1];

        for(int i = 0; i < m_size; i++) {
            m_str[i] = str[i];
        }
        
        m_str[m_size] = '\0';
    }

    void copy(const String &other) {
        copy(other.m_str, other.m_size);
    }
    
    void resize(size_t n) {
        char *temp = new char[n];
        for(int i = 0; i < m_size; i++) {
            temp[i] = m_str[i];
        }
        
        delete[] m_str;
        m_str = temp;

        m_size = n;
    }

    size_t len(const char *str)const{
        size_t size = 0;
        while(str[size] != '\0') {
            size++;
        }
        return size;
    }

    void appendStr(const char *str) {
        size_t size = len(str);
        size_t new_size = m_size + size;
        resize(new_size + 1);

        for(int i = 0; i < size; i++) {
            m_str[m_size + i] = str[i];
        }
        
        m_size = new_size;
        m_str[m_size] = '\0';
    }

public:

    String() {
        m_size = 0;
        m_str = new char[1];
        m_str[0] = '\0';
    }
    
    String(const char* str) {
        m_size = len(str);
        copy(str, m_size);
    }
    
    String(const String &other) {
        copy(other);
    }
    
    String& operator=(const String &other) {
        if(this != &other) {
            clear();
            copy(other);
        }
        return *this;
    }

    ~String() {
        clear();
    }

    void print() const{
        cout << m_str;
    }

    size_t size() const{
        return m_size;
    }

    bool empty() const{
        return !m_size;
    }

    void append(const char *str) {
        appendStr(str);
    }

    void append(const String &other) {
        appendStr(other.m_str);
    }

    String substring(size_t start, size_t len) const{
        if(start >= m_size) {
            return String();
        }
        if(start + len >= m_size) {
            return String(m_str + start);
        }

        String newStr;

        newStr.m_size = len;
        newStr.m_str = new char[len + 1];

        for(int i = 0; i < len; i++) {
            newStr.m_str[i] = m_str[start + i];
        }
        
        newStr.m_str[len] = '\0';
        return newStr;
    }

    const char* getCString()const{
        return m_str;
    }
};

int main(){
    String s("abc");
    s.print();
    cout << s.size() << endl;   // 3
    cout << s.empty() << endl;  // 0
    s.append("def");
    s.print();                  // abcdef
    cout << s.size() << endl;   // 6
    cout << s.empty() << endl;  // 0
    String s2("xyz");
    s.append(s2);
    s.print();                  // abcdefxyz
    cout << s.size() << endl;   // 9
    cout << s.empty() << endl;  // 0
    String s3 = s.substring(3, 4);
    s3.print();                 // defx
    cout << s3.size() << endl;  // 4
    cout << s3.empty() << endl; // 0
    const char* cstr = s3.getCString();
    // cstr[0] = 'D';
    return 0;
}