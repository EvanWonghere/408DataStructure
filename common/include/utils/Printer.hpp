#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <iterator>

// 检查是否为 std::pair，用于打印 map 类型
template <typename T>
struct is_pair : std::false_type {};

template <typename T1, typename T2>
struct is_pair<std::pair<T1, T2>> : std::true_type {};

namespace ds::utils {

    /**
     * @brief Generic container printer that works with any iterable container.
     *
     * @tparam Container The type of container (e.g., std::vector, std::list, std::set, std::map).
     * @param container The container to print.
     * @param name Optional name to be printed before the container content.
     */
    template<typename Container>
    void print_container(const Container& container, const std::string& name = "") {
        using value_type = typename Container::value_type;

        if (!name.empty()) {
            std::cout << name << ": ";
        }

        std::cout << "[";

        auto it = container.begin();
        while (it != container.end()) {
            if constexpr (is_pair<value_type>::value) {
                std::cout << "(" << it->first << ": " << it->second << ")";
            } else {
                std::cout << *it;
            }

            if (++it != container.end()) {
                std::cout << ", ";
            }
        }

        std::cout << "]" << std::endl;
    }

} // namespace ds::utils
