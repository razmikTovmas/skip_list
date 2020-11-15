#include <iostream>

#include "skip_list.hpp"

int main()
{
    skip_list::skip_list<int> sl {1, 2,4};
    std::cout << "Size: " << sl.size() << std::endl;
    sl.clear();
    auto [it, res] = sl.insert(3);
    if (res) {
        std::cout << "Value: " << *it << std::endl;
    }
    sl.insert(0);
    sl.insert(2);
    sl.insert(2);
    sl.insert(1);
    sl.insert(4);
    std::cout << "Size: " << sl.size() << std::endl;

    if (auto nextIt = sl.erase(3);
        nextIt != sl.end()) {
        std::cout << "Next value: " << *nextIt << std::endl;
    }

    for (auto val : sl) {
        std::cout << val << " -> ";
    }
    std::cout << std::endl;

    auto up = sl.upper_bound(3);
    std::cout << *up << std::endl;

    return 0;
}
