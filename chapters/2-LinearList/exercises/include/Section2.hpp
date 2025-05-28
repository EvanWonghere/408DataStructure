/**
 * @file Section2.hpp
 * @brief Implements various operations on static and dynamic sequential lists.
 *
 * @namespace ex
 * Contains functions for manipulating StaticSequentialList<T> and DynamicSequentialList<T>.
 *
 * @details
 * The following operations are provided for both static and dynamic sequential lists:
 * - pop_min                : Remove and return the minimum element from the list.
 * - reverse                : Reverse the entire list or a subrange of the list.
 * - del_x                  : Delete all occurrences of a specific value from the list.
 * - del_between            : Delete all elements within a specified exclusive range.
 * - unique                 : Remove duplicate elements from a sorted list.
 * - merge                  : Merge two sorted lists into a new sorted list.
 * - swap_inside            : Swap two adjacent blocks within the list.
 * - find_and_swap_or_insert : Insert an element into a sorted list while maintaining order.
 * - output_intersection    : Output the intersection of three sorted lists.
 * - sift_left              : Left-rotate the list by a specified number of positions.
 * - get_median             : Find the median of two sorted lists of equal length.
 * - get_main_element       : Find the majority element (appearing more than half the time), if any.
 * - get_min_positive       : Find the smallest missing positive integer in the list.
 * - get_min_triplet_dist   : Find the minimal "triplet distance" among three sorted arrays.
 *
 * Each function is overloaded for both StaticSequentialList<T> and DynamicSequentialList<T> where applicable.
 *
 * Helper functions for block swapping are also provided for dynamic lists.
 *
 * @note
 * - Some functions assume the input lists are sorted.
 * - Some functions may throw exceptions on invalid input (e.g., empty list, invalid range).
 */

#pragma once

#include "StaticSequentialList.hpp"
#include "DynamicSequentialList.hpp"

#include <cmath>
#include <limits>
#include <algorithm>

using namespace ds;

namespace ex {
// -------------- Declarations --------------

template<class type_t> type_t pop_min(StaticSequentialList<type_t>& list);
template<class type_t> type_t pop_min(DynamicSequentialList<type_t>& list);

template<class type_t> void reverse(StaticSequentialList<type_t>& list);
template<class type_t> void reverse(StaticSequentialList<type_t>& list, int i, int j);
template<class type_t> void reverse(DynamicSequentialList<type_t>& list);
template<class type_t> void reverse(DynamicSequentialList<type_t>& list, int i, int j);

template<class type_t> void del_x(StaticSequentialList<type_t>& list, const type_t& x);
template<class type_t> void del_x(DynamicSequentialList<type_t>& list, const type_t& x);

template<class type_t> void del_between(StaticSequentialList<type_t>& list, const type_t& s, const type_t& t);
template<class type_t> void del_between(DynamicSequentialList<type_t>& list, const type_t& s, const type_t& t);

template<class type_t> void unique(StaticSequentialList<type_t>& list);
template<class type_t> void unique(DynamicSequentialList<type_t>& list);

template<class type_t> StaticSequentialList<type_t> merge(const StaticSequentialList<type_t>& a, const StaticSequentialList<type_t>& b);
template<class type_t> DynamicSequentialList<type_t> merge(const DynamicSequentialList<type_t>& a, const DynamicSequentialList<type_t>& b);

template<class type_t> void swap_inside(StaticSequentialList<type_t>& list, const int& m, const int& n);
// Helper methods of swap_inside.
template<class type_t> void swap_block(DynamicSequentialList<type_t>& list, const int& start1, const int& start2, const int& len);
template<class type_t> void block_swap(DynamicSequentialList<type_t>& list, const int& l, const int& m, const int& r);
// Using block swap.
template<class type_t> void swap_inside(DynamicSequentialList<type_t>& list, const int& m, const int& n);

template<class type_t> void find_and_swap_or_insert(StaticSequentialList<type_t>& list, const type_t& x);
template<class type_t> void find_and_swap_or_insert(DynamicSequentialList<type_t>& list, const type_t& x);

template<class type_t> void output_intersection(const StaticSequentialList<type_t>& a, const StaticSequentialList<type_t>& b, const StaticSequentialList<type_t>& c);
template<class type_t> void output_intersection(const DynamicSequentialList<type_t>& a, const DynamicSequentialList<type_t>& b, const DynamicSequentialList<type_t>& c);

template<class type_t> void sift_left(StaticSequentialList<type_t>& list, const int& p);
template<class type_t> void sift_left(DynamicSequentialList<type_t>& list, const int& p);

template<class type_t> type_t get_median(const StaticSequentialList<type_t>& a, const StaticSequentialList<type_t>& b);
template<class type_t> type_t get_median(const DynamicSequentialList<type_t>& a, const DynamicSequentialList<type_t>& b);

template<class type_t> type_t get_main_element(StaticSequentialList<type_t>& list);
template<class type_t> type_t get_main_element(DynamicSequentialList<type_t>& list);

template<class type_t> type_t get_min_positive(StaticSequentialList<type_t>& list);
template<class type_t> type_t get_min_positive(DynamicSequentialList<type_t>& list);

// dist = |a-b| + |b-c| + |a-c| = max(a, b, c) - min(a, b, c)
template<class type_t> int get_min_triplet_dist(const StaticSequentialList<type_t>& a, const StaticSequentialList<type_t>& b, const StaticSequentialList<type_t>& c);
template<class type_t> int get_min_triplet_dist(const DynamicSequentialList<type_t>& a, const DynamicSequentialList<type_t>& b, const DynamicSequentialList<type_t>& c);


// -------------- Implementations --------------

/**
 * @brief Removes and returns the minimum element from a StaticSequentialList.
 * 
 * Finds the minimum element, replaces its position with the last element, and removes the last element.
 * Only the first occurrence of the minimum is removed.
 * 
 * @tparam type_t The type of elements in the list.
 * @param list The static sequential list to operate on.
 * @return The minimum element that was removed.
 * @throws std::out_of_range if the list is empty.
 */
template<class type_t>
type_t pop_min(StaticSequentialList<type_t>& list) {
    if (list.empty()) throw std::out_of_range("List can't be empty.");

    auto minimum = list[0];
    for (auto i = 1; i < list.length(); ++i)
        if (list[i] < minimum) minimum = list[i];
    
    auto index = list.locate(minimum);
    list[index] = list[list.length()-1];
    list.del(list.length()-1);

    return minimum;
}

/**
 * @brief Removes and returns the minimum element from a DynamicSequentialList.
 * 
 * Finds the minimum element, replaces its position with the last element, and removes the last element.
 * Only the first occurrence of the minimum is removed.
 * 
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to operate on.
 * @return The minimum element that was removed.
 * @throws std::out_of_range if the list is empty.
 */
template<class type_t>
type_t pop_min(DynamicSequentialList<type_t>& list) {
    if (list.empty()) throw std::out_of_range("List can't be empty.");

    auto minimum = list[0];
    for (auto i = 1; i < list.length(); ++i)
        if (list[i] < minimum) minimum = list[i];
    
    auto index = list.locate(minimum);
    list[index] = list[list.length()-1];
    list.del(list.length()-1);

    return minimum;
}

/**
 * @brief Reverses the entire StaticSequentialList in place.
 * 
 * Swaps elements from both ends of the list moving towards the center.
 * If the list is empty, the function does nothing.
 * 
 * @tparam type_t The type of elements in the list.
 * @param list The static sequential list to reverse.
 */
template <class type_t>
void reverse(StaticSequentialList<type_t> &list)
{
    if (list.empty()) return;

    int i = 0, j = list.length()-1;
    while (i < j) {
        std::swap(list[i++], list[j--]);
    }
}

/**
 * @brief Reverses a subrange [i, j] of the StaticSequentialList in place.
 * 
 * Swaps elements between indices i and j moving towards the center.
 * If the list is empty or indices are out of range or i >= j, the function does nothing.
 * 
 * @tparam type_t The type of elements in the list.
 * @param list The static sequential list to reverse a subrange of.
 * @param i The starting index of the subrange (inclusive).
 * @param j The ending index of the subrange (inclusive).
 */
template <class type_t>
void reverse(StaticSequentialList<type_t> &list, int i, int j)
{
    if (list.empty()) return;
    if (i < 0 || j >= list.length() || i >= j) return;

    while (i < j) {
        std::swap(list[i++], list[j--]);
    }
}

/**
 * @brief Reverses the entire DynamicSequentialList in place.
 *
 * Swaps elements from both ends of the list moving towards the center.
 * If the list is empty, the function does nothing.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to reverse.
 */
template <class type_t>
void reverse(DynamicSequentialList<type_t> &list)
{
    if (list.empty()) return;

    int i = 0, j = list.length() - 1;
    while (i < j) {
        std::swap(list[i++], list[j--]);
    }
}

/**
 * @brief Reverses a subrange [i, j] of the DynamicSequentialList in place.
 *
 * Swaps elements between indices i and j moving towards the center.
 * If the list is empty or indices are out of range or i >= j, the function does nothing.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to reverse a subrange of.
 * @param i The starting index of the subrange (inclusive).
 * @param j The ending index of the subrange (inclusive).
 */
template <class type_t>
void reverse(DynamicSequentialList<type_t> &list, int i, int j)
{
    if (list.empty()) return;
    if (i < 0 || j >= list.length() || i >= j) return;

    while (i < j) {
        std::swap(list[i++], list[j--]);
    }
}

/**
 * @brief Deletes all occurrences of a specific value from a StaticSequentialList.
 *
 * Iterates through the list from start to end, skipping elements equal to x,
 * and compacts the remaining elements towards the front.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The static sequential list to operate on.
 * @param x The value to delete from the list.
 */
template <class type_t>
void del_x(StaticSequentialList<type_t> &list, const type_t &x)
{
    if (list.empty()) return;

    int new_length = 0;
    for (int i = 0; i < list.length(); ++i) {
        if (list[i] == x) continue;
        list[new_length++] = list[i];
    }

    while (list.length() > new_length) list.del(list.length() - 1);
}

/**
 * @brief Deletes all occurrences of a specific value from a DynamicSequentialList.
 *
 * Iterates through the list from start to end, skipping elements equal to x,
 * and compacts the remaining elements towards the front.
 * Resizes the list to the new length.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to operate on.
 * @param x The value to delete from the list.
 */
template <class type_t>
void del_x(DynamicSequentialList<type_t> &list, const type_t &x)
{
    if (list.empty()) return;

    int new_length = 0;
    for (int i = 0; i < list.length(); ++i) {
        if (list[i] == x) continue;
        list[new_length++] = list[i];
    }

    list.resize(new_length);
}

/**
 * @brief Deletes all elements strictly between s and t (exclusive) from a StaticSequentialList, preserving order.
 *
 * Iterates through the list, copying elements not in the exclusive range (s, t) to the front.
 * The order of the remaining elements is preserved.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The static sequential list to operate on.
 * @param s The lower bound (inclusive).
 * @param t The upper bound (inclusive).
 * @throws std::out_of_range if the list is empty.
 * @throws std::logic_error if s >= t.
 */
template <class type_t>
void del_between(StaticSequentialList<type_t> &list, const type_t &s, const type_t &t)
{
    if (list.empty()) throw std::out_of_range("List can't be empty");
    if (s >= t) throw std::logic_error("Lower bound must be less than upper bound");

    int new_length = 0;
    for (int i = 0; i < list.length(); ++i) {
        if (list[i] >= s && list[i] <= t) continue;
        list[new_length++] = list[i];
    }
    while (list.length() != new_length) list.del(list.length() - 1);
}

/**
 * @brief Deletes all elements strictly between s and t (exclusive) from a DynamicSequentialList, preserving order.
 *
 * Iterates through the list, copying elements not in the exclusive range (s, t) to the front.
 * The order of the remaining elements is preserved.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to operate on.
 * @param s The lower bound (inclusive).
 * @param t The upper bound (inclusive).
 * @throws std::out_of_range if the list is empty.
 * @throws std::logic_error if s >= t.
 */
template <class type_t>
void del_between(DynamicSequentialList<type_t> &list, const type_t &s, const type_t &t)
{
    if (list.empty()) throw std::out_of_range("List can't be empty");
    if (s >= t) throw std::logic_error("Lower bound must be less than upper bound");

    int new_length = 0;
    for (int i = 0; i < list.length(); ++i) {
        if (list[i] >= s && list[i] <= t) continue;
        list[new_length++] = list[i];
    }
    list.resize(new_length);
}

/**
 * @brief Removes duplicate elements from a sorted StaticSequentialList in place.
 *
 * Iterates through the sorted list, moving unique elements to the front and deleting the rest.
 * The order of the remaining elements is preserved.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The static sequential list to operate on (must be sorted).
 */
template <class type_t>
void unique(StaticSequentialList<type_t> &list)
{
    if (list.length() <= 1) return;

    int i = 0;
    for (int j = 1; j < list.length(); ++j) {
        if (list[j] != list[i]) {
            ++i;
            list[i] = list[j];
        }
    }
    while (list.length() != i + 1) list.del(list.length() - 1);
}

/**
 * @brief Removes duplicate elements from a sorted DynamicSequentialList in place.
 *
 * Iterates through the sorted list, moving unique elements to the front and resizing the list.
 * The order of the remaining elements is preserved.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to operate on (must be sorted).
 */
template <class type_t>
void unique(DynamicSequentialList<type_t> &list)
{
    if (list.length() <= 1) return;

    int i = 0;
    for (int j = 1; j < list.length(); ++j) {
        if (list[j] != list[i]) {
            ++i;
            list[i] = list[j];
        }
    }
    list.resize(i + 1);
}

/**
 * @brief Merges two sorted StaticSequentialLists into a new sorted list.
 *
 * Iterates through both input lists, comparing elements and inserting the smaller one into the new list.
 * Remaining elements from either list are appended at the end.
 *
 * @tparam type_t The type of elements in the lists.
 * @param a The first sorted static sequential list.
 * @param b The second sorted static sequential list.
 * @return A new StaticSequentialList containing all elements from a and b in sorted order.
 */
template <class type_t>
StaticSequentialList<type_t> merge(const StaticSequentialList<type_t> &a, const StaticSequentialList<type_t> &b)
{
    if (a.empty()) return StaticSequentialList<type_t>(b);
    if (b.empty()) return StaticSequentialList<type_t>(a);

    StaticSequentialList<type_t> new_list(a.length() + b.length());

    auto i = 0, j = 0;
    while (i < a.length() && j < b.length()) {
        new_list.push_back(a[i] < b[j] ? a[i++] : b[j++]);
    }

    while (i < a.length()) new_list.push_back(a[i++]);
    while (j < b.length()) new_list.push_back(b[j++]);

    return new_list;
}

/**
 * @brief Merges two sorted DynamicSequentialLists into a new sorted list.
 *
 * Iterates through both input lists, comparing elements and inserting the smaller one into the new list.
 * Remaining elements from either list are appended at the end.
 *
 * @tparam type_t The type of elements in the lists.
 * @param a The first sorted dynamic sequential list.
 * @param b The second sorted dynamic sequential list.
 * @return A new DynamicSequentialList containing all elements from a and b in sorted order.
 */
template <class type_t>
DynamicSequentialList<type_t> merge(const DynamicSequentialList<type_t> &a, const DynamicSequentialList<type_t> &b)
{
    if (a.empty()) return DynamicSequentialList<type_t>(b);
    if (b.empty()) return DynamicSequentialList<type_t>(a);

    DynamicSequentialList<type_t> new_list;

    auto i = 0, j = 0;
    while (i < a.length() && j < b.length()) {
        new_list.push_back(a[i] < b[j] ? a[i++] : b[j++]);
    }

    while (i < a.length()) new_list.push_back(a[i++]);
    while (j < b.length()) new_list.push_back(b[j++]);

    return new_list;
}

/**
 * @brief Swaps two adjacent blocks of size m and n in a StaticSequentialList using the reversal method.
 *
 * The function swaps the first block [0, m-1] with the second block [m, m+n-1] in place.
 * The algorithm reverses the first block, then the second block, then the whole block [0, m+n-1].
 * If m or n is invalid, throws std::out_of_range.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The static sequential list to operate on.
 * @param m The size of the first block.
 * @param n The size of the second block.
 * @throws std::out_of_range if m or n is negative or m+n > list.length().
 */
template <class type_t>
void swap_inside(StaticSequentialList<type_t> &list, const int &m, const int &n)
{
    if (m < 0 || n < 0 || m + n > list.length())
        throw std::out_of_range("Invalid sublist size");
    if (m == 0 || n == 0) return;
    reverse(list, 0, m-1);
    reverse(list, m, m+n-1);
    reverse(list, 0, m+n-1);
}

/**
 * @brief Swaps two blocks of equal or different sizes in a DynamicSequentialList using block swap algorithm.
 *
 * Swaps the block [start1, start1+len-1] with [start2, start2+len-1].
 * Used internally by block_swap.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to operate on.
 * @param start1 The starting index of the first block.
 * @param start2 The starting index of the second block.
 * @param len The length of the blocks to swap.
 */
template <class type_t>
void swap_block(DynamicSequentialList<type_t> &list, const int &start1, const int &start2, const int &len)
{
    for (auto i = 0; i < len; ++i) {
        std::swap(list[start1+i], list[start2+i]);
    }
}

/**
 * @brief Recursively swaps two adjacent blocks in a DynamicSequentialList using the block swap algorithm.
 *
 * Swaps the blocks [l, m-1] and [m, r-1].
 * Used internally by swap_inside for dynamic lists.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to operate on.
 * @param l The starting index of the first block.
 * @param m The starting index of the second block.
 * @param r The index one past the end of the second block.
 */
template <class type_t>
void block_swap(DynamicSequentialList<type_t> &list, const int &l, const int &m, const int &r)
{
    auto len1 = m - l;
    auto len2 = r - m;

    if (len1 == 0 || len2 == 0) return;

    if (len1 == len2) {
        swap_block(list, l, m, len1);
    } else if (len1 < len2) {
        swap_block(list, l, m, len1);
        block_swap(list, m, m+len1, r);
    } else {
        swap_block(list, l, m, len2);
        block_swap(list, l+len2, m, r);
    }
}

/**
 * @brief Swaps two adjacent blocks of size m and n in a DynamicSequentialList using the block swap algorithm.
 *
 * The function swaps the first block [0, m-1] with the second block [m, m+n-1] in place.
 * If m or n is invalid, throws std::out_of_range.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to operate on.
 * @param m The size of the first block.
 * @param n The size of the second block.
 * @throws std::out_of_range if m or n is negative or m+n > list.length().
 */
template <class type_t>
void swap_inside(DynamicSequentialList<type_t> &list, const int &m, const int &n)
{
    if (m < 0 || n < 0 || m + n > list.length())
        throw std::out_of_range("Invalid sublist size");
    if (m == 0 || n == 0) return;
    block_swap(list, 0, m, m + n);
}

/**
 * @brief Finds x in a sorted StaticSequentialList and swaps it with its next element, or inserts x in order if not found.
 *
 * If x exists in the list, swaps it with the next element (unless it is already the last element).
 * If x does not exist, inserts x into the list while maintaining sorted order.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The sorted static sequential list to operate on.
 * @param x The value to find and swap, or insert if not found.
 */
template <class type_t>
void find_and_swap_or_insert(StaticSequentialList<type_t> &list, const type_t &x)
{
    if (list.empty()) {
        list.push_back(x);
        return;
    }

    auto target = list.locate(x, true);
    if (target != -1) {
        if (target != list.length()-1)
            std::swap(list[target], list[target+1]);
    } else {
        auto i = list.length() - 1;
        while (i >= 0 && list[i] > x) --i;
        list.insert(i+1, x);
    }
}

/**
 * @brief Finds x in a sorted DynamicSequentialList and swaps it with its next element, or inserts x in order if not found.
 *
 * If x exists in the list, swaps it with the next element (unless it is already the last element).
 * If x does not exist, inserts x into the list while maintaining sorted order.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The sorted dynamic sequential list to operate on.
 * @param x The value to find and swap, or insert if not found.
 */
template <class type_t>
void find_and_swap_or_insert(DynamicSequentialList<type_t> &list, const type_t &x)
{
    if (list.empty()) {
        list.push_back(x);
        return;
    }

    auto target = list.locate(x, true);
    if (target != -1) {
        if (target != list.length()-1)
            std::swap(list[target], list[target+1]);
    } else {
        auto i = list.length() - 1;
        while (i >= 0 && list[i] > x) --i;
        list.insert(i+1, x);
    }
}

/**
 * @brief Outputs the intersection of three sorted StaticSequentialLists.
 *
 * Iterates through all three sorted lists and prints elements that are present in all three.
 * The intersection is printed in sorted order, and only common elements are output.
 *
 * @tparam type_t The type of elements in the lists.
 * @param a The first sorted static sequential list.
 * @param b The second sorted static sequential list.
 * @param c The third sorted static sequential list.
 */
template <class type_t>
void output_intersection(const StaticSequentialList<type_t> &a, const StaticSequentialList<type_t> &b, const StaticSequentialList<type_t> &c)
{
    std::cout << "Intersection: [ ";
    auto i = 0, j = 0, k = 0;
    auto la = a.length(), lb = b.length(), lc = c.length();

    while (i < la && j < lb && k < lc) {
        auto maximum = std::max({a[i], b[j], c[k]});
        while (i < la && a[i] < maximum) ++i;
        while (j < lb && b[j] < maximum) ++j;
        while (k < lc && c[k] < maximum) ++k;

        if (i < la && j < lb && k < lc && a[i] == maximum && b[j] == maximum && c[k] == maximum) {
            std::cout << maximum << ' ';
            ++i, ++j, ++k;
        }
    }

    std::cout << ']' << std::endl;
}

/**
 * @brief Outputs the intersection of three sorted DynamicSequentialLists.
 *
 * Iterates through all three sorted lists and prints elements that are present in all three.
 * The intersection is printed in sorted order, and only common elements are output.
 *
 * @tparam type_t The type of elements in the lists.
 * @param a The first sorted dynamic sequential list.
 * @param b The second sorted dynamic sequential list.
 * @param c The third sorted dynamic sequential list.
 */
template <class type_t>
void output_intersection(const DynamicSequentialList<type_t> &a, const DynamicSequentialList<type_t> &b, const DynamicSequentialList<type_t> &c)
{
    std::cout << "Intersection: [ ";
    auto i = 0, j = 0, k = 0;
    auto la = a.length(), lb = b.length(), lc = c.length();

    while (i < la && j < lb && k < lc) {
        auto maximum = std::max({a[i], b[j], c[k]});
        while (i < la && a[i] < maximum) ++i;
        while (j < lb && b[j] < maximum) ++j;
        while (k < lc && c[k] < maximum) ++k;

        if (i < la && j < lb && k < lc && a[i] == maximum && b[j] == maximum && c[k] == maximum) {
            std::cout << maximum << ' ';
            ++i, ++j, ++k;
        }
    }

    std::cout << ']' << std::endl;
}

/**
 * @brief Left-rotates a StaticSequentialList by p positions.
 *
 * Moves the first p elements to the end of the list, shifting the remaining elements to the left.
 * Uses the block swap algorithm via swap_inside for efficient in-place rotation.
 * If p is zero, negative, or a multiple of the list length, the list remains unchanged.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The static sequential list to rotate.
 * @param p The number of positions to rotate left by.
 */
template <class type_t>
void sift_left(StaticSequentialList<type_t> &list, const int &p)
{
    if (list.length() <= 1) return;

    auto step = p % list.length();
    if (step == 0) return;
    swap_inside(list, step, list.length()-step);
}

/**
 * @brief Left-rotates a DynamicSequentialList by p positions.
 *
 * Moves the first p elements to the end of the list, shifting the remaining elements to the left.
 * Uses the block swap algorithm via swap_inside for efficient in-place rotation.
 * If p is zero, negative, or a multiple of the list length, the list remains unchanged.
 *
 * @tparam type_t The type of elements in the list.
 * @param list The dynamic sequential list to rotate.
 * @param p The number of positions to rotate left by.
 */
template <class type_t>
void sift_left(DynamicSequentialList<type_t> &list, const int &p)
{
    if (list.length() <= 1) return;

    auto step = p % list.length();
    if (step == 0) return;
    swap_inside(list, step, list.length()-step);
}

/**
 * @brief Finds the median of two sorted StaticSequentialLists of equal length.
 *
 * Uses a binary search approach to find the median in O(log n) time.
 * Both lists must be sorted and have the same non-zero length.
 * If both lists are empty, throws std::invalid_argument.
 *
 * @tparam type_t The type of elements in the lists.
 * @param a The first sorted static sequential list.
 * @param b The second sorted static sequential list.
 * @return The median value.
 * @throws std::invalid_argument if both lists are empty or lengths differ.
 */
template <class type_t>
type_t get_median(const StaticSequentialList<type_t> &a, const StaticSequentialList<type_t> &b)
{
    if (a.length() != b.length() || a.empty())
        throw std::invalid_argument("Lists must be non-empty and of equal length.");

    int la = 0, ra = a.length() - 1, lb = 0, rb = b.length() - 1;
    while (la < ra && lb < rb) {
        int mida = (la + ra) / 2;
        int midb = (lb + rb) / 2;
        type_t vala = a[mida];
        type_t valb = b[midb];
        int offset = ((ra - la + 1) & 1) ^ 1; // 0 if odd, 1 if even

        if (vala == valb) return vala;
        if (vala > valb) {
            ra = mida;
            lb = midb + offset;
        } else {
            rb = midb;
            la = mida + offset;
        }
    }
    return std::min(a[la], b[lb]);
}

/**
 * @brief Finds the median of two sorted DynamicSequentialLists of equal length.
 *
 * Uses a binary search approach to find the median in O(log n) time.
 * Both lists must be sorted and have the same non-zero length.
 * If both lists are empty, throws std::invalid_argument.
 *
 * @tparam type_t The type of elements in the lists.
 * @param a The first sorted dynamic sequential list.
 * @param b The second sorted dynamic sequential list.
 * @return The median value.
 * @throws std::invalid_argument if both lists are empty or lengths differ.
 */
template <class type_t>
type_t get_median(const DynamicSequentialList<type_t> &a, const DynamicSequentialList<type_t> &b)
{
    if (a.length() != b.length() || a.empty())
        throw std::invalid_argument("Lists must be non-empty and of equal length.");

    int la = 0, ra = a.length() - 1, lb = 0, rb = b.length() - 1;
    while (la < ra && lb < rb) {
        int mida = (la + ra) / 2;
        int midb = (lb + rb) / 2;
        type_t vala = a[mida];
        type_t valb = b[midb];
        int offset = ((ra - la + 1) & 1) ^ 1; // 0 if odd, 1 if even

        if (vala == valb) return vala;
        if (vala > valb) {
            ra = mida;
            lb = midb + offset;
        } else {
            rb = midb;
            la = mida + offset;
        }
    }
    return std::min(a[la], b[lb]);
}

/**
 * @brief Finds the majority element (appearing more than half the time) in a StaticSequentialList.
 *
 * Uses the Boyer-Moore Voting Algorithm to find a candidate for the majority element,
 * then verifies if it actually appears more than half the time.
 * Returns the majority element if found, otherwise returns -1.
 *
 * @tparam type_t The type of elements in the list (must be comparable to -1).
 * @param list The static sequential list to search.
 * @return The majority element, or -1 if none exists.
 */
template <class type_t>
type_t get_main_element(StaticSequentialList<type_t> &list)
{
    if (list.empty()) return -1;
    if (list.length() == 1) return list[0];

    // Boyer-Moore Voting Algorithm
    type_t candidate = list[0];
    int count = 1;
    for (int i = 1; i < list.length(); ++i) {
        if (list[i] == candidate) {
            ++count;
        } else if (--count == 0) {
            candidate = list[i];
            count = 1;
        }
    }

    // Verify candidate
    count = 0;
    for (int i = 0; i < list.length(); ++i) {
        if (list[i] == candidate) ++count;
    }
    if (count > list.length() / 2) return candidate;
    return -1;
}

/**
 * @brief Finds the majority element (appearing more than half the time) in a DynamicSequentialList.
 *
 * Uses the Boyer-Moore Voting Algorithm to find a candidate for the majority element,
 * then verifies if it actually appears more than half the time.
 * Returns the majority element if found, otherwise returns -1.
 *
 * @tparam type_t The type of elements in the list (must be comparable to -1).
 * @param list The dynamic sequential list to search.
 * @return The majority element, or -1 if none exists.
 */
template <class type_t>
type_t get_main_element(DynamicSequentialList<type_t> &list)
{
    if (list.empty()) return -1;
    if (list.length() == 1) return list[0];

    // Boyer-Moore Voting Algorithm
    type_t candidate = list[0];
    int count = 1;
    for (int i = 1; i < list.length(); ++i) {
        if (list[i] == candidate) {
            ++count;
        } else if (--count == 0) {
            candidate = list[i];
            count = 1;
        }
    }

    // Verify candidate
    count = 0;
    for (int i = 0; i < list.length(); ++i) {
        if (list[i] == candidate) ++count;
    }
    if (count > list.length() / 2) return candidate;
    return -1;
}

/**
 * @brief Finds the smallest missing positive integer in a StaticSequentialList.
 *
 * Rearranges the list in-place so that if possible, list[i] == i+1 for all valid i.
 * Then scans for the first index where this is not true, returning i+1 as the missing integer.
 * If all positions are filled correctly, returns list.length()+1.
 * Time complexity: O(n), Space: O(1).
 *
 * @tparam type_t The type of elements in the list (should be integer-like).
 * @param list The static sequential list to search.
 * @return The smallest missing positive integer (returns 0 if list is empty).
 */
template <class type_t>
type_t get_min_positive(StaticSequentialList<type_t> &list)
{
    if (list.empty()) return 0;

    for (auto i = 0; i < list.length(); ++i) {
        // Place list[i] at its correct position if possible
        while (
            list[i] > 0 &&
            list[i] <= list.length() &&
            list[list[i] - 1] != list[i]
        ) {
            std::swap(list[i], list[list[i] - 1]);
        }
    }

    for (auto i = 0; i < list.length(); ++i)
        if (list[i] != i + 1) return i + 1;
    return list.length() + 1;
}

/**
 * @brief Finds the smallest missing positive integer in a DynamicSequentialList.
 *
 * Rearranges the list in-place so that if possible, list[i] == i+1 for all valid i.
 * Then scans for the first index where this is not true, returning i+1 as the missing integer.
 * If all positions are filled correctly, returns list.length()+1.
 * Time complexity: O(n), Space: O(1).
 *
 * @tparam type_t The type of elements in the list (should be integer-like).
 * @param list The dynamic sequential list to search.
 * @return The smallest missing positive integer (returns 0 if list is empty).
 */
template <class type_t>
type_t get_min_positive(DynamicSequentialList<type_t> &list)
{
    if (list.empty()) return 0;

    for (auto i = 0; i < list.length(); ++i) {
        // Place list[i] at its correct position if possible
        while (
            list[i] > 0 &&
            list[i] <= list.length() &&
            list[list[i] - 1] != list[i]
        ) {
            std::swap(list[i], list[list[i] - 1]);
        }
    }

    for (auto i = 0; i < list.length(); ++i)
        if (list[i] != i + 1) return i + 1;
    return list.length() + 1;
}

/**
 * @brief Finds the minimal "triplet distance" among three sorted StaticSequentialLists.
 *
 * The "triplet distance" for a triplet (a, b, c) is defined as max(a, b, c) - min(a, b, c).
 * This function finds the minimum such distance among all possible triplets, where each element
 * is taken from one of the three lists. The lists must be sorted in ascending order.
 *
 * @tparam type_t The type of elements in the lists (must support comparison).
 * @param a The first sorted static sequential list.
 * @param b The second sorted static sequential list.
 * @param c The third sorted static sequential list.
 * @return The minimal triplet distance (max - min) among all triplets.
 */
template <class type_t>
int get_min_triplet_dist(const StaticSequentialList<type_t> &a, const StaticSequentialList<type_t> &b, const StaticSequentialList<type_t> &c)
{
    auto i = 0, j = 0, k = 0;
    int min_dist = std::numeric_limits<int>::max();

    while (i < a.length() && j < b.length() && k < c.length()) {
        auto min_val = std::min({a[i], b[j], c[k]});
        auto max_val = std::max({a[i], b[j], c[k]});
        min_dist = std::min(min_dist, static_cast<int>(max_val - min_val));

        // Advance the pointer of the list with the current minimum value
        if (min_val == a[i]) ++i;
        else if (min_val == b[j]) ++j;
        else ++k;
    }

    return 2*min_dist;
}

/**
 * @brief Finds the minimal "triplet distance" among three sorted DynamicSequentialLists.
 *
 * The "triplet distance" for a triplet (a, b, c) is defined as max(a, b, c) - min(a, b, c).
 * This function finds the minimum such distance among all possible triplets, where each element
 * is taken from one of the three lists. The lists must be sorted in ascending order.
 *
 * @tparam type_t The type of elements in the lists (must support comparison).
 * @param a The first sorted dynamic sequential list.
 * @param b The second sorted dynamic sequential list.
 * @param c The third sorted dynamic sequential list.
 * @return The minimal triplet distance (max - min) among all triplets.
 */
template <class type_t>
int get_min_triplet_dist(const DynamicSequentialList<type_t> &a, const DynamicSequentialList<type_t> &b, const DynamicSequentialList<type_t> &c)
{
    auto i = 0, j = 0, k = 0;
    int min_dist = std::numeric_limits<int>::max();

    while (i < a.length() && j < b.length() && k < c.length()) {
        auto min_val = std::min({a[i], b[j], c[k]});
        auto max_val = std::max({a[i], b[j], c[k]});
        min_dist = std::min(min_dist, static_cast<int>(max_val - min_val));

        // Advance the pointer of the list with the current minimum value
        if (min_val == a[i]) ++i;
        else if (min_val == b[j]) ++j;
        else ++k;
    }

    return 2*min_dist;
}
} // namespace ex