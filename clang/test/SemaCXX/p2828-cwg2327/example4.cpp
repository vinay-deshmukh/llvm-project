
// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23
// expected-no-diagnostics

// Example 4
struct Dog;
struct Cat {
Cat(const Dog&);
};
struct Dog {
operator Cat();
};
Cat cat(Dog{});