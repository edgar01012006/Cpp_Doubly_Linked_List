#include <iostream>
#include <string>
#include "list.hpp"

void test_title(const std::string& title)
{
    std::cout << "\n========== " << title << " ==========\n";
}

/* -------------------------------------------------- */
/* BASIC MODIFIER TESTS */
/* -------------------------------------------------- */

void test_basic_modifiers()
{
    test_title("Basic Modifiers");

    list<int> l;

    l.push_front(10);
    l.push_back(20);
    l.pop_front();
    l.pop_back();

    std::cout << "Empty after push/pop cycle: "
              << (l.empty() ? "Yes" : "No")
              << " | Size: " << l.size() << "\n";
}

/* -------------------------------------------------- */
/* POINTER INTEGRITY */
/* -------------------------------------------------- */

void test_pointer_integrity()
{
    test_title("Pointer Integrity");

    list<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    std::cout << "Initial: ";
    l.print();

    l.pop_front();
    l.push_front(0);

    std::cout << "Modified: ";
    l.print();

    std::cout << "Size: " << l.size() << "\n";
}

/* -------------------------------------------------- */
/* ERASE TEST */
/* -------------------------------------------------- */

void test_erase_middle()
{
    test_title("Erase Middle");

    list<int> l{10, 20, 30, 40};

    auto it = l.begin();
    ++it; // points to 20

    l.erase(it);

    std::cout << "After erasing 20: ";
    l.print();

    std::cout << "Size: " << l.size() << "\n";
}

/* -------------------------------------------------- */
/* REVERSE ITERATION */
/* -------------------------------------------------- */

void test_reverse_iteration()
{
    test_title("Reverse Iteration");

    list<int> l{1, 2, 3, 4};

    for (auto it = l.rbegin(); it != l.rend(); ++it)
        std::cout << *it << " ";

    std::cout << "\n";
}

/* -------------------------------------------------- */
/* CONST ITERATION */
/* -------------------------------------------------- */

void test_const_iteration()
{
    test_title("Const Iteration");

    const list<int> l{5, 6, 7};

    for (const auto& v : l)
        std::cout << v << " ";

    std::cout << "\n";
}

/* -------------------------------------------------- */
/* COPY & ASSIGNMENT */
/* -------------------------------------------------- */

void test_copy_semantics()
{
    test_title("Copy Constructor");

    list<int> original{100, 200, 300};
    list<int> copy = original;

    copy.push_back(400);

    std::cout << "Original: ";
    original.print();

    std::cout << "Copy:     ";
    copy.print();
}

void test_assignment_operator()
{
    test_title("Copy Assignment");

    list<int> heavy{1, 2, 3, 4, 5};
    list<int> small{99};

    heavy = small;

    std::cout << "After assignment: ";
    heavy.print();

    std::cout << "Size: " << heavy.size() << "\n";
}

/* -------------------------------------------------- */
/* MOVE SEMANTICS */
/* -------------------------------------------------- */

void test_move_semantics()
{
    test_title("Move Semantics");

    list<int> source{10, 20, 30};
    list<int> destination = std::move(source);

    std::cout << "Destination: ";
    destination.print();

    std::cout << "Source empty? "
              << (source.empty() ? "Yes" : "No")
              << "\n";
}

/* -------------------------------------------------- */
/* TEMPLATE FLEXIBILITY */
/* -------------------------------------------------- */

void test_string_type()
{
    test_title("Template Type: std::string");

    list<std::string> words{"Hello", "linked", "list"};
    words.push_back("world");

    words.print();
}

/* -------------------------------------------------- */
/* EDGE CASES */
/* -------------------------------------------------- */

void test_empty_operations()
{
    test_title("Empty List Safety");

    list<std::string> l;

    l.pop_front();
    l.pop_back();

    std::cout << "No crash on empty pop\n";
}

/* -------------------------------------------------- */
/* MAIN */
/* -------------------------------------------------- */

int main()
{
    test_basic_modifiers();
    test_pointer_integrity();
    test_erase_middle();
    test_reverse_iteration();
    test_const_iteration();
    test_copy_semantics();
    test_assignment_operator();
    test_move_semantics();
    test_string_type();
    test_empty_operations();

    std::cout << "\n========== All Tests Completed ==========\n";

    return 0;
}