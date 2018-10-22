
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _BoolExpr {
  enum { 
    E_BOOL,
    E_B_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

typedef struct _Expr Expr; // Convenience typedef

typedef struct _BoolExpr BoolExpr;

typedef struct _ExprList{
	Expr* exp;
	struct _ExprList* tail;
	
} ExprList;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
ExprList* ast_exprlist(Expr* expr, ExprList* next);
BoolExpr* ast_Bool_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_bool(int v);

#endif
