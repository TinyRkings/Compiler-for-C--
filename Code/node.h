#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

enum NodeType{IntType, FloatType, IDType, OtherTerminal, Nonterminal};
typedef enum NodeType NodeType;

struct Node;
struct SubNode{
	int arity;
	struct Node **children;
};
typedef struct SubNode SubNode;

struct Node{
	NodeType node_type;	
	char *name;
	int lineno;
	union{
		int int_value;
		float float_value;
		char *id_value;//the name of id
		char *other_terminal;
		SubNode cnode;
	};
};
typedef struct Node Node;
#endif
