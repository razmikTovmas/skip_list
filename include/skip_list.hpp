#pragma once

#include <memory>
#include <limits>
#include <vector>

#include "internal/sl_impl.hpp"

namespace skip_list
{
template <typename T,
          typename Compare = std::less<T>,
          typename Allocator = std::allocator<T>>
class skip_list
{
private:
    using impl_type = internal::sl_impl<T, Compare, Allocator>;
    using node_type = typename impl_type::node_type;

public:
    using value_type                = typename impl_type::value_type;
    using size_type                 = typename impl_type::size_type;
    using allocator_type            = typename impl_type::allocator_type;
    using difference_type           = typename allocator_type::difference_type;
    using reference                 = typename allocator_type::reference;
    using const_reference           = typename allocator_type::const_reference;
    using pointer                   = typename allocator_type::pointer;
    using const_pointer             = typename allocator_type::const_pointer;
    using compare                   = typename impl_type::compare;

    using iterator                  = internal::sl_iterator<impl_type>;
    using const_iterator            = internal::sl_const_iterator<impl_type>;

    explicit skip_list(const Allocator& alloc = Allocator())
        : m_impl(alloc)
    { }

    reference front()
    {
        assert(!empty());
        return m_impl.front()->m_value;
    }
    const_reference front() const
    {
        assert(!empty());
        return m_impl.front()->m_value;
    }

    reference back()
    {
        assert(!empty());
        return m_impl.back()->m_value;
    }
    const_reference back() const
    {
        assert(!empty());
        return m_impl.back()->m_value;
    }

    iterator       begin()                  { return iterator(m_impl.front()); }
    const_iterator begin() const            { return const_iterator(m_impl.front()); }
    const_iterator cbegin() const           { return const_iterator(m_impl.front()); }

    iterator       end()                    { return iterator(m_impl.tail()); }
    const_iterator end() const              { return const_iterator(m_impl.tail()); }
    const_iterator cend() const             { return const_iterator(m_impl.tail()); }

    bool      empty() const         { return m_impl.size() == 0; }
    size_type size() const          { return m_impl.size(); }
    size_type max_size() const      { return m_impl.get_allocator().max_size(); }

    void clear() { m_impl.remove_all(); }

    std::pair<iterator, bool> insert(const_reference value)
    {
        node_type* node = m_impl.insert(value);
        return std::make_pair(iterator(node), true);
    }

    iterator erase(const_reference value)
    {
        node_type* node = m_impl.find(value);
        if (m_impl.is_equal(node->m_value, value)) {
            node_type* next = node->m_next[0];
            m_impl.remove(node);
            return iterator(next);
        }
        return iterator(m_impl.tail());
    }

    iterator find(const_reference value)
    {
        node_type* node = m_impl.find(value);
        if (m_impl.is_equal(node->value, value)) {
            return iterator(node);
        }
        return iterator(m_impl.tail());
    }

    const_iterator find(const_reference value) const
    {
        node_type* node = m_impl.find(value);
        if (m_impl.is_equal(node->value, value)) {
            return const_iterator(node);
        }
        return const_iterator(m_impl.tail());
    }

private:
    impl_type m_impl;

}; // skip_list

} // namespace skip_list
