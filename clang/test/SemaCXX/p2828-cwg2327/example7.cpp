// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23
// expected-no-diagnostics

// Example 7
struct Y;
struct X {
X(const Y&);
};
struct A {
operator X();
};
struct B {
operator X();
};
struct Y : A, B { };
X x(Y{}); // well-formed in current C++, ambiguous in Clang