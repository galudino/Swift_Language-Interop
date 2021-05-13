//
//  cpp_stack_int.hpp
//  StackTest-ObjCPP
//
//  Created by Gemuele Aludino on 5/13/21.
//

#ifndef CPP_STACK_INT_HPP
#define CPP_STACK_INT_HPP

#include <cstddef>

class stack {
public:
    stack() = default;
    
    stack(size_t capacity);
    
    stack(const stack &s);
    stack(stack &&s);
    
    ~stack() {
        delete m_start;
        m_start = m_finish = m_end_of_storage = nullptr;
    }
    
    void push(int val);
    
    void pop() {
        if (m_finish > m_start) {
            --m_finish;
        }
    }
    
    int top() const { return *(m_finish - 1); }
    bool empty() const { return m_finish == m_start; }
    
    void clear();
    
    stack &operator=(const stack &s);
    stack &operator=(stack &&s);
private:
    static constexpr auto DEFAULT_CAPACITY = 16;
    
    size_t capacity() const {
        return m_end_of_storage - m_start;
    }
    
    size_t size() const {
        return m_finish - m_start;
    }
    
    void resize(size_t old_capacity, size_t new_capacity);
    
    int *m_start;
    int *m_finish;
    int *m_end_of_storage;
};


#endif /* CPP_STACK_INT_HPP */
