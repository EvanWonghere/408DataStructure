#include "StaticSequentialList.hpp"

#include <iostream>

int main() {
    ds::StaticSequentialList<int> sl(5);

    std::cout << "After initialization, capacity is " << sl.capacity() << ", length is " << sl.length()
              << ", empty is " << sl.empty() << ", full is " << sl.full() << std::endl << std::endl;

    sl.push_back(1);
    sl.push_back(2);
    sl.push_back(3);
    sl.push_back(4);
    sl.push_back(5);

    std::cout << "After add numbers to the end, capacity is " << sl.capacity() << ", length is " << sl.length()
              << ", empty is " << sl.empty() << ", full is " << sl.full() << std::endl;
    std::cout << "Try to output the elements in list: ";
    sl.output();
    std::cout << std::endl;

    std::cout << "Try to modify elements." << std::endl;
    for (auto i = 0; i < sl.length(); ++i) sl[i] = sl.length() - i;
    std::cout << "After modify: ";
    sl.output();
    std::cout << std::endl;

    std::cout << "Try to delete middle element then insert a new one." << std::endl;
    sl.del(2);
    sl.insert(2, 6);
    std::cout << "After modify: ";
    sl.output();
    std::cout << std::endl;

    std::cout << "Try to add element while full." << std::endl;
    if (sl.push_back(7)) std::cout << "Add element succeed." << std::endl;
    else std::cout << "Add element failed." << std::endl << std::endl;

    std::cout << "Try to clear the list." << std::endl;
    sl.clear();
    std::cout << "List cleared, capacity is " << sl.capacity() << ", length is " << sl.length()
              << ", empty is " << sl.empty() << ", full is " << sl.full() << ", elements: ";
    sl.output();
    std::cout << std::endl;

    std::cout << "Try to delete element while empty." << std::endl;
    if (sl.del(0)) std::cout << "Delete element succeed." << std::endl;
    else std::cout << "Delete element failed." << std::endl << std::endl;

    std::cout << "Try to access element while empty." << std::endl;
    try {
        auto num = sl[0];
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught an out_of_range exception: " << e.what() << std::endl;
    }
}
