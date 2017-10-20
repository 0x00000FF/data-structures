#include <cassert>
#include <cstdint>

template <typename T, const int32_t capacity>
class Stack
{
public:
    const bool  empty ();
    const T&    peek  ();
    const T&    pop   ();
    void        push  (const T& element);

private:
    int32_t     top            =  -1;
    T           data[capacity];
};


template<typename T, const int32_t capacity>
const bool      Stack<T, capacity>::empty()
{
    return top == -1;
}

template<typename T, const int32_t capacity>
const T&        Stack<T, capacity>::peek()
{
    assert(!empty());

    return data[top];
}

template<typename T, const int32_t capacity>
const T&        Stack<T, capacity>::pop()
{
    auto& data = peek();
    top--;

    return data;
}

template<typename T, const int32_t capacity>
void            Stack<T, capacity>::push(const T &element)
{
    top++;
    data[top] = element;
}
