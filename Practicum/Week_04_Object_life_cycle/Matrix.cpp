#include <iostream>

using namespace std;

class Matrix{

private:
    void dealllocate(){
        for(size_t i = 0; i < m_rows; i++){
            delete[] m_matrix[i];
        }
        delete[] m_matrix;
    }

    void allocate(size_t rows, size_t cols){
        m_matrix = new int*[rows];
        for(size_t i = 0; i < rows; i++){
            m_matrix[i] = new int[cols];
        }
    }

    void copy(int** other){
        for(size_t i = 0; i < m_rows; i++)
        {
            for(size_t j = 0; j < m_cols; j++){
                m_matrix[i][j] = other[i][j];
            }
        }
    }

    void fill(int value){
        for(size_t i = 0; i < m_rows; i++)
        {
            for(size_t j = 0; j < m_cols; j++){
                m_matrix[i][j] = value;
            }
        }
    }

public:

    Matrix(size_t n){
        m_rows = n;
        m_cols = n;
        allocate(n, n);
    }
    
    Matrix(size_t rows, size_t cols){
        m_rows = rows;
        m_cols = cols;
        allocate(rows, cols);
    }

    Matrix(size_t rows, size_t cols, int value){
        m_rows = rows;
        m_cols = cols;
        allocate(rows, cols);
        fill(value);
    }
    
    Matrix(const Matrix& other){
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        allocate(m_rows, m_cols);
        copy(other.m_matrix);
    }
    
    Matrix& operator=(const Matrix& other){
        if(this != &other){
            dealllocate();
            m_rows = other.m_rows;
            m_cols = other.m_cols;
            allocate(m_rows, m_cols);
            copy(other.m_matrix);
        }
        return *this;
    }

    ~Matrix(){
        dealllocate();
    }

    bool isSquare()const{
        return m_rows == m_cols;
    }

    bool isIdentity()const{
        if(!isSquare()){
            return false;
        }

        for(size_t i = 0; i < m_rows; i++)
        {
            for(size_t j = 0; j < m_cols; j++){
                
                if(i == j && m_matrix[i][j] != 1)
                    return false;

                if( i != j && m_matrix[i][j] != 0)
                    return false;
            }
        }
        
        return true;
    }

    Matrix add(const Matrix& other) const{

        if(m_rows != other.m_rows || m_cols != other.m_cols){
            throw invalid_argument("Matrices must have the same dimensions");
        }

        Matrix result(m_rows, m_cols);
        for(size_t i = 0; i < m_rows; i++)
        {
            for(size_t j = 0; j < m_cols; j++){
                result.m_matrix[i][j] = m_matrix[i][j] + other.m_matrix[i][j];
            }
        }   

        return result;
    }

    Matrix subtract(const Matrix& other) const{
        
        if(m_rows != other.m_rows || m_cols != other.m_cols){
            throw invalid_argument("Matrices must have the same dimensions");
        }

        Matrix result(m_rows, m_cols);
        for(size_t i = 0; i < m_rows; i++)
        {
            for(size_t j = 0; j < m_cols; j++){
                result.m_matrix[i][j] = m_matrix[i][j] - other.m_matrix[i][j];
            }
        }   

        return result;
    }

    bool canMultiply(const Matrix& other)const{
        return m_cols == other.m_rows;
    }   

    Matrix multiply(const Matrix& other) const{
        if(!canMultiply(other)){
            cout<<"Invalid multiplication"<<endl;
            return Matrix(0, 0);
        }

        Matrix result(m_rows, other.m_cols);
        for(size_t i = 0; i < m_rows; i++)
        {
            for(size_t j = 0; j < other.m_cols; j++)
            {
                for(size_t k = 0; k < m_cols; k++){
                    result.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
                }
            }
        }   

        return result;
    }

    Matrix transpose() const{
        Matrix result(m_cols, m_rows);
        for(size_t i = 0; i < m_rows; i++)
        {
            for(size_t j = 0; j < m_cols; j++){
                result.m_matrix[j][i] = m_matrix[i][j];
            }
        }   

        return result;
    }

    bool isOrtogonal() const{
        if(!isSquare())
            return false;
        
        return this->multiply(this->transpose()).isIdentity();
    }
    
private:
    size_t m_rows;
    size_t m_cols;
    int **m_matrix;   

};
