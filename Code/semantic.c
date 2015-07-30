#include "hash.h"
#include "semantic.h"

extern char*strdup(char*s);
int currentDepth = 0;
int funlineno = 0;
int semantic_error_info=0;
int test_test_id1=0;

void semanticCheck(Node *p){
	if(strcmp(p->name,"ExtDef") == 0){
		test_test1();
		symbol *sym_temp = (symbol *)malloc(sizeof(symbol));
		if(strcmp(p->cnode.children[1]->name,"SEMI") == 0){
		//ExtDef->Specifier SEMI:  		structure definition
			test_test1();
			if(strcmp(p->cnode.children[0]->cnode.children[0]->name,"StructSpecifier") == 0){
				if((p->cnode.children[0]->cnode.children[0]->cnode.arity != 5))
					printf("Error type 1 at line %d : 这里只能定义结构，而不能使用结构，因为后跟分号而不是变量名",p->cnode.children[0]->lineno);
				else{
					sym_temp = structDef(p->cnode.children[0]->cnode.children[0]);//StructSpecifier		
					if(sym_temp != NULL){
						if(searchTable(structTable, sym_temp->sym_name, 0) != NULL || searchTable(varTable, sym_temp->sym_name, 0) != NULL)
							semantic_error(16, p->cnode.children[0]->lineno, sym_temp->sym_name);
						else	
							insertTable(structTable, sym_temp, 0);
					}
				}			
			}
		}
		else if(strcmp(p->cnode.children[1]->name,"ExtDecList") == 0){
		//ExtDef->Specifier ExtDecList SEMI
		//global variable
			addSym_ExtDecList(p->cnode.children[1], p->cnode.children[0]->cnode.children[0]);

		}
		else{
		//ExtDef->Specifier FunDec CompSt:	function definition
			currentDepth ++;
			sym_temp = FunDec(p->cnode.children[1], p->cnode.children[0]->cnode.children[0]);
			if(sym_temp != NULL){
				HashNode *hnode = searchTable(funcTable, sym_temp->sym_name, 0);
				if(hnode != NULL)
					semantic_error(4, p->cnode.children[1]->lineno, sym_temp->sym_name);
				else{
					test_test1();
					insertTable(funcTable, sym_temp, 0);
					//CompSt : LC DefList StmtList RC
					semanticCheck(p->cnode.children[2]->cnode.children[1]); //check DefList
					Node *stmt_list = p->cnode.children[2]->cnode.children[2];
					while(stmt_list->cnode.arity != 0){
					//StmtList->Stmt StmtList
						if(strcmp(stmt_list->cnode.children[0]->cnode.children[0]->name, "RETURN") != 0){
							semanticCheck(stmt_list->cnode.children[0]);		
						}
						else{
						//Stmt->RETURN Exp SEMI
							Type return_exp = checkExp(stmt_list->cnode.children[0]->cnode.children[1]);
							if(return_exp == NULL)
								return;
	 						if(sameType(return_exp, sym_temp->fun->return_type) == 0)
								semantic_error(8, stmt_list->lineno, sym_temp->sym_name);
						}

						//if(stmt_list->cnode.children[1]->cnode.arity != 0)
							stmt_list = stmt_list->cnode.children[1];
					}

					deleteTable(varTable, currentDepth);		
				}
			}
			currentDepth --;
		}
		return;
	}
	else if(strcmp(p->name,"Def") == 0){
	//Def->Specifier DecList SEMI	
		addSym_DecList(p->cnode.children[1], p->cnode.children[0]->cnode.children[0]);
		return;
	}
	else if(strcmp(p->name,"CompSt") == 0){
	//CompSt->LC DefList StmtList RC
		currentDepth ++;
		semanticCheck(p->cnode.children[1]);
		semanticCheck(p->cnode.children[2]);
		deleteTable(varTable, currentDepth);
		currentDepth --;
		return;
	}
	else if(strcmp(p->name,"Exp") == 0){
		checkExp(p);
		test_test1();
		return;
	}
	else{
		int i = 0;
		if(p->node_type == Nonterminal){
			for(; i < p->cnode.arity; i++){
				semanticCheck(p->cnode.children[i]);	
			}
		}	
		return;
	}
}

void test_test1()
{
	if(test_test_id1==1)
	{	
		printf("error\n");
		exit(0);
	}
}
Type basicType(Node *specifier_node){
	Type currentType = malloc(sizeof(struct Type_));
	currentType->kind = basic;
	if(strcmp(specifier_node->other_terminal, "int") == 0)
	{//ID: int
		currentType->basic = 0;
		test_test1();
	}
	else if(strcmp(specifier_node->other_terminal, "float") == 0)
	//ID: float
		currentType->basic = 1;
	else
		currentType->basic = 0;
	return currentType;
}

Type arrayType(Node *p, char *array_id, Node *specifier_nextnode){
	//VarDec : VarDec LB INT RB
	Type temp = malloc(sizeof(struct Type_));
	temp->kind = array;
	//Specifier->StructSpecifier
	if(strcmp(specifier_nextnode->name, "StructSpecifier") == 0){
		temp->array.elem = structureType(specifier_nextnode);
		if(temp->array.elem == NULL)
			return NULL;	
	}
	//Specifier : TYPE
	else if(strcmp(specifier_nextnode->name, "TYPE") == 0){
		temp->array.elem = basicType(specifier_nextnode);
		test_test1();
	}
	temp->array.size = p->cnode.children[2]->int_value;
	Node *array_node = p->cnode.children[0];
	while(strcmp(array_node->cnode.children[0]->name, "ID") != 0){
		Type new_type = malloc(sizeof(struct Type_));
		new_type->kind = array;
		new_type->array.elem = temp;
		test_test1();
		new_type->array.size = array_node->cnode.children[2]->int_value;
		temp = new_type;
		array_node = array_node->cnode.children[0];
	}
	strcpy(array_id, strdup(array_node->cnode.children[0]->id_value));
	return temp;
}

Type structureType(Node *specifier_node){
	Type currentType = malloc(sizeof(struct Type_));
	currentType->kind = structure;
	HashTable *temptable = initialTable();//in order to solve the overdefinition in the struct
	//StructSpecifier : STRUCT OptTag LC DefList RC
	if(specifier_node->cnode.arity == 5){
		currentType->structure = structureField(specifier_node->cnode.children[3]);
		FieldList currentField = currentType->structure;
		test_test1();
		while(currentField != NULL){
			symbol *symtemp = malloc(sizeof(symbol));
			symtemp->sym_name = currentField->name;
			symtemp->type = currentField->type;
			HashNode *tempnode = searchTable(temptable, symtemp->sym_name, 0);
			if(tempnode!= NULL){
				semantic_error(15, funlineno, symtemp->sym_name);
				return NULL;
			}
			insertTable(temptable, symtemp, 0);
			HashNode *temp = temptable->hashTable[0].next;
			currentField = currentField->tail;
		}
	}
	//StructSpecifier : STRUCT Tag	
	else{
		HashNode *tempnode = searchTable(structTable, specifier_node->cnode.children[1]->cnode.children[0]->id_value, 0);
		if(tempnode == NULL){
			semantic_error(17, specifier_node->cnode.children[0]->lineno, specifier_node->cnode.children[1]->cnode.children[0]->id_value);	
			return NULL;
		}
		currentType = tempnode->symbol->type;
	}
	return currentType;	
}

FieldList VarDecField(Node *p, Node *specifier_node){
	funlineno = p->lineno;
	FieldList fl = malloc(sizeof(struct FieldList_));
	if(p->cnode.arity == 1){	
	//VarDec->ID
		fl->name = strdup(p->cnode.children[0]->id_value);
		//fl->depth = 1;
		if(strcmp(specifier_node->name, "TYPE") == 0){
		//Specifier->TYPE:      ID:basic(int or float)
			fl->type = basicType(specifier_node);
		}
		else if(strcmp(specifier_node->name, "StructSpecifier") == 0){
		//Specifier->StructSpecifier
			fl->type = structureType(specifier_node);	
		}
	}
	else{
	//VarDec->VarDec LB INT RB :array
		char array_id[20];
		fl->type = arrayType(p, array_id, specifier_node);
		if(fl->type == NULL)
			return NULL;
		fl->name = strdup(array_id);
	}
	fl->tail = NULL;
	return fl;	
}
//a field list with same 
FieldList sameSpecifierField(Node *p, Node *specifier_node){
	if(p->cnode.arity == 1){  	
	//DecList->Dec	
		FieldList fl = malloc(sizeof(struct FieldList_));
		if(p->cnode.children[0]->cnode.arity == 3){
		//Dec->VarDec ASSIGNOP Exp
			semantic_error(15, p->lineno, " ");	
			return NULL;
		}
		fl = VarDecField(p->cnode.children[0]->cnode.children[0], specifier_node);
		return fl;
	}			
	else{				
	//DecList->Dec COMMA DecList
	FieldList fl = malloc(sizeof(struct FieldList_));
		fl = VarDecField(p->cnode.children[0]->cnode.children[0], specifier_node);
		fl->tail = sameSpecifierField(p->cnode.children[2], specifier_node);
		if(fl->tail == NULL)
			return NULL;
		return fl;
	}
}
//p : DefList
FieldList structureField(Node *p){
	FieldList temp = malloc(sizeof(struct FieldList_));
	test_test1();
	if(p->cnode.arity == 0){
		return NULL;
	}
	//DefList : Def DefList
	//Def : Specifier DecList SEMI
	else{
		temp = sameSpecifierField(p->cnode.children[0]->cnode.children[1], p->cnode.children[0]->cnode.children[0]->cnode.children[0]);
		FieldList last = temp;
		while(last->tail != NULL)
			last = last->tail;
		last->tail = structureField(p->cnode.children[1]);
		return temp;
	}	
}

symbol* structDef(Node *p){
//StructSpecifier->STRUCT OptTag LC DefList RC
	symbol *struct_sym = malloc(sizeof(symbol));
	if(strcmp(p->cnode.children[1]->cnode.children[0]->name, "ID") == 0)
	//OptTag->ID
		struct_sym->sym_name = strdup(p->cnode.children[1]->cnode.children[0]->id_value);
	else
	//OptTag->nil
		struct_sym->sym_name = " ";
	struct_sym->type = structureType(p);
	if(struct_sym->type == NULL)
		return NULL;
	return struct_sym;
}


symbol *VarDec(Node *p, Node *specifier_node){
//返回一个需要添加的数组或变量
	symbol *sym_temp = malloc(sizeof(symbol));
	//VarDec : ID
	if(p->cnode.arity == 1){
		sym_temp->sym_name = strdup(p->cnode.children[0]->id_value);
		if(strcmp(specifier_node->name, "TYPE") == 0){
		//Specifier->TYPE:      ID:basic(int or float)
			sym_temp->type = basicType(specifier_node);
			test_test1();
		}
		else if(strcmp(specifier_node->name, "StructSpecifier") == 0){
		//Specifier->StructSpecifier
			sym_temp->type = structureType(specifier_node);	
			if(specifier_node->cnode.arity == 5){
			//StructSpecifier->STRUCT OptTag LC DefList RC
				symbol *new_struct = structDef(specifier_node);
				if(new_struct == NULL)
					return NULL;
				if(searchTable(structTable, new_struct->sym_name, 0) != NULL || searchTable(varTable, new_struct->sym_name, 0) != NULL)
					semantic_error(16, p->cnode.children[0]->lineno, new_struct->sym_name);
				else	
					insertTable(structTable, new_struct, 0);
			}	
		}
	}
	else{
	//VarDec->VarDec LB INT RB :array
		char array_id[20];
		sym_temp->type = arrayType(p, array_id, specifier_node);
		sym_temp->sym_name = strdup(array_id);
	}
	if(sym_temp->type == NULL)
		return NULL;
	return 	sym_temp;
}

void addSym_ExtDecList(Node *p, Node *specifier_node){
	if(p->cnode.arity == 1){  	
	//ExtDecList->VarDec	
		symbol *newSym = VarDec(p->cnode.children[0], specifier_node);
		if(newSym != NULL){
			test_test1();
			HashNode *hnode = searchTable(varTable, newSym->sym_name, 0);
			if(hnode != NULL)
				semantic_error(3, p->cnode.children[0]->lineno, newSym->sym_name);
			else
				insertTable(varTable, newSym, 0);
		}
	}			
	else{				
	//ExtDecList->VarDec COMMA ExtDecList
		symbol *newSym = VarDec(p->cnode.children[0], specifier_node);
		if(newSym != NULL){
			HashNode *hnode = searchTable(varTable, newSym->sym_name, 0);
			if(hnode != NULL)
				semantic_error(3, p->cnode.children[0]->lineno, newSym->sym_name);
			else
				insertTable(varTable, newSym, 0);
		}
		addSym_ExtDecList(p->cnode.children[2], specifier_node);
	}
	return;
}

void addSym_DecList(Node *p, Node *specifier_node){
	if(p->cnode.arity == 1){
	//DecList->Dec
		symbol *newSym = VarDec(p->cnode.children[0]->cnode.children[0], specifier_node);
		if(newSym != NULL){
			HashNode *hnode = searchTable(varTable, newSym->sym_name, currentDepth);
			if(hnode != NULL && hnode->depth == currentDepth)
				semantic_error(3, p->cnode.children[0]->lineno, newSym->sym_name);
			else if(p->cnode.children[0]->cnode.arity == 3 && sameType(newSym->type, checkExp(p->cnode.children[0]->cnode.children[2])) == 0)
			//Dec->VarDec ASSIGNOP Exp
				semantic_error(5, p->cnode.children[0]->lineno, " ");			
			else
				insertTable(varTable, newSym, currentDepth);
		}
	}
	else{
	//DecList->Dec COMMA DecList
		symbol *newSym = VarDec(p->cnode.children[0]->cnode.children[0], specifier_node);
		if(newSym != NULL){
			HashNode *hnode = searchTable(varTable, newSym->sym_name, currentDepth);
			if(hnode != NULL && hnode->depth == currentDepth)
				semantic_error(3, p->cnode.children[0]->lineno, newSym->sym_name);
			else if(p->cnode.children[0]->cnode.arity == 3 && sameType(newSym->type, checkExp(p->cnode.children[0]->cnode.children[2])) == 0)
			//Dec->VarDec ASSIGNOP Exp
				semantic_error(5, p->cnode.children[0]->lineno, " ");
			else
				insertTable(varTable, newSym, currentDepth);
		}
		addSym_DecList(p->cnode.children[2], specifier_node);
	}
	return;
}
//return parameter number
//VarList : ParamDec COMMA VarList
//VarList : ParamDec
int paraList(Node *p, Type_Kind paraType[10]){
	Node *next = p;
	Node *specifier_node;
	test_test1();
	int paraNum = 0;
	while(1){
		specifier_node = next->cnode.children[0]->cnode.children[0]->cnode.children[0];
		test_test1();
		symbol *para_sym = VarDec(next->cnode.children[0]->cnode.children[1], specifier_node);
		if(para_sym != NULL){
			HashNode *hnode = searchTable(varTable, para_sym->sym_name, currentDepth);
			if(hnode!= NULL && hnode->depth == currentDepth)
				semantic_error(3, p->cnode.children[0]->lineno, para_sym->sym_name);
			else
				insertTable(varTable, para_sym, currentDepth);
			paraType[paraNum] = para_sym->type->kind;
			paraNum ++;
		}
		//VarList->ParamDec COMMA VarList
		if(next->cnode.arity == 3)
			next = next->cnode.children[2];
		//VarList : ParamDec
		else
			break;
	}
	return paraNum;
}

symbol* FunDec(Node *p, Node *specifier_node){
	symbol *sym_temp = malloc(sizeof(symbol));
	Fun_symbol *fun_sym = malloc(sizeof(Fun_symbol));
	sym_temp->sym_name = strdup(p->cnode.children[0]->id_value);
	if(strcmp(specifier_node->name, "TYPE") == 0){	
		fun_sym->return_type = basicType(specifier_node);
	}
	else{
		HashNode *struct_node = searchTable(structTable, sym_temp->sym_name, 0);
		if(struct_node == NULL){
			//函数的返回值是结构但该结构未定义
			semantic_error(17, p->cnode.children[0]->lineno, p->cnode.children[0]->id_value);
			test_test1();
			return NULL;
		}
		fun_sym->return_type = struct_node->symbol->type;
		
	}
	//FunDec : ID LP RP
	if(p->cnode.arity == 3){
		fun_sym->para_num = 0;
	}
	//FunDec : ID LP VarList RP
	else{
		fun_sym->para_num = paraList(p->cnode.children[2], fun_sym->para_type);
	}
	sym_temp->fun = fun_sym;
	return sym_temp;
}

Type arrayExp(Node *p){
//Exp->Exp LB Exp RB	
	if(p->cnode.arity != 4 || strcmp(p->cnode.children[0]->name, "Exp") != 0){
		if(strcmp(p->cnode.children[0]->name, "ID") == 0){
			test_test1();
			HashNode *hnode = searchTable(varTable, p->cnode.children[0]->id_value, currentDepth);
			if(hnode == NULL){	
				semantic_error(1, p->cnode.children[0]->lineno, p->cnode.children[0]->id_value);
				return NULL;
			}
			else
				return hnode->symbol->type;
		}
		else
			return checkExp(p);
	}
		
	Type ex2_type = checkExp(p->cnode.children[2]);
	test_test1();
	if(ex2_type->kind != basic || ex2_type->basic != 0){
		semantic_error(12, p->cnode.children[0]->lineno, " ");
		return NULL;
	}
	Type temp = arrayExp(p->cnode.children[0]);
	if(temp == NULL)
		return NULL;
	if(temp->kind == basic){
		semantic_error(10, p->cnode.children[0]->lineno, p->cnode.children[0]->id_value);
		return NULL;
	}
	else
		return temp->array.elem;
}

int sameType(Type type1, Type type2){
	if(type1->kind != type2->kind)
		return 0;
	if(type1->kind == basic && type1->basic != type2->basic)
		return 0;
	if(type1->kind == basic && type1->basic == type2->basic)
		return 1;
	if(type1->kind == array)
		return sameType(type1->array.elem, type2->array.elem);
	FieldList fl1 = type1->structure;
	FieldList fl2 = type2->structure;
	while(fl1 != NULL && fl2 != NULL){
		if(fl1->name != fl2->name || (sameType(fl1->type, fl2->type) == 0))
			return 0;
		fl1 = fl1->tail;
		fl2 = fl2->tail;
	}
	if(fl1 != NULL || fl2 != NULL)
		return 0;
	return 1;
}

Type checkExp(Node *p){
	if(strcmp(p->cnode.children[0]->name, "ID") == 0 && p->cnode.arity == 1){
	//Exp->ID
		HashNode *hnode = searchTable(varTable, p->cnode.children[0]->id_value, currentDepth);
		test_test1();
		if(hnode == NULL){
			semantic_error(1, p->cnode.children[0]->lineno, p->cnode.children[0]->id_value);
			return NULL;
		}
		return hnode->symbol->type;
	}
	else if(strcmp(p->cnode.children[0]->name, "INT") == 0){
	//Exp->INT
		Type int_type = malloc(sizeof(struct Type_));
		int_type->kind = basic;
		int_type->basic = 0;
		return int_type;
	}
	else if(strcmp(p->cnode.children[0]->name, "FLOAT") == 0){
	//Exp->FLOAT
		Type float_type = malloc(sizeof(struct Type_));
		float_type->kind = basic;
		float_type->basic = 1;
		return float_type;
	}
	else if(strcmp(p->cnode.children[0]->name, "ID") == 0 && p->cnode.arity == 3){		
	//Exp->ID LP RP
		HashNode *hnode = searchTable(funcTable, p->cnode.children[0]->id_value, 0);
		if(hnode == NULL){
			if(searchTable(varTable, p->cnode.children[0]->id_value, currentDepth) != NULL){
				semantic_error(11, p->lineno, p->cnode.children[0]->id_value);
				return NULL;
			}
			semantic_error(2, p->cnode.children[0]->lineno, p->cnode.children[0]->id_value);
			return NULL;		
		}
		else if(hnode->symbol->fun->para_num != 0)
			semantic_error(9, p->cnode.children[0]->lineno, p->cnode.children[0]->id_value);
		return hnode->symbol->fun->return_type;  	
	}
	else if(strcmp(p->cnode.children[0]->name, "ID") == 0 && p->cnode.arity == 4){		
	//Exp->ID LP Args RP
		HashNode *hnode = searchTable(funcTable, p->cnode.children[0]->id_value, 0);
		if(hnode == NULL){
			if(searchTable(varTable, p->cnode.children[0]->id_value, currentDepth) != NULL){
				semantic_error(11, p->lineno, p->cnode.children[0]->id_value);
				return NULL;
			}
			semantic_error(2, p->cnode.children[0]->lineno, p->cnode.children[0]->id_value);
			return NULL;		
		}
		Node *args = p->cnode.children[2];
		int args_num = 0;
		while(args_num < hnode->symbol->fun->para_num){	
			if(checkExp(args->cnode.children[0])->kind != hnode->symbol->fun->para_type[args_num]){
				semantic_error(9, p->lineno, p->cnode.children[0]->id_value);
				return NULL;
			}
			args_num ++;
			if(args->cnode.arity == 1)
			//Args->Exp
				break;
			//Args->Exp COMMA Args
			args = args->cnode.children[2];
		}
		if(args->cnode.arity != 1 || args_num != hnode->symbol->fun->para_num){
			semantic_error(9, p->lineno, p->cnode.children[0]->id_value);
			return NULL;
		}	
		return hnode->symbol->fun->return_type;   
	}
	else if(strcmp(p->cnode.children[1]->name, "LB") == 0){
	//Exp->Exp LB Exp RB
		return arrayExp(p);
	}
	else if(strcmp(p->cnode.children[1]->name, "ASSIGNOP") == 0){
	//Exp->Exp ASSIGNOP Exp	
		Node *leftExp = p->cnode.children[0];
		Type leftType = checkExp(leftExp);
		Type rightType = checkExp(p->cnode.children[2]);
		if((leftType == NULL) || (rightType == NULL)){
			return NULL;
		}
		else{
			if(!((strcmp(leftExp->cnode.children[0]->name, "ID") == 0 && leftExp->cnode.arity == 1) || strcmp(leftExp->cnode.children[1]->name, "DOT") == 0 || strcmp(leftExp->cnode.children[1]->name, "LB") == 0)){
				semantic_error(6, p->cnode.children[0]->lineno, " ");
				return NULL;
			}
			if(sameType(leftType, rightType) == 0){
				semantic_error(5, p->cnode.children[0]->lineno, " ");
				return NULL;
			}
			return leftType;
		}
	}	
	else if(strcmp(p->cnode.children[1]->name, "PLUS") == 0 || strcmp(p->cnode.children[1]->name,"MINUS") == 0 || strcmp(p->cnode.children[1]->name, "STAR") == 0 || strcmp(p->cnode.children[1]->name, "DIV") == 0){
	//Exp->Exp PLUS Exp
	//Exp->Exp MINUS Exp
	//Exp->Exp STAR Exp
	//Exp->Exp DIV Exp
		Type leftType = checkExp(p->cnode.children[0]);
		Type rightType = checkExp(p->cnode.children[2]);
		if((leftType == NULL) || (rightType == NULL)){
			return NULL;
		}
		else{
			if(leftType->kind != basic || rightType->kind != basic){
				semantic_error(7, p->cnode.children[0]->lineno, " ");
				return NULL;
			}
			
			else if(leftType->basic != rightType->basic){
				semantic_error(7, p->cnode.children[0]->lineno, " ");
				return NULL;
			}
			else
				return leftType;
		}				
	}
	//Exp->LP Exp RP
	//Exp->MINUS Exp
	//Exp->NOT Exp 不会出现 逻辑运算符
	else if(strcmp(p->cnode.children[1]->name, "Exp") == 0){
		return checkExp(p->cnode.children[1]);
	}
	else if(strcmp(p->cnode.children[1]->name, "DOT") == 0){
	//Exp->Exp DOT ID
		Type ref = checkExp(p->cnode.children[0]);
		if(ref == NULL)
			return NULL;
		if(ref->kind != structure){
			semantic_error(13, p->lineno, " ");
			return NULL;
		}
		FieldList currentField = ref->structure;
		while(currentField != NULL){
			if(strcmp(currentField->name, p->cnode.children[2]->id_value) == 0)
				break;
			currentField = currentField->tail;
		}
		if(currentField == NULL){
			semantic_error(14, p->lineno, p->cnode.children[2]->id_value);
			return NULL;
		}
		return currentField->type;
	}
	//Exp->Exp AND Exp
	//Exp->Exp OR Exp
	//Exp->Exp RELOP Exp
	//Exp->NOT Exp	
	else{
		return NULL;
	}
}

void semantic_error(int error_type, int lineno, char *msg){
	semantic_error_info=1;
	switch(error_type){
		case(1):
			printf("Error type 1 at line %d: 变量在使用时未经定义 \"%s\" \n", lineno, msg);break;
		case(2):
			printf("Error type 2 at line %d: 函数在调用时未经定义 \"%s\" \n", lineno, msg);break;	
		case(3):
			printf("Error type 3 at line %d: 变量重复定义 \"%s\" \n", lineno, msg);break;
		case(4):
			printf("Error type 4 at line %d: 函数重复定义 \"%s\" \n", lineno, msg);break;
		case(5):
			printf("Error type 5 at line %d: 赋值号两边表达式类型不匹配 \"%s\" \n", lineno, msg);break;
		case(6):
			printf("Error type 6 at line %d: 赋值号左边出现了一个只有右值的表达式\"%s\" \n", lineno, msg);break;
		case(7):
			printf("Error type 7 at line %d: 操作数类型不匹配 \"%s\" \n", lineno, msg);break;
		case(8):
			printf("Error type 8 at line %d: return 语句返回类型与函数本身的返回类型不匹配 \"%s\" \n", lineno, msg);break;	
		case(9):
			printf("Error type 9 at line %d: 函数调用时实参与形参的数目或者类型不匹配 \"%s\" \n", lineno, msg);break;	
		case(10):
			printf("Error type 10 at line %d: 对非数组型变量使用\"[...]\" \"%s\" \n",lineno,msg);break;
		case(11):
			printf("Error type 11 at line %d: 对普通变量使用\"()\" 操作符 \"%s\"\n", lineno, msg);break;		
		case(12):
			printf("Error type 12 at line %d: 数组访问操作符\"[...]\"中出现非整数\n", lineno);break;	
		case(13):
			printf("Error type 13 at line %d: 对非结构体型变量使用\".\"操作符 \"%s\" \n", lineno, msg);break;
		case(14):
			printf("Error type 14 at line %d: 访问结构体中未定义过的域 \"%s\" \n", lineno, msg);break;
		case(15):
			printf("Error type 15 at line %d: 结构体中域名的重复定义,或者定义时对域进行了初始化 \"%s\" \n", lineno, msg);break;
		case(16):
			printf("Error type 16 at line %d: 结构体名与前面定义过的某个结构体或者某个变量的名字重复 \"%s\" \n", lineno, msg);break;
		case(17):
			printf("Error type 17 at line %d: 直接使用未定义过的结构体来定义变量 \"%s\" \n", lineno, msg);break;
		case(18):
			printf("Error type 18 at line %d: 函数进行了声明,但没有被定义 \"%s\"\n",lineno,msg);break;
	}
	return;
}


