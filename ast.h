
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_VAR,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    char* varname; // for vars
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

struct _VarList{
	char* head;
	struct _VarList* next;
};

struct _DeclList{
	char* var;
	struct _Expr* val;
	struct _DeclList* next;
};

typedef struct _DeclList DeclList;

struct _CMD{
	enum{
			CMD_DECL,
			CMD_ASSIGN,
			CMD_IF,
			CMD_ELSE,
			CMD_WHILE,
			CMD_FOR,
			CMD_SCAN,
			CMD_PRINT
	}id;
	union{
		struct{
			char* var_type;
			/*char* declared_var;
			struct _Expr* expr;*/
			DeclList* declList;
		}sdecl;
		
		struct{
			char* assigned_var;
			struct _Expr* expr;
		}sassign;
		
		struct{
			struct _CMDList *insideBlock;
			struct _BoolExpr* cond;
			struct _CMD *cmd_else;
		}sif;
		
		struct{
			struct _CMDList *insideBlock;
		}selse;
		
		struct{
			struct _CMDList *insideBlock;
			struct _BoolExpr* cond;
		}swhile;
		
		struct{
			//struct _Expr* init_attr;
			//char* init_var_name;
			struct _CMD *cmd_init;
			//Incr condition
			struct _BoolExpr* cond;
			//struct _Expr* incr_attr;
			//char* incr_var_name;
			struct _CMD *cmd_incr;
			struct _CMDList *insideBlock;
		}sfor;
		
		struct{
			
			char* str;
			struct _VarList* vList;
			
		}sscan;
		
		struct{
			
			char* str;
			struct _VarList* vList;
			
		}sprint;
		
	}att;
};

struct _CMDList{
	struct _CMD *cmd;
	struct _CMDList *next;
};

typedef struct _Expr Expr; // Convenience typedef

typedef struct _BoolExpr BoolExpr;

typedef struct _VarList VarList;

typedef struct _CMD CMD;

typedef struct _CMDList CMDList;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_var(char* v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
CMD* ast_cmd(char* str1,CMD* cmd_else,CMDList* inside);
CMDList* ast_cmdlist(CMD* c, CMDList* next);
BoolExpr* ast_Bool_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_bool(int v);
//----
CMD* ast_cmd_decl(char* str1,DeclList* d);
DeclList* ast_cmd_declList(char* vName,Expr* exp,DeclList* next);
CMD* ast_cmd_assign(char* vname, Expr* expr);
CMD* ast_cmd_if(CMD* cmd_else,CMDList* inside,BoolExpr* b);
CMD* ast_cmd_else(CMDList* inside);
CMD* ast_cmd_while(CMDList* inside,BoolExpr* b);
CMD* ast_cmd_for(CMD* start, BoolExpr* b, CMD* incr, CMDList* inside);
CMD* ast_cmd_scan(char* str,VarList* v);
CMD* ast_cmd_print(char* str,VarList* v);

//----
//CMD* ast_cmd_IF_WHILE(char* str1,CMD* cmd_else,CMDList* inside,BoolExpr* b);
CMD* ast_cmd_PRINT_SCAN(char* str1,char* str,VarList* v);
VarList* ast_var_list(char* head,VarList* tail);
#endif
