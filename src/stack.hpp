#include <stdexcept>
#include <cstdint>

template <typename T, const int32_t capacity>
class Stack
{
public:
    const bool  empty () noexcept const;
    const T&    peek  () const;
    const T&    pop   () noexcept;
    
    template<typename U>
    void        push  (U&& element);

private:
    int32_t     top            =  -1;
    T           data[capacity];
};


template<typename T, const int32_t capacity>
const bool      Stack<T, capacity>::empty() noexcept const
{
    return top == -1;
}

template<typename T, const int32_t capacity>
const T&        Stack<T, capacity>::peek() const
{
    if(empty())
        throw std::runtime_error("stack is empty");
    
    return data[top];
}

template<typename T, const int32_t capacity>
const T&        Stack<T, capacity>::pop() noexcept
{
    if(empty())
        throw std::runtime_error("stack is empty");
    
    auto elem = data[top];
    
    data[top]->~T();
    top--;

    return elem;
}

template<typename T, const int32_t capacity>
template<typename U>
void            Stack<T, capacity>::push(U&& element)
{
    static_assert(std::is_same<std::decay<T>,
                  std::decay<U>>::value, "argument type or qualifier doesn't match")
    top++;
    data[top] = T();
    data[top] = std::forward<U>(element);
}
