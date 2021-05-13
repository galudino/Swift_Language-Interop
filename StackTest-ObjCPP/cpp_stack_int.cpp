//
//  cpp_stack_int.cpp
//  StackTest-ObjCPP
//
//  Created by Gemuele Aludino on 5/13/21.
//

#include "cpp_stack_int.hpp"

#include <memory>
#include <algorithm>
#include <iostream>

using cpp::stack;

stack::stack(size_t capacity) {
    auto *start = new int[capacity];
    
    m_start = m_finish = start;
    m_end_of_storage = start + capacity;
}

stack::stack(const stack &s) {
    auto *start = new int[s.capacity()];
    
    std::copy(s.m_start, s.m_finish, start);
    
    m_finish = m_start + s.size();
    m_end_of_storage = m_start + s.capacity();
}

stack::stack(stack &&s) :
    m_start(std::exchange(s.m_start, nullptr)),
    m_finish(std::exchange(s.m_finish, nullptr)),
    m_end_of_storage(std::exchange(s.m_end_of_storage, nullptr)) {
}

void stack::push(int val) {
    if (!m_start) {
        auto *start = new int[DEFAULT_CAPACITY];
        
        m_start = m_finish = start;
        m_end_of_storage = start + DEFAULT_CAPACITY;
    }
    
    if (size() == capacity()) {
        resize(capacity(), capacity() * 2);
    }
    
    *(m_finish++) = val;
}

void stack::clear() {
    std::fill(m_start, m_finish, 0);
    m_finish = m_start;
}

stack &stack::operator=(const stack &s) {
    auto *new_start = new int[s.capacity()];
    
    delete m_start;
    
    std::copy(s.m_start, s.m_finish, new_start);
    
    m_start = new_start;
    return *this;
}

stack &stack::operator=(stack &&s) {
    m_start = std::exchange(s.m_start, nullptr);
    m_finish = std::exchange(s.m_finish, nullptr);
    m_end_of_storage = std::exchange(s.m_end_of_storage, nullptr);
    
    return *this;
}

void stack::resize(size_t old_capacity, size_t new_capacity) {
    if (old_capacity == new_capacity) { return; }
    
    auto *new_start = new int[new_capacity];
    delete m_start;
    
    if (old_capacity < new_capacity) {
        std::copy(m_start, m_finish, new_start);
        
        m_start = new_start;
        m_finish = m_start + old_capacity;
        m_end_of_storage = m_start + new_capacity;
    } else {
        std::copy(m_start, m_start + new_capacity, new_start);
        
        m_start = new_start;
        m_finish = m_end_of_storage = m_start + new_capacity;
    }
}
