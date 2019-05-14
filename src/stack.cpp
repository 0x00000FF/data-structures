#include "stack.hpp"

template <typename T, unsigned _capacity>
Stack<T, _capacity>::Stack() noexcept
{
    static_assert(_capacity > 0, "invalid capacity value");

    data = (T*)malloc(_capacity * sizeof(T));
}

template <typename T, unsigned _capacity>
Stack<T, _capacity>::~Stack()
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

template <typename T, unsigned _capacity>
bool     Stack<T, _capacity>::empty() const noexcept
{
    return top == -1;
}

template <typename T, unsigned _capacity>
bool     Stack<T, _capacity>::full() const noexcept
{
    return top == _capacity - 1;
}

template <typename T, unsigned _capacity>
void     Stack<T, _capacity>::push(T const& item)
{
    if (full())
        throw std::runtime_error("stack is full");

    top++;
    *(data+top) = item;
}

template <typename T, unsigned _capacity>
auto     Stack<T, _capacity>::pop()
{
    if (empty())
        throw std::runtime_error("stack is empty");

    auto elem = std::move(data[top]);
    (data+top)->~T();

    top--;

    return elem;
}

template <typename T, unsigned _capacity>
const auto& Stack<T, _capacity>::peek() const
{
    if (empty())
        throw std::runtime_error("stack is empty");

    return *(data + top);
}
