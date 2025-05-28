// DynamicSequentialList.hpp
// A dynamic array-based sequential list with STL-like iterators.
// Implements common container operations such as insertion, deletion,
// copy/move semantics, and dynamic resizing.

#pragma once

#include <memory>
#include <iterator>
#include <iostream>
#include <stdexcept>

namespace ds {

// Forward declaration for swap
template<class type_t> class DynamicSequentialList;
template<class type_t>
void swap(DynamicSequentialList<type_t>& a, DynamicSequentialList<type_t>& b);

/**
 * @brief A dynamic sequential list with random access, auto-resizing, and STL-style iterators.
 * 
 * @tparam type_t Element type stored in the list.
 */
template<class type_t>
class DynamicSequentialList {
private:
    int capacity_;                          ///< Maximum capacity of the list.
    int length_;                            ///< Current number of elements.
    std::unique_ptr<type_t[]> data;         ///< Underlying array for storage.

    /**
     * @brief Ensures the internal array has at least `min_capacity`.
     *        Expands the capacity geometrically if needed.
     * 
     * @param min_capacity Minimum required capacity.
     */
    void ensure_capacity(int min_capacity);

public:
    // ---------------- Constructors & Assignment ----------------

    /** @brief Default constructor. Initializes an empty list. */
    DynamicSequentialList();

    /**
     * @brief Constructs a list of given size filled with the given value.
     * 
     * @param count Number of elements.
     * @param value Value to fill.
     */
    DynamicSequentialList(int count, const type_t& value = type_t());

    /** @brief Copy constructor. Performs deep copy. */
    DynamicSequentialList(const DynamicSequentialList& other);

    /** @brief Move constructor. Transfers ownership. */
    DynamicSequentialList(DynamicSequentialList&& other) noexcept;

    /** @brief Destructor. Defaulted. */
    ~DynamicSequentialList() = default;

    /** @brief Subscript operator for const access. Throws if out of bounds. */
    const type_t& operator[](const int& i) const;

    /** @brief Subscript operator for mutable access. Throws if out of bounds. */
    type_t& operator[](const int& i);

    /** @brief Copy assignment. Strong exception safety. */
    DynamicSequentialList& operator=(const DynamicSequentialList& other);

    /** @brief Move assignment. Transfers ownership. */
    DynamicSequentialList& operator=(DynamicSequentialList&& other) noexcept;

    /** @brief Swaps two lists. */
    friend void swap<type_t>(DynamicSequentialList<type_t>& a, DynamicSequentialList<type_t>& b);

    // ---------------- Capacity & Status ----------------

    int length() const;      ///< Returns current length.
    int capacity() const;    ///< Returns current capacity.
    bool empty() const;      ///< Checks if the list is empty.

    // ---------------- Element Operations ----------------

    /** @brief Searches for a value. Returns index or -1 if not found. */
    int locate(const type_t& value) const;

    /** @brief Inserts value at position. Throws std::out_of_range if invalid. */
    bool insert(const int& pos, const type_t& val);

    /** @brief Appends value at end. */
    bool push_back(const type_t& val);

    /** @brief Deletes element at position. Throws if out of range. */
    bool del(const int& pos);

    /** @brief Clears the list. */
    void clear();

    /** @brief Prints the list content to stdout. */
    void output() const;

    /** @brief Expands capacity to new_capacity if greater than current. */
    void reserve(int new_capacity);

    /** @brief Resizes list to new_size, filling new elements with `value`. */
    void resize(int new_size, const type_t& value = type_t());

    // ---------------- Iterators ----------------
    class iterator {
    private:
        type_t* ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = type_t;
        using difference_type = std::ptrdiff_t;
        using pointer = type_t*;
        using reference = type_t&;

        explicit iterator(type_t* p = nullptr) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr; return tmp; }

        iterator& operator--() { --ptr; return *this; }
        iterator operator--(int) { iterator tmp = *this; --ptr; return tmp; }

        iterator operator+(difference_type n) const { return iterator(ptr + n); }
        iterator operator-(difference_type n) const { return iterator(ptr - n); }

        difference_type operator-(const iterator& other) const { return ptr - other.ptr; }

        reference operator[](difference_type n) const { return ptr[n]; }

        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
        bool operator<(const iterator& other) const { return ptr < other.ptr; }
        bool operator>(const iterator& other) const { return ptr > other.ptr; }
        bool operator<=(const iterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const iterator& other) const { return ptr >= other.ptr; }
    };

    class const_iterator {
    private:
        const type_t* ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = type_t;
        using difference_type = std::ptrdiff_t;
        using pointer = const type_t*;
        using reference = const type_t&;

        explicit const_iterator(const type_t* p = nullptr) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        const_iterator& operator++() { ++ptr; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++ptr; return tmp; }

        const_iterator& operator--() { --ptr; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --ptr; return tmp; }

        const_iterator operator+(difference_type n) const { return const_iterator(ptr + n); }
        const_iterator operator-(difference_type n) const { return const_iterator(ptr - n); }

        difference_type operator-(const const_iterator& other) const { return ptr - other.ptr; }

        reference operator[](difference_type n) const { return ptr[n]; }

        bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }
        bool operator<(const const_iterator& other) const { return ptr < other.ptr; }
        bool operator>(const const_iterator& other) const { return ptr > other.ptr; }
        bool operator<=(const const_iterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const const_iterator& other) const { return ptr >= other.ptr; }
    };

    // Standard iterator accessors
    iterator begin() { return iterator(data.get()); }
    iterator end() { return iterator(data.get() + length_); }

    const_iterator begin() const { return const_iterator(data.get()); }
    const_iterator end() const { return const_iterator(data.get() + length_); }

    const_iterator cbegin() const { return const_iterator(data.get()); }
    const_iterator cend() const { return const_iterator(data.get() + length_); }

    // Reverse iterator types and accessors
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }
};


// ------------------ Implementation ------------------

template<class type_t>
void DynamicSequentialList<type_t>::ensure_capacity(int min_capacity) {
    if (capacity_ >= min_capacity) return;

    int new_capacity = std::max(capacity_ * 2, min_capacity);
    auto new_data = std::make_unique<type_t[]>(new_capacity);
    for (int i = 0; i < length_; ++i) {
        new_data[i] = std::move(data[i]);
    }
    data = std::move(new_data);
    capacity_ = new_capacity;
}

template<class type_t>
DynamicSequentialList<type_t>::DynamicSequentialList() : capacity_(0), length_(0), data(nullptr) {}

template<class type_t>
DynamicSequentialList<type_t>::DynamicSequentialList(int count, const type_t& value)
    : capacity_(count), length_(count), data(std::make_unique<type_t[]>(count)) {
    for (auto i = 0; i < length_; ++i) {
        data[i] = value;
    }
}

template<class type_t>
DynamicSequentialList<type_t>::DynamicSequentialList(const DynamicSequentialList& other)
    : capacity_(other.capacity_), length_(other.length_), data(std::make_unique<type_t[]>(other.capacity_)) {
    for (auto i = 0; i < length_; ++i) {
        data[i] = other.data[i];
    }
}

template<class type_t>
DynamicSequentialList<type_t>::DynamicSequentialList(DynamicSequentialList&& other) noexcept
    : capacity_(other.capacity_), length_(other.length_), data(std::move(other.data)) {
        other.length_ = 0;
        other.capacity_ = 0;
}

template<class type_t>
const type_t& DynamicSequentialList<type_t>::operator[](const int& i) const {
    if (i < 0 || i >= length_) throw std::out_of_range("Index out of range");
    return data[i];
}

template<class type_t>
type_t& DynamicSequentialList<type_t>::operator[](const int& i) {
    if (i < 0 || i >= length_) throw std::out_of_range("Index out of range");
    return data[i];
}

template<class type_t>
DynamicSequentialList<type_t>& DynamicSequentialList<type_t>::operator=(const DynamicSequentialList& other) {
    if (this != &other) {
        auto new_data = std::make_unique<type_t[]>(other.capacity_);
        for (int i = 0; i < other.length_; ++i)
            new_data[i] = other.data[i];
        capacity_ = other.capacity_;
        length_ = other.length_;
        data = std::move(new_data);
    }
    return *this;
}

template<class type_t>
DynamicSequentialList<type_t>& DynamicSequentialList<type_t>::operator=(DynamicSequentialList&& other) noexcept {
    if (this != &other) {
        capacity_ = other.capacity_;
        length_ = other.length_;
        data = std::move(other.data);
        other.capacity_ = 0;
        other.length_ = 0;
    }
    return *this;
}

template<class type_t>
void swap(DynamicSequentialList<type_t>& a, DynamicSequentialList<type_t>& b) {
    using std::swap;
    swap(a.capacity_, b.capacity_);
    swap(a.length_, b.length_);
    swap(a.data, b.data);
}

template<class type_t>
int DynamicSequentialList<type_t>::length() const {
    return length_;
}

template<class type_t>
int DynamicSequentialList<type_t>::capacity() const {
    return capacity_;
}

template<class type_t>
bool DynamicSequentialList<type_t>::empty() const {
    return length_ == 0;
}

template<class type_t>
int DynamicSequentialList<type_t>::locate(const type_t& value) const {
    for (int i = 0; i < length_; ++i) {
        if (data[i] == value) return i;
    }
    return -1;
}

template<class type_t>
bool DynamicSequentialList<type_t>::insert(const int& pos, const type_t& val) {
    if (pos < 0 || pos > length_) throw std::out_of_range("Insert position out of range");

    ensure_capacity(length_+1);
    // Shift elements to the right to make room
    for (int i = length_; i > pos; --i) {
        data[i] = data[i - 1];
    }

    data[pos] = val;
    ++length_;
    return true;
}

template<class type_t>
bool DynamicSequentialList<type_t>::push_back(const type_t& val) {
    return insert(length_, val);
}

template<class type_t>
bool DynamicSequentialList<type_t>::del(const int& pos) {
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
void DynamicSequentialList<type_t>::clear() {
    length_ = 0;
}

template<class type_t>
void DynamicSequentialList<type_t>::output() const {
    std::cout << '[';
    for (int i = 0; i < length_; ++i) {
        std::cout << data[i];
        if (i + 1 < length_) std::cout << ", ";
    }
    std::cout << ']' << std::endl;
}

template<class type_t>
void DynamicSequentialList<type_t>::reserve(int new_capacity) {
    if (new_capacity <= capacity_) return;
    auto new_data = std::make_unique<type_t[]>(new_capacity);
    for (int i = 0; i < length_; ++i)
        new_data[i] = std::move(data[i]);
    data = std::move(new_data);
    capacity_ = new_capacity;
}

template<class type_t>
void DynamicSequentialList<type_t>::resize(int new_size, const type_t& value) {
    if (new_size < length_) {
        length_ = new_size;
    } else if (new_size > length_) {
        ensure_capacity(new_size);
        for (int i = length_; i < new_size; ++i)
            data[i] = value;
        length_ = new_size;
    }
}

} // namespace ds
