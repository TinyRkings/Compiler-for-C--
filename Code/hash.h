#ifndef HASH_H
#define HASH_H
#include "node.h"
#define TableSize 1024
#define StackSize 20

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

enum Type_Kind{ basic, array, structure };
typedef enum Type_Kind Type_Kind;

struct Type_{
	Type_Kind kind;
	union{
		// 基本类型,0:int; 1:float
		int basic;
		// 数组类型信息包括元素类型与数组大小构成 
		struct { Type elem; int size; } array;
		// 结构体类型信息是一个链表	
		FieldList structure;
	};
};

struct FieldList_{
	char* name; 	// 域的名字	
	Type type;	// 域的类型
	FieldList tail;	// 下一个域		
};

struct Fun_symbol{
	Type return_type;  
	int para_num;
	Type_Kind para_type[10];
};
typedef struct Fun_symbol Fun_symbol;

struct symbol{
	char *sym_name;	//key
	union{
		Type type;
		Fun_symbol *fun;
	};
};
typedef struct symbol symbol;

struct HashNode{
	int depth;
	symbol *symbol;
	struct HashNode *next;
};
typedef struct HashNode HashNode;

struct StackNode{
	HashNode *hnode;
	struct StackNode *next;
};
typedef struct StackNode StackNode;

struct HashTable{
	StackNode stack[StackSize];
	HashNode hashTable[TableSize];
};
typedef struct HashTable HashTable;

void test_test_test_test();
extern HashTable* initialTable();
extern HashTable* initialFunTable();
extern void insertTable(HashTable *ht, symbol *symbol, int depth);
extern HashNode* searchTable(HashTable *ht, char *name, int depth);
extern void deleteTable(HashTable *ht, int depth);
extern unsigned int hash_pjw(char* name);

#endif
