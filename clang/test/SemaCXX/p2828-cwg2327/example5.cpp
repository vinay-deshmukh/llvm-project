// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23
// expected-no-diagnostics

// Example 5
struct A1 {};
struct A2 {
A2(const A2&);
A2(const A1&); // EDG and MSVC call this (conform to current standard)
};
struct B : A1 {
operator A2(); // Clang and GCC call this
};
A2 a(B{});