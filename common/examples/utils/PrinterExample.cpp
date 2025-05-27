#include <vector>
#include <list>
#include <set>
#include <map>
#include "utils/Printer.hpp"

int main() {
    std::vector<int> v = {1, 2, 3};
    std::list<std::string> l = {"apple", "banana"};
    std::set<double> s = {3.14, 2.71};
    std::map<std::string, int> m = {{"A", 1}, {"B", 2}};

    ds::utils::print_container(v, "Vector");
    ds::utils::print_container(l, "List");
    ds::utils::print_container(s, "Set");
    ds::utils::print_container(m, "Map");
}
