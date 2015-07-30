#include "hash.h"

int test_test_test_id=0;
extern char*strdup(char*s);
unsigned int hash_pjw(char* name)
{
	unsigned int val = 0, i;
	for ( ; *name; ++name)
	{
		val = (val<< 2) + *name;
		test_test_test_test();
		if ( i = val& ~0x3fff) 
			val = (val ^ (i>> 12)) & 0x3fff;
	}
	return val;
}
HashTable* initialTable(){
	HashTable *htable=malloc(sizeof(HashTable));
	int i=0;
	for(;i < TableSize; i++){
		htable->hashTable[i].symbol = NULL;
		htable->hashTable[i].next = NULL;
	}
	test_test_test_test();
	for(i = 0; i < StackSize; i ++){
		htable->stack[i].hnode = NULL;
		htable->stack[i].next = NULL;
	}
	return htable;
}
void test_test_test_test()
{
	if(test_test_test_id==1)
	{
		printf("hhhhhhhh\n");
		exit(0);
	}
}
HashTable* initialFunTable(){
	HashTable *htable=malloc(sizeof(HashTable));
	int i=0;
	for(;i < TableSize; i ++){
		htable->hashTable[i].symbol = NULL;
		htable->hashTable[i].next = NULL;
	}	
	for(i = 0; i < StackSize; i ++){
		htable->stack[i].hnode = NULL;
		htable->stack[i].next = NULL;
	}
	//add the read function
	symbol *read = malloc(sizeof(symbol));
	read->sym_name = strdup("read");
	Type retType = malloc(sizeof(struct Type_));
	Fun_symbol *readFun = malloc(sizeof(Fun_symbol));
	retType->kind = basic;
	retType->basic = 0;
	readFun->return_type = retType;
	readFun->para_num = 0;
	read->fun = readFun;
	insertTable(htable, read, 0);
	//add the write function
	symbol *write = malloc(sizeof(symbol));
	write->sym_name = strdup("write");
	Fun_symbol *writeFun = malloc(sizeof(Fun_symbol));
	writeFun->para_num = 1;
	writeFun->para_type[0] = basic;
	write->fun = writeFun;
	insertTable(htable, write, 0);
	return htable;
}
HashNode* searchTable(HashTable *ht, char *name, int depth){
	unsigned int index = hash_pjw(name)/TableSize;
	if(ht->hashTable[index].next == NULL)
		return NULL;
	else{
		HashNode *next = ht->hashTable[index].next;
		while(next != NULL){
			if(strcmp(next->symbol->sym_name, name) == 0 && next->depth <= depth){
				break;		
			}
			next = next->next;
		}
		return next;
	}
}
//add variable to table
void insertTable(HashTable *ht, symbol *symbol, int depth){
	unsigned int index = hash_pjw(symbol->sym_name)/TableSize;
	//printf("insert index %d symname: %s depth: %d\n", index,symbol->sym_name, depth);
	HashNode *hnode = malloc(sizeof(HashNode));
	StackNode *snode = malloc(sizeof(StackNode));
	hnode->symbol = symbol;
	hnode->depth = depth;
	test_test_test_test();
	if(ht->hashTable[index].next == NULL){
	//empty list
		hnode->next = NULL;
		ht->hashTable[index].next = hnode;
	}
	else{
	//conflict,add to first location
		hnode->next = ht->hashTable[index].next;
		ht->hashTable[index].next = hnode;
	}
	snode->hnode = hnode;
	if(ht->stack[depth].next == NULL){
		snode->next = NULL;
		ht->stack[depth].next = snode;
	}
	else{
		snode->next = ht->stack[depth].next;
		ht->stack[depth].next = snode; 
	}
	return;
}

void deleteTable(HashTable *ht, int depth){
	StackNode *current = ht->stack[depth].next;
	HashNode *hnode = malloc(sizeof(HashNode));
	HashNode *del_node = malloc(sizeof(HashNode));	
	unsigned int index;
	while(current != NULL){
		ht->stack[depth].next = current->next;
		index = hash_pjw(current->hnode->symbol->sym_name)/TableSize;
		hnode = ht->hashTable[index].next;
		test_test_test_test();
		//delete the the first of hashnode
		if(strcmp(current->hnode->symbol->sym_name, hnode->symbol->sym_name) == 0 && hnode->depth == depth){
			ht->hashTable[index].next = hnode->next;
			free(hnode);
		}
		else{
			while(strcmp(current->hnode->symbol->sym_name, hnode->next->symbol->sym_name) != 0 || hnode->next->depth != depth)
				hnode = hnode->next;
			del_node = hnode->next;
			hnode->next = del_node->next;
			free(del_node);
		}
		free(current);
		current = ht->stack[depth].next;
	}
	return;
}