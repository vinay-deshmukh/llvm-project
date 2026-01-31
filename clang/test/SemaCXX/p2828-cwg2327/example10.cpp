// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23
// expected-no-diagnostics

// Example 10
#include <type_traits>
template <bool has_copy_constructor>
struct Cat {
Cat();
Cat(const Cat&) requires has_copy_constructor;
Cat(Cat&&) requires has_copy_constructor;
template <class C = Cat>
Cat(std::type_identity_t<C>&&) = delete;
};
struct Dog {
operator Cat<false>();
};
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2828r2.html 6/9
// 31/01/2026, 11:41 Copy elision for direct-initialization with a conversion function (Core issue 2327)
Dog d;
Cat<false> c(d); // OK in Clang and NVC++; ill-formed in GCC, MSVC, and the current standard