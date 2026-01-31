// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23
// expected-no-diagnostics

// Example 6
struct T {
T(T const&);
};
struct S {
operator T();
operator T&();
};
S s;
T t(s);