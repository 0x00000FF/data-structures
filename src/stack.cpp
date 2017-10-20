#include <cstdint>

template <typename T, const int capacity>
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


const bool      Stack::empty()
{
    return top == -1;
}

template <typename T>
const T&        Stack::peek()
{
    return empty() ? nullptr : data[top];
}

template <typename T>
const T&        Stack::pop()
{
    auto data = peek();
    top--;

    return data;
}

template <typename T>
void            Stack::push(const T &element)
{
    top++;
    data[top] = element;
}