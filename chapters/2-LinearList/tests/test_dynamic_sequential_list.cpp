#include "DynamicSequentialList.hpp"
#include <iostream>
#include <stdexcept>

using ds::DynamicSequentialList;

void printStatus(const DynamicSequentialList<int>& list, const std::string& label) {
    std::cout << label << ": ";
    std::cout << "[length=" << list.length() << ", capacity=" << list.capacity()
              << ", empty=" << list.empty() << "] ";
    list.output();
}

void testConstructorsAndCopy() {
    std::cout << "=== Constructor & Copy/Move ===" << std::endl;
    DynamicSequentialList<int> a; // default
    printStatus(a, "Default");

    DynamicSequentialList<int> b(5, 42); // fill with 42
    printStatus(b, "Fill");

    DynamicSequentialList<int> c(b); // copy constructor
    printStatus(c, "Copy");

    DynamicSequentialList<int> d(std::move(b)); // move constructor
    printStatus(d, "Move");

    DynamicSequentialList<int> e;
    e = c; // copy assignment
    printStatus(e, "Copy Assign");

    DynamicSequentialList<int> f;
    f = std::move(c); // move assignment
    printStatus(f, "Move Assign");

    std::cout << std::endl;
}

void testBasicOperations() {
    std::cout << "=== Basic Insertion, Deletion, Access ===" << std::endl;
    DynamicSequentialList<int> list;

    for (int i = 1; i <= 5; ++i) list.push_back(i);
    printStatus(list, "After push_back");

    list.insert(2, 99);
    printStatus(list, "After insert at pos 2");

    list.del(3);
    printStatus(list, "After delete at pos 3");

    try {
        list[100] = 1;
    } catch (const std::out_of_range& e) {
        std::cout << "[PASS] Caught out_of_range on operator[]: " << e.what() << std::endl;
    }

    std::cout << "Locate value 99 at pos: " << list.locate(99) << std::endl;
    std::cout << std::endl;
}

void testResizeAndReserve() {
    std::cout << "=== Resize and Reserve ===" << std::endl;
    DynamicSequentialList<int> list(3, 7);
    printStatus(list, "Initial");

    list.reserve(10);
    printStatus(list, "After reserve(10)");

    list.resize(6, 9);
    printStatus(list, "After resize(6, 9)");

    list.resize(3);
    printStatus(list, "After resize(3)");

    std::cout << std::endl;
}

void testClearAndSwap() {
    std::cout << "=== Clear and Swap ===" << std::endl;
    DynamicSequentialList<int> a(3, 1);
    DynamicSequentialList<int> b(2, 9);

    printStatus(a, "A before swap");
    printStatus(b, "B before swap");

    swap(a, b);

    printStatus(a, "A after swap");
    printStatus(b, "B after swap");

    a.clear();
    printStatus(a, "A after clear");

    std::cout << std::endl;
}

void testIterators() {
    std::cout << "=== Iterator Test ===" << std::endl;
    DynamicSequentialList<int> list;
    for (int i = 1; i <= 5; ++i) list.push_back(i); // [1,2,3,4,5]

    std::cout << "Forward iteration: ";
    for (auto it = list.begin(); it != list.end(); ++it) std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Reverse iteration: ";
    for (auto rit = list.rbegin(); rit != list.rend(); ++rit) std::cout << *rit << " ";
    std::cout << std::endl;

    std::cout << "Const iteration: ";
    const auto& clist = list;
    for (auto it = clist.cbegin(); it != clist.cend(); ++it) std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << std::endl;
}

int main() {
    testConstructorsAndCopy();
    testBasicOperations();
    testResizeAndReserve();
    testClearAndSwap();
    testIterators();
}
