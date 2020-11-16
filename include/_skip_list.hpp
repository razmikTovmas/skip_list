#pragma once

namespace skip_list
{

template <class T, class C, class A>
skip_list<T, C, A>::skip_list(const allocator_type& alloc)
    : m_impl(alloc)
{ }

template <class T, class C, class A>
template <class InputIterator>
skip_list<T, C, A>::skip_list(InputIterator first, InputIterator last, const allocator_type& alloc)
    : m_impl(alloc)
{
    assign(first, last);
}


template <class T, class C, class A>
skip_list<T, C, A>::skip_list(const skip_list& other)
    : m_impl(other.get_allocator())
{
    assign(other.begin(), other.end());
}

template <class T, class C, class A>
skip_list<T, C, A>::skip_list(const skip_list& other, const allocator_type& alloc)
    : m_impl(alloc)
{
    assign(other.begin(), other.end());
}

template <class T, class C, class A>
skip_list<T, C, A>::skip_list(skip_list&& other)
    : m_impl(std::move(other.m_impl))
{ }

template <class T, class C, class A>
skip_list<T, C, A>::skip_list(skip_list&& other, const allocator_type &alloc)
    : m_impl(alloc)
{
    assign(other.begin(), other.end());
}

template <class T, class C, class A>
skip_list<T, C, A>::skip_list(std::initializer_list<T> init, const allocator_type& alloc)
    : m_impl(alloc)
{
    assign(init.begin(), init.end());
}

template <class T, class C, class A>
skip_list<T, C, A>& skip_list<T, C, A>::operator=(const skip_list& other)
{
    assign(other.begin(), other.end());
    return *this;
}

template <class T, class C, class A>
skip_list<T, C, A>& skip_list<T, C, A>::operator=(skip_list&& other)
{
    clear();
    m_impl = std::move(other.m_impl);
    return *this;
}

template <class T, class C, class A>
skip_list<T, C, A>& skip_list<T, C, A>::operator=(std::initializer_list<T> init)
{
    assign(init.begin(), init.end());
    return *this;
}

template <class T, class C, class A>
template <typename InputIterator>
void skip_list<T, C, A>::assign(InputIterator first, InputIterator last)
{
    clear();
    while (first != last) {
        insert(*first++);
    }
}

template <class T, class C, class A>
void skip_list<T, C, A>::assign(std::initializer_list<T> init)
{
    assign(init.begin(), init.end());
}

template <class T, class C, class A>
typename skip_list<T, C, A>::reference skip_list<T, C, A>::front()
{
    assert(!empty());
    return m_impl.front()->m_value;
}

template <class T, class C, class A>
const typename skip_list<T, C, A>::value_type& skip_list<T, C, A>::front() const
{
    assert(!empty());
    return m_impl.front()->m_value;
}

template <class T, class C, class A>
typename skip_list<T, C, A>::reference skip_list<T, C, A>::back()
{
    assert(!empty());
    return m_impl.back()->m_value;
}

template <class T, class C, class A>
const typename skip_list<T, C, A>::value_type& skip_list<T, C, A>::back() const
{
    assert(!empty());
    return m_impl.back()->m_value;
}

template <class T, class C, class A>
std::pair<typename skip_list<T, C, A>::iterator, bool> skip_list<T, C, A>::insert(const value_type& value)
{
    node_type* node = m_impl.insert(value);
    return std::make_pair(iterator(node), (nullptr != node));
}

template <class T, class C, class A>
void skip_list<T, C, A>::insert(std::initializer_list<T> init)
{
    for (auto& val : init) {
        m_impl.insert(val);
    }
}

template <class T, class C, class A>
typename skip_list<T, C, A>::iterator skip_list<T, C, A>::erase(const value_type& value)
{
    node_type* node = m_impl.find(value);
    if (m_impl.is_equal(node->m_value, value)) {
        node_type* next = node->m_next[0];
        m_impl.remove(node);
        return iterator(next);
    }
    return iterator(m_impl.tail());
}

template <class T, class C, class A>
typename skip_list<T, C, A>::iterator skip_list<T, C, A>::find(const value_type& value)
{
    node_type* node = m_impl.find(value);
    if (m_impl.is_equal(node->m_value, value)) {
        return iterator(node);
    }
    return iterator(m_impl.tail());
}

template <class T, class C, class A>
typename skip_list<T, C, A>::const_iterator skip_list<T, C, A>::find(const value_type& value) const
{
    return const_iterator(const_cast<skip_list&>(this).find(value));
}

template <class T, class C, class A>
typename skip_list<T, C, A>::iterator skip_list<T, C, A>::lower_bound(const value_type& value)
{
    return iterator(m_impl.find_first(value));
}

template <class T, class C, class A>
typename skip_list<T, C, A>::const_iterator skip_list<T, C, A>::lower_bound(const value_type& value) const
{
    return const_iterator(const_cast<skip_list&>(this).lower_bound(value));
}

template <class T, class C, class A>
typename skip_list<T, C, A>::iterator skip_list<T, C, A>::upper_bound(const value_type& value)
{
    node_type* node = m_impl.find_first(value);
    if (node != m_impl.tail()) {
        while (m_impl.is_less_or_equal(node->m_value, value)) {
            node = node->m_next[0];
        }
    }
    return iterator(node);
}

template <class T, class C, class A>
typename skip_list<T, C, A>::const_iterator skip_list<T, C, A>::upper_bound(const value_type& value) const
{
    return const_iterator(const_cast<skip_list&>(this).upper_bound(value));
}

} // namespace skip_list
