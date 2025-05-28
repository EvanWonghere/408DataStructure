#include <iostream>
#include <vector> // For easily initializing test data
#include <stdexcept> // For try-catch
#include <limits> // For numeric_limits

// Assuming these files are in the same directory or accessible in include paths
#include "StaticSequentialList.hpp"
#include "DynamicSequentialList.hpp"
#include "Section2.hpp" // This should include the implementations

// Use the namespaces defined in your header files
using namespace ds;
using namespace ex;

// Helper to print a list with a message
template<typename ListType>
void print_list(const std::string& msg, const ListType& list) {
    std::cout << msg;
    list.output(); // Assuming your list classes have an output() method
}

// Helper to print a value with a message
template<typename T>
void print_value(const std::string& msg, const T& value) {
    std::cout << msg << value << std::endl;
}

// --- Test Functions for each operation ---

void test_pop_min() {
    std::cout << "\n--- Testing pop_min ---" << std::endl;
    
    // Test StaticSequentialList
    try {
        StaticSequentialList<int> s_list(5);
        s_list.push_back(50); s_list.push_back(20); s_list.push_back(80); s_list.push_back(10); s_list.push_back(40);
        print_list("Static List (Original): ", s_list);
        int min_val = pop_min(s_list);
        print_value("Popped min: ", min_val);
        print_list("Static List (After pop_min): ", s_list);

        StaticSequentialList<int> s_list_empty(5);
        print_list("Static List Empty (Original): ", s_list_empty);
        pop_min(s_list_empty); // This should throw
    } catch (const std::exception& e) {
        std::cerr << "Caught exception (Static): " << e.what() << std::endl;
    }

    // Test DynamicSequentialList
    try {
        DynamicSequentialList<int> d_list;
        d_list.push_back(50); d_list.push_back(20); d_list.push_back(80); d_list.push_back(10); d_list.push_back(40);
        print_list("Dynamic List (Original): ", d_list);
        int min_val = pop_min(d_list);
        print_value("Popped min: ", min_val);
        print_list("Dynamic List (After pop_min): ", d_list);

        DynamicSequentialList<int> d_list_single;
        d_list_single.push_back(100);
        print_list("Dynamic List Single (Original): ", d_list_single);
        min_val = pop_min(d_list_single);
        print_value("Popped min from single: ", min_val);
        print_list("Dynamic List Single (After pop_min): ", d_list_single);
        
        DynamicSequentialList<int> d_list_empty;
        print_list("Dynamic List Empty (Original): ", d_list_empty);
        pop_min(d_list_empty); // This should throw
    } catch (const std::exception& e) {
        std::cerr << "Caught exception (Dynamic): " << e.what() << std::endl;
    }
}

void test_reverse() {
    std::cout << "\n--- Testing reverse ---" << std::endl;
    // Static
    StaticSequentialList<int> s_list(5);
    s_list.push_back(1); s_list.push_back(2); s_list.push_back(3); s_list.push_back(4); s_list.push_back(5);
    print_list("Static List (Original): ", s_list);
    reverse(s_list);
    print_list("Static List (Reversed full): ", s_list);
    reverse(s_list, 1, 3);
    print_list("Static List (Reversed 1-3): ", s_list);

    // Dynamic
    DynamicSequentialList<int> d_list;
    d_list.push_back(1); d_list.push_back(2); d_list.push_back(3); d_list.push_back(4); d_list.push_back(5); d_list.push_back(6);
    print_list("Dynamic List (Original): ", d_list);
    reverse(d_list);
    print_list("Dynamic List (Reversed full): ", d_list);
    reverse(d_list, 1, 4);
    print_list("Dynamic List (Reversed 1-4): ", d_list);
    reverse(d_list, 0, 0); // single element sublist
    print_list("Dynamic List (Reversed 0-0): ", d_list);
}

void test_del_x() {
    std::cout << "\n--- Testing del_x ---" << std::endl;
    // Static
    StaticSequentialList<int> s_list(10);
    s_list.push_back(1); s_list.push_back(2); s_list.push_back(3); s_list.push_back(2); s_list.push_back(4); s_list.push_back(2);
    print_list("Static List (Original): ", s_list);
    del_x(s_list, 2);
    print_list("Static List (After del_x(2)): ", s_list); // Expected: [4,3,1] or similar (order of kept reversed)

    // Dynamic
    DynamicSequentialList<int> d_list;
    d_list.push_back(1); d_list.push_back(2); d_list.push_back(3); d_list.push_back(2); d_list.push_back(4); d_list.push_back(2); d_list.push_back(5);
    print_list("Dynamic List (Original): ", d_list);
    del_x(d_list, 2);
    print_list("Dynamic List (After del_x(2)): ", d_list); // Expected: [5,4,3,1] or similar

    DynamicSequentialList<int> d_list_all_x;
    d_list_all_x.push_back(7); d_list_all_x.push_back(7); d_list_all_x.push_back(7);
    print_list("Dynamic List (All 7s Original): ", d_list_all_x);
    del_x(d_list_all_x, 7);
    print_list("Dynamic List (After del_x(7)): ", d_list_all_x); // Expected: []
}

void test_del_between() {
    std::cout << "\n--- Testing del_between ---" << std::endl;
    // Static
    try {
        StaticSequentialList<int> s_list(7);
        s_list.push_back(1); s_list.push_back(2); s_list.push_back(3); s_list.push_back(4); s_list.push_back(5); s_list.push_back(6); s_list.push_back(7);
        print_list("Static List (Original): ", s_list);
        del_between(s_list, 2, 6); // Delete 3, 4, 5
        print_list("Static List (After del_between(2,6)): ", s_list); // Expected: [1,2,6,7]
        // del_between(s_list, 6, 2); // This should throw logic_error
    } catch (const std::exception& e) {
        std::cerr << "Caught exception (Static): " << e.what() << std::endl;
    }

    // Dynamic
    try {
        DynamicSequentialList<int> d_list;
        d_list.push_back(10); d_list.push_back(20); d_list.push_back(30); d_list.push_back(40); d_list.push_back(50); d_list.push_back(60);
        print_list("Dynamic List (Original): ", d_list);
        del_between(d_list, 15, 45); // Delete 20, 30, 40
        print_list("Dynamic List (After del_between(15,45)): ", d_list); // Expected: [10,50,60]
    } catch (const std::exception& e) {
        std::cerr << "Caught exception (Dynamic): " << e.what() << std::endl;
    }
}

void test_unique_sorted() {
    std::cout << "\n--- Testing unique (sorted) ---" << std::endl;
    // Static
    StaticSequentialList<int> s_list(10);
    s_list.push_back(1); s_list.push_back(2); s_list.push_back(2); s_list.push_back(3); s_list.push_back(4); s_list.push_back(4); s_list.push_back(4); s_list.push_back(5);
    print_list("Static Sorted List (Original): ", s_list);
    unique(s_list);
    print_list("Static Sorted List (After unique): ", s_list); // Expected: [1,2,3,4,5]

    // Dynamic
    DynamicSequentialList<int> d_list;
    d_list.push_back(11); d_list.push_back(11); d_list.push_back(22); d_list.push_back(33); d_list.push_back(33); d_list.push_back(33);
    print_list("Dynamic Sorted List (Original): ", d_list);
    unique(d_list);
    print_list("Dynamic Sorted List (After unique): ", d_list); // Expected: [11,22,33]
}

void test_merge_sorted() {
    std::cout << "\n--- Testing merge (sorted) ---" << std::endl;
    // Static
    StaticSequentialList<int> s_a(5); s_a.push_back(1); s_a.push_back(3); s_a.push_back(5);
    StaticSequentialList<int> s_b(5); s_b.push_back(2); s_b.push_back(4); s_b.push_back(6);
    print_list("Static List A: ", s_a);
    print_list("Static List B: ", s_b);
    StaticSequentialList<int> s_merged = merge(s_a, s_b);
    print_list("Static Merged List: ", s_merged); // Expected: [1,2,3,4,5,6]

    // Dynamic
    DynamicSequentialList<int> d_a; d_a.push_back(10); d_a.push_back(30); d_a.push_back(50); d_a.push_back(70);
    DynamicSequentialList<int> d_b; d_b.push_back(20); d_b.push_back(40); d_b.push_back(60);
    print_list("Dynamic List A: ", d_a);
    print_list("Dynamic List B: ", d_b);
    DynamicSequentialList<int> d_merged = merge(d_a, d_b);
    print_list("Dynamic Merged List: ", d_merged); // Expected: [10,20,30,40,50,60,70]
}

void test_swap_inside() {
    std::cout << "\n--- Testing swap_inside ---" << std::endl;
    // Static
    try {
        StaticSequentialList<int> s_list(7);
        s_list.push_back(1); s_list.push_back(2); s_list.push_back(3); // m=3
        s_list.push_back(4); s_list.push_back(5); s_list.push_back(6); s_list.push_back(7); // n=4
        print_list("Static List (Original): ", s_list); // [1,2,3,4,5,6,7]
        swap_inside(s_list, 3, 4);
        print_list("Static List (After swap_inside(3,4)): ", s_list); // Expected: [4,5,6,7,1,2,3]
    } catch (const std::exception& e) {
        std::cerr << "Caught exception (Static): " << e.what() << std::endl;
    }
    
    // Dynamic
    try {
        DynamicSequentialList<int> d_list;
        d_list.push_back(10); d_list.push_back(20); // m=2
        d_list.push_back(30); d_list.push_back(40); d_list.push_back(50); // n=3
        print_list("Dynamic List (Original): ", d_list); // [10,20,30,40,50]
        swap_inside(d_list, 2, 3);
        print_list("Dynamic List (After swap_inside(2,3)): ", d_list); // Expected: [30,40,50,10,20]

        DynamicSequentialList<int> d_list2; // Test len1 < len2 for block_swap
        d_list2.push_back(1); // m=1
        d_list2.push_back(2);d_list2.push_back(3);d_list2.push_back(4); // n=3
        print_list("Dynamic List2 (Original): ", d_list2); // [1,2,3,4]
        swap_inside(d_list2, 1, 3);
        print_list("Dynamic List2 (After swap_inside(1,3)): ", d_list2); // Expected: [2,3,4,1]

        DynamicSequentialList<int> d_list3; // Test len1 > len2 for block_swap
        d_list3.push_back(1);d_list3.push_back(2);d_list3.push_back(3); // m=3
        d_list3.push_back(4); // n=1
        print_list("Dynamic List3 (Original): ", d_list3); // [1,2,3,4]
        swap_inside(d_list3, 3, 1);
        print_list("Dynamic List3 (After swap_inside(3,1)): ", d_list3); // Expected: [4,1,2,3]


    } catch (const std::exception& e) {
        std::cerr << "Caught exception (Dynamic): " << e.what() << std::endl;
    }
}

void test_find_and_swap_or_insert() {
    std::cout << "\n--- Testing find_and_swap_or_insert (sorted) ---" << std::endl;
    // Static
    StaticSequentialList<int> s_list(10);
    s_list.push_back(10); s_list.push_back(20); s_list.push_back(30); s_list.push_back(40);
    print_list("Static Sorted List (Original): ", s_list);
    find_and_swap_or_insert(s_list, 20); // Found, swap with next
    print_list("Static List (After find(20)): ", s_list); // Expected: [10,30,20,40]
    find_and_swap_or_insert(s_list, 40); // Found at end, no swap
    print_list("Static List (After find(40)): ", s_list); // Expected: [10,30,20,40]
    find_and_swap_or_insert(s_list, 25); // Not found, insert
    print_list("Static List (After find(25)): ", s_list); // Expected: [10,20,25,30,40] (order restored by sort logic)
                                                          // Oh, the original list was [10,30,20,40], not sorted after first op.
                                                          // This function assumes list *IS* sorted for locate.
                                                          // Let's re-test with fresh sorted lists for each sub-case.
    StaticSequentialList<int> s_list2(10);
    s_list2.push_back(10);s_list2.push_back(20);s_list2.push_back(30);
    print_list("Static Sorted List (Original): ", s_list2);
    find_and_swap_or_insert(s_list2, 5); // Insert at beginning
    print_list("Static List (Insert 5): ", s_list2); // [5,10,20,30]
    find_and_swap_or_insert(s_list2, 35); // Insert at end
    print_list("Static List (Insert 35): ", s_list2); // [5,10,20,30,35]


    // Dynamic
    DynamicSequentialList<int> d_list;
    d_list.push_back(5); d_list.push_back(15); d_list.push_back(25); d_list.push_back(35);
    print_list("Dynamic Sorted List (Original): ", d_list);
    find_and_swap_or_insert(d_list, 15);
    print_list("Dynamic List (After find(15)): ", d_list); // Expected: [5,25,15,35]
    
    // Reset for insert test
    d_list.clear();
    d_list.push_back(5); d_list.push_back(15); d_list.push_back(25); d_list.push_back(35);
    find_and_swap_or_insert(d_list, 20); // Not found, insert
    print_list("Dynamic List (After find(20) - insert): ", d_list); // Expected: [5,15,20,25,35]
    find_and_swap_or_insert(d_list, 40); // Not found, insert at end
    print_list("Dynamic List (After find(40) - insert): ", d_list); // Expected: [5,15,20,25,35,40]
    find_and_swap_or_insert(d_list, 0); // Not found, insert at beginning
    print_list("Dynamic List (After find(0) - insert): ", d_list); // Expected: [0,5,15,20,25,35,40]
}

void test_output_intersection() {
    std::cout << "\n--- Testing output_intersection (sorted) ---" << std::endl;
    // Static
    StaticSequentialList<int> s_a(5); s_a.push_back(1); s_a.push_back(2); s_a.push_back(3); s_a.push_back(4);
    StaticSequentialList<int> s_b(5); s_b.push_back(2); s_b.push_back(3); s_b.push_back(5);
    StaticSequentialList<int> s_c(5); s_c.push_back(2); s_c.push_back(4); s_c.push_back(6);
    print_list("Static List A: ", s_a); print_list("Static List B: ", s_b); print_list("Static List C: ", s_c);
    std::cout << "Static Intersection: "; output_intersection(s_a, s_b, s_c); // Expected: [ 2 ]

    // Dynamic
    DynamicSequentialList<int> d_a; d_a.push_back(10); d_a.push_back(20); d_a.push_back(30); d_a.push_back(40);
    DynamicSequentialList<int> d_b; d_b.push_back(20); d_b.push_back(30); d_b.push_back(50); d_b.push_back(40); // Unsorted element for testing, but function expects sorted
                                                                                                            // Let's fix d_b to be sorted
    d_b.clear(); d_b.push_back(20); d_b.push_back(30); d_b.push_back(40); d_b.push_back(50);
    DynamicSequentialList<int> d_c; d_c.push_back(20); d_c.push_back(40); d_c.push_back(60);
    print_list("Dynamic List A: ", d_a); print_list("Dynamic List B: ", d_b); print_list("Dynamic List C: ", d_c);
    std::cout << "Dynamic Intersection: "; output_intersection(d_a, d_b, d_c); // Expected: [ 20 40 ]
}

void test_sift_left() {
    std::cout << "\n--- Testing sift_left ---" << std::endl;
    // Static
    StaticSequentialList<int> s_list(5);
    s_list.push_back(1); s_list.push_back(2); s_list.push_back(3); s_list.push_back(4); s_list.push_back(5);
    print_list("Static List (Original): ", s_list);
    sift_left(s_list, 2);
    print_list("Static List (After sift_left(2)): ", s_list); // Expected: [3,4,5,1,2]
    sift_left(s_list, 0); // No change
    print_list("Static List (After sift_left(0)): ", s_list);
    sift_left(s_list, s_list.length()); // No change
    print_list("Static List (After sift_left(length)): ", s_list);


    // Dynamic
    DynamicSequentialList<int> d_list;
    d_list.push_back(10); d_list.push_back(20); d_list.push_back(30); d_list.push_back(40); d_list.push_back(50); d_list.push_back(60);
    print_list("Dynamic List (Original): ", d_list);
    sift_left(d_list, 3);
    print_list("Dynamic List (After sift_left(3)): ", d_list); // Expected: [40,50,60,10,20,30]
}

void test_get_median() {
    std::cout << "\n--- Testing get_median (sorted, equal length) ---" << std::endl;
    // Static
    try {
        StaticSequentialList<int> s_a(5); s_a.push_back(1); s_a.push_back(10); s_a.push_back(20);
        StaticSequentialList<int> s_b(5); s_b.push_back(2); s_b.push_back(12); s_b.push_back(15); // Merged: 1,2,10,12,15,20. Median items: 10,12. One of them.
        print_list("Static List A: ", s_a); print_list("Static List B: ", s_b);
        print_value("Static Median: ", get_median(s_a, s_b)); // Expected: 10 (or 12 depending on exact definition for even total)

        StaticSequentialList<int> s_a2(2); s_a2.push_back(10); s_a2.push_back(20);
        StaticSequentialList<int> s_b2(2); s_b2.push_back(30); s_b2.push_back(40);
        print_list("Static List A2: ", s_a2); print_list("Static List B2: ", s_b2);
        print_value("Static Median2: ", get_median(s_a2,s_b2)); // Merged: 10,20,30,40. Medians 20,30. Output: 20
    } catch (const std::exception& e) {
        std::cerr << "Caught exception (Static): " << e.what() << std::endl;
    }

    // Dynamic
    try {
        DynamicSequentialList<int> d_a; d_a.push_back(5); d_a.push_back(15); d_a.push_back(25); d_a.push_back(35);
        DynamicSequentialList<int> d_b; d_b.push_back(10); d_b.push_back(20); d_b.push_back(30); d_b.push_back(40);
        // Merged: 5,10,15,20,25,30,35,40. Medians 20,25.
        print_list("Dynamic List A: ", d_a); print_list("Dynamic List B: ", d_b);
        print_value("Dynamic Median: ", get_median(d_a, d_b)); // Expected: 20 (or 25)
    } catch (const std::exception& e) {
        std::cerr << "Caught exception (Dynamic): " << e.what() << std::endl;
    }
}

void test_get_main_element() {
    std::cout << "\n--- Testing get_main_element ---" << std::endl;
    // Static
    StaticSequentialList<int> s_list(10);
    s_list.push_back(1); s_list.push_back(2); s_list.push_back(1); s_list.push_back(1); s_list.push_back(3); s_list.push_back(1);
    print_list("Static List: ", s_list);
    print_value("Static Main Element: ", get_main_element(s_list)); // Expected: 1

    StaticSequentialList<int> s_list_no_main(5);
    s_list_no_main.push_back(1); s_list_no_main.push_back(2); s_list_no_main.push_back(3);
    print_list("Static List No Main: ", s_list_no_main);
    print_value("Static Main Element (None): ", get_main_element(s_list_no_main)); // Expected: -1


    // Dynamic
    DynamicSequentialList<int> d_list;
    d_list.push_back(5); d_list.push_back(5); d_list.push_back(2); d_list.push_back(5); d_list.push_back(2); d_list.push_back(5); d_list.push_back(5);
    print_list("Dynamic List: ", d_list); // 5 appears 5 times in 7 elements.
    print_value("Dynamic Main Element: ", get_main_element(d_list)); // Expected: 5

    DynamicSequentialList<int> d_list_empty;
    print_list("Dynamic List Empty: ", d_list_empty);
    print_value("Dynamic Main Element (Empty): ", get_main_element(d_list_empty)); // Expected: -1
}

void test_get_min_positive() {
    std::cout << "\n--- Testing get_min_positive ---" << std::endl;
    // Static
    StaticSequentialList<int> s_list(10);
    s_list.push_back(3); s_list.push_back(4); s_list.push_back(-1); s_list.push_back(1);
    print_list("Static List: ", s_list);
    print_value("Static Min Positive: ", get_min_positive(s_list)); // Expected: 2

    StaticSequentialList<int> s_list2(5);
    s_list2.push_back(1); s_list2.push_back(2); s_list2.push_back(3);
    print_list("Static List [1,2,3]: ", s_list2);
    print_value("Static Min Positive: ", get_min_positive(s_list2)); // Expected: 4
    
    StaticSequentialList<int> s_list_empty(5);
    print_list("Static List Empty: ", s_list_empty);
    print_value("Static Min Positive (Empty): ", get_min_positive(s_list_empty)); // Expected: 0 (as per implementation)


    // Dynamic
    DynamicSequentialList<int> d_list;
    d_list.push_back(7); d_list.push_back(8); d_list.push_back(9); d_list.push_back(11); d_list.push_back(12);
    print_list("Dynamic List: ", d_list);
    print_value("Dynamic Min Positive: ", get_min_positive(d_list)); // Expected: 1 (because 1-6 are missing, list values > length)

    DynamicSequentialList<int> d_list2;
    d_list2.push_back(1); d_list2.push_back(5); d_list2.push_back(2); d_list2.push_back(4); // Missing 3
    print_list("Dynamic List [1,5,2,4]: ", d_list2);
    print_value("Dynamic Min Positive: ", get_min_positive(d_list2)); // Expected: 3
}

void test_get_min_triplet_dist() {
    std::cout << "\n--- Testing get_min_triplet_dist (sorted) ---" << std::endl;
    // Static
    StaticSequentialList<int> s_a(5); s_a.push_back(1); s_a.push_back(4); s_a.push_back(7);
    StaticSequentialList<int> s_b(5); s_b.push_back(2); s_b.push_back(5); s_b.push_back(8);
    StaticSequentialList<int> s_c(5); s_c.push_back(3); s_c.push_back(6); s_c.push_back(9);
    // Example triplets: (1,2,3) -> max-min = 2. 2*(max-min) = 4
    // (4,5,6) -> max-min = 2. 2*(max-min) = 4
    // (7,8,9) -> max-min = 2. 2*(max-min) = 4
    // (1,5,3) -> sort -> (1,3,5) -> max-min = 4. 2*(max-min)=8
    // (4,2,6) -> sort -> (2,4,6) -> max-min = 4. 2*(max-min)=8
    print_list("Static List A: ", s_a); print_list("Static List B: ", s_b); print_list("Static List C: ", s_c);
    print_value("Static Min Triplet Distance: ", get_min_triplet_dist(s_a, s_b, s_c)); // Expected: 4

    // Dynamic
    DynamicSequentialList<int> d_a; d_a.push_back(10); d_a.push_back(20);
    DynamicSequentialList<int> d_b; d_b.push_back(12); d_b.push_back(23);
    DynamicSequentialList<int> d_c; d_c.push_back(15); d_c.push_back(28);
    // (10,12,15) -> max-min = 5. 2*5 = 10
    // (20,23,28) -> max-min = 8. 2*8 = 16
    // (10,12,28) -> max-min=18. 2*18=36
    // (10,23,15) -> sort(10,15,23) -> max-min=13. 2*13=26
    print_list("Dynamic List A: ", d_a); print_list("Dynamic List B: ", d_b); print_list("Dynamic List C: ", d_c);
    print_value("Dynamic Min Triplet Distance: ", get_min_triplet_dist(d_a, d_b, d_c)); // Expected: 10
}


int main() {
    std::cout << "Starting tests for functions in Section2.hpp..." << std::endl;

    test_pop_min();
    test_reverse();
    test_del_x();
    test_del_between();
    test_unique_sorted();
    test_merge_sorted();
    test_swap_inside();
    test_find_and_swap_or_insert(); // Remember this assumes sorted list for locate and may change order
    test_output_intersection();
    test_sift_left();
    test_get_median();
    test_get_main_element();
    test_get_min_positive();
    test_get_min_triplet_dist();

    std::cout << "\n--- All tests complete. Please review output. ---" << std::endl;

    return 0;
}