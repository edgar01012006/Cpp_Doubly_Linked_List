#include <iostream>
#include <string>
#include <cassert>
#include "list.hpp"

void test_title(const std::string &title)
{
    std::cout << "\n--- Testing: " << title << " ---" << std::endl;
}

int main()
{
    // 1. Stress Testing Basic Modifiers
    test_title("Edge Case Modifiers");
    list<int> l;
    l.push_front(10); // First element
    l.push_back(20);  // Second element
    l.pop_front();    // Back to one element
    l.pop_back();     // Back to empty
    std::cout << "Empty after toggle: " << (l.empty() ? "Yes" : "No") << " (Size: " << l.size() << ")" << std::endl;

    // 2. Comprehensive Pointer Integrity
    test_title("Pointer Consistency (Front & Back)");
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.print(); // Expected: 1 2 3
    l.pop_front();
    l.push_front(0);
    l.print(); // Expected: 0 2 3
    std::cout << "Current Size: " << l.size() << std::endl;

    // 3. Deep Copy Integrity
    test_title("Deep Copy & Independence");
    list<int> original{100, 200, 300};
    list<int> copy_cat = original;
    copy_cat.push_back(400);
    std::cout << "Original: ";
    original.print();
    std::cout << "Copy:     ";
    copy_cat.print();

    // 4. Assignment Operator Overwrite
    test_title("Assignment Overwriting Existing Data");
    list<int> heavy{1, 2, 3, 4, 5};
    list<int> small{99};
    heavy = small;
    std::cout << "Heavy (now small): ";
    heavy.print();
    std::cout << "New Size: " << heavy.size() << std::endl;

    // 5. Move Semantics & Null States
    test_title("Move Semantics (Self-Assignment & State)");
    list<int> move_source{10, 20, 30};
    list<int> move_dest = std::move(move_source);
    std::cout << "Destination: ";
    move_dest.print();
    std::cout << "Source (should be empty): " << (move_source.empty() ? "Yes" : "No") << std::endl;

    // 6. Exception Robustness
    test_title("Exception Handling");
    list<std::string> str_list;
    try
    {
        str_list.pop_front();
    }
    catch (const empty_list_exception &e)
    {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }

    // 7. Template Flexibility
    test_title("Template Type: std::string");
    list<std::string> words{"Hello", "linked", "list"};
    words.push_back("world");
    words.print();

    // 8. Sort Basic Integers
    test_title("Sort: Integers");
    list<int> nums{4, 2, 5, 1, 3};
    nums.sort();
    nums.print();

    // 9. Sort Already Sorted
    test_title("Sort: Already Sorted");
    list<int> sorted{1, 2, 3, 4, 5};
    sorted.sort();
    sorted.print();

    // 10. Sort Reverse Order
    test_title("Sort: Reverse Order");
    list<int> rev{5, 4, 3, 2, 1};
    rev.sort();
    rev.print();

    // 11. Sort Single Element
    test_title("Sort: Single Element");
    list<int> single{42};
    single.sort();
    single.print();

    // 12. Sort std::string
    test_title("Sort: std::string");
    list<std::string> str_sort{"banana", "apple", "cherry"};
    str_sort.sort();
    str_sort.print();

    // 13. Non-member swap
    test_title("Non-member swap");
    int a = 1;
    int b = 2;
    swap(a, b);
    std::cout << a << " " << b << std::endl;

    // 14. Sorting an empty list
    test_title("Sort: Empty List");
    list<int> empty_list;
    try
    {
        empty_list.sort();  // Currently your sort() might underflow m_size - 1
        empty_list.print(); // Should print nothing
    }
    catch (const empty_list_exception &e)
    {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }

    // 15. Merge Two Non-Empty Lists
    test_title("Merge: Normal Lists");
    list<int> l1{1, 3, 5};
    list<int> l2{2, 4, 6};
    l1.merge(l2);
    std::cout << "Merged List: ";
    l1.print(); // Expected sorted: 1 2 3 4 5 6
    std::cout << "Second list empty? " << (l2.empty() ? "Yes" : "No") << std::endl;

    // 16. Merge Empty List into Non-Empty List
    test_title("Merge: Empty into Non-Empty");
    list<int> l3{10, 20};
    list<int> l4;
    l3.merge(l4);
    std::cout << "Merged List: ";
    l3.print(); // Expected: 10 20
    std::cout << "Second list empty? " << (l4.empty() ? "Yes" : "No") << std::endl;

    // 17. Merge Non-Empty List into Empty List
    test_title("Merge: Non-Empty into Empty");
    list<int> l5;
    list<int> l6{7, 8, 9};
    l5.merge(l6);
    std::cout << "Merged List: ";
    l5.print(); // Expected: 7 8 9
    std::cout << "Second list empty? " << (l6.empty() ? "Yes" : "No") << std::endl;

    // 18. Merge List with Itself (should do nothing)
    test_title("Merge: Self Merge");
    list<int> l7{1, 2, 3};
    l7.merge(l7);
    std::cout << "After Self Merge: ";
    l7.print(); // Expected: 1 2 3

    // 19. Reverse a normal list
    test_title("Reverse: Normal List");
    list<int> rev1{1, 2, 3, 4, 5};
    rev1.reverse();
    rev1.print(); // Expected: 5 4 3 2 1

    // 20. Reverse a single element list
    test_title("Reverse: Single Element");
    list<int> rev2{42};
    rev2.reverse();
    rev2.print(); // Expected: 42

    // 21. Reverse an already reversed list
    test_title("Reverse: Already Reversed");
    rev1.reverse(); // reverse back
    rev1.print();   // Expected: 1 2 3 4 5

    // 22. Reverse an empty list (should throw)
    test_title("Reverse: Empty List");
    list<int> rev_empty;
    try
    {
        rev_empty.reverse();
    }
    catch (const empty_list_exception &e)
    {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }

    // 23. Reverse with even number of elements
    test_title("Reverse: Even Number of Elements");
    list<int> rev_even{10, 20, 30, 40};
    rev_even.reverse();
    rev_even.print(); // Expected: 40 30 20 10

    // 24. Reverse with strings
    test_title("Reverse: std::string");
    list<std::string> rev_str{"one", "two", "three"};
    rev_str.reverse();
    rev_str.print(); // Expected: three two one

    // 25. Unique: Sorted list with duplicates
    test_title("Unique: Sorted List with Duplicates");
    list<int> u1{1, 1, 2, 2, 2, 3, 3, 4};
    u1.unique();
    u1.print(); // Expected: 1 2 3 4

    // 26. Unique: Already Unique
    test_title("Unique: Already Unique");
    list<int> u2{1, 2, 3, 4, 5};
    u2.unique();
    u2.print(); // Expected: 1 2 3 4 5

    // 27. Unique: All Same Elements
    test_title("Unique: All Same Elements");
    list<int> u3{7, 7, 7, 7, 7};
    u3.unique();
    u3.print(); // Expected: 7

    // 28. Unique: Single Element
    test_title("Unique: Single Element");
    list<int> u4{42};
    u4.unique();
    u4.print(); // Expected: 42

    // 29. Unique: Empty List (should throw)
    test_title("Unique: Empty List");
    list<int> u5;
    try
    {
        u5.unique();
    }
    catch (const empty_list_exception &e)
    {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }

    // 30. Unique: std::string
    test_title("Unique: std::string");
    list<std::string> u6{"apple", "apple", "banana", "banana", "cherry"};
    u6.unique();
    u6.print(); // Expected: apple banana cherry

    // 31. Unique: Sort + Unique (common usage)
    test_title("Unique: Sort + Unique");
    list<int> u7{3, 1, 2, 3, 2, 1, 1};
    u7.sort();
    u7.unique();
    u7.print(); // Expected: 1 2 3


    std::cout << "\n--- All custom tests completed ---" << std::endl;

    return 0;
}