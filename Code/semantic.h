#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "node.h"

HashTable *varTable;
HashTable *funcTable;
HashTable *structTable;
extern int currentDepth;

extern void test_test1();
extern void semanticCheck(Node *p);
extern Type basicType(Node *specifier_node);
extern Type arrayType(Node *p, char *array_id, Node *specifier_node);
extern Type structureType(Node *specifier_node);

extern symbol* structDef(Node *p);
extern symbol *VarDec(Node *p, Node *specifier_node);
extern symbol* FunDec(Node *p, Node *specifier_node);

extern FieldList VarDecField(Node *p, Node *specifier_node);
extern FieldList sameSpecifierField(Node *p, Node *specifier_node);
extern FieldList structureField(Node *p);

extern void addSym_ExtDecList(Node *p, Node *specifier_node);
extern void addSym_DecList(Node *p, Node *specifier_node);
extern int VarList(Node *p, Type_Kind paraType[10]);

extern Type arrayExp(Node *p);
extern int sameType(Type type1, Type type2);
extern Type checkExp(Node *p);

extern void semantic_error(int error_type, int lineno, char *msg);

#endif
