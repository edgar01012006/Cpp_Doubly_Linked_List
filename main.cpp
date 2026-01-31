#include <iostream>
#include <string>
#include <cassert>
#include "list.hpp"

void test_title(const std::string& title) {
    std::cout << "\n--- Testing: " << title << " ---" << std::endl;
}

int main() {
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
    list<int> original {100, 200, 300};
    list<int> copy_cat = original;
    copy_cat.push_back(400);
    std::cout << "Original: "; original.print();
    std::cout << "Copy:     "; copy_cat.print();

    // 4. Assignment Operator Overwrite
    test_title("Assignment Overwriting Existing Data");
    list<int> heavy {1, 2, 3, 4, 5};
    list<int> small {99};
    heavy = small; 
    std::cout << "Heavy (now small): "; heavy.print();
    std::cout << "New Size: " << heavy.size() << std::endl;

    // 5. Move Semantics & Null States
    test_title("Move Semantics (Self-Assignment & State)");
    list<int> move_source {10, 20, 30};
    list<int> move_dest = std::move(move_source);
    std::cout << "Destination: "; move_dest.print();
    std::cout << "Source (should be empty): " << (move_source.empty() ? "Yes" : "No") << std::endl;

    // 6. Exception Robustness
    test_title("Exception Handling");
    list<std::string> str_list;
    try {
        str_list.pop_front();
    } catch (const empty_list_exception& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }

    // 7. Template Flexibility
    test_title("Template Type: std::string");
    list<std::string> words {"Hello", "linked", "list"};
    words.push_back("world");
    words.print();

    std::cout << "\n--- All custom tests completed ---" << std::endl;

    return 0;
}