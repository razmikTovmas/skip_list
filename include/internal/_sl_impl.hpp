#pragma once

namespace skip_list
{

namespace internal
{

template <class T>
sl_node<T>::sl_node(value_type value, size_type level)
    : m_value(value)
    , m_level(level)
    , m_prev(nullptr)
    , m_next(new self_type*[level + 1])
{
    for (size_type i = 0; i <= level; ++i) {
        m_next[i] = nullptr;
    }
}

template <class T>
sl_node<T>::~sl_node()
{
    delete [] m_next;
    m_prev = nullptr; // don't need this
    m_next = nullptr; // don't need this
}



template <class T, class C, class A>
sl_impl<T, C, A>::sl_impl(const allocator_type& alloc)
    : m_alloc(alloc)
    , m_levels(max_levels)
    , m_size(0)
    , m_head(new node_type(std::numeric_limits<typename node_type::value_type>::min(), max_levels))
    , m_tail(new node_type(std::numeric_limits<typename node_type::value_type>::max(), max_levels))
{
    for (size_type i = 0; i <= max_levels; ++i) {
        m_head->m_next[i] = m_tail;
        m_tail->m_next[i] = nullptr;
    }
    m_head->m_prev = nullptr;
    m_tail->m_prev = m_head;
}

template <class T, class C, class A>
sl_impl<T, C, A>::~sl_impl()
{
    remove_all();
    delete m_head;
    delete m_tail;
}

template <class T, class C, class A>
typename sl_impl<T, C, A>::node_type* sl_impl<T, C, A>::find(const_reference value)
{
    node_type* curr = m_head;
    for (level_type level = m_levels + 1; level > 0; ) {
        --level;
        while ((curr->m_next[level] != m_tail) &&
                !is_equal(curr->m_value, value) &&
                is_less_or_equal(curr->m_next[level]->m_value, value)) {
            curr = curr->m_next[level];
        }
    }
    return curr;
}

template <class T, class C, class A>
const typename sl_impl<T, C, A>::node_type* sl_impl<T, C, A>::find(const_reference value) const
{
    return const_cast<sl_impl*>(this)->find(value);
}

template <class T, class C, class A>
typename sl_impl<T, C, A>::node_type* sl_impl<T, C, A>::find_first(const value_type& value)
{
    node_type* node = find(value);
    if (!is_equal(node->m_value, value)) {
        node = node->m_next[0];
    }
    return node;
}

template <class T, class C, class A>
const typename sl_impl<T, C, A>::node_type* sl_impl<T, C, A>::find_first(const_reference value) const
{
    return const_cast<sl_impl*>(this)->find_first(value);
}

template <class T, class C, class A>
typename sl_impl<T, C, A>::node_type* sl_impl<T, C, A>::insert(const value_type& value, node_type* hint)
{
    const level_type node_level = random_level();

    node_type* new_node = new node_type(value, node_level);
    const bool is_valid_hint = (hint != nullptr);

    node_type* curr = (is_valid_hint) ? hint : m_head; // for now start from head
    level_type level = curr->m_level + 1;
    do {
        --level;
        while ((curr->m_next[level] != m_tail) && m_less(curr->m_next[level]->m_value, value)) {
            curr = curr->m_next[level];
            assert(level <= curr->m_level);
        }
        if (level <= node_level) {
            assert(curr->m_next[level] != nullptr);
            new_node->m_next[level] = curr->m_next[level];
            curr->m_next[level] = new_node;
        }
    } while (level != 0);
    // level is 0
    assert(level == 0);
    assert(curr->m_next[0] != nullptr);
    new_node->m_prev = curr;
    new_node->m_next[0]->m_prev = new_node;
    ++m_size;

    return new_node;
}

template <class T, class C, class A>
void sl_impl<T, C, A>::remove(node_type* node)
{
    assert(nullptr != node);
    assert(nullptr != node->m_next[0]);
    assert(m_head != node);
    assert(m_tail != node);

    node->m_next[0]->m_prev = node->m_prev;;

    node_type* curr = m_head;
    for (level_type level = m_levels + 1; level > 0;) {
        --level;
        assert(level <= curr->m_level);
        while (curr->m_next[level] != m_tail && m_less(curr->m_next[level]->m_value, node->m_value)) {
            curr = curr->m_next[level];
        }
        if (curr->m_next[level] == node)
        {
            curr->m_next[level] = node->m_next[level];
        }
    }

    delete node;
    --m_size;
}

template <class T, class C, class A>
void sl_impl<T, C, A>::remove_all()
{
    node_type* node = m_head->m_next[0];
    while (node != m_tail) {
        node_type* next = node->m_next[0];
        delete node;
        node = next;
    }
    for (level_type level = 0; level < m_levels + 1; ++level) {
        m_head->m_next[level] = m_tail;
    }
    m_tail->m_prev = m_head;
    m_size = 0;
}

template <class T, class C, class A>
void sl_impl<T, C, A>::dump() const
{
    for (level_type level = 0; level <= m_levels; ++level) {
        std::cout << "L" << level << ": " << std::flush;
        node_type* curr = m_head->m_next[level];
        std::cout << m_head->m_value << " -> "<< std::flush;
        while (curr != m_tail) {
            std::cout << curr->m_value << "(" << curr->m_prev->m_value << ") -> "<< std::flush;
            curr = curr->m_next[level];
        }
        std::cout << m_tail->m_value << "(" << m_tail->m_prev->m_value << ")" << std::endl;
    }
}

} // namespace internal

} // namespace skip_list
