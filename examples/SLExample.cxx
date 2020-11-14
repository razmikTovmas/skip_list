#include <iostream>

#include "skip_list.hpp"

int main()
{
    skip_list::skip_list<int> sl;
    std::cout << "Size: " << sl.size() << std::endl;
    sl.clear();
    auto [it, res] = sl.insert(3);
    if (res) {
        std::cout << "Value: " << *it << std::endl;
    }
    sl.insert(0);
    sl.insert(2);
    sl.insert(1);
    sl.insert(4);
    std::cout << "Size: " << sl.size() << std::endl;

    auto nextIt = sl.erase(3);
    std::cout << "Value: " << *nextIt << std::endl;

    for (auto val : sl) {
        std::cout << val << " -> ";
    }
    std::cout << std::endl;

    return 0;
}
