// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23
// expected-no-diagnostics

// Example 3
#include <string>
struct X {
template <typename T>
operator T();
};
std::string s(X{});
// string(string&&)?
// string(const char*)?
// string(const allocator&)?
// string(initializer_list<char>)?
// string(nullptr_t)?