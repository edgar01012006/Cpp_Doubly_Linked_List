#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <utility>

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

                // template<typename... Args>
                // Node(Node* next = nullptr, Node* prev = nullptr, Args&&... args)
                //     : m_next { next }, m_prev { prev }, m_data { std::forward<Args>(args)... } {}
        };

    public:
        struct iterator {
            friend class list;
            private:
                Node* m_current;

            public:
                iterator(Node* current) : m_current { current } {}

                bool operator!=(const iterator& other) const {
                    return this->m_current != other.m_current;
                }
                
                bool operator==(const iterator& other) const {
                    return this->m_current == other.m_current;
                }

                iterator& operator++() {
                    m_current = m_current->m_next;
                    return *this;
                }

                iterator& operator--() {
                    m_current = m_current->m_prev;
                    return *this;
                }

                T& operator*() const {
                    return m_current->m_data;
                }
        };

        struct const_iterator {
            friend class list;
            private:
                const Node* m_current;

            public:
                const_iterator(const Node* current) : m_current { current } {}

                bool operator!=(const const_iterator& other) const {
                    return this->m_current != other.m_current;
                }

                bool operator==(const const_iterator& other) const {
                    return this->m_current == other.m_current;
                }

                const_iterator& operator++() {
                    m_current = m_current->m_next;
                    return *this;
                }

                const_iterator& operator--() {
                    m_current = m_current->m_prev;
                    return *this;
                }

                const T& operator*() const {
                    return m_current->m_data;
                }
        };

        struct reverse_iterator {
            friend class list;
            private:
                iterator m_iterator;
            
            public:
                reverse_iterator(Node* current) : m_iterator { current } {}

                bool operator!=(const reverse_iterator& other) const {
                    return (m_iterator != other.m_iterator);
                }
                
                bool operator==(const reverse_iterator& other) const {
                    return (m_iterator == other.m_iterator);
                }

                reverse_iterator& operator++() {
                    --(m_iterator);
                    return *this;
                }

                reverse_iterator& operator--() {
                    ++(m_iterator);
                    return *this;
                }

                T& operator*() const {
                    auto tmp = m_iterator;
                    --tmp;
                    return *tmp;
                }
        };

        struct const_reverse_iterator {
            friend class list;
            private:
                const_iterator m_const_iterator;

            public:
                const_reverse_iterator(const Node* current) : m_const_iterator { current } {}

                bool operator!=(const const_reverse_iterator& other) const {
                    return (this->m_const_iterator != other.m_const_iterator);
                }

                bool operator==(const const_reverse_iterator& other) const {
                    return (this->m_const_iterator == other.m_const_iterator);
                }

                const_reverse_iterator& operator++() {
                    --(m_const_iterator);
                    return *this;
                }

                const_reverse_iterator& operator--() {
                    ++(m_const_iterator);
                    return *this;
                }

                const T& operator*() const {
                    auto tmp = m_const_iterator;
                    --tmp;
                    return *tmp;
                }
        };
    
    private:
        Node* m_sentinel;
        size_t m_size;

    public:
        list();
        list(const list& other);
        list& operator=(const list& other);
        list(list&& other) noexcept;
        list& operator=(list&& other) noexcept;
        list(std::initializer_list<T> init);
        ~list();

        // iterators
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const noexcept;

        iterator end();
        const_iterator end() const;
        const_iterator cend() const noexcept;

        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator crbegin() const noexcept;

        reverse_iterator rend();
        const_reverse_iterator rend() const;
        const_reverse_iterator crend() const noexcept;


        // Capacity
        bool empty() const;
        size_t size() const;

        // Modifiers
        iterator insert(iterator pos, const T& value);
        iterator erase(iterator pos);     

        void push_back(const T& value);
        void pop_back();

        void push_front(const T& value);
        void pop_front();

        void clear();

        // template<typename... Args>
        // void emplace_back(Args&&... args);

        // // Non-member functions
        // template<typename U>
        // friend void swap(U& lhs, U& rhs);

        // // Operations
        // void merge(list& other);
        // void sort();
        // void reverse();
        // void unique();

        // miscellaneous
        void print() const;
};

template<typename T>
list<T>::list()
    : m_sentinel { new Node{} }, m_size {} {
    m_sentinel->m_next = m_sentinel;
    m_sentinel->m_prev = m_sentinel;
}

template<typename T>
list<T>::list(const list& other)
    : m_sentinel { new Node{} }, m_size {} {
    m_sentinel->m_next = m_sentinel;
    m_sentinel->m_prev = m_sentinel;

    for (const auto& i: other) {
        this->push_back(i);
    }
}

template<typename T>
list<T>& list<T>::operator=(const list& other) {
    if (this != &other) {
        this->clear();
        for (const auto& i: other) {
            this->push_back(i);
        }
    }
    return *this;
}

template<typename T>
list<T>::list(list&& other) noexcept
    : m_sentinel { other.m_sentinel }, m_size { other.m_size } {
    other.m_sentinel = new Node{};
    other.m_sentinel->m_next = other.m_sentinel;
    other.m_sentinel->m_prev = other.m_sentinel;
    other.m_size = 0;
}

template<typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
    if (this != &other) {
        this->clear();
        delete m_sentinel;

        m_sentinel = other.m_sentinel;
        m_size = other.m_size;

        other.m_sentinel = new Node{};
        other.m_sentinel->m_next = other.m_sentinel;
        other.m_sentinel->m_prev = other.m_sentinel;
        other.m_size = 0;
    }
    return *this;
}

template<typename T>
list<T>::list(std::initializer_list<T> init) 
    : m_sentinel { new Node{} }, m_size {} {
    m_sentinel->m_next = m_sentinel;
    m_sentinel->m_prev = m_sentinel;

    for (const auto& i : init) {
        this->push_back(i);
    }
}

template<typename T>
list<T>::~list() {
    clear();
    delete m_sentinel;
}



// iterators
template <typename T>
typename list<T>::iterator list<T>::begin() {
    return list<T>::iterator(m_sentinel->m_next);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
    return list<T>::const_iterator(m_sentinel->m_next);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const noexcept {
    return list<T>::const_iterator(m_sentinel->m_next);
}



template <typename T>
typename list<T>::iterator list<T>::end() {
    return list<T>::iterator(m_sentinel);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
    return list<T>::const_iterator(m_sentinel);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const noexcept {
    return list<T>::const_iterator(m_sentinel);
}



template <typename T>
typename list<T>::reverse_iterator list<T>::rbegin() {
    return list<T>::reverse_iterator(m_sentinel);
}

template <typename T>
typename list<T>::const_reverse_iterator list<T>::rbegin() const {
    return list<T>::const_reverse_iterator(m_sentinel);
}

template <typename T>
typename list<T>::const_reverse_iterator list<T>::crbegin() const noexcept {
    return list<T>::const_reverse_iterator(m_sentinel);
}



template <typename T>
typename list<T>::reverse_iterator list<T>::rend() {
    return list<T>::reverse_iterator(m_sentinel->m_next);
}

template <typename T>
typename list<T>::const_reverse_iterator list<T>::rend() const {
    return list<T>::const_reverse_iterator(m_sentinel->m_next);
}

template <typename T>
typename list<T>::const_reverse_iterator list<T>::crend() const noexcept {
    return list<T>::const_reverse_iterator(m_sentinel->m_next);
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
template <typename T>
typename list<T>::iterator list<T>::insert(list<T>::iterator pos, const T& value) {
    Node* current = pos.m_current;

    Node* newNode = new Node(value, current, current->m_prev);

    current->m_prev->m_next = newNode;
    current->m_prev = newNode;

    ++m_size;

    return list<T>::iterator(newNode);
}

template <typename T>
typename list<T>::iterator list<T>::erase(list<T>::iterator pos) {
    if (empty() || pos == end()) { return end(); }
    Node* current = pos.m_current;

    current->m_prev->m_next = current->m_next;
    current->m_next->m_prev = current->m_prev;

    Node* tmp = current->m_next;

    delete current;

    --m_size;

    return list<T>::iterator(tmp);
}

template<typename T>
void list<T>::push_back(const T& value) {
    insert(this->end(), value);
}

template<typename T>
void list<T>::pop_back() {
    erase(--this->end());
}

template<typename T>
void list<T>::push_front(const T& value) {
    insert(this->begin(), value);
} 

template<typename T>
void list<T>::pop_front() {
    erase(this->begin());
}

template<typename T>
void list<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

// template<typename T>
// template<typename... Args>
// void list<T>::emplace_back(Args&&... args) {
//     if (empty() == true) {
//         m_head = new Node(nullptr, nullptr, std::forward<Args>(args)...);
//         m_tail = m_head;
//     }
//     else if (m_head == m_tail) {
//         m_tail = new Node(nullptr, m_head, std::forward<Args>(args)...);
//         m_head->m_next = m_tail;
//     }
//     else {
//         Node* prev = m_tail;
//         m_tail = new Node(nullptr, prev, std::forward<Args>(args)...);
//         prev->m_next = m_tail;
//     }
//     ++m_size;
// }



// // Non-member functions
// template<typename U>
// void swap(U& lhs, U& rhs) {
//     U tmp = lhs;
//     lhs = rhs;
//     rhs = tmp;
// }



// // Operations
// template<typename T>
// void list<T>::merge(list<T>& other) {
//     if (this == &other) {
//         return;
//     }
//     else if (other.empty()) {
//         return;
//     }

//     list<T> newList;

//     Node* head = m_head;
//     Node* otherHead = other.m_head;

//     for (size_t i = 0; i < m_size + other.m_size; ++i) {
//         if (head != nullptr && head->m_data <= otherHead->m_data) {
//             newList.push_back(head->m_data);
//             head = head->m_next;
//         }
//         else if (otherHead != nullptr) {
//             newList.push_back(otherHead->m_data);
//             otherHead = otherHead->m_next;
//         }
//     }

//     other.m_head = nullptr;
//     other.m_tail = nullptr;
//     other.m_size = 0;

//     this->operator=(std::move(newList));
// }

// template<typename T>
// void list<T>::reverse() {
//     if (empty()) {
//         throw empty_list_exception("empty list");
//     }

//     Node* head = m_head;
//     Node* tail = m_tail;

//     for (size_t i = 0; i < m_size / 2; ++i) {
//         Node* tmp_head_next = head->m_next;
//         head->m_next = head->m_prev;
//         head->m_prev = tmp_head_next;
//         head = head->m_prev;

//         Node* tmp_tail_next = tail->m_next;
//         tail->m_next = tail->m_prev;
//         tail->m_prev = tmp_tail_next;
//         tail = tail->m_next;
//     }

//     // for middle element, when the number of elements is odd
//     if (m_size % 2 != 0) {
//         Node* tmp_head_next = head->m_next;
//         head->m_next = head->m_prev;
//         head->m_prev = tmp_head_next;
//     }

//     Node* tmp_head = m_head;
//     m_head = m_tail;
//     m_tail = tmp_head;
// }

// template<typename T>
// void list<T>::sort() {
//     if (empty()) {
//         throw empty_list_exception("empty list");
//     }

//     for (size_t i = 0; i < m_size - 1; ++i) {
//         Node* head = m_head;  
//         for (size_t j = 0; j < m_size - i - 1; ++j) {
//             if (head->m_data > head->m_next->m_data) {
//                 swap(head->m_data, head->m_next->m_data);
//             }
//             head = head->m_next;
//         }
//     }
// }

// template<typename T>
// void list<T>::unique() {
//     if (empty()) {
//         throw empty_list_exception("empty list");
//     }
    
//     list<T> newList;

//     Node* head = m_head;

//     newList.push_back(head->m_data);
//     head = head->m_next;

//     Node* newHead = newList.m_head;

//     for (size_t i = 1; i < m_size; ++i) {
//         if (newHead->m_data != head->m_data) {
//             newList.push_back(head->m_data);
//             newHead = newHead->m_next;
//         }
//         head = head->m_next;
//     }

//     this->operator=(std::move(newList));
// }



// miscellaneous
template<typename T>
void list<T>::print() const {
    for (const auto& i: *this) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

#endif