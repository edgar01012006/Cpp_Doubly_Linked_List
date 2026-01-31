# 🔗 Doubly Linked List (C++ Template)

## 1. Project Overview

The **Doubly Linked List** is a custom-built, template-based C++ container designed for efficient bidirectional data traversal.  
It focuses on **manual memory management** and strict adherence to the **Rule of Five**, ensuring safety and performance when copying or moving list resources.

This project serves as a demonstration of **template programming**, **low-level pointer manipulation**, and modern C++ resource management techniques.

---

## 2. Features

### Efficient Bidirectional Traversal
- **Doubly Linked Structure**: Each node maintains links to both previous and next elements, allowing `O(1)` insertions and deletions at both ends.
- **Generic Design**: Implemented as a template class, supporting primitive types as well as complex user-defined objects.

### Resource Management
- **Rule of Five**: Custom copy/move constructors and assignment operators ensure deep copying and safe resource transfers.
- **Zero Memory Leaks**: Guaranteed through a robust destructor and a comprehensive `clear()` mechanism.

### Robust Error Handling
- **Custom Exception Hierarchy**: Dedicated `list_exception` and `empty_list_exception` classes provide precise error reporting for invalid operations.

---

## 3. Project Structure

```text
linked-list/
├── list.hpp               # Template header and implementation
├── list_exception.hpp     # Custom exception hierarchy
├── main.cpp               # Comprehensive test suite
└── README.md              # Project documentation
```

### Key Components
- **Node Structure**: Private internal struct managing `m_data`, `m_next`, and `m_prev`.
- **Modifiers**: Full support for `push_back`, `push_front`, `pop_back`, and `pop_front`.
- **Move Semantics**: Optimized assignment operators using `std::move` to eliminate unnecessary allocations.

---

## 4. Build & Run Instructions

### Build the Project
Since the container is template-based (header-only), compile the test file directly:

```bash
g++ -std=c++17 main.cpp -o ListTest
```

### Run the Program
```bash
./ListTest
```

### Clean Compiled Files
```bash
rm ListTest
```