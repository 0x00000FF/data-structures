#include "stack.hpp"

templated_tc Stack<T, C>::Stack() noexcept
{
    static_assert(C > 0, "invalid capacity value");

    data = (T*)malloc(C * sizeof(T));
}

templated_tc Stack<T, C>::~Stack()
{
    if (data)
    {
        if (empty())
        {
            for (int32_t i = top; i > -1; --i)
            {
                (data + top)->~T();
            }
        }

        free(data);
    }
}

templated_tc bool     Stack<T, C>::empty() const noexcept
{
    return top == -1;
}

templated_tc bool     Stack<T, C>::full() const noexcept
{
    return top == C - 1;
}

templated_tc void     Stack<T, C>::push(T const& item)
{
    if (full())
        throw std::runtime_error("stack is full");

    top++;
    *(data+top) = item;
}

templated_tc auto     Stack<T, C>::pop()
{
    if (empty())
        throw std::runtime_error("stack is empty");

    auto elem = std::move(data[top]);
    (data+top)->~T();

    top--;

    return elem;
}

templated_tc const auto& Stack<T, C>::peek() const
{
    if (empty())
        throw std::runtime_error("stack is empty");

    return *(data + top);
}
