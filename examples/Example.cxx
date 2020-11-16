#include <iostream>

#include "skip_list.hpp"

int main()
{
    skip_list::skip_list<int> sl {1, 2, 4};
    std::cout << "Size: " << sl.size() << std::endl;

    auto insert = [&sl](skip_list::skip_list<int>::value_type val) {
        [[maybe_unused]] auto [it, res] = sl.insert(val);
        if (res) {
            std::cout << val << " is inserted: " << *it << "." << std::endl;
        } else {
            std::cout << val << " is not inserted." << std::endl;
        }
    };
    auto erase = [&sl](skip_list::skip_list<int>::value_type val) {
        auto it = sl.erase(val);
        std::cout << "Erasing " << val << ". ";
        if (it != sl.end()) {
            std::cout << "The next value is " << *it << "." << std::endl;
        } else {
            std::cout << "It was the end of the list." << std::endl;
        }
    };

    insert(3);
    insert(1);

    sl.clear();

    std::vector<int> v {4, 5, 2, 7, 6, 9, 1, 8, 3};
    sl.assign(v.begin(), v.end());

    sl.pretty_dump();

    erase(4);
    erase(9);

    std::cout << "Revers iterator" << std::endl;
    for (auto rit = sl.rbegin(); rit != sl.rend(); ++rit) {
        std::cout << *rit << " > ";
    }
    std::cout << std::endl;

    return 0;
}
