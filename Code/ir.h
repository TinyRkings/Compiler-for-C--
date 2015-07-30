#ifndef IR_H
#define IR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct InterCodes_* InterCodes;
typedef struct Arguments_* Arguments;

struct Operand_ {
	enum { VARIABLE, CONSTANT, FCONSTANT, ADDRESS, TEMP, SPACE, POINT, STRUCTURE} kind;
	union {
		char *var_name;//Variable
		int value;//CONSTANT,SPACE
		float fvalue;//FCONSTANT
		int temp_id;//TEMP(record by tempNum)
		Operand addr;//ADDRESS,POINT
	};
};	
struct Arguments_ {
	Operand op;
	Arguments next;
};

struct InterCode_ {
	enum { ASSIGN, ADD, SUB, MUL, DIVIDE, CALL, READ, WRITE, ARG, LABEL, RET, IFGOTO, GOTO, DEC, FUNDEC, PARAM} kind;
	union {
		struct { Operand right, left; } assign;//ASSIGN,READ(right),WRITE(right),ARG(right),PARAM(right),RET(right),DEC(left,right)
		struct { Operand result, op1, op2; } binop;//MUL,ADD,SUB,DIVIDE
		struct { Operand result; char * funName; } call;//CALL(function,not include read and write)
		int id;//LABEL,GOTO
		struct { Operand op1, op2; InterCodes label; char *relop; } ifgoto; //IFGOTO(relop record the relop_sign)
		char *fun_name;//FUNDEC
	};
};


struct InterCodes_ { 
	struct InterCode_ code; 
	InterCodes prev, next; 
};

void test();
void test2();
InterCodes ir_generate(Node *p);
InterCodes translate_Exp(Node *p, Operand place);
InterCodes translate_CompSt(Node *p);
InterCodes translate_StmtList(Node *p);
InterCodes translate_Stmt(Node *p);
InterCodes translate_Args(Node *p, Arguments* arg_list);
InterCodes translate_ExtDefList(Node *p);
InterCodes translate_ExtDef(Node *p);
InterCodes translate_ExtDecList(Node *specifier, Node *p);
InterCodes translate_VarDec(Node *specifier, Node *p, int param);
InterCodes translate_DefList(Node *p);
InterCodes translate_DecList(Node *specifier, Node *p);
InterCodes translate_Dec(Node *specifier, Node *p);
InterCodes translate_VarList(Node *p);
InterCodes translate_FunDec(Node *p);
InterCodes translate_Cond(Node *p, InterCodes label_true, InterCodes label_false);
Operand lookup(char *name);
Operand new_temp();
Operand new_space(int value);
InterCodes new_label();
InterCodes new_goto(int i);
int getArraySpace(Type type);
InterCodes connectCodes(int total, ...);
void optimizeifgoto(InterCodes codes);
void optimizetwolabels(InterCodes codes);
void print_op(Operand op, FILE *fp);
void print_code(InterCodes codes,char*output_name);
#endif
