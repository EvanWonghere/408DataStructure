#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <stdexcept> // For std::out_of_range
#include <algorithm> // For std::equal, std::reverse_copy
#include <list>      // For comparison in some iterator tests

// Assuming these files are in the same directory or accessible by include paths
// and they include their .tpp files correctly if implementations are separate.
#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"

// Helper function to print test section headers
void print_header(const std::string& header) {
    std::cout << "\n========================================\n";
    std::cout << "    Testing: " << header << "\n";
    std::cout << "========================================\n";
}

void print_subheader(const std::string& subheader) {
    std::cout << "\n--- " << subheader << " ---\n";
}

// ==========================================================================
//                       SinglyLinkedList Tests
// ==========================================================================

void test_sll_int_default_constructor() {
    print_subheader("SLL<int>: Default Constructor");
    ds::SinglyLinkedList<int> list;
    assert(list.empty());
    assert(list.length() == 0);
    std::cout << "Default constructor: OK\n";
}

void test_sll_int_push_access_length_empty() {
    print_subheader("SLL<int>: Push, Operator[], Length, Empty");
    ds::SinglyLinkedList<int> list;
    assert(list.empty());
    assert(list.length() == 0);

    list.push_back(10); // [10]
    assert(!list.empty());
    assert(list.length() == 1);
    assert(list[0] == 10);

    list.push_front(5); // [5, 10]
    assert(list.length() == 2);
    assert(list[0] == 5);
    assert(list[1] == 10);

    list.push_back(20); // [5, 10, 20]
    assert(list.length() == 3);
    assert(list[0] == 5);
    assert(list[1] == 10);
    assert(list[2] == 20);

    list[1] = 15; // [5, 15, 20]
    assert(list[1] == 15);
    std::cout << "Push, Operator[], Length, Empty: OK\n";
    // list.output(); // Visual check
}

void test_sll_int_copy_constructor_assignment() {
    print_subheader("SLL<int>: Copy Constructor & Assignment");
    ds::SinglyLinkedList<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    ds::SinglyLinkedList<int> copy_constructed = original;
    assert(copy_constructed.length() == 3);
    assert(copy_constructed[0] == 1 && copy_constructed[1] == 2 && copy_constructed[2] == 3);
    original[0] = 10; // Modify original
    assert(copy_constructed[0] == 1); // Assert copy is independent (deep copy)
    std::cout << "Copy constructor: OK\n";

    ds::SinglyLinkedList<int> copy_assigned;
    copy_assigned.push_back(100);
    copy_assigned = original;
    assert(copy_assigned.length() == 3);
    assert(copy_assigned[0] == 10 && copy_assigned[1] == 2 && copy_assigned[2] == 3);
    original[1] = 20; // Modify original
    assert(copy_assigned[1] == 2); // Assert copy is independent
    std::cout << "Copy assignment: OK\n";

    // Self-assignment
    copy_assigned = copy_assigned;
    assert(copy_assigned.length() == 3);
    assert(copy_assigned[0] == 10 && copy_assigned[1] == 2 && copy_assigned[2] == 3);
    std::cout << "Self-assignment: OK\n";
}

void test_sll_int_move_constructor_assignment() {
    print_subheader("SLL<int>: Move Constructor & Assignment");
    ds::SinglyLinkedList<int> source1;
    source1.push_back(1);
    source1.push_back(2);

    ds::SinglyLinkedList<int> move_constructed = std::move(source1);
    assert(move_constructed.length() == 2);
    assert(move_constructed[0] == 1 && move_constructed[1] == 2);
    assert(source1.empty()); // Source should be empty or in a valid unspecified state
    assert(source1.length() == 0);
    std::cout << "Move constructor: OK\n";

    ds::SinglyLinkedList<int> source2;
    source2.push_back(3);
    source2.push_back(4);
    ds::SinglyLinkedList<int> move_assigned;
    move_assigned.push_back(100); // To ensure old content is cleared
    move_assigned = std::move(source2);
    assert(move_assigned.length() == 2);
    assert(move_assigned[0] == 3 && move_assigned[1] == 4);
    assert(source2.empty());
    assert(source2.length() == 0);
    std::cout << "Move assignment: OK\n";
}

void test_sll_int_clear() {
    print_subheader("SLL<int>: Clear");
    ds::SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();
    assert(list.empty());
    assert(list.length() == 0);
    list.push_back(3); // Ensure it works after clear
    assert(list.length() == 1 && list[0] == 3);
    std::cout << "Clear: OK\n";
}

void test_sll_int_insert_del() {
    print_subheader("SLL<int>: Insert & Del");
    ds::SinglyLinkedList<int> list;
    list.insert(0, 10); // [10]
    assert(list.length() == 1 && list[0] == 10);
    list.insert(0, 5);  // [5, 10]
    assert(list.length() == 2 && list[0] == 5 && list[1] == 10);
    list.insert(2, 20); // [5, 10, 20]
    assert(list.length() == 3 && list[0] == 5 && list[1] == 10 && list[2] == 20);
    list.insert(1, 7);  // [5, 7, 10, 20]
    assert(list.length() == 4 && list[0] == 5 && list[1] == 7 && list[2] == 10 && list[3] == 20);
    std::cout << "Insert: OK\n";

    list.del(1); // [5, 10, 20] (delete 7)
    assert(list.length() == 3 && list[0] == 5 && list[1] == 10 && list[2] == 20);
    list.del(0); // [10, 20] (delete 5)
    assert(list.length() == 2 && list[0] == 10 && list[1] == 20);
    list.del(1); // [10] (delete 20)
    assert(list.length() == 1 && list[0] == 10);
    list.del(0); // [] (delete 10)
    assert(list.empty());
    std::cout << "Del: OK\n";
}

void test_sll_int_locate() {
    print_subheader("SLL<int>: Locate");
    ds::SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(10);
    list.push_back(30);
    assert(list.locate(10) == 0);
    assert(list.locate(20) == 1);
    assert(list.locate(30) == 3);
    assert(list.locate(100) == -1); // Not found
    ds::SinglyLinkedList<int> empty_list;
    assert(empty_list.locate(5) == -1);
    std::cout << "Locate: OK\n";
}

void test_sll_int_resize() {
    print_subheader("SLL<int>: Resize");
    ds::SinglyLinkedList<int> list;
    list.resize(3, 100); // [100, 100, 100]
    assert(list.length() == 3);
    assert(list[0] == 100 && list[1] == 100 && list[2] == 100);

    list.resize(5, 200); // [100, 100, 100, 200, 200]
    assert(list.length() == 5);
    assert(list[3] == 200 && list[4] == 200);
    
    list.resize(2); // [100, 100] uses default value for type_t() which is 0 for int if not specified, but here it shrinks
    assert(list.length() == 2);
    assert(list[0] == 100 && list[1] == 100);

    list.resize(0);
    assert(list.empty());
    std::cout << "Resize: OK\n";
}

void test_sll_int_iterators() {
    print_subheader("SLL<int>: Iterators");
    ds::SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Non-const iterator and modification
    int val = 10;
    for (ds::SinglyLinkedList<int>::iterator it = list.begin(); it != list.end(); ++it) {
        *it = val;
        val += 10;
    }
    assert(list[0] == 10 && list[1] == 20 && list[2] == 30);
    std::cout << "Non-const iterators modification: OK\n";

    // Range-based for loop (uses const iterators if list is const, or non-const if list is non-const)
    // To force const iteration, use cbegin/cend or a const reference
    std::cout << "Iterating with range-based for (const): ";
    const ds::SinglyLinkedList<int>& const_list_ref = list;
    std::vector<int> v_const;
    for (int x : const_list_ref) {
        std::cout << x << " ";
        v_const.push_back(x);
    }
    std::cout << std::endl;
    assert(v_const.size() == 3 && v_const[0] == 10 && v_const[1] == 20 && v_const[2] == 30);

    // Const iterators explicitly
    std::vector<int> v_citer;
    for (ds::SinglyLinkedList<int>::const_iterator it = list.cbegin(); it != list.cend(); ++it) {
        v_citer.push_back(*it);
    }
    assert(v_citer.size() == 3 && v_citer[0] == 10 && v_citer[1] == 20 && v_citer[2] == 30);
    std::cout << "Const iterators (begin/end on const, cbegin/cend): OK\n";

    // Empty list iteration
    ds::SinglyLinkedList<int> empty_list;
    int count = 0;
    for (int x : empty_list) {
        count++; (void)x; // Suppress unused variable warning
    }
    assert(count == 0);
    assert(empty_list.begin() == empty_list.end());
    assert(empty_list.cbegin() == empty_list.cend());
    std::cout << "Empty list iteration: OK\n";
}

void test_sll_string() {
    print_subheader("SLL<std::string>: Various Operations");
    ds::SinglyLinkedList<std::string> s_list;
    s_list.push_back("hello");
    s_list.push_front("world"); // ["world", "hello"]
    assert(s_list.length() == 2 && s_list[0] == "world" && s_list[1] == "hello");

    s_list.insert(1, "beautiful"); // ["world", "beautiful", "hello"]
    assert(s_list[1] == "beautiful");
    
    ds::SinglyLinkedList<std::string> s_list_copy = s_list;
    assert(s_list_copy.locate("beautiful") == 1);
    s_list_copy.del(1);
    assert(s_list_copy.locate("beautiful") == -1);
    assert(s_list_copy[0] == "world" && s_list_copy[1] == "hello");
    
    std::cout << "SLL<std::string> operations: OK\n";
    // s_list.output();
}

void test_sll_exceptions() {
    print_subheader("SLL: Exceptions");
    ds::SinglyLinkedList<int> list;
    list.push_back(1); // [1]

    // Operator[] out of bounds
    try { list[1]; assert(false && "Accessed list[1] out of bounds"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }
    try { list[-1]; assert(false && "Accessed list[-1] out of bounds"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }
    const ds::SinglyLinkedList<int>& const_list = list;
    try { const_list[1]; assert(false && "Accessed const_list[1] out of bounds"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }


    // Insert out of bounds
    try { list.insert(2, 100); assert(false && "Inserted at pos 2 (len 1)"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }
    try { list.insert(-1, 100); assert(false && "Inserted at pos -1"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }

    // Del out of bounds
    try { list.del(1); assert(false && "Deleted at pos 1 (len 1)"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }
    ds::SinglyLinkedList<int> empty_list;
    try { empty_list.del(0); assert(false && "Deleted from empty list"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }

    // Resize with negative value
    try { list.resize(-1, 0); assert(false && "Resized to -1"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }
    
    std::cout << "Exceptions test: OK\n";
}


// ==========================================================================
//                       DoublyLinkedList Tests
// ==========================================================================

void test_dll_int_default_constructor() {
    print_subheader("DLL<int>: Default Constructor");
    ds::DoublyLinkedList<int> list;
    assert(list.empty());
    assert(list.length() == 0);
    assert(list.head() == nullptr);
    assert(list.tail() == nullptr);
    std::cout << "Default constructor: OK\n";
}

void test_dll_int_push_pop_access() {
    print_subheader("DLL<int>: Push, Pop, Operator[], Head, Tail");
    ds::DoublyLinkedList<int> list;
    assert(list.empty() && list.length() == 0);

    list.push_back(10); // [10]
    assert(!list.empty() && list.length() == 1 && list[0] == 10);
    assert(list.head()->data == 10 && list.tail()->data == 10);

    list.push_front(5); // [5, 10]
    assert(list.length() == 2 && list[0] == 5 && list[1] == 10);
    assert(list.head()->data == 5 && list.tail()->data == 10);

    list.push_back(20); // [5, 10, 20]
    assert(list.length() == 3 && list[0] == 5 && list[1] == 10 && list[2] == 20);
    assert(list.head()->data == 5 && list.tail()->data == 20);

    list[1] = 15; // [5, 15, 20]
    assert(list[1] == 15);
    std::cout << "Push, Operator[], Head, Tail: OK\n";

    list.pop_front(); // [15, 20]
    assert(list.length() == 2 && list[0] == 15 && list[1] == 20);
    assert(list.head()->data == 15 && list.tail()->data == 20);

    list.pop_back(); // [15]
    assert(list.length() == 1 && list[0] == 15);
    assert(list.head()->data == 15 && list.tail()->data == 15);

    list.pop_front(); // []
    assert(list.empty() && list.length() == 0);
    assert(list.head() == nullptr && list.tail() == nullptr);
    std::cout << "Pop_front/Pop_back: OK\n";

    // Test pop on empty list (should do nothing)
    list.pop_front();
    list.pop_back();
    assert(list.empty() && list.length() == 0);
    std::cout << "Pop on empty list: OK\n";
}

void test_dll_int_copy_constructor_assignment() {
    print_subheader("DLL<int>: Copy Constructor & Assignment");
    ds::DoublyLinkedList<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    ds::DoublyLinkedList<int> copy_constructed = original; // Copy constructor
    assert(copy_constructed.length() == 3 && copy_constructed[0] == 1 && copy_constructed[2] == 3);
    original[0] = 10; // Modify original
    assert(copy_constructed[0] == 1); // Assert copy is independent
    assert(copy_constructed.head()->data == 1 && copy_constructed.tail()->data == 3);
    std::cout << "Copy constructor: OK\n";

    ds::DoublyLinkedList<int> copy_assigned;
    copy_assigned.push_back(100);
    copy_assigned = original; // Copy assignment
    assert(copy_assigned.length() == 3 && copy_assigned[0] == 10 && copy_assigned[2] == 3);
    original[1] = 20; // Modify original
    assert(copy_assigned[1] == 2); // Assert copy is independent
    std::cout << "Copy assignment: OK\n";

    copy_assigned = copy_assigned; // Self-assignment
    assert(copy_assigned.length() == 3 && copy_assigned[0] == 10 && copy_assigned[1] == 2);
    std::cout << "Self-assignment: OK\n";
}

void test_dll_int_move_constructor_assignment() {
    print_subheader("DLL<int>: Move Constructor & Assignment");
    ds::DoublyLinkedList<int> source1;
    source1.push_back(1);
    source1.push_back(2);

    ds::DoublyLinkedList<int> move_constructed = std::move(source1); // Move constructor
    assert(move_constructed.length() == 2 && move_constructed[0] == 1 && move_constructed[1] == 2);
    assert(source1.empty() && source1.length() == 0 && source1.head() == nullptr && source1.tail() == nullptr);
    std::cout << "Move constructor: OK\n";

    ds::DoublyLinkedList<int> source2;
    source2.push_back(3);
    source2.push_back(4);
    ds::DoublyLinkedList<int> move_assigned;
    move_assigned.push_back(100);
    move_assigned = std::move(source2); // Move assignment
    assert(move_assigned.length() == 2 && move_assigned[0] == 3 && move_assigned[1] == 4);
    assert(source2.empty() && source2.length() == 0 && source2.head() == nullptr && source2.tail() == nullptr);
    std::cout << "Move assignment: OK\n";
}

void test_dll_int_clear() {
    print_subheader("DLL<int>: Clear");
    ds::DoublyLinkedList<int> list;
    list.push_back(1); list.push_back(2);
    list.clear();
    assert(list.empty() && list.length() == 0 && list.head() == nullptr && list.tail() == nullptr);
    list.push_back(3); // Test usability after clear
    assert(list.length() == 1 && list[0] == 3 && list.head()->data == 3 && list.tail()->data == 3);
    std::cout << "Clear: OK\n";
}

void test_dll_int_swap() {
    print_subheader("DLL<int>: Swap");
    ds::DoublyLinkedList<int> list1;
    list1.push_back(1); list1.push_back(2);
    ds::DoublyLinkedList<int> list2;
    list2.push_back(10); list2.push_back(20); list2.push_back(30);

    list1.swap(list2);

    assert(list1.length() == 3 && list1[0] == 10 && list1[2] == 30);
    assert(list2.length() == 2 && list2[0] == 1 && list2[1] == 2);
    std::cout << "Swap: OK\n";
}

void test_dll_int_iterators() {
    print_subheader("DLL<int>: Iterators (Forward, Const, Reverse)");
    ds::DoublyLinkedList<int> list;
    list.push_back(10); list.push_back(20); list.push_back(30);

    // Forward iterator (non-const)
    std::vector<int> fwd_vec;
    for (ds::DoublyLinkedList<int>::iterator it = list.begin(); it != list.end(); ++it) {
        fwd_vec.push_back(*it);
        *it += 5; // Modify
    }
    assert(fwd_vec.size() == 3 && fwd_vec[0] == 10 && fwd_vec[1] == 20 && fwd_vec[2] == 30);
    assert(list[0] == 15 && list[1] == 25 && list[2] == 35);
    std::cout << "Forward iterator (non-const) & modification: OK\n";

    // Const forward iterator (cbegin/cend)
    std::vector<int> cfwd_vec;
    for (ds::DoublyLinkedList<int>::const_iterator it = list.cbegin(); it != list.cend(); ++it) {
        cfwd_vec.push_back(*it);
    }
    assert(cfwd_vec.size() == 3 && cfwd_vec[0] == 15 && cfwd_vec[1] == 25 && cfwd_vec[2] == 35);
    std::cout << "Const forward iterator (cbegin/cend): OK\n";

    // Test decrementing forward iterator
    ds::DoublyLinkedList<int>::iterator it_fwd = list.end();
    // --(list.end()) behavior as documented: if current_ is nullptr, does nothing.
    // To get to the last element, one common pattern is this (if list not empty):
    if (!list.empty()) {
        it_fwd = list.end(); 
        --it_fwd; // This will make it point to tail if list.end() was iterator(nullptr) AND current_->prev was tail
                  // However, per docs for THIS list: `if (current_) current_ = current_->prev;`
                  // So if current_ is nullptr, it stays nullptr. We need an iterator to an actual node to test --.
        it_fwd = list.begin();
        ++it_fwd; // Now points to 25
        ++it_fwd; // Now points to 35 (tail)
        assert(*it_fwd == 35);
        --it_fwd; // Points to 25
        assert(*it_fwd == 25);
        --it_fwd; // Points to 15 (head)
        assert(*it_fwd == 15);
        --it_fwd; // Points to nullptr (before-begin state)
        ds::DoublyLinkedList<int>::iterator it_fwd_decrement_test = list.begin(); // Points to 15 (head)
        assert(*it_fwd_decrement_test == 15);

        --it_fwd_decrement_test; // Points to a conceptual "before-begin" state
                                // In your implementation, current_ becomes nullptr

        // To check this "before-begin" state, you can compare it with an iterator explicitly constructed with nullptr.
        // This is similar to how end() is often represented for forward iteration.
        ds::DoublyLinkedList<int>::iterator before_begin_iterator(nullptr);
        assert(it_fwd_decrement_test == before_begin_iterator);
        // Or, if you want to directly check the documented behavior that current_ is nullptr:
        // This would require making current_ accessible for testing or relying on the comparison above.
        // The comparison `it_fwd_decrement_test == ds::DoublyLinkedList<int>::iterator(nullptr)` is the most idiomatic.
        std::cout << "Forward iterator decrement past beginning: OK\n";
    }
    std::cout << "Forward iterator decrement: OK (tested on actual nodes)\n";


    // Reverse iterator (non-const)
    list.push_back(45); // list is now [15, 25, 35, 45]
    std::vector<int> rev_vec;
    for (ds::DoublyLinkedList<int>::reverse_iterator rit = list.rbegin(); rit != list.rend(); ++rit) {
        rev_vec.push_back(*rit);
        *rit -= 2; // Modify
    }
    // Expected reverse: 45, 35, 25, 15
    assert(rev_vec.size() == 4 && rev_vec[0] == 45 && rev_vec[1] == 35 && rev_vec[2] == 25 && rev_vec[3] == 15);
    // List is now [13, 23, 33, 43]
    assert(list[0] == 13 && list[1] == 23 && list[2] == 33 && list[3] == 43);
    std::cout << "Reverse iterator (non-const) & modification: OK\n";

    // Const reverse iterator (crbegin/crend)
    std::vector<int> crev_vec;
    for (ds::DoublyLinkedList<int>::const_reverse_iterator rit = list.crbegin(); rit != list.crend(); ++rit) {
        crev_vec.push_back(*rit);
    }
    assert(crev_vec.size() == 4 && crev_vec[0] == 43 && crev_vec[1] == 33 && crev_vec[2] == 23 && crev_vec[3] == 13);
    std::cout << "Const reverse iterator (crbegin/crend): OK\n";

    // Empty list iteration for all types
    ds::DoublyLinkedList<int> empty_list;
    assert(empty_list.begin() == empty_list.end());
    assert(empty_list.cbegin() == empty_list.cend());
    assert(empty_list.rbegin() == empty_list.rend());
    assert(empty_list.crbegin() == empty_list.crend());
    std::cout << "Empty list iteration for all iterator types: OK\n";

    // Test decrementing reverse_iterator
    // Similar logic to forward iterator: --(list.rend()) does nothing if current_ is nullptr.
    if(!list.empty()){
        ds::DoublyLinkedList<int>::reverse_iterator rit_rev = list.rbegin(); // points to 43 (tail)
        ++rit_rev; // points to 33
        ++rit_rev; // points to 23
        assert(*rit_rev == 23);
        --rit_rev; // points to 33
        assert(*rit_rev == 33);
    }
    std::cout << "Reverse iterator decrement: OK (tested on actual nodes)\n";
}

void test_dll_string() {
    print_subheader("DLL<std::string>: Various Operations");
    ds::DoublyLinkedList<std::string> s_list;
    s_list.push_back("hello");
    s_list.push_front("world"); // ["world", "hello"]
    assert(s_list.length() == 2 && s_list[0] == "world" && s_list[1] == "hello");
    assert(s_list.head()->data == "world" && s_list.tail()->data == "hello");

    s_list.pop_back(); // ["world"]
    assert(s_list.length() == 1 && s_list.tail()->data == "world");

    ds::DoublyLinkedList<std::string> s_list_copy = s_list;
    assert(s_list_copy.length() == 1 && s_list_copy[0] == "world");
    s_list_copy.push_back("again"); // ["world", "again"]
    
    std::cout << "DLL<std::string> operations: OK\n";
    // s_list_copy.output();
}


void test_dll_exceptions() {
    print_subheader("DLL: Exceptions");
    ds::DoublyLinkedList<int> list;
    list.push_back(1); // [1]

    // Operator[] out of bounds
    try { list[1]; assert(false && "Accessed list[1] out of bounds"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }
    try { list[-1]; assert(false && "Accessed list[-1] out of bounds"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }
    
    const ds::DoublyLinkedList<int>& const_list = list;
    try { const_list[1]; assert(false && "Accessed const_list[1] out of bounds"); }
    catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }

    // No generic insert/del to test for out of bounds for DLL in the provided HPP
    // Pop on empty list is a no-op, not an exception based on documentation.
    std::cout << "Exceptions test: OK\n";
}


int main() {
    print_header("SinglyLinkedList Tests");
    test_sll_int_default_constructor();
    test_sll_int_push_access_length_empty();
    test_sll_int_copy_constructor_assignment();
    test_sll_int_move_constructor_assignment();
    test_sll_int_clear();
    test_sll_int_insert_del();
    test_sll_int_locate();
    test_sll_int_resize();
    test_sll_int_iterators();
    test_sll_string();
    test_sll_exceptions();

    print_header("DoublyLinkedList Tests");
    test_dll_int_default_constructor();
    test_dll_int_push_pop_access();
    test_dll_int_copy_constructor_assignment();
    test_dll_int_move_constructor_assignment();
    test_dll_int_clear();
    test_dll_int_swap();
    test_dll_int_iterators();
    test_dll_string();
    test_dll_exceptions();

    std::cout << "\n========================================\n";
    std::cout << "          All tests completed!          \n";
    std::cout << "========================================\n" << std::endl;

    return 0;
}