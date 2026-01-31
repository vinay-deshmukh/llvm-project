// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23

// expected-no-diagnostics

// Example 1
struct Cat {};
struct Dog { operator Cat(); };

Dog d;
Cat c(d);
