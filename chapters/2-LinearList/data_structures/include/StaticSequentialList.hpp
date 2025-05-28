#pragma once

#include <memory>
#include <iostream>
#include <stdexcept>

namespace ds {

/**
 * @brief A statically allocated sequential list (array-based list with fixed capacity).
 * 
 * This template class implements a static sequential list using dynamic memory (via unique_ptr),
 * providing basic operations such as insertion, deletion, search, and element access.
 * 
 * @tparam type_t The type of the elements stored in the list.
 */
template<class type_t>
class StaticSequentialList {
private:
    int capacity_;                          ///< Maximum number of elements the list can hold.
    int length_;                            ///< Current number of elements in the list.
    std::unique_ptr<type_t[]> data;         ///< Pointer to the underlying array storing the elements.

public:
    /**
     * @brief Constructs a StaticSequentialList instance with a specified capacity.
     * 
     * @param capacity The maximum number of elements the list can contain.
     */
    StaticSequentialList(int capacity);

    /**
     * @brief Default destructor.
     */
    ~StaticSequentialList() = default;

    /**
     * @brief Provides read-only access to an element by index.
     * 
     * @param i The index of the element.
     * @return A constant reference to the element.
     * @throws std::out_of_range if the index is invalid.
     */
    const type_t& operator[](const int& i) const;

    /**
     * @brief Provides read-write access to an element by index.
     * 
     * @param i The index of the element.
     * @return A reference to the element.
     * @throws std::out_of_range if the index is invalid.
     */
    type_t& operator[](const int& i);

    /**
     * @brief Returns the current number of elements in the list.
     * 
     * @return The list's current size.
     */
    int length() const;

    /**
     * @brief Returns the total capacity of the list.
     * 
     * @return The maximum number of elements the list can hold.
     */
    int capacity() const;

    /**
     * @brief Checks whether the list is empty.
     * 
     * @return True if the list has no elements, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Checks whether the list is full.
     * 
     * @return True if the list has reached its capacity, false otherwise.
     */
    bool full() const;

    /**
     * @brief Locates the first occurrence of a given value.
     * 
     * @param value The value to search for.
     * @return The index of the value if found, -1 otherwise.
     */
    int locate(const type_t& value) const;

    /**
     * @brief Inserts a value at the specified index, shifting subsequent elements right.
     * 
     * @param pos The position at which to insert the value (0-based index).
     * @param val The value to insert.
     * @return True if insertion is successful, false otherwise.
     */
    bool insert(const int& pos, const type_t& val);

    /**
     * @brief Appends a value to the end of the list.
     * 
     * @param val The value to append.
     * @return True if insertion is successful, false otherwise.
     */
    bool push_back(const type_t& val);

    /**
     * @brief Deletes the element at the specified index, shifting subsequent elements left.
     * 
     * @param pos The position of the element to delete.
     * @return True if deletion is successful, false otherwise.
     */
    bool del(const int& pos);

    /**
     * @brief Clears the list by resetting its length to 0.
     */
    void clear();

    /**
     * @brief Outputs the current list contents to std::cout in the format: [a, b, c].
     */
    void output() const;
};

// ------------------ Implementation ------------------

template<class type_t>
StaticSequentialList<type_t>::StaticSequentialList(int capacity)
    : capacity_(capacity), length_(0), data(std::make_unique<type_t[]>(capacity)) {}

template<class type_t>
const type_t& StaticSequentialList<type_t>::operator[](const int& i) const {
    if (i < 0 || i >= length_) throw std::out_of_range("Index out of range");
    return data[i];
}

template<class type_t>
type_t& StaticSequentialList<type_t>::operator[](const int& i) {
    if (i < 0 || i >= length_) throw std::out_of_range("Index out of range");
    return data[i];
}

template<class type_t>
int StaticSequentialList<type_t>::length() const {
    return length_;
}

template<class type_t>
int StaticSequentialList<type_t>::capacity() const {
    return capacity_;
}

template<class type_t>
bool StaticSequentialList<type_t>::empty() const {
    return length_ == 0;
}

template<class type_t>
bool StaticSequentialList<type_t>::full() const {
    return length_ == capacity_;
}

template<class type_t>
int StaticSequentialList<type_t>::locate(const type_t& value) const {
    for (int i = 0; i < length_; ++i) {
        if (data[i] == value) return i;
    }
    return -1;
}

template<class type_t>
bool StaticSequentialList<type_t>::insert(const int& pos, const type_t& val) {
    if (full()) throw std::out_of_range("Insert position out of range");
    if (pos < 0 || pos > length_) throw std::out_of_range("Insert position out of range");

    // Shift elements to the right to make room
    for (int i = length_; i > pos; --i) {
        data[i] = data[i - 1];
    }

    data[pos] = val;
    ++length_;
    return true;
}

template<class type_t>
bool StaticSequentialList<type_t>::push_back(const type_t& val) {
    return insert(length_, val);
}

template<class type_t>
bool StaticSequentialList<type_t>::del(const int& pos) {
    if (empty()) throw std::out_of_range("Delete position out of range");
    if (pos < 0 || pos >= length_) throw std::out_of_range("Delete position out of range");

    // Shift elements to the left to fill the gap
    for (int i = pos; i < length_ - 1; ++i) {
        data[i] = data[i + 1];
    }

    --length_;
    return true;
}

template<class type_t>
void StaticSequentialList<type_t>::clear() {
    length_ = 0;
}

template<class type_t>
void StaticSequentialList<type_t>::output() const {
    std::cout << '[';
    for (int i = 0; i < length_; ++i) {
        std::cout << data[i];
        if (i + 1 < length_) std::cout << ", ";
    }
    std::cout << ']' << std::endl;
}

} // namespace ds
