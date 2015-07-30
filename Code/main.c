#include "node.h"
#include "hash.h"
#include "semantic.h"
#include "ir.h"

extern char*strdup(char*s);
char*outputname;
extern FILE* yyin;
extern Node*root;
extern int morphology;//stand for the error type A
extern int grammar_error;//stand for the error type B
extern int semantic_error_info;//stand for the semantic error
extern HashTable *varTable;
extern HashTable *funcTable;
extern HashTable *structTable;
int main(int argc, char** argv){
	if(argc<=1)
		return 1;
	FILE* f = fopen(argv[1], "r");
	if(!f){
		perror(argv[1]);
		return 1;
	}
	outputname=strdup(argv[2]);
	yyrestart(f);
	yyparse();
	if(morphology==0&&grammar_error==0)//no morphology and grammar error 
	{	
		varTable = initialTable(); //variable table
		funcTable = initialFunTable();//func table
		structTable = initialTable();//struct table
		semanticCheck(root);//semantic anlysis,add content to the sign_table
		deleteTable(varTable, 0);//delete variable sign table
		if(semantic_error_info==0)//no sematic error
		{	InterCodes total=ir_generate(root);
			//optimizeifgoto(total);
			//optimizetwolabels(total);
			//print_code(total,outputname);
			create_mips_code(total,outputname);
		}
	}
	return 0;
}
