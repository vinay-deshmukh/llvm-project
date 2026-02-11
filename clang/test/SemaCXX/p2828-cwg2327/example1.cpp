// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23

// expected-no-diagnostics

// Original example from CWG2327
// https://www.open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#2327

// Example 1
struct Cat {};
struct Dog { operator Cat(); };

Dog d;
Cat c(d);
