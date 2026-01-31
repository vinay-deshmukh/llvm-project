
// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23
// expected-no-diagnostics

// Example 2
struct X {
X(int);
// X(X&&); // implicitly declared
};
struct Y {
operator X();
operator int();
};
X x(Y{});