// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++23
// expected-no-diagnostics

// Example 8
template <int i = 0>
class NonCopyable {
public:
NonCopyable(const NonCopyable&) requires(i != 0);
private:
NonCopyable(int x);
friend struct Source;
};
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2828r2.html 5/9
// 31/01/2026, 11:41 
struct Source {
operator NonCopyable<0>();
// Copy elision for direct-initialization with a conversion function (Core issue 2327)
};
NonCopyable<0> nc(Source{}); // OK in Clang; ill-formed in GCC, MSVC, and the current standard