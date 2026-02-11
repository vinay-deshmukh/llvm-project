// use 14 as the version _before_ mandatory copy elision
// RUN: %clang_cc1 %s -std=c++14 -fsyntax-only -ast-dump 2>&1 | FileCheck -check-prefix=CHECK-CXX14 %s 
// RUN: %clang_cc1 %s -std=c++17 -fsyntax-only -ast-dump 2>&1 | FileCheck -check-prefix=CHECK-CXX17 %s

// expected-no-diagnostics

// Original example from CWG2327
// https://www.open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#2327

// Example 1
struct Cat {};
struct Dog { operator Cat(); };

Dog d;
Cat c(d);

/*
CHECK-CXX14: `-VarDecl {{.*}} c 'Cat' callinit
CHECK-CXX14-NEXT: `-ExprWithCleanups {{.*}} 'Cat'
CHECK-CXX14-NEXT:    `-CXXConstructExpr {{.*}} 'Cat' 'void (Cat &&) noexcept' elidable
CHECK-CXX14-NEXT:      `-MaterializeTemporaryExpr {{.*}} 'Cat' xvalue
CHECK-CXX14-NEXT:        `-ImplicitCastExpr {{.*}} 'Cat' <UserDefinedConversion>
CHECK-CXX14-NEXT:          `-CXXMemberCallExpr {{.*}} 'Cat'
CHECK-CXX14-NEXT:            `-MemberExpr {{.*}} '<bound member function type>' .operator Cat {{.*}}
CHECK-CXX14-NEXT:              `-DeclRefExpr {{.*}} 'Dog' lvalue Var {{.*}} 'd' 'Dog'
*/

/*
CHECK-CXX17: `-VarDecl {{.*}} c 'Cat' callinit
CHECK-CXX17-NEXT:  `-ImplicitCastExpr {{.*}} 'Cat' <UserDefinedConversion>
CHECK-CXX17-NEXT:    `-CXXMemberCallExpr {{.*}} 'Cat'
CHECK-CXX17-NEXT:      `-MemberExpr {{.*}} '<bound member function type>' .operator Cat {{.*}}
CHECK-CXX17-NEXT:        `-DeclRefExpr {{.*}} 'Dog' lvalue Var {{.*}} 'd' 'Dog'
*/