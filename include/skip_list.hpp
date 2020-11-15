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
    using reverse_iterator          = std::reverse_iterator<iterator>;
    using const_reverse_iterator    = std::reverse_iterator<const_iterator>;

    ///@{ @name Member functions

    ///@{ @name Constructors and destructor

    explicit skip_list(const allocator_type& alloc = allocator_type());
    template <class InputIterator>
    skip_list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
    skip_list(const skip_list& other);
    skip_list(const skip_list& other, const allocator_type& alloc);
    skip_list(skip_list&& other);
    skip_list(skip_list&& other, const allocator_type &alloc);
    skip_list(std::initializer_list<T> init, const allocator_type& alloc = allocator_type());

    ~skip_list() = default;

    ///@}

    ///@{ @name Assignment

    skip_list& operator=(const skip_list& other);
    skip_list& operator=(skip_list&& other);
    skip_list& operator=(std::initializer_list<T> init);

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last);
    void assign(std::initializer_list<T> init);

    ///@}

    allocator_type get_allocator() const { return m_impl.get_allocator(); }

    ///@{ @name Element access

    reference front();
    const value_type& front() const;
    reference back();
    const value_type& back() const;

    ///@}

    ///@{ @name Iterators

    iterator       begin()          { return iterator(m_impl.front()); }
    const_iterator begin() const    { return const_iterator(m_impl.front()); }
    const_iterator cbegin() const   { return const_iterator(m_impl.front()); }

    iterator       end()            { return iterator(m_impl.tail()); }
    const_iterator end() const      { return const_iterator(m_impl.tail()); }
    const_iterator cend() const     { return const_iterator(m_impl.tail()); }

    reverse_iterator       rbegin()         { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const   { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const  { return const_reverse_iterator(end()); }

    reverse_iterator       rend()           { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const     { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const    { return const_reverse_iterator(begin()); }
    ///@}

    ///@{ @name Capacity

    bool      empty() const         { return m_impl.size() == 0; }
    size_type size() const          { return m_impl.size(); }
    size_type max_size() const      { return m_impl.get_allocator().max_size(); }

    ///@}

    ///@{ @name Modifiers

    void clear() { m_impl.remove_all(); }

    std::pair<iterator, bool> insert(const value_type& value);
    void insert(std::initializer_list<T> init);

    iterator erase(const value_type& value);

    ///@}

    ///@{ @name Lookup

    iterator find(const value_type& value);
    const_iterator find(const value_type& value) const;

    iterator lower_bound(const value_type& value);
    const_iterator lower_bound(const value_type& value) const;

    iterator upper_bound(const value_type& value);
    const_iterator upper_bound(const value_type& value) const;

    ///@}

    ///@}

private:
    impl_type m_impl;

}; // skip_list

} // namespace skip_list


#include "_skip_list.hpp"
