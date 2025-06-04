#pragma once

#include <stdexcept> // For std::out_of_range
#include <cstddef>   // For std::ptrdiff_t
#include <iostream>  // For output() method (and potential debugging)
#include <utility>   // For std::move

namespace ds {

/**
 * @brief A templated singly linked list container.
 * @tparam type_t The type of data to be stored in the list.
 */
template<class type_t>
class SinglyLinkedList {
public:
    /**
     * @brief Represents a node in the singly linked list.
     */
    struct Node {
        type_t data; ///< Data stored in the node.
        Node* next;  ///< Pointer to the next node in the list, or nullptr if this is the last node.

        /**
         * @brief Constructs a new Node.
         * @param value The data to store in the node.
         * @param next_node Pointer to the next node (defaults to nullptr).
         */
        Node(const type_t& value, Node* next_node = nullptr)
            : data(value), next(next_node) {}
    };

private:
    Node* head_;   ///< Pointer to the first node in the list.
    int length_;   ///< Number of elements currently in the list.

public:
    // Forward declaration for iterator classes
    class iterator;
    class const_iterator;

    /**
     * @brief Default constructor. Creates an empty list.
     * @post The list is empty (length() == 0).
     */
    SinglyLinkedList();

    /**
     * @brief Destructor. Frees all dynamically allocated memory.
     * @post All nodes in the list are deallocated. The list is empty.
     */
    ~SinglyLinkedList();

    /**
     * @brief Copy constructor. Creates a deep copy of another list.
     * @param other The SinglyLinkedList to copy.
     * @post This list is a deep copy of 'other'.
     */
    SinglyLinkedList(const SinglyLinkedList& other);

    /**
     * @brief Move constructor. Takes ownership of resources from another list.
     * @param other The SinglyLinkedList to move from.
     * @post This list contains the elements of 'other', and 'other' is left in a valid but unspecified (typically empty) state.
     */
    SinglyLinkedList(SinglyLinkedList&& other) noexcept;

    /**
     * @brief Copy assignment operator.
     * @param other The SinglyLinkedList to assign from.
     * @return A reference to this list after assignment.
     * @post This list is a deep copy of 'other'.
     */
    SinglyLinkedList& operator=(const SinglyLinkedList& other);

    /**
     * @brief Move assignment operator.
     * @param other The SinglyLinkedList to move assign from.
     * @return A reference to this list after move assignment.
     * @post This list contains the elements of 'other', and 'other' is left in a valid but unspecified (typically empty) state.
     */
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept;

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
     * @brief Removes all elements from the list.
     * @post The list is empty (length() == 0). All nodes are deallocated.
     */
    void clear();

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
     * @brief Finds the first occurrence of a value in the list.
     * @param value The value to locate.
     * @return The 0-based index of the first occurrence of the value, or -1 if not found.
     */
    int locate(const type_t& value) const;

    /**
     * @brief Inserts an element at a specific position.
     * @param pos The 0-based position at which to insert the value.
     * 0 <= pos <= length().
     * @param value The value to insert.
     * @return True if insertion was successful (always true if pos is valid).
     * @throw std::out_of_range if pos is invalid.
     * @post The element is inserted at 'pos', and elements from 'pos' onwards are shifted. Length increases by 1.
     */
    bool insert(const int& pos, const type_t& value);

    /**
     * @brief Deletes an element at a specific position.
     * @param pos The 0-based position of the element to delete.
     * 0 <= pos < length().
     * @return True if deletion was successful (always true if pos is valid and list not empty).
     * @throw std::out_of_range if pos is invalid or the list is empty.
     * @post The element at 'pos' is removed. Length decreases by 1.
     */
    bool del(const int& pos);

    /**
     * @brief Resizes the list to contain new_size elements.
     * @param new_size The desired new size of the list.
     * @param value The value to initialize new elements with if new_size > current length.
     * Defaults to a default-constructed type_t object.
     * @throw std::out_of_range if new_size is negative.
     * @post If new_size > length(), new elements are added to the end, initialized with 'value'.
     * If new_size < length(), elements are removed from the end.
     * If new_size == length(), no change.
     */
    void resize(int new_size, const type_t& value = type_t());

    /**
     * @brief Accesses the element at a specific position (const version).
     * @param i The 0-based index of the element to access.
     * @return A const reference to the element at index 'i'.
     * @throw std::out_of_range if index 'i' is invalid.
     */
    const type_t& operator[](const int& i) const;

    /**
     * @brief Accesses the element at a specific position (non-const version).
     * @param i The 0-based index of the element to access.
     * @return A reference to the element at index 'i'.
     * @throw std::out_of_range if index 'i' is invalid.
     */
    type_t& operator[](const int& i);

    // --- Iterator Support ---

    /**
     * @brief Provides an iterator for traversing the SinglyLinkedList.
     */
    class iterator {
    private:
        Node* current_; ///< Pointer to the current node the iterator points to.
    public:
        // C++ standard iterator traits
        using iterator_category = std::forward_iterator_tag;
        using value_type = type_t;
        using difference_type = std::ptrdiff_t;
        using pointer = type_t*;
        using reference = type_t&;

        /**
         * @brief Explicit constructor for the iterator.
         * @param node Pointer to the node to start iterating from.
         */
        explicit iterator(Node* node) : current_(node) {}

        /**
         * @brief Dereferences the iterator to get the data.
         * @return A reference to the data in the current node.
         */
        reference operator*() { return current_->data; }

        /**
         * @brief Accesses members of the data object via pointer.
         * @return A pointer to the data in the current node.
         */
        pointer operator->() { return &(current_->data); }

        /**
         * @brief Pre-increment operator. Advances the iterator to the next node.
         * @return A reference to this iterator after advancement.
         */
        iterator& operator++() {
            if (current_) current_ = current_->next;
            return *this;
        }

        /**
         * @brief Post-increment operator. Advances the iterator to the next node.
         * @return A copy of the iterator before advancement.
         */
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        /**
         * @brief Equality comparison operator.
         * @param other The iterator to compare against.
         * @return True if both iterators point to the same node, false otherwise.
         */
        bool operator==(const iterator& other) const { return current_ == other.current_; }

        /**
         * @brief Inequality comparison operator.
         * @param other The iterator to compare against.
         * @return True if the iterators point to different nodes, false otherwise.
         */
        bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    /**
     * @brief Provides a const_iterator for traversing the SinglyLinkedList with read-only access.
     */
    class const_iterator {
    private:
        const Node* current_; ///< Pointer to the current const node the iterator points to.
    public:
        // C++ standard iterator traits
        using iterator_category = std::forward_iterator_tag;
        using value_type = type_t; // Even for const_iterator, value_type is T, not const T
        using difference_type = std::ptrdiff_t;
        using pointer = const type_t*;   // Pointer to const
        using reference = const type_t&; // Reference to const

        /**
         * @brief Explicit constructor for the const_iterator.
         * @param node Pointer to the const node to start iterating from.
         */
        explicit const_iterator(const Node* node) : current_(node) {}

        /**
         * @brief Dereferences the iterator to get the data (const access).
         * @return A const reference to the data in the current node.
         */
        reference operator*() const { return current_->data; }

        /**
         * @brief Accesses members of the data object via pointer (const access).
         * @return A const pointer to the data in the current node.
         */
        pointer operator->() const { return &(current_->data); }

        /**
         * @brief Pre-increment operator. Advances the iterator to the next node.
         * @return A reference to this iterator after advancement.
         */
        const_iterator& operator++() {
            if (current_) current_ = current_->next;
            return *this;
        }

        /**
         * @brief Post-increment operator. Advances the iterator to the next node.
         * @return A copy of the iterator before advancement.
         */
        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++(*this);
            return temp;
        }

        /**
         * @brief Equality comparison operator.
         * @param other The const_iterator to compare against.
         * @return True if both iterators point to the same node, false otherwise.
         */
        bool operator==(const const_iterator& other) const { return current_ == other.current_; }
        
        /**
         * @brief Inequality comparison operator.
         * @param other The const_iterator to compare against.
         * @return True if the iterators point to different nodes, false otherwise.
         */
        bool operator!=(const const_iterator& other) const { return !(*this == other); }
    };

    /**
     * @brief Returns an iterator to the beginning of the list.
     * @return An iterator pointing to the first element.
     */
    iterator begin();

    /**
     * @brief Returns an iterator to the end of the list (one past the last element).
     * @return An iterator pointing to the theoretical element after the last one.
     */
    iterator end();

    /**
     * @brief Returns a const_iterator to the beginning of the list.
     * @return A const_iterator pointing to the first element.
     */
    const_iterator begin() const;

    /**
     * @brief Returns a const_iterator to the end of the list (one past the last element).
     * @return A const_iterator pointing to the theoretical element after the last one.
     */
    const_iterator end() const;

    /**
     * @brief Returns a const_iterator to the beginning of the list (canonical const version).
     * @return A const_iterator pointing to the first element.
     */
    const_iterator cbegin() const;

    /**
     * @brief Returns a const_iterator to the end of the list (canonical const version).
     * @return A const_iterator pointing to the theoretical element after the last one.
     */
    const_iterator cend() const;
};

template<class type_t>
SinglyLinkedList<type_t>::SinglyLinkedList() : head_(nullptr), length_(0) {}

template<class type_t>
SinglyLinkedList<type_t>::~SinglyLinkedList() {
    clear(); // Essential fix for memory leak
}

template<class type_t>
SinglyLinkedList<type_t>::SinglyLinkedList(const SinglyLinkedList& other) : head_(nullptr), length_(0) {
    Node* current_other = other.head_;
    while (current_other) {
        push_back(current_other->data); // Creates new nodes with copies of data
        current_other = current_other->next;
    }
}

template<class type_t>
SinglyLinkedList<type_t>::SinglyLinkedList(SinglyLinkedList&& other) noexcept
    : head_(other.head_), length_(other.length_) {
    other.head_ = nullptr;
    other.length_ = 0;
}

template<class type_t>
SinglyLinkedList<type_t>& SinglyLinkedList<type_t>::operator=(const SinglyLinkedList& other) {
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
SinglyLinkedList<type_t>& SinglyLinkedList<type_t>::operator=(SinglyLinkedList&& other) noexcept {
    if (this != &other) { // Self-assignment check
        clear(); // Clear current contents to free existing resources

        head_ = other.head_;
        length_ = other.length_;

        other.head_ = nullptr;
        other.length_ = 0;
    }
    return *this;
}

template<class type_t>
void SinglyLinkedList<type_t>::push_back(const type_t& value) {
    Node* new_node = new Node(value);
    if (!head_) {
        head_ = new_node;
    } else {
        Node* current = head_;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    ++length_;
}

template<class type_t>
void SinglyLinkedList<type_t>::push_front(const type_t& value) {
    Node* new_node = new Node(value, head_);
    head_ = new_node;
    ++length_;
}

template<class type_t>
void SinglyLinkedList<type_t>::clear() {
    Node* current = head_;
    while (current) {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
    head_ = nullptr;
    length_ = 0;
}

template<class type_t>
int SinglyLinkedList<type_t>::length() const {
    return length_;
}

template<class type_t>
bool SinglyLinkedList<type_t>::empty() const {
    return length_ == 0;
}

template<class type_t>
void SinglyLinkedList<type_t>::output() const {
    Node* current = head_;
    std::cout << "[";
    while (current) {
        std::cout << current->data;
        if (current->next) {
            std::cout << ", ";
        }
        current = current->next;
    }
    std::cout << "]" << std::endl;
}

template<class type_t>
typename SinglyLinkedList<type_t>::iterator SinglyLinkedList<type_t>::begin() {
    return iterator(head_);
}

template<class type_t>
typename SinglyLinkedList<type_t>::iterator SinglyLinkedList<type_t>::end() {
    return iterator(nullptr); // Points one beyond the last element
}

template<class type_t>
typename SinglyLinkedList<type_t>::const_iterator SinglyLinkedList<type_t>::begin() const {
    return const_iterator(head_);
}

template<class type_t>
typename SinglyLinkedList<type_t>::const_iterator SinglyLinkedList<type_t>::end() const {
    return const_iterator(nullptr);
}

template<class type_t>
typename SinglyLinkedList<type_t>::const_iterator SinglyLinkedList<type_t>::cbegin() const {
    return const_iterator(head_);
}

template<class type_t>
typename SinglyLinkedList<type_t>::const_iterator SinglyLinkedList<type_t>::cend() const {
    return const_iterator(nullptr);
}

template<class type_t>
int SinglyLinkedList<type_t>::locate(const type_t& value) const {
    Node* current = head_;
    int index = 0;
    while (current) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        ++index;
    }
    return -1; // Not found
}

template<class type_t>
bool SinglyLinkedList<type_t>::insert(const int& pos, const type_t& value) {
    if (pos < 0 || pos > length_) { // Allow insertion at pos == length_ (equivalent to push_back)
        throw std::out_of_range("Insert position out of range");
    }

    Node* new_node = new Node(value); // Fix: Declare new_node before if/else

    if (pos == 0) {
        new_node->next = head_;
        head_ = new_node;
    } else {
        Node* current = head_;
        // Traverse to the node *before* the insertion point
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    ++length_;
    return true;
}

template<class type_t>
bool SinglyLinkedList<type_t>::del(const int& pos) {
    if (empty()) { // Check if list is empty first
        throw std::out_of_range("Delete from empty list or position out of range");
    }
    if (pos < 0 || pos >= length_) { // pos must be within [0, length-1]
        throw std::out_of_range("Delete position out of range");
    }

    Node* to_delete = nullptr;
    if (pos == 0) {
        to_delete = head_;
        head_ = head_->next;
    } else {
        Node* current = head_;
        // Traverse to the node *before* the one to be deleted
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        to_delete = current->next;
        current->next = to_delete->next;
    }
    delete to_delete;
    --length_;
    return true;
}

template<class type_t>
void SinglyLinkedList<type_t>::resize(int new_size, const type_t& value) {
    if (new_size < 0) {
        throw std::out_of_range("New size must be non-negative");
    }
    while (length_ < new_size) {
        push_back(value);
    }
    while (length_ > new_size) {
        // Deleting from the end is less efficient for singly linked list
        // but del(length_ - 1) is the most straightforward way given current methods.
        // A pop_back() method would be more direct.
        del(length_ - 1);
    }
}

template<class type_t>
const type_t& SinglyLinkedList<type_t>::operator[](const int& i) const {
    if (i < 0 || i >= length_) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head_;
    for (int index = 0; index < i; ++index) {
        current = current->next;
    }
    return current->data;
}

template<class type_t>
type_t& SinglyLinkedList<type_t>::operator[](const int& i) {
    if (i < 0 || i >= length_) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head_;
    for (int index = 0; index < i; ++index) {
        current = current->next;
    }
    return current->data;
}

} // namespace ds