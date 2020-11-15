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


    ///@{ @name Member functions

    ///@{ @name Constructors and destructor

    explicit skip_list(const Allocator& alloc = Allocator())
        : m_impl(alloc)
    { }

    template <class InputIterator>
    skip_list(InputIterator first, InputIterator last, const Allocator& alloc = Allocator())
        : m_impl(alloc)
    {
        assign(first, last);
    }

    skip_list(const skip_list& other)
        : m_impl(other.get_allocator())
    {
        assign(other.begin(), other.end());
    }

    skip_list(const skip_list& other, const Allocator& alloc)
        : m_impl(alloc)
    {
        assign(other.begin(), other.end());
    }

    skip_list(skip_list&& other)
        : m_impl(std::move(other.m_impl))
    {

    }

    skip_list(skip_list&& other, const Allocator &alloc)
        : m_impl(alloc)
    {
        assign(other.begin(), other.end());
    }

    skip_list(std::initializer_list<T> init, const Allocator& alloc = Allocator())
        : m_impl(alloc)
    {
        assign(init.begin(), init.end());
    }

    ~skip_list() = default;

    ///@}

    ///@{ @name Assignment

    skip_list& operator=(const skip_list& other)
    {
        assign(other.begin(), other.end());
        return *this;
    }

    skip_list& operator=(skip_list&& other)
    {
        clear();
        m_impl = std::move(other.m_impl);
        return *this;
    }

    skip_list& operator=(std::initializer_list<T> init)
    {
        assign(init.begin(), init.end());
        return *this;
    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        clear();
        while (first != last) {
            insert(*first++);
        }
    }

    void assign(std::initializer_list<T> init)
    {
        assign(init.begin(), init.end());
    }

    ///@}

    allocator_type get_allocator() const { return m_impl.get_allocator(); }

    ///@{ @name Element access

    reference front()
    {
        assert(!empty());
        return m_impl.front()->m_value;
    }

    const value_type& front() const
    {
        assert(!empty());
        return m_impl.front()->m_value;
    }

    reference back()
    {
        assert(!empty());
        return m_impl.back()->m_value;
    }

    const value_type& back() const
    {
        assert(!empty());
        return m_impl.back()->m_value;
    }

    ///@}

    ///@{ @name Iterators

    iterator       begin()          { return iterator(m_impl.front()); }
    const_iterator begin() const    { return const_iterator(m_impl.front()); }
    const_iterator cbegin() const   { return const_iterator(m_impl.front()); }

    iterator       end()            { return iterator(m_impl.tail()); }
    const_iterator end() const      { return const_iterator(m_impl.tail()); }
    const_iterator cend() const     { return const_iterator(m_impl.tail()); }

    ///@}

    ///@{ @name Capacity

    bool      empty() const         { return m_impl.size() == 0; }
    size_type size() const          { return m_impl.size(); }
    size_type max_size() const      { return m_impl.get_allocator().max_size(); }

    ///@}

    ///@{ @name Modifiers

    void clear() { m_impl.remove_all(); }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        node_type* node = m_impl.insert(value);
        return std::make_pair(iterator(node), true);
    }

    void insert(std::initializer_list<T> init)
    {
        for (auto& val : init) {
            m_impl.insert(val);
        }
    }

    iterator erase(const value_type& value)
    {
        node_type* node = m_impl.find(value);
        if (m_impl.is_equal(node->m_value, value)) {
            node_type* next = node->m_next[0];
            m_impl.remove(node);
            return iterator(next);
        }
        return iterator(m_impl.tail());
    }

    ///@}

    ///@{ @name Lookup

    iterator find(const value_type& value)
    {
        node_type* node = m_impl.find(value);
        if (m_impl.is_equal(node->value, value)) {
            return iterator(node);
        }
        return iterator(m_impl.tail());
    }

    const_iterator find(const value_type& value) const
    {
        return const_iterator(const_cast<skip_list&>(this).find(value));
    }

    iterator lower_bound(const value_type& value)
    {
        return iterator(m_impl.find_first(value));
    }

    const_iterator lower_bound(const value_type& value) const
    {
        return const_iterator(const_cast<skip_list&>(this).lower_bound(value));
    }

    iterator upper_bound(const value_type& value)
    {
        node_type* node = m_impl.find_first(value);
        if (node != m_impl.tail()) {
            while (m_impl.is_less_or_equal(node->m_value, value)) {
                node = node->m_next[0];
            }
        }
        return iterator(node);
    }

    const_iterator upper_bound(const value_type& value) const
    {
        return const_iterator(const_cast<skip_list&>(this).upper_bound(value));
    }

    ///@}

    ///@}

private:
    impl_type m_impl;

}; // skip_list

} // namespace skip_list
