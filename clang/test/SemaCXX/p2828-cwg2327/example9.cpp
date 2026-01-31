// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23
// expected-no-diagnostics

// Example 9
struct Cat {
Cat(const Cat&);
Cat(int);
};
struct Dog {
operator Cat();
operator int();
};
Cat cat(Dog{}); // ambiguous in current C++