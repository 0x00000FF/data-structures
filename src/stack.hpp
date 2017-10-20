#pragma once
#include <stdexcept>

template <typename T, int32_t _capacity>
class Stack
{
public:
    explicit         Stack   ();
                     Stack   (Stack&  stack)                 = default;
                     Stack   (Stack&& stack) noexcept        = default;
                     ~Stack  () noexcept;

    const bool       empty   () const noexcept;
    const bool       full    () const noexcept;
    const T&         peek    () const;
    const T&&        pop     () noexcept;
    const int32_t    size    () const noexcept;
    const T* const   ptr     () const noexcept;

    void             push    (const T&& elem);

    Stack<T, _capacity>&           operator= (Stack<T, _capacity> const&);
    const bool                     operator==(const Stack<T, _capacity>&);

private:
    int32_t   top  = -1;
    T*        data;
};

template <typename T, int32_t _capacity>
Stack<T, _capacity>::Stack ()
{
    static_assert(std::is_reference<T>::value, "reference type cannot be element of stack");

    data = new T[_capacity];
}

template <typename T, int32_t _capacity>
Stack<T, _capacity>::~Stack() noexcept
{
    delete [] data;
}

template <typename T, int32_t _capacity>
const bool        Stack<T, _capacity>::empty() const noexcept
{
    return top == -1;
}

template <typename T, int32_t _capacity>
const bool        Stack<T, _capacity>::full() const noexcept
{
    return top == _capacity - 1;
}

template <typename T, int32_t _capacity>
const T&          Stack<T, _capacity>::peek()  const
{
    if (empty())
        throw std::runtime_error("stack is empty");

    return data[top];
}

template <typename T, int32_t _capacity>
const T&&         Stack<T, _capacity>::pop()   noexcept
{
    if (empty())
        throw std::runtime_error("stack is empty");

    auto ret = std::move(data[top]);
    data[top--].~T();

    return ret;
}

template <typename T, int32_t _capacity>
void              Stack<T, _capacity>::push(const T&& elem)
{
    if (full())
        throw std::runtime_error("stack is full");

    top++;
    data[top] = elem;
}

template <typename T, int32_t _capacity>
const int32_t     Stack<T, _capacity>::size() const noexcept
{
    return _capacity;
}

template <typename T, int32_t _capacity>
const T* const    Stack<T, _capacity>::ptr() const noexcept
{
    return data;
}
