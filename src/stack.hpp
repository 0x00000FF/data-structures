#include <stdexcept>

template <typename T, unsigned _capacity>
class Stack
{
    static_assert(!std::is_reference<T>::value,
                  "reference type data cannot be element of stack");

public:

    explicit
    Stack() noexcept;
    Stack(Stack<T, _capacity> const&)           = default;
    Stack(Stack<T, _capacity>&&)      noexcept  = default;
    ~Stack();

    bool        empty()        const noexcept;
    bool        full()         const noexcept;

    void        push(T const&);
    auto        pop();
    const auto& peek() const;



private:
    int32_t top  = -1;
    T*      data = NULL;
};

template <typename T, unsigned _capacity>
Stack<T, _capacity>::Stack() noexcept
{
    static_assert(_capacity > 0, "invalid capacity value");

    data = new T[_capacity];
}

template <typename T, unsigned _capacity>
Stack<T, _capacity>::~Stack()
{
    if (data)
        delete [] data;
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

    if(&data[top])
        data[top].~T();

    data[top] = item;
}

template <typename T, unsigned _capacity>
auto     Stack<T, _capacity>::pop()
{
    if (empty())
        throw std::runtime_error("stack is empty");

    auto elem = std::move(data[top]);
    data[top].~T();

    top--;

    return elem;
}

template <typename T, unsigned _capacity>
const auto& Stack<T, _capacity>::peek() const
{
    if (empty())
        throw std::runtime_error("stack is empty");

    return data[top];
}
