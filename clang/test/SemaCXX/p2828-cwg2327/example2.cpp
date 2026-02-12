
// RUN: %clang_cc1 %s -std=c++14 -fsyntax-only -verify=since-cxx14 -ast-dump 2>&1 | FileCheck -allow-empty %s 
// RUN: %clang_cc1 %s -std=c++17 -fsyntax-only -ast-dump 2>&1 | FileCheck -check-prefix=CHECK-CXX17 %s

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
X x(Y{}); // since-cxx14-error {{call to constructor of 'X' is ambigious}}

/*
CHECK-CXX17: `-VarDecl {{.*}} x 'X' callinit
CHECK-CXX17-NEXT:  `-ExprWithCleanups {{.*}} 'X'
CHECK-CXX17-NEXT:    `-ImplicitCastExpr {{.*}} 'X' <UserDefinedConversion>
CHECK-CXX17-NEXT:      `-CXXMemberCallExpr {{.*}} 'X'
CHECK-CXX17-NEXT:        `-MemberExpr {{.*}} '<bound member function type>' .operator X {{.*}}
CHECK-CXX17-NEXT:          `-MaterializeTemporaryExpr {{.*}} 'Y' lvalue
CHECK-CXX17-NEXT:            `-CXXFunctionalCastExpr {{.*}} 'Y' functional cast to Y <NoOp>
CHECK-CXX17-NEXT:              `-InitListExpr {{.*}} 'Y'
*/