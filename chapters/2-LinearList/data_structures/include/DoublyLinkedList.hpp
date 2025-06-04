#pragma once

#include <stdexcept> // For std::out_of_range
#include <cstddef>   // For std::ptrdiff_t
#include <iostream>  // For output() method, std::cout
#include <utility>   // For std::swap, std::move

namespace ds {

/**
 * @brief A templated doubly linked list container.
 * @tparam type_t The type of data to be stored in the list.
 */
template<class type_t>
class DoublyLinkedList {
public:
    /**
     * @brief Represents a node in the doubly linked list.
     */
    struct Node {
        type_t data;          ///< Data stored in the node.
        Node* next;          ///< Pointer to the next node in the list.
        Node* prev;          ///< Pointer to the previous node in the list.

        /**
         * @brief Constructs a new Node.
         * @param value The data to store in the node.
         * @param next_node Pointer to the next node (defaults to nullptr).
         * @param prev_node Pointer to the previous node (defaults to nullptr).
         */
        Node(const type_t& value, Node* next_node = nullptr, Node* prev_node = nullptr)
            : data(value), next(next_node), prev(prev_node) {}
    };

private:
    Node* head_;   ///< Pointer to the first node in the list (nullptr if empty).
    Node* tail_;   ///< Pointer to the last node in the list (nullptr if empty).
    int length_;   ///< Number of elements currently in the list.

public:
    // Forward declarations for iterator classes
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    /**
     * @brief Default constructor. Creates an empty list.
     * @post The list is empty (length() == 0, head() == nullptr, tail() == nullptr).
     */
    DoublyLinkedList();

    /**
     * @brief Copy constructor. Creates a deep copy of another list.
     * @param other The DoublyLinkedList to copy.
     * @post This list is a deep copy of 'other'.
     */
    DoublyLinkedList(const DoublyLinkedList& other);

    /**
     * @brief Move constructor. Takes ownership of resources from another list.
     * @param other The DoublyLinkedList to move from.
     * @post This list contains the elements of 'other', and 'other' is left in a valid empty state.
     */
    DoublyLinkedList(DoublyLinkedList&& other) noexcept;

    /**
     * @brief Destructor. Frees all dynamically allocated memory.
     * @post All nodes in the list are deallocated. The list is empty.
     */
    ~DoublyLinkedList();

    /**
     * @brief Copy assignment operator.
     * @param other The DoublyLinkedList to assign from.
     * @return A reference to this list after assignment.
     * @post This list is a deep copy of 'other'. Previous contents are cleared.
     */
    DoublyLinkedList& operator=(const DoublyLinkedList& other);

    /**
     * @brief Move assignment operator.
     * @param other The DoublyLinkedList to move assign from.
     * @return A reference to this list after move assignment.
     * @post This list contains the elements of 'other', and 'other' is left in a valid empty state. Previous contents are cleared.
     */
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;

    /**
     * @brief Removes all elements from the list.
     * @post The list is empty (length() == 0). All nodes are deallocated.
     */
    void clear();

    /**
     * @brief Adds an element to the end of the list.
     * @param value The value to add.
     * @post The list's length is incremented by 1, and the new element is at the end.
     */
    void push_back(const type_t& value);

    /**
     * @brief Adds an element to the front of the list.
     * @param value The value to add.
     * @post The list's length is incremented by 1, and the new element is at the front.
     */
    void push_front(const type_t& value);

    /**
     * @brief Removes the first node from the list.
     * @post The first node is removed, and length() is decremented by 1.
     * If the list was empty, no operation is performed.
     * @note If the list is empty, the behavior is a no-op.
     */
    void pop_front();

    /**
     * @brief Removes the last node from the list.
     * @post The last node is removed, and length() is decremented by 1.
     * If the list was empty, no operation is performed.
     * @note If the list is empty, the behavior is a no-op.
     */
    void pop_back();

    /**
     * @brief Returns the number of elements in the list.
     * @return The current length of the list.
     */
    int length() const;

    /**
     * @brief Checks if the list is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Prints the contents of the list to standard output.
     * @note Requires that type_t is streamable via std::cout.
     * Example format: [data1, data2, data3]
     */
    void output() const;

    /**
     * @brief Accesses the element at a specific position (const version).
     * Optimized to traverse from head or tail based on index proximity.
     * @param i The 0-based index of the element to access.
     * @return A const reference to the element at index 'i'.
     * @throw std::out_of_range if index 'i' is invalid.
     */
    const type_t& operator[](const int& i) const;

    /**
     * @brief Accesses the element at a specific position (non-const version).
     * Optimized to traverse from head or tail based on index proximity.
     * @param i The 0-based index of the element to access.
     * @return A reference to the element at index 'i'.
     * @throw std::out_of_range if index 'i' is invalid.
     */
    type_t& operator[](const int& i);

    /**
     * @brief Swaps the contents of this list with another.
     * @param other The list to swap with.
     * @post The contents of this list and 'other' are exchanged.
     */
    void swap(DoublyLinkedList& other) noexcept;

    /**
     * @brief Returns a pointer to the head node.
     * @return Pointer to the first node in the list, or nullptr if empty.
     */
    Node* head() const;

    /**
     * @brief Returns a pointer to the tail node.
     * @return Pointer to the last node in the list, or nullptr if empty.
     */
    Node* tail() const;

    // --- Iterator Support ---

    /**
     * @brief Provides a bidirectional iterator for traversing the DoublyLinkedList.
     */
    class iterator {
    private:
        Node* current_; ///< Pointer to the current node.
        // To implement end()-- to last element, iterator might need a pointer to tail_ or list.
        // Current implementation: --end() does nothing if current_ is nullptr.

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = type_t;
        using difference_type = std::ptrdiff_t;
        using pointer = type_t*;
        using reference = type_t&;

        /** @brief Constructs an iterator pointing to the given node. @param node Node to point to. */
        explicit iterator(Node* node) : current_(node) {}

        /** @brief Dereferences the iterator. @return Reference to the current element's data. */
        reference operator*() { return current_->data; }
        /** @brief Member access operator. @return Pointer to the current element's data. */
        pointer operator->() { return &(current_->data); }

        /** @brief Pre-increment. Advances to the next node. @return Reference to this iterator. */
        iterator& operator++() { if (current_) current_ = current_->next; return *this; }
        /** @brief Post-increment. Advances to the next node. @return Iterator before incrementing. */
        iterator operator++(int) { iterator temp = *this; ++(*this); return temp; }

        /** @brief Pre-decrement. Moves to the previous node. @return Reference to this iterator. 
         * @note If current_ is nullptr (e.g. end iterator), this operation has no effect.
         * If current_ points to head, it becomes nullptr (before-begin).
         */
        iterator& operator--() { if (current_) current_ = current_->prev; return *this; }
        /** @brief Post-decrement. Moves to the previous node. @return Iterator before decrementing. */
        iterator operator--(int) { iterator temp = *this; --(*this); return temp; }

        /** @brief Equality comparison. @param other Iterator to compare. @return True if pointing to the same node. */
        bool operator==(const iterator& other) const { return current_ == other.current_; }
        /** @brief Inequality comparison. @param other Iterator to compare. @return True if not pointing to the same node. */
        bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    /** @brief Provides a const bidirectional iterator. */
    class const_iterator {
    private:
        const Node* current_;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = type_t;
        using difference_type = std::ptrdiff_t;
        using pointer = const type_t*;
        using reference = const type_t&;

        explicit const_iterator(const Node* node) : current_(node) {}
        reference operator*() const { return current_->data; }
        pointer operator->() const { return &(current_->data); }
        const_iterator& operator++() { if (current_) current_ = current_->next; return *this; }
        const_iterator operator++(int) { const_iterator temp = *this; ++(*this); return temp; }
        /** @note If current_ is nullptr (e.g. cend iterator), this operation has no effect.
         * If current_ points to head, it becomes nullptr (before-begin).
         */
        const_iterator& operator--() { if (current_) current_ = current_->prev; return *this; }
        const_iterator operator--(int) { const_iterator temp = *this; --(*this); return temp; }
        bool operator==(const const_iterator& other) const { return current_ == other.current_; }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }
    };

    /** @brief Provides a reverse bidirectional iterator. */
    class reverse_iterator {
    private:
        Node* current_; // Points to the current element from a reverse perspective.
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = type_t;
        using difference_type = std::ptrdiff_t;
        using pointer = type_t*;
        using reference = type_t&;

        explicit reverse_iterator(Node* node) : current_(node) {}
        reference operator*() { return current_->data; }
        pointer operator->() { return &(current_->data); }

        /** @brief Pre-increment (moves reverse iterator towards beginning). @return Reference to this iterator. */
        reverse_iterator& operator++() { if (current_) current_ = current_->prev; return *this; }
        /** @brief Post-increment. @return Iterator before incrementing. */
        reverse_iterator operator++(int) { reverse_iterator temp = *this; ++(*this); return temp; }
        
        /** @brief Pre-decrement (moves reverse iterator towards end). @return Reference to this iterator. 
         * @note If current_ is nullptr (e.g. rend iterator), this operation has no effect.
         * If current_ points to tail, it becomes nullptr (after-end for reverse).
        */
        reverse_iterator& operator--() { if (current_) current_ = current_->next; return *this; }
        /** @brief Post-decrement. @return Iterator before decrementing. */
        reverse_iterator operator--(int) { reverse_iterator temp = *this; --(*this); return temp; }

        bool operator==(const reverse_iterator& other) const { return current_ == other.current_; }
        bool operator!=(const reverse_iterator& other) const { return !(*this == other); }
    };
    
    /** @brief Provides a const reverse bidirectional iterator. */
    class const_reverse_iterator {
    private:
        const Node* current_;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = type_t;
        using difference_type = std::ptrdiff_t;
        using pointer = const type_t*;
        using reference = const type_t&;

        explicit const_reverse_iterator(const Node* node) : current_(node) {}
        reference operator*() const { return current_->data; }
        pointer operator->() const { return &(current_->data); }
        const_reverse_iterator& operator++() { if (current_) current_ = current_->prev; return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator temp = *this; ++(*this); return temp; }
        /** @note If current_ is nullptr (e.g. crend iterator), this operation has no effect.
         * If current_ points to tail, it becomes nullptr (after-end for reverse).
        */
        const_reverse_iterator& operator--() { if (current_) current_ = current_->next; return *this; }
        const_reverse_iterator operator--(int) { const_reverse_iterator temp = *this; --(*this); return temp; }
        bool operator==(const const_reverse_iterator& other) const { return current_ == other.current_; }
        bool operator!=(const const_reverse_iterator& other) const { return !(*this == other); }
    };

    // Iterator methods
    /** @brief Returns an iterator to the beginning. @return Iterator to the first element. */
    iterator begin();
    /** @brief Returns an iterator to past-the-end. @return Iterator one position beyond the last element. */
    iterator end();
    /** @brief Returns a const_iterator to the beginning. @return Const_iterator to the first element. */
    const_iterator begin() const;
    /** @brief Returns a const_iterator to past-the-end. @return Const_iterator one position beyond the last element. */
    const_iterator end() const;
    /** @brief Returns a const_iterator to the beginning. @return Const_iterator to the first element. */
    const_iterator cbegin() const;
    /** @brief Returns a const_iterator to past-the-end. @return Const_iterator one position beyond the last element. */
    const_iterator cend() const;

    // Reverse iterator methods
    /** @brief Returns a reverse_iterator to the reverse beginning (last element). @return Reverse_iterator to the last element. */
    reverse_iterator rbegin();
    /** @brief Returns a reverse_iterator to past-the-reverse-end (before first element). @return Reverse_iterator one position before the first element. */
    reverse_iterator rend();
    /** @brief Returns a const_reverse_iterator to the reverse beginning (last element). @return Const_reverse_iterator to the last element. */
    const_reverse_iterator rbegin() const;
    /** @brief Returns a const_reverse_iterator to past-the-reverse-end (before first element). @return Const_reverse_iterator one position before the first element. */
    const_reverse_iterator rend() const;
    /** @brief Returns a const_reverse_iterator to the reverse beginning (last element). @return Const_reverse_iterator to the last element. */
    const_reverse_iterator crbegin() const;
    /** @brief Returns a const_reverse_iterator to past-the-reverse-end (before first element). @return Const_reverse_iterator one position before the first element. */
    const_reverse_iterator crend() const;
};

// --- Constructors, Destructor, Assignment Operators ---

template<class type_t>
DoublyLinkedList<type_t>::DoublyLinkedList() : head_(nullptr), tail_(nullptr), length_(0) {}

template<class type_t>
DoublyLinkedList<type_t>::DoublyLinkedList(const DoublyLinkedList& other)
    : head_(nullptr), tail_(nullptr), length_(0) {
    Node* current_other = other.head_;
    while (current_other) {
        push_back(current_other->data); // Creates new nodes with copies of data
        current_other = current_other->next;
    }
}

template<class type_t>
DoublyLinkedList<type_t>::DoublyLinkedList(DoublyLinkedList&& other) noexcept
    : head_(other.head_), tail_(other.tail_), length_(other.length_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.length_ = 0;
}

template<class type_t>
DoublyLinkedList<type_t>::~DoublyLinkedList() {
    clear();
}

template<class type_t>
DoublyLinkedList<type_t>& DoublyLinkedList<type_t>::operator=(const DoublyLinkedList& other) {
    if (this != &other) { // Self-assignment check
        clear(); // Clear current contents
        Node* current_other = other.head_;
        while (current_other) {
            push_back(current_other->data);
            current_other = current_other->next;
        }
    }
    return *this;
}

template<class type_t>
DoublyLinkedList<type_t>& DoublyLinkedList<type_t>::operator=(DoublyLinkedList&& other) noexcept {
    if (this != &other) { // Self-assignment check
        clear(); // Clear current contents to free existing resources

        head_ = other.head_;
        tail_ = other.tail_;
        length_ = other.length_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.length_ = 0;
    }
    return *this;
}

// --- Basic Operations ---

template<class type_t>
void DoublyLinkedList<type_t>::clear() {
    Node* current = head_;
    while (current) {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
}

template<class type_t>
void DoublyLinkedList<type_t>::push_back(const type_t& value) {
    Node* new_node = new Node(value);
    if (tail_) { // List is not empty
        tail_->next = new_node;
        new_node->prev = tail_;
        tail_ = new_node;
    } else { // List was empty
        head_ = tail_ = new_node;
    }
    ++length_;
}

template<class type_t>
void DoublyLinkedList<type_t>::push_front(const type_t& value) {
    Node* new_node = new Node(value);
    if (head_) { // List is not empty
        head_->prev = new_node;
        new_node->next = head_;
        head_ = new_node;
    } else { // List was empty
        head_ = tail_ = new_node;
    }
    ++length_;
}

template<class type_t>
void DoublyLinkedList<type_t>::pop_front() {
    if (head_) { // If list is not empty
        Node* to_delete = head_;
        head_ = head_->next;
        if (head_) { // List still not empty
            head_->prev = nullptr;
        } else { // List became empty
            tail_ = nullptr;
        }
        delete to_delete;
        --length_;
    }
}

template<class type_t>
void DoublyLinkedList<type_t>::pop_back() {
    if (tail_) { // If list is not empty
        Node* to_delete = tail_;
        tail_ = tail_->prev;
        if (tail_) { // List still not empty
            tail_->next = nullptr;
        } else { // List became empty
            head_ = nullptr;
        }
        delete to_delete;
        --length_;
    }
}

template<class type_t>
int DoublyLinkedList<type_t>::length() const {
    return length_;
}

template<class type_t>
bool DoublyLinkedList<type_t>::empty() const {
    return length_ == 0;
}

template<class type_t>
void DoublyLinkedList<type_t>::output() const {
    Node* current = head_;
    std::cout << "[";
    bool first = true;
    while (current) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << current->data;
        first = false;
        current = current->next;
    }
    std::cout << "]" << std::endl;
}

template<class type_t>
const type_t& DoublyLinkedList<type_t>::operator[](const int& i) const {
    if (i < 0 || i >= length_) {
        throw std::out_of_range("Index out of range in DoublyLinkedList::operator[] const");
    }
    Node* current;
    if (i < length_ / 2) { // Closer to head
        current = head_;
        for (int index = 0; index < i; ++index) {
            current = current->next;
        }
    } else { // Closer to tail
        current = tail_;
        for (int index = 0; index < length_ - 1 - i; ++index) {
            current = current->prev;
        }
    }
    return current->data;
}

template<class type_t>
type_t& DoublyLinkedList<type_t>::operator[](const int& i) {
    if (i < 0 || i >= length_) {
        throw std::out_of_range("Index out of range in DoublyLinkedList::operator[]");
    }
    Node* current;
    if (i < length_ / 2) { // Closer to head
        current = head_;
        for (int index = 0; index < i; ++index) {
            current = current->next;
        }
    } else { // Closer to tail
        current = tail_;
        for (int index = 0; index < length_ - 1 - i; ++index) {
            current = current->prev;
        }
    }
    return current->data;
}

template<class type_t>
void DoublyLinkedList<type_t>::swap(DoublyLinkedList& other) noexcept {
    using std::swap; // Enable ADL
    swap(head_, other.head_);
    swap(tail_, other.tail_);
    swap(length_, other.length_);
}

template<class type_t>
typename DoublyLinkedList<type_t>::Node* DoublyLinkedList<type_t>::head() const {
    return head_;
}

template<class type_t>
typename DoublyLinkedList<type_t>::Node* DoublyLinkedList<type_t>::tail() const {
    return tail_;
}

// --- Iterator Method Implementations ---

template<class type_t>
typename DoublyLinkedList<type_t>::iterator DoublyLinkedList<type_t>::begin() {
    return iterator(head_);
}

template<class type_t>
typename DoublyLinkedList<type_t>::iterator DoublyLinkedList<type_t>::end() {
    return iterator(nullptr); // Points one beyond the last element (tail_->next)
}

template<class type_t>
typename DoublyLinkedList<type_t>::const_iterator DoublyLinkedList<type_t>::begin() const {
    return const_iterator(head_);
}

template<class type_t>
typename DoublyLinkedList<type_t>::const_iterator DoublyLinkedList<type_t>::end() const {
    return const_iterator(nullptr);
}

template<class type_t>
typename DoublyLinkedList<type_t>::const_iterator DoublyLinkedList<type_t>::cbegin() const {
    return const_iterator(head_);
}

template<class type_t>
typename DoublyLinkedList<type_t>::const_iterator DoublyLinkedList<type_t>::cend() const {
    return const_iterator(nullptr);
}

// Reverse Iterators
template<class type_t>
typename DoublyLinkedList<type_t>::reverse_iterator DoublyLinkedList<type_t>::rbegin() {
    return reverse_iterator(tail_); // Starts at the actual last element
}

template<class type_t>
typename DoublyLinkedList<type_t>::reverse_iterator DoublyLinkedList<type_t>::rend() {
    return reverse_iterator(nullptr); // Points one beyond the "reverse" end (head_->prev)
}

template<class type_t>
typename DoublyLinkedList<type_t>::const_reverse_iterator DoublyLinkedList<type_t>::rbegin() const {
    return const_reverse_iterator(tail_);
}

template<class type_t>
typename DoublyLinkedList<type_t>::const_reverse_iterator DoublyLinkedList<type_t>::rend() const {
    return const_reverse_iterator(nullptr);
}

template<class type_t>
typename DoublyLinkedList<type_t>::const_reverse_iterator DoublyLinkedList<type_t>::crbegin() const {
    return const_reverse_iterator(tail_);
}

template<class type_t>
typename DoublyLinkedList<type_t>::const_reverse_iterator DoublyLinkedList<type_t>::crend() const {
    return const_reverse_iterator(nullptr);
}
} // namespace ds
