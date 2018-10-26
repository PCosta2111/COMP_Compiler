
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

struct _CMD{
	char *leftTXT; 
	struct _CMDList *insideBlock;
	struct _CMD *cmd_else; //in case of if
};

struct _CMDList{
	struct _CMD *cmd;
	struct _CMDList *next;
};

typedef struct _Expr Expr; // Convenience typedef

typedef struct _BoolExpr BoolExpr;

typedef struct _CMD CMD;

typedef struct _CMDList CMDList;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
CMD* ast_cmd(char* str1,CMD* cmd_else,CMDList* inside);
CMDList* ast_cmdlist(CMD* c, CMDList* next);
BoolExpr* ast_Bool_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_bool(int v);

#endif
