
#pragma once
#include <stdexcept>

template <typename T, int32_t _capacity>
class Stack
{
public:
    explicit      Stack   ();
                  Stack   (Stack&  stack)                 = default;
                  Stack   (Stack&& stack) noexcept        = default;
                  ~Stack  () noexcept;

    const bool    empty   () const noexcept;
    const bool    full    () const noexcept;
    const T&      peek    () const;
    const T&&     pop     () noexcept;

    void          push    (const T&& elem);

    //Stack&        operator= (Stack const&)                                    = default;
    //const bool    operator==(const Stack<T, _capacity>&) noexcept             = default;

private:
    int32_t   top  = -1;
    T*        data;
};

template <typename T, int32_t _capacity>
Stack<T, _capacity>::Stack ()
{
    if (_capacity > 0)
        data = new T[_capacity];
    else
        std::runtime_error("invalid capacity");
};

template <typename T, int32_t _capacity>
Stack<T, _capacity>::~Stack() noexcept
{
    delete data;
};

template <typename T, int32_t _capacity>
const bool  Stack<T, _capacity>::empty() const noexcept
{
    return top == -1;
};

template <typename T, int32_t _capacity>
const bool  Stack<T, _capacity>::full() const noexcept
{
    return top == _capacity - 1;
};

template <typename T, int32_t _capacity>
const T&    Stack<T, _capacity>::peek()  const
{
    if (empty())
        throw std::runtime_error("stack is empty");

    return data[top];
}

template <typename T, int32_t _capacity>
const T&&   Stack<T, _capacity>::pop()   noexcept
{
    if (empty())
        throw std::runtime_error("stack is empty");

    return std::move(data[top--]);
};

template <typename T, int32_t _capacity>
void        Stack<T, _capacity>::push(const T&& elem)
{
    if (full())
        throw std::runtime_error("stack is full");

    top++;
    data[top] = elem;
};
