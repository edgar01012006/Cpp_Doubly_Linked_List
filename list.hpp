#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <initializer_list>

#include "list_exception.hpp"

template<typename T>
class list {
    private:
        struct Node {
            public:
                T m_data;
                Node* m_next;
                Node* m_prev;

            public:
                Node(T value = T{}, Node* next = nullptr, Node* prev = nullptr) 
                    : m_data { value }, m_next { next }, m_prev { prev } {}
        };
    
    private:
        Node* m_head;
        Node* m_tail;
        size_t m_size;

    public:
        list();
        list(const list& other);
        list& operator=(const list& other);
        list(list&& other) noexcept;
        list& operator=(list&& other) noexcept;
        list(std::initializer_list<T> init);
        ~list();

        // Capacity
        bool empty() const;
        size_t size() const;

        // Modifiers
        void push_back(const T& value);
        void pop_back();

        void push_front(const T& value);
        void pop_front();

        void clear();

        // Non-member functions
        template<typename U>
        friend void swap(U& lhs, U& rhs);

        // Operations
        void merge(list& other);
        void sort();
        void reverse();
        void unique();

        // miscellaneous
        void print() const;
};

template<typename T>
list<T>::list()
    : m_head { nullptr }, m_tail { nullptr }, m_size {} {}

template<typename T>
list<T>::list(const list& other)
    : m_head { nullptr }, m_tail { nullptr }, m_size {} {
    Node* otherHead = other.m_head;
    for (size_t i = 0; i < other.m_size; ++i) {
        this->push_back(otherHead->m_data);
        otherHead = otherHead->m_next;
    }
}

template<typename T>
list<T>& list<T>::operator=(const list& other) {
    if (this != &other) {
        this->clear();
        Node* otherHead = other.m_head;
        for (size_t i = 0; i < other.m_size; ++i) {
            this->push_back(otherHead->m_data);
            otherHead = otherHead->m_next;
        }
    }
    return *this;
}

template<typename T>
list<T>::list(list&& other) noexcept
    : m_head { other.m_head }, m_tail { other.m_tail }, m_size { other.m_size } {
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template<typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
    if (this != &other) {
        this->clear();
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }
    return *this;
}

template<typename T>
list<T>::list(std::initializer_list<T> init) 
    : m_head { nullptr }, m_tail { nullptr }, m_size {} {
    for (auto i : init) {
        this->push_back(i);
    }
}

template<typename T>
list<T>::~list() {
    clear();
}



// Capacity
template<typename T>
bool list<T>::empty() const {
    return !m_size;
}

template<typename T>
size_t list<T>::size() const {
    return m_size;
}


// Modifiers
template<typename T>
void list<T>::push_back(const T& value) {
    if (empty() == true) {
        m_head = new Node(value);
        m_tail = m_head;
    }
    else if (m_head == m_tail) {
        m_tail = new Node(value, nullptr, m_head);
        m_head->m_next = m_tail;
    }
    else {
        Node* prev = m_tail;
        m_tail = new Node(value, nullptr, prev);
        prev->m_next = m_tail;
    }
    ++m_size;
}

template<typename T>
void list<T>::pop_back() {
    if (empty() == true) {
        throw empty_list_exception("empty list");
    }
    else if (m_head == m_tail) {
        delete m_head;
        m_head = m_tail = nullptr;
    }
    else {
        Node* tail = m_tail;
        m_tail = m_tail->m_prev;
        delete tail;
        m_tail->m_next = nullptr;
    }
    --m_size;
}

template<typename T>
void list<T>::push_front(const T& value) {
    if (empty() == true) {
        m_head = new Node(value);
        m_tail = m_head;
    }
    else if (m_head == m_tail) {
        m_head = new Node(value, m_tail, nullptr);
        m_tail->m_prev = m_head;
    }
    else {
        Node* head = m_head;
        m_head = new Node(value, head, nullptr);
        head->m_prev = m_head;
    }
    ++m_size;
} 

template<typename T>
void list<T>::pop_front() {
    if (empty() == true) {
        throw empty_list_exception("empty list");
    }
    else if (m_head == m_tail) {
        delete m_head;
        m_head = m_tail = nullptr;
    }
    else {
        Node* head = m_head;
        m_head = m_head->m_next;
        delete head;
        m_head->m_prev = nullptr;
    }
    --m_size;
}

template<typename T>
void list<T>::clear() {
    Node* head = m_head;
    for (size_t i = 0; i < m_size; ++i) {
        m_head = m_head->m_next;
        delete head;
        head = m_head;
    }
    m_head = m_tail = nullptr;
    m_size = 0;
}



// Non-member functions
template<typename U>
void swap(U& lhs, U& rhs) {
    U tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}



// Operations
template<typename T>
void list<T>::merge(list<T>& other) {
    if (this == &other) {
        return;
    }
    else if (other.empty()) {
        return;
    }
    else if (this->empty()) {
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;
    }
    else {
        m_tail->m_next = other.m_head;
        other.m_head->m_prev = m_tail;
        m_tail = other.m_tail;
        m_size += other.m_size;
        this->sort();
    }
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template<typename T>
void list<T>::reverse() {
    if (empty()) {
        throw empty_list_exception("empty list");
    }
    Node* head = m_head;
    Node* tail = m_tail;
    for (size_t i = 0; i < m_size / 2; ++i) {
        swap(head->m_data, tail->m_data);
        head = head->m_next;
        tail = tail->m_prev;
    }
}

template<typename T>
void list<T>::sort() {
    if (empty()) {
        throw empty_list_exception("empty list");
    }
    for (size_t i = 0; i < m_size - 1; ++i) {
        Node* head = m_head;  
        for (size_t j = 0; j < m_size - i - 1; ++j) {
            if (head->m_data > head->m_next->m_data) {
                swap(head->m_data, head->m_next->m_data);
            }
            head = head->m_next;
        }
    }
}

template<typename T>
void list<T>::unique() {

}



// miscellaneous
template<typename T>
void list<T>::print() const {
    Node* head = m_head;
    while (head != nullptr) {
        std::cout << head->m_data << " ";
        head = head->m_next;
    }
    std::cout << std::endl;
}

#endif