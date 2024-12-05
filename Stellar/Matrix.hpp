#ifndef __STELLAR_MATRIX_HPP__
#define __STELLAR_MATRIX_HPP__
#include <cstdint>
#include <vector>
#include <iterator>
#include <cstddef>

/**
 * @todo make template specialization for built-in types for some optimization purposes
*/

template <typename _Ty> 
class Matrix {
private:
    using value_t     = _Ty;
    using pointer_t   = value_t*;  // or also value_type*
    using reference_t = value_t&;  // or also value_type&
    using size_t      = uint32_t;

public: //Iterator
struct Iterator 
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        
        Iterator(pointer_t ptr) : m_Ptr(ptr){}

        reference_t operator*() const { return *m_Ptr; }
        pointer_t operator->() { return m_Ptr; }

        // Prefix increment
        Iterator& operator++() { m_Ptr++; return *this; }  

        // Postfix increment
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_Ptr == b.m_Ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_Ptr != b.m_Ptr; };  

        Iterator begin() { return Iterator(m_Ptr->begin()); }
        Iterator end()   { return Iterator(m_Ptr->end()); }
        
        private:
        pointer_t m_Ptr;
    };
public:
    Matrix(size_t width, size_t height) : m_Width(width),m_Height(height),m_Size(width*height){
        m_Matrix.reserve(width * height);
        m_Matrix.resize(width * height,value_t());
    }

    ~Matrix(){

    }

    void SetValueAt(uint32_t row,uint32_t index, const value_t& value){
        m_Matrix[row * m_Width + index] = value;
    }

    reference_t GetValueAt(uint32_t row, uint32_t index){
        return m_Matrix[row * m_Width + index];
    }
    
    reference_t GetValueAt(uint32_t row, uint32_t index) const{
        return m_Matrix[row * m_Width + index];
    }
    
    std::vector<value_t>& GetMatrix() const {return m_Matrix;}

    Iterator begin() { return Iterator(&m_Matrix[0]); }
    Iterator end()   { return Iterator(&m_Matrix[m_Size]); }
    
    size_t Size() const {return m_Size;}
    size_t Width() const {return m_Width;}
    size_t Height() const {return m_Height;}
private:
  std::vector<value_t> m_Matrix;
  size_t m_Width,m_Height;
  size_t m_Size;
};

#endif //! __STELLAR_MATRIX_HPP__