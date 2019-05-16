#pragma once

#include <cstdlib>
#include <stdexcept>

#include "def.hpp"

templated_tc class Stack
{
    static_assert(!std::is_reference<T>::value,
                  "reference type data cannot be element of stack");

public:
    Stack() noexcept;
    Stack(Stack<T, C> const&)           = default;
    Stack(Stack<T, C>&&)      noexcept  = default;
    ~Stack();

    bool        empty()        const noexcept;
    bool        full()         const noexcept;

    void        push(T const&);
    auto        pop();
    const auto& peek() const;

private:
    int32_t top  = -1;
    T*      data = nullptr;
};
