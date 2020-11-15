#include <iostream>

#include "internal/sl_impl.hpp"

int main()
{
    using skip_list = skip_list::internal::sl_impl<int, std::less<int>, std::allocator<int>>;

    skip_list sl;

    sl.insert(3);
    sl.insert(0);
    sl.insert(2);
    sl.insert(1);
    sl.insert(1);
    std::cout << "Size: " << sl.size() << std::endl;
    sl.insert(4);
    sl.insert(5);
    sl.insert(6);
    sl.insert(7);
    sl.insert(8);
    sl.insert(9);
    typename skip_list::value_type val = 1;
    if (auto* res = sl.find(val);
        nullptr != res) {
        std::cout << val;
        if (res->m_value == val) {
            std::cout << " is found "<< std::endl;
            sl.remove(res);
        } else {
            std::cout << " is not found "<< std::endl;
        }
    }


    std::cout << " Printing " << std::endl;
    for (auto* it = sl.head(); it != sl.tail(); it = it->m_next[0]) {
        std::cout << it->m_value << " <= " << std::flush;
    }
    std::cout << std::endl;

    sl.dump();

    sl.remove_all();
    std::cout << "Size: " << sl.size() << std::endl;

    return 0;
}
